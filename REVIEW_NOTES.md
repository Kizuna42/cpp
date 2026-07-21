# CPP05-09 Defense Notes

2026-07-21の最終監査に基づく校舎review用ノートです。実装・公式subject・検証結果が矛盾しないことを優先しています。

## 共通チェック

- 全16 Exercise: `c++ -Wall -Wextra -Werror -std=c++98`
- 全Makefile: `all`, `clean`, `fclean`, `re`, `.PHONY`、header依存、不要な再リンクなし(検証スクリプトが16 Makefile全部の必須フラグ実在もgrep検査)
- `-pedantic-errors`を追加したstrict buildも16/16成功
- 26 headerすべてstandalone include compile成功
- 禁止API（`*printf`, `*alloc`, `free`）、`using namespace`, `friend`なし(検証スクリプトの静的sweep `sources free of forbidden constructs` で機械検査)
- `<typeinfo>` includeなし(静的sweep `no typeinfo include anywhere`)
- subject記載の実行例ブロック(convert 0/nan/42.0f、whatever、RPN 3例、btc、PmergeMe 4行出力)と完全一致(`subject example`系ケース)
- CPP05〜CPP07でSTL container/algorithmなし。CPP08/09ではsubjectに従って使用
- OCFはsubjectが要求するclassに実装。CPP06 ex02のBase/A/B/Cなど、subjectが明示的に除外する型は例外

### 再検証

```bash
./scripts/verify_cpp05_09.sh
```

Ubuntuでの完全再現(Docker、リポジトリはread-onlyで汚さない):

```bash
docker run --rm -v /path/to/cpp:/src:ro ubuntu:24.04 bash -c \
  'apt-get update && apt-get install -y g++ make valgrind && \
   cp -a /src /work && cd /work && ./scripts/verify_cpp05_09.sh'
```

VM等に直接導入済みの場合は一時copyで実行:

```bash
cp -a /path/to/cpp /tmp/cpp05-09-audit
cd /tmp/cpp05-09-audit
./scripts/verify_cpp05_09.sh
```

個別のbuildと実行:

```bash
(cd cpp05/ex00 && make re && ./bureaucrat)
(cd cpp05/ex01 && make re && ./form)
(cd cpp05/ex02 && make re && ./aform)
(cd cpp05/ex03 && make re && ./intern)
(cd cpp06/ex00 && make re && ./convert 42)
(cd cpp06/ex01 && make re && ./serializer)
(cd cpp06/ex02 && make re && ./identify)
(cd cpp07/ex00 && make re && ./whatever)
(cd cpp07/ex01 && make re && ./iter)
(cd cpp07/ex02 && make re && ./array_test)
(cd cpp08/ex00 && make re && ./easyfind)
(cd cpp08/ex01 && make re && ./span)
(cd cpp08/ex02 && make re && ./mutantstack)
(cd cpp09/ex00 && make re && ./btc input.txt)
(cd cpp09/ex01 && make re && ./RPN '8 9 * 9 - 9 - 9 - 4 - 1 +')
(cd cpp09/ex02 && make re && ./PmergeMe 3 5 9 7 4 1)
```

Valgrindのoptionは一括scriptと同じく次を使う。

```bash
valgrind --error-exitcode=99 --leak-check=full \
  --show-leak-kinds=all --errors-for-leak-kinds=all ./binary [args...]
```

## CPP05 — Repetition and Exceptions

| Ex | Binary | Defense要点 |
|---|---|---|
| ex00 | bureaucrat | grade 1が最高、150が最低。constructorとincrement/decrementの両方で境界を守る |
| ex01 | form | name/required gradesはconst、全属性private、署名状態だけ変更可能 |
| ex02 | aform | AFormが前提条件を一元検査し、派生classはactionだけ実装 |
| ex03 | intern | form名とstatic creator function pointerの表をloop検索 |

- `beSigned()`: grade不足なら`GradeTooLowException`。十分なら`_isSigned = true`。既署名でも成功状態を維持する
- `execute()`: unsignedなら`FormNotSignedException`、grade不足なら`GradeTooLowException`、その後`executeAction()`
- `executeAction()`はAFormでprotected、concrete classでprivate。外部から前提条件を迂回できない
- 成功表示はactionがreturnした後の`Bureaucrat::executeForm()`だけ。file生成失敗時に成功と失敗を同時表示しない
- grade: Shrubbery 145/137、Robotomy 72/45、Presidential 25/5
- `executeForm(AForm const& form) const`の末尾`const`もsubjectどおり

想定Q: なぜtemplate method方式か。  
AFormが共通の署名/grade検査を一度だけ実装し、派生classの責務をactionに限定できるため。

想定Q: なぜconstructor/destructorで出力しないか。  
subjectが要求する結果出力とaction出力だけを安定させ、OCFの内部イベントを公開動作へ混ぜないため。

想定Q: ex02のmainはなぜ全体をtry/catchで囲まないか。  
mainが直接構築するBureaucrat/Formはすべて有効grade値で、constructorがthrowする経路が構造的に存在しないため。例外経路は`signForm`/`executeForm`内部のcatchが仕様どおりのメッセージへ変換し、境界例外のcatch実演はex00/ex01のmainで行っている。

## CPP06 — C++ Casts

| Ex | Binary | Cast |
|---|---|---|
| ex00 | convert | `static_cast` |
| ex01 | serializer | `reinterpret_cast` |
| ex02 | identify | `dynamic_cast` |

### ScalarConverter

- 判定順はpseudo-literal → char → int → float → double
- floatは末尾`f`を除いてparseし、`FLT_MAX`超をfloatへcastしない
- NaNは`v != v`、Infは`numeric_limits<>::infinity()`でC++98判定
- `strtod`のERANGEでも非0のsubnormalは有効。Infまたは0への完全underflowはparse失敗
- char/int変換は先に0方向へ小数を切り捨てた値で範囲判定する
- int範囲外のinteger literalも、各変換を個別判定する。例: `2147483648`はintだけ`impossible`でfloat/doubleは値を表示
- finite doubleがfloat範囲外ならfloatだけ`impossible`
- classの公開static methodは`convert()`だけ。判定・表示helperは`.cpp`のfile-local関数

### Serializer / identify

- `Data*` → `uintptr_t` → `Data*`のaddress identityを確認
- C++98のため`<stdint.h>`を使用
- pointer版`dynamic_cast<T*>`は失敗時NULL
- reference版`dynamic_cast<T&>`は失敗時例外。関数内でpointerを使わない
- `<typeinfo>`をincludeせず、reference cast失敗は各`catch (...)`で次の型判定へ進む
- `identify()`自身はsubjectどおり単独の`A`, `B`, `C`を出力

## CPP07 — C++ Templates

### ex00 whatever

- `swap`, `min`, `max`は引数を参照で受ける
- 等値時は第2引数を返すsubject要件を満たす

### ex01 iter

```cpp
template<typename T>
void iter(T* array, const size_t length, void (*function)(T&));

template<typename T>
void iter(const T* array, const size_t length, void (*function)(const T&));
```

第3引数を任意の`F`ではなくfunction pointerにする理由:

- evaluator形式の`iter(tab, 5, print)`は、`print`が未instantiated function template名
- 第1引数から`T`を先に決定し、目標function-pointer型によって`print<T>`を選択できる
- `F`推論だけに任せると、未instantiated overload setから型を決められない
- subjectはfunctionを要求しており、functor対応は必須でない

NULL arrayまたはlength 0は何も実行しない。zero-length array extensionは使わず、1要素arrayをlength 0で試験する。

### ex02 Array

- template実装がheader内にあるのはinstantiation時にdefinitionが必要なため
- `new T[n]()`でvalue-initialize
- copy constructorは要素assignmentがthrowした場合にtemporary allocationを`delete[]`
- assignmentはcopyを先に完成させてからswapするためstrong exception guarantee
- deep copy、self-assignment、`size() const`、範囲外例外を確認
- binary名`array_test`は、libc++内部の`<array>`と同名binary `array`のinclude衝突を避ける

PDF掲載mainには`<cstdlib>`/`<ctime>`が不足するため、検証harnessでその2行だけ補完して実行している。

## CPP08 — Templated Containers

### ex00 easyfind

- `std::find`を使用
- mutable/const containerの両overload
- 未発見は`std::runtime_error`

### ex01 Span

- `shortestSpan()`: copyをsortし、隣接差の最小を取る。O(n log n)
- `longestSpan()`: min/maxの差。O(n)
- 戻り値と差分を`unsigned int`にし、`INT_MIN`〜`INT_MAX`の差`UINT_MAX`を表現
- operandをunsigned化してから減算するためsigned overflowなし
- `addRange`はrangeをtemporary vectorへ一度だけ読む。single-pass `istream_iterator`でも要素を失わない
- 10,000件、同値、負値、満杯、要素不足を試験

### ex02 MutantStack

- `std::stack<T, Container>`のprotected member `c`へ派生classからアクセス
- mutable/constのforward iteratorを公開
- 継承済み`size()`/`empty()`を再定義せず、stackの全機能をそのまま利用
- subject main相当の操作列、copy/assignment、空stack、vector backing containerを試験

## CPP09 — STL

### Containerの非再利用

| Ex | Container | 理由 |
|---|---|---|
| ex00 btc | `std::map<std::string, double>` | ordered date lookupと`lower_bound` |
| ex01 RPN | `std::stack<int, std::list<int> >` | stack処理。backing containerをlistに固定 |
| ex02 PmergeMe | `std::vector<int>`, `std::deque<int>` | subjectが異なる2 containersを要求 |

map/list/vector/dequeは後続Exerciseで再利用していない。stackはcontainer adaptorで、backing containerも明示している。

### ex00 BitcoinExchange

- dateは固定幅`YYYY-MM-DD`なのでlexicographic orderとchronological orderが一致
- exact dateがなければ`lower_bound`から1つ戻し、必ずpast側のclosest date
- future dateにもDB末尾のrateを使用。first DB dateより前ならrateなし
- Gregorian leap year、月の日数、year 0000拒否
- valueは0〜1000、NaN/Inf拒否
- resultは固定小数桁で丸めず、有効桁precisionを使うため極小の正数も保持
- `data.csv`は`cpp09/ex00`をcurrent directoryにして読む

想定Q: 日付分解になぜ`std::atoi`を使うか。  
subjectの禁止関数は`*printf`/`*alloc`/`free`のみでatoiは対象外。呼び出し前に`validateDateFormat`が固定長10文字・`-`位置・全桁数字を保証するため、atoiに渡るのは最大4桁の数字列に有界でオーバーフローも未定義動作もない。エラー検出が必要なvalue側は`stringToDouble`(istringstream)で失敗・NaN/Infを検査しており、要件の違いで使い分けている。

想定Q: 別のdirectoryから`./btc`を実行すると。  
`loadDatabase("data.csv")`が`FileException`を投げ、mainが`Error: could not open file.`をstderrへ出して終了コード1で終わる。入力ファイル欠如時も同じメッセージ(検証スクリプトの`btc requires input file argument`/`btc missing input file`ケースで実挙動を確認済み)。

### ex01 RPN

- input tokenは1文字の`0`〜`9`だけ
- operatorは`+ - * /`
- 先にpopした値が右operand、次が左operand
- stackは`int`なので`5 2 / 2 *`は`4`
- decimal、token不足/余り、ゼロ除算はstderrに`Error`、nonzero exit
- 加減乗はdouble空間でrangeを先に確認し、int overflowする演算を実行しない
- `INT_MIN / -1`も明示的に拒否
- 連続乗算で`INT_MAX`を超える回帰caseもnonzero exitを確認

### ex02 PmergeMe

Ford–Johnsonの流れ:

1. 隣接要素をpair化し、1比較でwinner/loserへ分ける
2. winner列を同じalgorithmで再帰sort
3. 最小winnerのpartner `b1`を比較なしでmain chain先頭へ置く
4. 残りのloserとstragglerをJacobsthal順でbinary insert
5. vector版とdeque版を独立実装

実装は値のcopyではなくindex順列をsortする。`partnerOf[winnerIndex]`でpairを保持するため重複値でもpartnerを取り違えない。
`displayAfter()`はvector/dequeのsizeと全要素一致を先に検査するため、正常終了したproperty testは両実装を検証している。

想定Q: なぜbinary-search上限をpartner位置にできるか。  
`b_j <= a_j`がpair比較で既知なので、`a_j`より右を探す必要がない。挿入後は`winnerPos`を更新して現在位置を追跡する。

想定Q: なぜJacobsthal順か。  
挿入群を降順で処理して探索範囲を`2^k - 1`付近に揃え、binary insertionのworst comparisonsを抑えるため。

想定Q: stragglerはどう扱うか。  
仮想pending index `k+1`として同じJacobsthal順へ入れ、探索上限だけchain全体にする。

想定Q: 計測範囲は。  
token→int、container格納、Ford–Johnson、結果container構築まで。入力妥当性検査は表示前に必要なので`parseInput`で先に行う。

入力はpositive integerのみで`0`と負数を拒否。重複はsubjectが裁量としているため受理する。

### 比較回数の実測

監査用copyでpair比較とbinary-search比較だけをcountし、n=1〜10の全4,037,913 permutationを列挙した。

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| measured worst | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |
| Ford–Johnson bound | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |

全て`sum ceil(log2(3k/4))`と一致。計測codeは提出実装に残していない。

## 最終検証

2026-07-21実測(検証スクリプトにsubject実行例照合・静的sweep・コンパイルコマンドフラグ検証の計21ケースを追加後):

| Check | Result |
|---|---|
| macOS verification script | 159 PASS / 0 FAIL / Valgrindのみ1 SKIP |
| macOS ASan + UBSan | 16/16 binary PASS |
| Docker Ubuntu 24.04 aarch64 (g++ 13.3.0) verification script | 176 PASS / 0 FAIL / 0 SKIP |
| Linux Valgrind 3.22.0 | 17/17 case PASS |
| Docker Ubuntu 24.04 amd64 (qemu、Valgrindなし) | 159 PASS / 0 FAIL / 1 SKIP |
| Linux regular build / no-relink | 16/16 / 16/16 |
| Linux `-pedantic-errors` | 16/16 |

参考: 2026-07-20のUTM Ubuntu 24.04実測はケース追加前で155 PASS / 0 FAIL / 0 SKIP。
| Standalone headers | 26/26 |
| Linux Valgrind 3.22.0 | Array例外経路 + 16/16 binary PASS |
| PmergeMe | 3000降順 + 500 property cases + comparisons総当たり PASS |

現時点でCPP05〜CPP09の提出blockerは確認されていません。
