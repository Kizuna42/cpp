# CPP05-09 Defense Notes

2026-09-02最終監査版。current 42 EvalHub HTML criteriaを基準に、CPP05〜CPP09をreviewで説明・実演するための防御ノートである。監査対象source baseline `e04faff6cdb55e15fa7be1f287fc512235a9d742`を全source確認し、指定repo内はcode-readyと判定した。実際の提出可否は、Intraが参照する公式repo/branchとこのsourceの同一性確認を条件とする。current subject PDF CDNは404のため、基準の範囲は[包括評価レポート](COMPREHENSIVE_EVALUATION.md)のprovenanceを参照する。

## 共通review contract

- 各Exerciseは`c++ -Wall -Wextra -Werror -std=c++98`でbuildする。Makefileには`all`、`clean`、`fclean`、`re`を置く。
- non-template実装をheaderに置かず、`printf`系、`alloc`系、`free`、`using namespace`、`friend`、外部libraryを使わない。
- evaluatorがmainを差し替える前提で、公開API・const性・例外型・出力をsubjectどおりに説明する。自作mainが通るだけでは合格根拠にしない。
- 質問に答えられない、ライブ変更後にbuildできない、例外・不正入力で未定義動作またはリークがある場合は、そのExerciseをstopする。

## ライブコーディング・口頭質問への対応

2026-09-02時点のEvalHub CPP05〜09には、独立した「Live coding」採点欄はない。ただし、evaluatorはmain差し替え、追加case、設計説明を求められる。提出sourceの編集は本来不要というEvalHub guidelineがあるため、変更を求められたら意図を確認し、合意後に最小のtestだけを追加する。

回答は次の順で行う。

1. 先に結論を一文で答える。例: 「reference `dynamic_cast`は失敗時に例外、pointer版はNULLです」。
2. その根拠となるclass invariant、関数、所有権をsource上で指す。
3. 正常系1本か致命的失敗1本だけを小さなmainで実演する。既存の提出mainを大改造しない。
4. `c++ -Wall -Wextra -Werror -std=c++98`でcompileし、終了codeと出力を一緒に確認する。
5. 実演後に「何を証明したか」を一文でまとめる。通ったことだけでなく、なぜその結果になるか説明する。

提出fileを汚さず試す例:

```bash
c++ -Wall -Wextra -Werror -std=c++98 \
  -Icpp05/ex00 /tmp/evaluator_main.cpp cpp05/ex00/Bureaucrat.cpp \
  -o /tmp/cpp-evaluator-check
/tmp/cpp-evaluator-check
```

分からない質問で推測しない。「確認したい前提はXです」と切り分け、該当sourceを見てから答える。表の「想定質問」「ライブコーディング案」が各exerciseの最短回答である。

## CPP05 — Repetition and Exceptions

| Exercise | Review contract / design defense | Test coverage | 想定質問 | ライブコーディング案 | Stop rule |
|---|---|---|---|---|---|
| ex00 `bureaucrat` | `Bureaucrat`のgradeは常に1〜150。constructor・increment・decrementが同じ不変条件を守り、挿入演算子は状態を読むだけ。 | grade 1/150、両方向の境界例外、名前・grade出力。 | 「境界検査をsetterだけに置かない理由は？」→無効状態を生成できないため。 | grade 1でincrement、150でdecrementする小mainを追加。 | 範囲外stateが残る、例外型/出力が不正。 |
| ex01 `form` | `Form`のnameと署名必要grade/実行必要gradeは`const`かつprivate。`beSigned`は署名者gradeを検査し、状態だけを更新する。 | valid/invalid constructor、署名成功・不足・再署名、`<<`。 | 「なぜrequired gradeを変更できないか？」→formの契約値だから。 | grade不足の`beSigned`をcatchして表示。 | 属性の可視性/const性不適合、署名条件の迂回。 |
| ex02 `aform` | `AForm::execute`がunsigned・executor gradeを一元検査するTemplate Method。Shrubbery/Robotomy/Presidentialはactionのみを実装する。 | 各formのsign/execute不足・成功、Shrubbery file、Robotomy失敗分岐、Pardon出力。 | 「なぜactionを直接publicにしないか？」→共通前提を迂回させないため。 | unsigned formへ`executeForm`、署名後に低gradeで実行。 | actionが検査を迂回、成功と失敗を同時表示、必要な具象form不足。 |
| ex03 `intern` | `Intern::makeForm`はform名とstatic creator function pointerのtableをloop検索してdispatchする。if/else-if chainは使わない。未知名は明示エラーを一度表示して`UnknownFormException`を投げる。 | 3既知名が対応型を生成、未知名、戻りpointerのdelete、生成通知。 | 「tableがif chainより良い理由は？」→name/creator対応をdata化し追加時に分岐を増やさず、同じ呼出し型でdispatchできるため。 | tableに一行追加できる形を示し、未知名を入力して単発エラーと例外経路を確認。 | if/else-if dispatch、未知名を既知formへすり替え、エラーの二重表示、所有権不明。 |

### CPP05 口頭防御の要点

- `beSigned()`はgrade不足時に`GradeTooLowException`、十分ならsigned状態へ遷移する。`execute()`はsigned確認、executor grade確認、actionの順である。
- gradeはShrubberyがsign 145 / execute 137、Robotomyが72 / 45、Presidentialが25 / 5である。小さいほど高いgradeである。
- `Bureaucrat::signForm`と`executeForm`は操作の窓口であり、例外を捕捉して結果を表示する。action完了前に成功を表示しない。
- Internの返却raw pointerはcallerが所有する。失敗時の扱いと、成功後に`delete`する場所をライブで指せるようにする。

## CPP06 — C++ Casts

| Exercise | Review contract / design defense | Test coverage | 想定質問 | ライブコーディング案 | Stop rule |
|---|---|---|---|---|---|
| ex00 `convert` | `ScalarConverter`はprivate constructor、公開static `convert`。scalar literalを判定し、表示ごとに表現可能性を判断して`static_cast`する。 | char/int/float/double、pseudo literal、NaN/Inf、非表示char、範囲外、末尾`f`。 | 「なぜC castでないか？」→変換意図を明示し、scalar conversionに`static_cast`を選ぶため。 | `42.0f`、`nan`、範囲外値を追加して4表示を説明。 | private/static要件違反、literal誤分類、範囲外castを実行。 |
| ex01 `serializer` | `Serializer`はprivate constructorと2 static functionのみ。pointerと`uintptr_t`を`reinterpret_cast`で往復し、object値ではなくaddress identityを確認する。 | `Data`を生成、serialize/deserialize後のpointer equality、値アクセス。 | 「static_castでない理由は？」→無関係なpointer/integer表現の再解釈だから。 | round-tripして`ptr == restored`を出力。 | cast種別違い、pointer identity未確認、所有権を誤ってdelete。 |
| ex02 `identify` | `Base`からA/B/Cを生成し、pointer版はNULL判定、reference版は`dynamic_cast<T&>`と`try/catch`で識別する。`typeinfo`は使わない。 | generate、各A/B/Cのpointer/reference識別、出力が単独の型名。 | 「pointerとreferenceの失敗の違いは？」→NULLと`std::bad_cast`。 | reference版にA/B/C順のcast/catchを実装し、pointerを使わないことを示す。 | `typeid`/`<typeinfo>`使用、reference版でpointer cast、型名以外の出力。 |

### CPP06 口頭防御の要点

- `static_cast`は数値型間、`reinterpret_cast`はaddress表現、`dynamic_cast`はpolymorphic baseからの実行時型検査に選ぶ。各castの失敗時の意味まで説明する。
- ScalarConverterは一つのparse結果を全型へ盲目的にcastしない。`int`、`char`、`float`、`double`ごとに範囲・表示可能性を決める。
- reference `dynamic_cast`は失敗時に例外を投げるため、`catch (...)`で次の型を試せる。`<typeinfo>`は不要である。

## CPP07 — C++ Templates

| Exercise | Review contract / design defense | Test coverage | 想定質問 | ライブコーディング案 | Stop rule |
|---|---|---|---|---|---|
| ex00 `whatever` | `swap`、`min`、`max`は任意型に対して必要最小限の演算だけを要求するtemplate。等値時の`min/max`は第2引数を返す。 | subject例、int/string、比較可能な自作型、等値時の参照identity。 | 「なぜ`const T&`を返すか？」→copyを避け、元の第2引数を参照として返すため。 | 同値の2変数のaddressを比較し第2引数を返すことを示す。 | 等値時に第1引数、template外の型依存実装。 |
| ex01 `iter` | array pointer、length、関数を受け、各要素へ適用する。mutable/const arrayを適切なcallback型で受ける。 | int/string、自作型、const array、length 0、NULL guard。 | 「なぜfunction-pointer signatureか？」→第1引数から`T`を決めた後、未instantiated function template名を目標pointer型へ解決できるから。 | `print<T>`とconst callbackを渡すevaluator型呼出しを追加。 | template deduction不能、constを破るcallback、要素数外アクセス。 |
| ex02 `array_test` | `Array<T>`は`new[]`で所有し、空/size constructor、`size`、`operator[]`、deep copyを提供する。template実装のheader配置は許容される。 | empty、sizedのdefault/value initialization、read/write、const read、bounds、simple/complex type、copy/assignment/self-assignment。 | 「代入の例外安全は？」→新しい配列のcopyが成功してから旧stateを置換し、失敗時は左辺を維持する。 | throwする要素型でcopy/assignmentを試し、catch後のsize/valueを確認。 | shallow copy、bounds例外なし、途中copyでリーク/左辺破壊、mainにcomplex/defaultの証拠なし。 |

### CPP07 口頭防御の要点

- `iter`の`F`を任意callableにする拡張は必須ではない。評価用の`iter(tab, len, print)`を正しく推論できる関数pointer overloadを優先する。
- `Array<T>(n)`は`new T[n]()`でvalue-initializeする。組込み型も未初期化にしない。
- allocation後のelement assignmentがthrowし得るなら、copy constructorは確保済み配列を解放して再throwする。assignmentはcopy-first/swapでstrong guaranteeを保つ。

## CPP08 — Templated Containers

| Exercise | Review contract / design defense | Test coverage | 想定質問 | ライブコーディング案 | Stop rule |
|---|---|---|---|---|---|
| ex00 `easyfind` | `std::find`でintを持つcontainerからiteratorを返す。未発見は例外。 | vector/list、先頭/末尾、未発見、const container。 | 「手書きloopでなくalgorithmを使う理由は？」→criteriaがSTL algorithmを要求し、iterator抽象を保つため。 | listとvectorに同じtemplateを適用。 | `std::find`不使用、未発見を未定義iteratorとして返す。 |
| ex01 `span` | 容量を超えない`addNumber`とrange add。shortestはsortしたcopyの隣接差、longestはmin/max。 | 2未満、満杯、同値、負値、10,000件、`INT_MIN/INT_MAX`、input iterator。 | 「range addがinput iteratorで安全な理由は？」→temporaryへ一度だけ読む。distance後の再走査はsingle-pass sourceを消費する。 | `istream_iterator<int>`を渡し、容量超過ならstate不変を確認。 | rangeを二重走査、capacity超過で部分挿入、signed overflow、2未満で計算。 |
| ex02 `mutantstack` | `std::stack`のprotected `c`からiterator/const_iteratorを公開し、stack APIを保持する。 | subject sequence、begin/end、const iteration、copy/assignment、empty、別backing container。 | 「なぜ`c`へアクセスできるか？」→`std::stack`のprotected memberで派生classから合法的に参照できるため。 | `MutantStack<int, std::vector<int> >`のiteratorを通す。 | `c`を再実装、iteratorがstack順と不整合、subject main以下のtest。 |

## CPP09 — STL

### Containerの非再利用

| Exercise | Container | Defense |
|---|---|---|
| ex00 `btc` | `std::map<std::string, double>` | ordered keyと`lower_bound`による過去日の探索。 |
| ex01 `RPN` | `std::stack<int, std::list<int> >` | LIFO評価を明示し、backing containerを過去Exerciseと分ける。 |
| ex02 `PmergeMe` | `std::vector<int>`と`std::deque<int>` | subject要求の別々の2 containersで、両方をFord–Johnsonとして実装。 |

| Exercise | Review contract / design defense | Test coverage | 想定質問 | ライブコーディング案 | Stop rule |
|---|---|---|---|---|---|
| ex00 `btc` | CSVを`map`へ読み、入力dateのexact matchまたは過去側closest rateを使う。`lower_bound(date)`がbeginならrateなし、そうでなければ`--it`する。bad lineは表示して後続行を継続する。 | empty input、bad delimiter/date/value、leap year、DB先頭前/中間/末尾後、0/1000境界、`input.csv`。 | 「なぜ`lower_bound`後にdecrementか？」→戻りは最初の`>= date`なので、exact以外で直前が過去側最大keyだから。 | DB中間日と最終日より未来を実行してrateを確認。 | future側rateを選ぶ、beginをdecrement、bad lineで全処理停止、invalid date/値を通す。 |
| ex01 `RPN` | tokenは1桁整数または演算子。pop順は最初がright、次がleft。演算前にoperand数、zero division、overflowを検査する。 | subject例、`42`、`42`、`15`、減算/除算順、余りtoken、decimal、zero division、加減乗除overflow。 | 「`-`のoperand順は？」→`right=pop(); left=pop(); left-right`。 | `5 2 -`と`5 2 /`、`INT_MIN / -1`拒否を実演。 | 逆順計算、stack final sizeが1でない、overflow後に演算、エラーで成功終了。 |
| ex02 `PmergeMe` | vector/dequeそれぞれでFord–Johnsonを実装する。pairでwinner/partnerを作り、winnerを再帰sort、`b1`を先頭へ、残りをJacobsthal順にpartnerまでbinary insertしstragglerを処理する。 | 5〜10手動、重複、降順、3000 random、両containerのsorted/multiset一致、表示前後、timing。 | 「partner boundはなぜ正しい？」→pair比較で`b_j <= a_j`が既知であり、`a_j`右側は探索不要。 | 5〜10要素でpair/winner/pending/chainsを紙またはdebug出力で追い、Jacobsthal順を説明。 | 一方だけ別algorithm、partner右側を探索、Jacobsthalなし、3000 random未検証、時間を比較回数と混同。 |

### CPP09 口頭防御の要点

- `btc`の`YYYY-MM-DD`は固定幅なら辞書順と暦順が一致する。日付妥当性はformatだけでなく閏年・月日数まで検査する。
- current EvalHubの`input.csv`（header+21 data、22行）を実行し、exit 0・21 output linesを確認した。bad valueを報告した後も後続行を継続し、exact dateとclosest lower dateの両方を確認した。
- RPNは`double`へ逃がさず整数stackでsubjectの整数演算を行う。先にpopするoperandがrightであることを、減算・除算で必ず実演する。
- RPN advanced指定3式は順に`42`、`42`、`15`となることを最終実測した。
- Ford–Johnsonのpartner boundは比較回数を抑える根拠、Jacobsthal順はbinary insertionの探索長を整える順序である。wall-clock timingは環境・container差を観測する指標で、比較回数の証明ではない。
- timingはparseを含めるか、含めないなら両containerで同じ境界に揃える。microseconds表示の意味と、単発値を性能保証にしないことを説明する。
- PmergeMeはn=5〜10の固定ケース、3000 descending、500 deterministic property、3000 random duplicatesについて、vector/deque双方のsorted+multisetを最終実測した。

### 比較回数の履歴証拠（2026-07-21、今回のfresh測定ではない）

監査用一時copyでpair比較とbinary-search比較をcountし、n=1〜10の全4,037,913 permutationを列挙した履歴測定である。提出実装にinstrumentは残していない。

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| measured worst | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |
| Ford–Johnson bound | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |

## 最終verification結果

| Check | Result |
|---|---|
| macOS 26.6.2 / Apple clang 21（2026-09-02 fresh） | `./scripts/verify_cpp05_09.sh`: 176 PASS / 0 FAIL / 1 SKIP（Valgrind unavailableのみ）。 |
| macOS ASan + UBSan（2026-09-02 fresh） | 全16 binary: 16/16 PASS。Apple ASanは`detect_leaks=0`で実行。 |
| btc current EvalHub `input.csv`（2026-09-02 fresh） | header+21 dataをexit 0で処理し、21 output lines。exact 2011-09-14=6.19、closest-lower 2010-11-03→2010-11-02=0.21、2020-06-26→2020-06-25=9276.58を照合。 |
| RPN advanced | 指定3式の結果: `42`、`42`、`15`。 |
| PmergeMe | n=5〜10固定、3000 descending、500 deterministic property、3000 random duplicatesでvector/deque双方のsorted+multiset PASS。 |
| Ubuntu 24.04 Docker（2026-08-24履歴） | verifier: 193 PASS / 0 FAIL / 0 SKIP。ValgrindはArray例外経路+全16 binaryの17ケース全PASS。 |
| 静的検査 | 16 Exerciseのsource review、禁止構文、26 header単体、Makefile/compile flags PASS。 |

結果: 指定repo内はcurrent EvalHub HTML criteria、取得可能な履歴PDF、実装、上記fresh evidenceの確認範囲でblockerなし・code-ready。公式提出repo/branchとの同一性確認がPASSすれば提出可能・defense-ready。

## 提出当日の最終チェック

1. Intraで今提出するproject（CPP05、06、07、08、09のどれか）と公式Git URLを確認する。このmonorepoのrootではなく、公式提出repoのroot直下に対象moduleの`ex00`〜`exNN`が並ぶことを確認する。
2. 空directoryへ公式提出repoをcloneする。既存working treeだけで判定しない。
3. clone先で`git status -sb`、`git log -1 --oneline`、`git diff --check`を実行する。uncommitted file、誤branch、生成binary、`.o`、`*_shrubbery`がないことを確認する。
4. 下記の比較をmonorepo rootで実行する。`module`と`submission_dir`を実際の対象へ置き換え、監査baselineから展開したExercise一覧と各directoryの`diff`が無出力・exit 0になることを確認する。これにより、後日変更され得るworking treeではなく、監査済みsourceと実際の提出物が同一だと証明する。
5. 各exerciseで`make re`を実行し、必須flagsと`c++`を目視する。実行後は`make fclean`する。
6. 比較に使った監査baselineの一時directoryで`./scripts/verify_cpp05_09.sh`を実行し、`fail=0`を確認する。ValgrindなしのMacでは1 SKIPは想定どおりである。比較後に公式cloneを変更した場合は手順4からやり直す。
7. evaluatorが使う代表caseを口頭説明つきで再実行する。CPP09は`input.csv`、RPNのadvanced 3式、PmergeMeの5〜10件と3000件を優先する。
8. 最後のcommitを公式remoteへpushし、local HEADとremote branch SHAが同じことを確認する。Intra上の提出project/branchが正しいことも再確認する。

```bash
set -euo pipefail
baseline=e04faff6cdb55e15fa7be1f287fc512235a9d742
module=cpp05
submission_dir=/absolute/path/to/official-clone
baseline_dir=$(mktemp -d /tmp/cpp-audited-baseline.XXXXXX)
git archive "$baseline" | tar -x -C "$baseline_dir"
audited_module="$baseline_dir/$module"

diff -u \
  <(find "$audited_module" -maxdepth 1 -type d -name 'ex*' -exec basename {} \; | sort) \
  <(find "$submission_dir" -maxdepth 1 -type d -name 'ex*' -exec basename {} \; | sort)
for exercise_dir in "$audited_module"/ex*; do
  exercise_name=${exercise_dir##*/}
  diff -ru --exclude='.DS_Store' "$exercise_dir" "$submission_dir/$exercise_name" || exit 1
done

git -C "$submission_dir" diff --check
worktree_status=$(git -C "$submission_dir" status --porcelain)
if [ -n "$worktree_status" ]; then
  printf '%s\n' 'ERROR: official clone is dirty'
  exit 1
fi
git -C "$submission_dir" log -1 --oneline
branch=$(git -C "$submission_dir" branch --show-current)
if [ -z "$branch" ]; then
  printf '%s\n' 'ERROR: detached HEAD'
  exit 1
fi
local_sha=$(git -C "$submission_dir" rev-parse HEAD)
remote_sha=$(git -C "$submission_dir" ls-remote --exit-code origin "refs/heads/$branch" | awk 'NR == 1 {print $1}')
if [ -z "$local_sha" ] || [ -z "$remote_sha" ]; then
  printf '%s\n' 'ERROR: local or remote SHA is empty'
  exit 1
fi
if [ "$local_sha" != "$remote_sha" ]; then
  printf 'ERROR: local=%s remote=%s\n' "$local_sha" "$remote_sha"
  exit 1
fi
printf 'OK: %s %s\n' "$branch" "$local_sha"

(
  cd "$baseline_dir"
  ./scripts/verify_cpp05_09.sh
)
```

評価中は質問に即答するため、対象moduleだけを開いておく。自動testの数値を暗記するより、各classの不変条件、例外条件、container選定、所有権をsource上で指せることを優先する。
