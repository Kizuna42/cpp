# CPP05-09 包括評価レポート

**評価日:** 2026-08-24

**対象:** CPP05〜CPP09、全16 Exercise

**現状:** current EvalHub HTML criteria、取得可能な履歴PDF、実装、最終fresh evidenceの確認範囲でblockerなし。CPP05〜CPP09は提出可能・defense-ready。

## 1. 評価基準とprovenance

優先順位は次のとおりである。

1. 2026-08-24にChromeで確認したcurrent 42 EvalHub HTML criteria
2. Git履歴から回収しSHA-256を実測した旧subject PDF
3. 各`cppXX/subject.txt`（補助資料。PDFや現行HTMLと競合する場合は優先しない）

current EvalHub subject.pdfのCDN linkは確認時点で404だった。従って、最新PDFの現物を確認したとは主張しない。既存文書にあったv11.1/8.1/10.1/10.1/3.1のPDF hashも根拠として用いない。local `subject.txt`は補助資料にとどめる。

| Module | 履歴PDF version | 実測SHA-256 |
|---|---:|---|
| CPP05 | 11.0 | `88010ccfae0b7ec1da349b5f49ba8a1d900c992726bf136234166ed1b2ea6427` |
| CPP06 | 8.0 | `0903292a8cc805dd6262ff6f43e716ead0519cfe2b72975b7a2ae0b8346a7cfb` |
| CPP07 | 10.0 | `e5ae2d885d24187739eebe771ba13e7786d47d2f17c245cd3bfa9b7246018a52` |
| CPP08 | 10.0 | `4c284566cf2fa11e7868f6864b266a59ab551ce2198a1eb371e5d4dac36d9021` |
| CPP09 | 3.0 | `e56eee53d4b0c8cc0a1425fb53df959dcc98547b0bc448308a1fa6c322ff1d43` |

### Current EvalHub criteria matrix

| Module | EvalHubで確認した必須点 |
|---|---|
| 共通 | C++98、`c++ -Wall -Wextra -Werror`、non-template実装をheaderに置かない、`printf`/`alloc`/`free`/`using namespace`/`friend`/外部library禁止。 |
| CPP05 | Bureaucrat、Form、AForm、3 concrete forms、`executeForm`。Internはcreator function/member-function pointer tableでdispatchしif/else-if chain不可、未知名は明示エラー。 |
| CPP06 | ScalarConverterはprivate constructor/static cast、Serializerはprivate/static reinterpret_cast、identifyはpointer NULL/reference try-catch dynamic_cast、`typeinfo`禁止。 |
| CPP07 | whateverのsimple+complex、iterのevaluator harness、Arrayの`new[]`、empty/sized/default initialization/read-write/const/bounds/simple+complex/deep copy。 |
| CPP08 | easyfindはSTL algorithm、SpanはSTL algorithm+range add、MutantStack iteratorとsubject以上のtest。 |
| CPP09 | btcはmap/closest lower/empty+bad lines継続/invalid date/`<0`/`>1000`/`input.csv`。RPNは別containerとadvanced `42`/`42`/`15`。PmergeMeは未使用の2 containers、両方Ford–Johnson、5〜10手動+3000 random、timing差説明。 |

## 2. Exercise別の評価契約と最終判定

PASSは、current EvalHub HTML criteriaと取得可能な履歴PDF、現行実装、最終fresh evidenceの確認範囲でblockerがないことを表す。CDNが404の最新subject PDF現物まで確認済みという意味ではない。

| Module | Exercise | Binary | EvalHub主眼 | 判定 |
|---|---|---|---|---|
| CPP05 | ex00 | `bureaucrat` | grade境界、例外、出力 | PASS |
| CPP05 | ex01 | `form` | const/private属性、署名条件 | PASS |
| CPP05 | ex02 | `aform` | AForm、3 forms、execute前提 | PASS |
| CPP05 | ex03 | `intern` | static creator function pointer table、未知名エラー | PASS |
| CPP06 | ex00 | `convert` | private/static、scalar cast | PASS |
| CPP06 | ex01 | `serializer` | private/static、reinterpret_cast round-trip | PASS |
| CPP06 | ex02 | `identify` | NULL / try-catch dynamic_cast、typeinfoなし | PASS |
| CPP07 | ex00 | `whatever` | simple+complex、等値時の返却 | PASS |
| CPP07 | ex01 | `iter` | evaluator harness、const/non-const template deduction | PASS |
| CPP07 | ex02 | `array_test` | default init、bounds、complex、deep copy | PASS |
| CPP08 | ex00 | `easyfind` | STL algorithm、not found | PASS |
| CPP08 | ex01 | `span` | STL algorithm、range add、span境界 | PASS |
| CPP08 | ex02 | `mutantstack` | iterator、subject以上のtest | PASS |
| CPP09 | ex00 | `btc` | map/closest lower、bad line継続 | PASS |
| CPP09 | ex01 | `RPN` | 別container、operand順、advanced case | PASS |
| CPP09 | ex02 | `PmergeMe` | 2 containersのFord–Johnson、手動/3000 random、timing | PASS |

## 3. 実装・defenseで確認する事項

### CPP05

- `AForm::execute`は署名・gradeを共通検査し、concrete formはactionに限定する。Internはnameとstatic creator function pointerのtableをloopして選ぶ。
- 今回の修正対象: **Intern未知名出力**。final verificationでは未知名が明示エラーとなり、既知formへ誤dispatchしないことを確認する。

### CPP06

- ScalarConverterは`static_cast`、Serializerは`reinterpret_cast`、identifyは`dynamic_cast`の使い分けを説明可能にする。
- reference版identifyは例外で失敗を識別し、`<typeinfo>`や`typeid`を導入しない。

### CPP07

- `iter`はevaluator形式のfunction template名が解決でき、const arrayに非const callbackを渡さないことを示す。
- `Array<T>`は`new T[n]()`、bounds exception、deep copyに加え、要素copyがthrowした場合のcleanupとassignmentのstrong guaranteeを確認する。
- 今回の修正対象: **Array mainのcomplex/default proof**。最終mainまたはharnessで複雑型とdefault initializationを実証する。

### CPP08

- Spanのrange addはInputIteratorを一度しか消費せず、capacity超過時に部分変更を残さない。shortest/longestの計算でsigned overflowを起こさない。
- MutantStackは`std::stack`のprotected `c`からiteratorを公開し、stackの既存機能を保つ。

### CPP09

- btcは`map::lower_bound`のexact/non-exact/beginを区別し、invalid行を報告して処理を続ける。
- RPNは`right`を先にpopし`left op right`を計算する。overflowと`INT_MIN / -1`を演算前に止める。
- PmergeMeはvector/dequeの両方でpair/winner再帰sort/partner bound/Jacobsthal/stragglerを処理する。partner `a_j`より右は`b_j <= a_j`から探索不要である。

## 4. 最終fresh evidence（2026-08-24）

| 環境 / check | 最終結果 |
|---|---|
| macOS Apple clang 21 | `./scripts/verify_cpp05_09.sh`: 176 PASS / 0 FAIL / 1 SKIP（Valgrind unavailableのみ）。`cpp05/ex02/verifier_preserves_shrubbery`はscript実行後もpreserved、exit 0。 |
| Ubuntu 24.04 Docker（g++ / Valgrind） | verifier: 193 PASS / 0 FAIL / 0 SKIP。ValgrindはArray例外経路+全16 binaryの17ケース全PASS。 |
| macOS ASan + UBSan | 全16 binary: 16/16 PASS。Apple ASanは`detect_leaks=0`で実行し、leak検査はLinux Valgrindで補完。 |
| current EvalHub `input.csv` | 22行（header+21 data）をbtcがexit 0で処理、21 output lines。bad value後の継続、exact/lower-dateを確認。 |
| RPN advanced | 指定3式の結果: `42`、`42`、`15`。 |
| PmergeMe | n=5〜10固定、3000 descending、500 deterministic property、3000 random duplicatesでvector/deque双方のsorted+multiset PASS。 |
| 独立diff review | 初回P2（5〜10固定証跡不足）を修正。scoped re-reviewは承認・指摘なし。 |
| 静的検査 | `git diff --check`、`bash -n` PASS。 |

### 修正前baseline（履歴、2026-08-24）

最終結果と混同しないため、修正前に得られた数値は履歴としてのみ残す。

| 環境 / check | 修正前の結果 |
|---|---|
| macOS verification script | 159 PASS / 0 FAIL / 1 SKIP |
| Ubuntu 24.04 verification script | 176 PASS / 0 FAIL / 0 SKIP |

### PmergeMe比較回数の履歴測定（2026-07-21）

この測定は2026-08-24 fresh evidenceと混同しない。監査用一時copyで値比較をinstrumentし、n=1〜10の全4,037,913 permutationを列挙した。提出実装にはinstrumentを残していない。

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| measured worst | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |
| Ford–Johnson bound | 0 | 1 | 3 | 5 | 7 | 10 | 13 | 16 | 19 | 22 |

## 5. Known limitations / 要確認

- current EvalHub subject.pdf CDNは404で、current HTML以外の最新PDF現物はこの評価で確認できていない。
- 履歴PDFは実測SHA-256を記録した旧版であり、current EvalHub PDF現物の代替ではない。
- 修正前の159/176は履歴baselineであり、正式な最終値は上記の176/193である。
- timingは環境・入力・計測境界に依存する。PmergeMeの正しさや比較回数最適性を単発の経過時間だけでは立証しない。

## 6. 現時点の結論

CPP05〜CPP09は提出可能・defense-readyであり、current EvalHub HTML criteria、取得可能な履歴PDF、実装、最終fresh evidenceの確認範囲でblockerはない。これはCDNが404のcurrent EvalHub subject PDF現物を確認済みとする主張ではない。
