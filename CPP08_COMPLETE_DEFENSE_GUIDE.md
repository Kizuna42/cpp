# CPP08 — 実装解説と学習記録

> **対象**: `cpp08/ex00`〜`ex02`（STL のアルゴリズム / Span / 反復可能な stack）
> **この文書の役割**: 実装を読む人のための解説書であり、同時に自分がどこで何を理解したかの学習記録である。
> **提出手続き・リポジトリ同一性の確認**は [REVIEW_NOTES.md](REVIEW_NOTES.md) に分離してある。ここでは扱わない。

## 読み方

| 読む人 | 推奨ルート |
|---|---|
| レビュワー | [§1 要点カード](#1-要点カード) → [§2 この課題の性質](#2-この課題の性質) → 該当 Exercise 節 → [§8 指摘されうる点](#8-指摘されうる点) |
| 実装者（復習） | [§4 STL の基礎](#4-stl-の基礎) → ex00〜ex02 を順に読み、各節末の「学習メモ」で詰まった箇所を確認する |
| 防衛直前 | [§1](#1-要点カード) → [§6 の最短の差](#6-ex01--span) → [§9 想定質問](#9-想定質問) |

コード参照はすべてリポジトリ内の実ファイルへのリンクである。文章と実装が食い違っていたら**実装が正**。

---

## 1. 要点カード

```text
各 Exercise の中身:
        ex00  easyfind.hpp       std::find で最初の出現位置を探す関数テンプレート
        ex01  Span.hpp / .cpp    最大 N 個の int を持ち、最短・最長の差を返すクラス
        ex02  MutantStack.hpp    std::stack を継承し、中のコンテナのイテレータを公開する

ex00 の見つからないとき:
        std::find が end() を返す → std::runtime_error を投げる

ex01 の差の求め方:
        最短  コピーを std::sort → 隣同士の差の最小     O(n log n)
        最長  std::max_element − std::min_element       O(n)
        差は unsigned int で引く（INT_MAX − INT_MIN = 4294967295 を表すため）

ex01 のまとめて追加:
        addRange(begin, end)   一時 vector に写す → 空きを確認 → 一度に insert
                               1 回しか読めないイテレータ（istream_iterator）でも動く

ex02 の仕組み:
        std::stack は中のコンテナを protected メンバ c に持つ
        typedef Container::iterator iterator;   begin() { return this->c.begin(); }
        反復の順序は 底 → top（list に push_back した順と同じ）
```

ビルド条件は全 Exercise 共通で `c++ -Wall -Wextra -Werror -std=c++98`（[ex00/Makefile#L3-L4](cpp08/ex00/Makefile#L3)）。

---

## 2. この課題の性質

Module 08 から STL のコンテナとアルゴリズムが解禁される。Module 07 までの「使ってはいけない」から、「使いこなせているか」を問う側に変わる。EvalHub の評価表もこの方向で書かれており、ex00 は STL アルゴリズムを使っていること（手書きのイテレータ探索は不可）、ex01 はメンバ関数ができるだけ STL アルゴリズムで結果を出していること、ex02 は std::stack を継承して反復できることを確認する（[cpp08/evals.txt](cpp08/evals.txt)）。

もう 1 つ、3 つの Exercise すべてに共通する採点条件がある。**十分なテストを含む main がないか、インターフェース以外のクラスが Orthodox Canonical Form でなければ、その Exercise は採点しない。** 実装が正しくても、テストの量とクラスの形で止まりうる。

---

## 3. 共通ルール — 0 点と -42

subject の共通ルール（Chapter II）にある罰則。実装の良し悪し以前に、ここで評価が止まる。

| 条件 | 罰則 | 本実装 |
|---|---|---|
| `using namespace <ns_name>` または `friend` を使用 | -42 | 不使用 |
| ヘッダ内に関数の実装を記述（テンプレートを除く） | 0 | ヘッダにある実装は `easyfind`・`Span::addRange`・`MutantStack` のテンプレートだけ |
| インクルードガードがない | 0 | 3 ヘッダとも設置 |
| `*printf()` / `*alloc()` / `free()` を使用 | 0 | 不使用 |
| C++11 以降・Boost・その他外部ライブラリを使用 | 0 | 不使用（`-pedantic-errors` でも通る） |

STL のコンテナとアルゴリズムは Module 08・09 で許可されているので使ってよい。Orthodox Canonical Form（Module 02〜09）とメモリリーク禁止は引き続き守る。

---

## 4. STL の基礎

**STL はコンテナ・イテレータ・アルゴリズムの 3 つでできている。** アルゴリズムはイテレータを通してしか要素に触らないので、同じ `std::find` が vector にも list にも deque にも使える。

| 分類 | 例 | 特徴 |
|---|---|---|
| シーケンスコンテナ | `vector` `deque` `list` | 入れた順に並ぶ。vector は連続メモリで添字アクセスが速い。list は途中の挿入削除が速いが添字アクセスはできない |
| コンテナアダプタ | `stack` `queue` | 別のコンテナを中に持ち、使える操作を制限したもの。**イテレータを持たない** |
| 連想コンテナ | `map` `set` | キーの順に並ぶ。キー検索が O(log n) |

**範囲は半開区間 [begin, end) で表す。** `end()` は最後の要素の*次*を指すので、「見つからなかった」を `end()` で表せる。アルゴリズムごとに必要なイテレータの能力が違い、`std::sort` はランダムアクセス（vector・deque）が要る。list には使えず `list::sort` を使う。`std::find` は前に進めればよいので、どのコンテナにも使える。

**テンプレートの中の依存名には印が要る。** `T::iterator` は T が決まるまで型か値か分からないので、`typename T::iterator` と書いて型であることを示す。同様に、テンプレート引数に依存する基底クラスのメンバ（ex02 の `c`）は `this->c` と書かないと探されない。

---

## 5. ex00 — easyfind

### subject の要求

型 T を受け取る関数テンプレート `easyfind` を書く。第 1 引数は T（整数のコンテナとみなす）、第 2 引数は整数で、第 2 引数が**最初に現れる位置**を探す。見つからなければ、例外を投げるかエラー値を返す（どちらでもよい）。標準コンテナの振る舞いを参考にせよとあり、連想コンテナは扱わなくてよい。

### 実装

探索は `std::find` に任せ、自分で書いているのは「見つからなかったとき」の扱いだけである（[easyfind.hpp#L7-L16](cpp08/ex00/easyfind.hpp#L7)）。

```cpp
template<typename T>
typename T::iterator easyfind(T& container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);

	if (it == container.end()) {
		throw std::runtime_error("easyfind: value not found");
	}

	return it;
}
```

const なコンテナ用に、`const_iterator` を返す同じ形の版をもう 1 つ用意している（[easyfind.hpp#L18-L27](cpp08/ex00/easyfind.hpp#L18)）。

main は vector {5, 3, 5} から 5 を探して位置 0 が返ること（2 つ目ではなく**最初**の 5）、list と const な deque でも同じ関数が使えること、存在しない値で例外が出ることを確かめている（[ex00/main.cpp#L11-L35](cpp08/ex00/main.cpp#L11)）。

### なぜこの設計か

**イテレータを返すのは、標準コンテナの find と同じ振る舞いにするためである。** 位置が分かるので、値を読む・書き換える・`std::distance` で先頭からの距離を出す、のどれもできる。値や bool を返すと、この情報が失われる。

**見つからないときは例外にした。** 呼び出し側が end() との比較を忘れて `*it` すると未定義動作になるが、例外なら確実に気づける。end() を返す設計も成立し、その場合の書き換えは [§11](#11-評価中の改修依頼に備える) に置いた。

**const 版が要るのは、const なコンテナからは `iterator` が取れないからである。** const 版がないと、const なコンテナを渡した時点でコンパイルエラーになる。

### 学習メモ

- **ヘッダに置いた例外クラスが 0 点条件に当たっていた。** 2026-07-21 の整理（`80d365f`）より前の `easyfind.hpp` には、`NotFoundException` という例外クラスが `what()` の本体ごと書かれていた（`git show 80d365f^:cpp08/ex00/easyfind.hpp` の 11〜16 行目）。easyfind 自体はテンプレートなのでヘッダでよいが、この例外クラスは**テンプレートではない**ので、「ヘッダに関数の実装を書くと 0 点」の条件にそのまま当たる。標準の `std::runtime_error` に置き換えて、ヘッダにはテンプレートしか残らないようにした。**「ヘッダにあるものはすべてテンプレートか」を 1 行ずつ確かめる**のが、このモジュール以降の習慣になった。
- 同じ整理で、使っていない `#include <iostream>` と `<exception>` も外した。

---

## 6. ex01 — Span

### subject の要求

最大 N 個の整数を保持できるクラス `Span` を作る。N は unsigned int で、コンストラクタの唯一の引数。`addNumber()` で 1 つずつ追加し、すでに N 個あれば例外。`shortestSpan()` と `longestSpan()` は保持している数どうしの最短・最長の差を返し、数が 0 個か 1 個なら例外。最低 1 万個でテストする。最後に、イテレータの範囲で一度にまとめて追加するメンバ関数を実装する。subject はその理由を次のように書いている。

> Making thousands of calls to addNumber() is so annoying.
>
> — 公式 subject, Exercise 01（[cpp08/subject.txt](cpp08/subject.txt)）

subject の例は 6, 3, 17, 9, 11 を入れて、最短 `2`、最長 `14`。

### 実装

数は `std::vector<int>` に持つ（[Span.hpp#L10-L11](cpp08/ex01/Span.hpp#L10)）。Orthodox Canonical Form の 4 つと `Span(unsigned int n)` を明示している（[Span.hpp#L14-L18](cpp08/ex01/Span.hpp#L14)）。

最短の差は、コピーをソートして隣同士の差の最小を取る（[Span.cpp#L34-L53](cpp08/ex01/Span.cpp#L34)）。

```cpp
std::vector<int> sorted(_numbers);
std::sort(sorted.begin(), sorted.end());

unsigned int minSpan = UINT_MAX;

for (size_t i = 0; i < sorted.size() - 1; i++) {
	unsigned int span = static_cast<unsigned int>(sorted[i + 1])
		- static_cast<unsigned int>(sorted[i]);
	if (span < minSpan) {
		minSpan = span;
	}
}
```

最長の差は `std::min_element` と `std::max_element` で求める（[Span.cpp#L55-L65](cpp08/ex01/Span.cpp#L55)）。

まとめて追加する `addRange` はメンバ関数テンプレートで、ヘッダに置いている（[Span.hpp#L24-L32](cpp08/ex01/Span.hpp#L24)）。

```cpp
template<typename Iterator>
void addRange(Iterator begin, Iterator end) {
	std::vector<int> values(begin, end);
	if (values.size() > static_cast<size_t>(_maxSize) - _numbers.size()) {
		throw std::overflow_error("Adding range would exceed maximum capacity");
	}

	_numbers.insert(_numbers.end(), values.begin(), values.end());
}
```

### なぜこの設計か

**最短の差は、必ずソート後に隣り合う 2 つの間に現れる。** 間に別の数があれば、その数との差の方が小さいか等しいからである。全ペアを比べる O(n²) は要らず、ソートの O(n log n) で済む。評価表も「小さい 2 つの差で済ませていないか」を確認するよう求めている。subject の例をソートすると 3, 6, 9, 11, 17 で、小さい 2 つ（3 と 6）の差は 3 だが、正解は 9 と 11 の差 2 である。

**最長の差はソートしない。** 最大値 − 最小値なので、`std::min_element` / `std::max_element` の O(n) で十分である。

**差は `unsigned int` にしてから引く。** `INT_MAX - INT_MIN` は 4294967295 で int に収まらず、符号付き整数のオーバーフローは未定義動作になる。大きい方と小さい方を `unsigned int` にしてから引けば、差 0〜4294967295 を正しく表せる。戻り値が `unsigned int` なのもこのためである。

**`shortestSpan` はコピーをソートする。** const メンバ関数なので `_numbers` を並べ替えられない。追加した順序も保てる。

**`addRange` はいったん一時 vector に写す。** 理由は 2 つある。1 つは、`std::istream_iterator` のように 1 回しか読めないイテレータでも個数を数えられること。もう 1 つは、空きを確かめてから追加するので、容量を超えるときは例外を投げて Span を元のまま残せること。`_numbers.size()` は常に `_maxSize` 以下なので、`_maxSize - _numbers.size()` が負になることはない。

**コンストラクタで `reserve(n)` している**（[Span.cpp#L9-L11](cpp08/ex01/Span.cpp#L9)）。最大 N 個分の領域を先に確保し、`push_back` のたびの再確保を避ける。要素数は 0 のままである。

### 学習メモ

2026-07-21 の整理（`80d365f`）で Span はかなり書き直した。書き換え前の版を `80d365f^` から取り出し、現在の版と同じテストを当てて違いを確かめてある。

- **差を int で計算していた。** 旧版は `shortestSpan` / `longestSpan` が `int` を返し、`sorted[i + 1] - sorted[i]` を int のまま引いていた。INT_MIN と INT_MAX の 2 つを入れる [tests/cpp05_09/span_extreme.cpp](tests/cpp05_09/span_extreme.cpp) を旧版に当てると、最短・最長とも `-1` が出る（正しくは 4294967295）。**「差」は負にならないという性質を型で表す**ことで、オーバーフローの問題も一緒に消えた。
- **`addRange` が 1 回しか読めないイテレータを壊していた。** 旧版は `std::distance(begin, end)` で個数を数えてから `insert(begin, end)` していた。`std::istream_iterator` で "10 20 30" を渡す [tests/cpp05_09/span_input.cpp](tests/cpp05_09/span_input.cpp) を旧版に当てると、`std::distance` の時点でストリームを読み切ってしまい、`insert` には何も残らない。Span は空のままで、`shortestSpan` が例外を投げてプログラムが止まる。現在の版は `10 20` を出す。**イテレータには「何回読めるか」という能力の違いがある**ことを、ここで初めて意識した。
- **コンストラクタ・デストラクタ・`addNumber` がログを出していた。** 旧版は数を 1 つ追加するたびに 1 行出力していた。1 万個のテストでは 1 万行になる。課題の要求にない出力なので削除した。同時に、テスト用に足していた public メンバ（`size`・`maxSize`・`empty`・`full`・`display`）も削除した。課題が求めるインターフェースだけを残す、という判断である。

---

## 7. ex02 — MutantStack

### subject の要求

std::stack は STL のコンテナで数少ない反復できないものの 1 つである。これを反復できるようにする `MutantStack` を std::stack を元に作る。std::stack のメンバ関数をすべて提供し、さらにイテレータを追加する。subject には main の例があり、MutantStack で 1 回、std::list に置き換えて（`push` → `push_back` など）もう 1 回実行したとき、**出力が同じになる**ことが求められている。

### 実装

std::stack を public 継承し、中のコンテナのイテレータを公開している（[MutantStack.hpp#L7-L28](cpp08/ex02/MutantStack.hpp#L7)）。

```cpp
template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;

	// (OCF の 4 つ)

	iterator begin(void) { return this->c.begin(); }
	iterator end(void) { return this->c.end(); }
	const_iterator begin(void) const { return this->c.begin(); }
	const_iterator end(void) const { return this->c.end(); }
};
```

main は subject の例と同じ操作に加えて、MutantStack から std::stack へのコピー、const な MutantStack の const_iterator による合計、コピーと代入の独立性、中身を vector にした版、空の stack で begin == end を確かめている（[ex02/main.cpp#L8-L44](cpp08/ex02/main.cpp#L8)）。

### なぜこの設計か

**std::stack は中のコンテナを protected メンバ `c` として持っている。** 継承すれば派生クラスから `c` に触れるので、その begin / end を返すだけで反復できるようになる。std::stack の操作（push・pop・top・size・empty、比較演算子）は public 継承でそのまま使える。

**型引数は std::stack と同じ 2 つにした。** 要素の型 T と、中に使うコンテナ（既定は std::stack と同じ `std::deque<T>`）。これで `MutantStack<int, std::vector<int> >` のように中身を選べる。`> >` の空白は C++98 で必要で、ないと `>>` 演算子と読まれる。

**`this->c` の `this->` は省けない。** 基底クラス `std::stack<T, Container>` はテンプレート引数に依存するので、`c` とだけ書くと基底クラスの中が探されずにコンパイルエラーになる。`this->` を付けると、インスタンス化の時点で探される。

**反復の順序は底から top へ向かう。** list に `push_back` した順と同じなので、subject の main と list 版の出力が一致する。subject の例の `++it; --it;` も、中身が deque（双方向に動けるイテレータ）なので問題ない。

**デストラクタに virtual を付けているが、std::stack 側のデストラクタは virtual ではない**（[MutantStack.hpp#L22](cpp08/ex02/MutantStack.hpp#L22)）。std::stack のポインタ経由で MutantStack を delete するのは未定義動作のままである。本実装ではそういう使い方をしていない。

### 学習メモ

- **ログ出力が subject の要求そのものを壊していた。** 2026-07-21 の整理（`80d365f`）より前の MutantStack は、コンストラクタ・コピー・代入・デストラクタのたびに `MutantStack: Default constructor called` のような行を出力していた（`git show 80d365f^:cpp08/ex02/MutantStack.hpp` の 28・33・38・47 行目）。旧版で subject の main を動かすと 9 行、std::list 版は 7 行で、「出力が同じになる」という要求を満たさない（旧版を取り出して実測）。ログを消して一致させた。**デバッグ用の出力も仕様の一部として見られる**という教訓になった。
- 同じ整理で、std::stack から継承済みの `size()` / `empty()` を書き直していた部分と、表示用の `display()` を削除した。要件にない逆向きのイテレータ（`rbegin` / `rend`）も外した。必要になれば [§11](#11-評価中の改修依頼に備える) の方法で戻せる。

---

## 8. 指摘されうる点

自分で把握している「ここは突っ込まれうる」箇所。隠さず説明する方針。

### 8.1 Span の例外クラスは OCF を明示していない

評価表は 3 つの Exercise すべてで「インターフェース以外のクラスが OCF でなければ採点しない」としている。`Span` と `MutantStack` は 4 つの特殊メンバ関数を明示しているが、`Span::SpanFullException` と `Span::NoSpanException` は `what()` しか書いていない（[Span.hpp#L34-L42](cpp08/ex01/Span.hpp#L34)）。

- どちらもメンバ変数を持たないので、コンパイラが生成するコピー・代入・デストラクタで正しく動く。
- 例外クラスまで OCF を求める評価者は多くないが、厳密に読めば対象になりうる。
- 明示が必要なら、4 つを宣言して .cpp に定義するだけで済む（[§11](#11-評価中の改修依頼に備える)）。

### 8.2 最短の差の計算は for ループで書いている

評価表は「メンバ関数ができるだけ STL アルゴリズムを使っているか」を見る。本実装は `std::sort` の後、隣同士の差を for ループで調べている（[Span.cpp#L44-L50](cpp08/ex01/Span.cpp#L44)）。

- `std::adjacent_difference` と `std::min_element` でも書ける。ただし int のまま差を取ると INT_MIN と INT_MAX であふれるので、long の vector に写してから使う必要がある。
- ループなら unsigned へのキャストで済み、オーバーフローの扱いが読みやすいと判断した。書き換えの手順は [§11](#11-評価中の改修依頼に備える) に置いた。

### 8.3 addNumber と addRange で例外の型が違う

満杯の Span に `addNumber` すると `Span::SpanFullException`、`addRange` で容量を超えると `std::overflow_error` を投げる（[Span.hpp#L28](cpp08/ex01/Span.hpp#L28)）。どちらも `std::exception` の派生なので `catch (const std::exception&)` で受けられるが、型をそろえる方が一貫している。そろえるなら `addRange` 側も `SpanFullException` を投げればよい。

### 8.4 巨大な N ではコンストラクタが大きな領域を予約する

`reserve(n)` するので、`Span(4294967295)` は int 約 43 億個分（約 17 GB）の予約を試みる。Linux（Docker）で試した限りでは、実際に使うまで物理メモリが割り当てられないため例外にはならなかったが、環境によっては `std::bad_alloc` になりうる。`reserve` を外せば予約はなくなり、代わりに push_back の途中で再確保が起きる。

---

## 9. 想定質問

「こう答える」ではなく「なぜそうなっているか」として整理したもの。

**Q. なぜ std::find なのか。ループで探してはいけないのか。**
このモジュールの目的が STL を使うことで、評価表も ex00 で STL アルゴリズムを必須とし、手書きのイテレータ探索を不可としている。

**Q. なぜ値ではなくイテレータを返すのか。**
標準コンテナの find と同じ振る舞いにするため。位置が分かれば、値を読む・書き換える・距離を出す、のどれもできる。

**Q. `typename T::iterator` の typename は何のためか。**
T に依存する名前が型であることを示すため。テンプレートの段階では `T::iterator` が型か値か決まらないので、付けないとコンパイルエラーになる。

**Q. 連想コンテナを扱わないのはなぜか。**
subject で不要とされている。map の要素は key と value の pair なので int と直接比べられず、キーで探すなら map 自身の find（O(log n)）を使うべきである。

**Q. Span に vector を選んだ理由は。**
末尾に追加するだけで、あとでソートするから。連続メモリなので `std::sort` が速く、`reserve` で最大 N 個分を先に確保できる。

**Q. 「一番小さい 2 つの差」ではだめなのはなぜか。**
subject の例 6 3 17 9 11 で、小さい 2 つ（3 と 6）の差は 3 だが、正解は 9 と 11 の差 2 だから。ソートして隣同士をすべて比べる必要がある。

**Q. なぜ unsigned int にキャストしてから引くのか。**
`INT_MAX - INT_MIN` は int に収まらず、符号付き整数のオーバーフローは未定義動作だから。unsigned にしてから引けば 0〜4294967295 を正しく表せる。旧版は int で引いていて、INT_MIN と INT_MAX で -1 を返していた。

**Q. addRange はなぜ一時 vector に写すのか。**
1 回しか読めないイテレータでも個数を数えられるようにするためと、容量を確かめてから追加して、失敗したときに Span を元のまま残すため。旧版は `std::distance` で数えてからストリームを読み直そうとして、何も追加できていなかった。

**Q. addRange がヘッダにあるのは 0 点条件では。**
メンバ関数テンプレートなので除外される。どんなイテレータ型でも受けられるように、テンプレートにしている。

**Q. 1 万個以上でテストしたか。**
main で 1 万個を addRange で追加している。別に、乱数 10 万個で全ペアを総当たりした結果と一致することも確かめた。

**Q. std::stack にイテレータがないのはなぜか。**
LIFO（後入れ先出し）の使い方を強制するアダプタで、top しか触らせない設計だから。

**Q. `this->c` の `this->` は必要か。**
必要。基底クラスがテンプレート引数に依存するので、`c` とだけ書くと基底クラスの中が探されない。

**Q. どの順番で反復されるか。**
底（最初に push したもの）から top に向かって。list に push_back した順と同じなので、subject の list 版と出力が一致する。

**Q. push や pop の後もイテレータは使えるか。**
保証されない。中身が deque の場合、push（末尾への追加）でイテレータは無効になる。反復の途中で stack を変更しないのが前提である。

**Q. `std::stack<int> s(mstack);` が通るのはなぜか。**
MutantStack は std::stack を public 継承しているので、std::stack として扱える。基底部分だけがコピーされる。

**Q. virtual デストラクタは意味があるか。**
std::stack のデストラクタが virtual ではないので、std::stack のポインタ経由で delete するのは未定義動作のまま。MutantStack を new して基底クラスのポインタで扱う使い方はしていない。

---

## 10. 検証手順と実際の出力

以下は `cpp08/` をリポジトリ外へコピーしてビルドした実際の出力である。環境は macOS / Apple clang 21（2026-09-24、2026-09-28 に再確認）と Ubuntu 24.04（Docker）/ g++ 13.3.0・clang++ / Valgrind 3.22.0（2026-09-24）。cpp08 のソースは commit `80d365f` 以降変更されていない。

### ビルド

```console
$ cd cpp08/ex01 && make re
c++ -Wall -Wextra -Werror -std=c++98 -c main.cpp -o obj/main.o
c++ -Wall -Wextra -Werror -std=c++98 -c Span.cpp -o obj/Span.o
c++ -Wall -Wextra -Werror -std=c++98 obj/main.o obj/Span.o -o span
$ make
make: Nothing to be done for `all'.
```

ex00（`easyfind`）/ ex02（`mutantstack`）も同様に警告 0 で通り、再リンクしない。`-pedantic-errors` を足しても通る。3 ヘッダとも単体で include でき、2 回続けて include してもコンパイルできる。

### ex00

```console
$ ./easyfind
Found first occurrence of 5 at position: 0
List value: 30
Const deque value: 1
easyfind: value not found
```

空のコンテナ（例外）、見つかった位置のイテレータ経由での書き換え、要素がすべて同じ deque も確認した。

### ex01

```console
$ ./span
2
14
10000 spans: 2 19998
Input spans: 10 20
Span is full - cannot add more numbers
Cannot calculate span - need at least 2 numbers
```

追加で確認したもの:

| 確認内容 | 結果 |
|---|---|
| subject の main をそのまま実行 | `2` / `14` |
| 乱数 10 万個の最短の差を、全ペア総当たりの結果と比較 | 一致 |
| INT_MIN と INT_MAX の 2 つ（[span_extreme.cpp](tests/cpp05_09/span_extreme.cpp)） | 最短・最長とも `4294967295` |
| istream_iterator で追加（[span_input.cpp](tests/cpp05_09/span_input.cpp)） | `10 20` |
| 容量 3 に 4 個を addRange | 例外。Span は空のまま |
| `Span(0)` に addNumber | 例外 |
| 同じ数が 2 つ | 最短の差 `0` |

### ex02

```console
$ ./mutantstack
17
1
5
3
5
737
0
Const sum: 750
Copy top: 0, assigned top: 0
Vector top: 20
Empty iterators equal: yes
```

subject の main をそのまま MutantStack で動かした出力と、std::list に置き換えた版の出力は、どちらも `17 1 5 3 5 737 0` で完全に一致した（macOS と Ubuntu の g++ の両方）。std::stack の `==` と `<` が MutantStack にも使えることも確認した。

### メモリリーク

```console
$ valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=42 -q ./span
$ echo $?
0
```

Ubuntu で 3 つのバイナリと上記の追加テストすべてが valgrind のエラー・リーク 0。

### レビュワーが自分で確かめるとき

提出ファイルを書き換えずに main を差し替える形が安全である。

```bash
c++ -Wall -Wextra -Werror -std=c++98 -Icpp08/ex01 \
  tests/cpp05_09/span_extreme.cpp cpp08/ex01/Span.cpp -o /tmp/cpp08-span && /tmp/cpp08-span

c++ -Wall -Wextra -Werror -std=c++98 -Icpp08/ex01 \
  tests/cpp05_09/span_input.cpp cpp08/ex01/Span.cpp -o /tmp/cpp08-input && /tmp/cpp08-input
```

CPP05〜09 をまとめて検証するなら [scripts/verify_cpp05_09.sh](scripts/verify_cpp05_09.sh) を使う。

---

## 11. 評価中の改修依頼に備える

subject の最終章に、評価中に軽微な改修を求められることがあると明記されている。この課題で来そうなものと、触る場所を先に決めておく。以下はすべてコンパイルと実行を確認済み。

| 依頼されそうなこと | 触る場所 | やること |
|---|---|---|
| 逆向きに反復したい | [MutantStack.hpp#L24-L27](cpp08/ex02/MutantStack.hpp#L24) | `typedef typename Container::reverse_iterator reverse_iterator;` と const 版を足し、`rbegin` / `rend` を `this->c.rbegin()` / `this->c.rend()` で返す |
| easyfind を「見つからなければ end()」にする | [easyfind.hpp#L7-L16](cpp08/ex00/easyfind.hpp#L7) | `return std::find(container.begin(), container.end(), value);` だけにし、呼ぶ側で `== c.end()` を比べる |
| 最短の差を adjacent_difference で書く | [Span.cpp#L34-L53](cpp08/ex01/Span.cpp#L34) | `std::vector<long>` に写してソート → `std::adjacent_difference` → `std::min_element(diffs.begin() + 1, diffs.end())`。`<numeric>` を include。先頭要素は差ではないので除く |
| C 配列からまとめて追加する | 呼ぶ側 | `sp.addRange(arr, arr + 5);`（ポインタもイテレータ）。ヘッダは変更不要 |
| 乱数 1 万個でテストする | [ex01/main.cpp](cpp08/ex01/main.cpp) | `std::vector<int> v(10000); std::generate(v.begin(), v.end(), std::rand);` の後に addRange |
| MutantStack の中身を list にする | 呼ぶ側 | `MutantStack<int, std::list<int> >`。ヘッダは変更不要 |
| 例外クラスを OCF にする | [Span.hpp#L34-L42](cpp08/ex01/Span.hpp#L34) と Span.cpp | デフォルトコンストラクタ・コピーコンストラクタ・代入・`virtual ~X() throw()` を宣言し、コピーは `std::exception(other)`、代入は `std::exception::operator=(other)` に任せる |

---

## 12. つまずきやすい点の一覧

| 誤解 | 正しい理解 |
|---|---|
| Module 08 でも STL は禁止 | Module 08・09 で解禁される。むしろ使うことが評価される |
| easyfind はループで探してもよい | 評価表は STL アルゴリズムを必須としている |
| ヘッダにはテンプレート以外を書いても大丈夫 | 例外クラスの `what()` 本体など、非テンプレートの実装をヘッダに置くと 0 点条件に当たる |
| `T::iterator` はそのまま型として書ける | 依存名なので `typename` が要る |
| 最短の差は小さい 2 つの差 | ソートして隣同士をすべて比べる。subject の例がその反例 |
| 差は int で引けばよい | INT_MAX − INT_MIN があふれる。unsigned で引く |
| イテレータは何度でも読み直せる | istream_iterator は 1 回しか読めない。`std::distance` で数えると中身が消える |
| 最長の差もソートが必要 | 最大値 − 最小値なので min_element / max_element の O(n) で足りる |
| std::stack は中身に触れない | protected メンバ `c` として持っており、継承すれば触れる |
| 基底クラスのメンバは `c` と書けば見える | テンプレート引数に依存する基底では `this->c` が必要 |
| デバッグ用の出力は害がない | subject の「list 版と同じ出力」を壊す。出力も仕様の一部 |
| MutantStack の virtual デストラクタで基底経由の delete も安全 | std::stack のデストラクタは virtual ではない |

---

## 13. 関連資料

- [cpp08/subject.txt](cpp08/subject.txt) — 課題原文の写し（Exercise 以降）
- [cpp08/evals.txt](cpp08/evals.txt) — EvalHub の評価表
- [tests/cpp05_09/](tests/cpp05_09/) — 境界値と 1 回しか読めないイテレータのテスト（`span_extreme.cpp` / `span_input.cpp`）
- [REVIEW_NOTES.md](REVIEW_NOTES.md) — CPP05〜09 横断の防衛ノートと提出前チェック
- [COMPREHENSIVE_EVALUATION.md](COMPREHENSIVE_EVALUATION.md) — 監査レポートと provenance
- [CPP05_COMPLETE_DEFENSE_GUIDE.md](CPP05_COMPLETE_DEFENSE_GUIDE.md) / [CPP06_COMPLETE_DEFENSE_GUIDE.md](CPP06_COMPLETE_DEFENSE_GUIDE.md) — 同形式の CPP05 / CPP06 版
