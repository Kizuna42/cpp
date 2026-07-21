# CPP05-09 包括評価レポート

**監査日:** 2026-07-21(初回監査2026-07-20、同日主張を本日再実証+検証ケース21件追加)  
**対象:** CPP05〜CPP09、全16 Exercise  
**結論:** 現在の対象ファイルは、公式subject、C++98、macOS/Linux、Valgrind、defense準備の観点で提出可能な状態

## 1. 監査範囲と一次資料

ローカルのsubject PDFを一次資料として、テキスト抽出と全ページrenderの両方を確認しました。

| Module | Version | Pages | SHA-256 |
|---|---:|---:|---|
| CPP05 | 11.1 | 17 | `c17c5e2aa5ba297b7b815397a2eb267db9f259ff1052dd755164b15da5c6f5a2` |
| CPP06 | 8.1 | 15 | `8f1c117f9388d8cfba103af391e5b5ad71607c48d2e1f02c1c23b1a7a8c8f44a` |
| CPP07 | 10.1 | 13 | `a9dacf7af0525c67333c652d8665442b35a6ec8698dd26017d563d066152f1d6` |
| CPP08 | 10.1 | 15 | `a676834117b2ec5731c4dbedc201ab6e490e04ad4b8f0fea685c8d40f7085ce3` |
| CPP09 | 3.1 | 17 | `f07d21cc38bb84ba1e06b4d43914f8388fdac5fb9b8d4a4fd895cfe3bd8c27e2` |

リポジトリ内の`evals.txt`は補助資料として参照しましたが、元の評価票PDF/画像は存在しないため、版の真正性は断定していません。

## 2. Exercise別判定

| Module | Exercise | Binary | 判定 | 主な確認点 |
|---|---|---|---|---|
| CPP05 | ex00 | bureaucrat | PASS | grade 1〜150、例外、挿入演算子 |
| CPP05 | ex01 | form | PASS | private/const属性、署名grade、再署名 |
| CPP05 | ex02 | aform | PASS | AForm、3 concrete forms、実行前提条件 |
| CPP05 | ex03 | intern | PASS | factory、既知/未知form、全具象form |
| CPP06 | ex00 | convert | PASS | actual type判定、疑似literal、全境界変換 |
| CPP06 | ex01 | serializer | PASS | uintptr_t round-trip |
| CPP06 | ex02 | identify | PASS | pointer/reference dynamic_cast、単独A/B/C出力 |
| CPP07 | ex00 | whatever | PASS | swap/min/max、等値時第2引数 |
| CPP07 | ex01 | iter | PASS | evaluator形式、const/non-const callback |
| CPP07 | ex02 | array_test | PASS | value initialization、deep copy、例外安全 |
| CPP08 | ex00 | easyfind | PASS | std::find、const/non-const、未発見 |
| CPP08 | ex01 | span | PASS | 10,000件、全int範囲、input iterator |
| CPP08 | ex02 | mutantstack | PASS | forward/const iterators、stack機能、container差替え |
| CPP09 | ex00 | btc | PASS | CSV、暦日、lower date、値0〜1000 |
| CPP09 | ex01 | RPN | PASS | 1桁整数、整数演算、エラー、overflow防止 |
| CPP09 | ex02 | PmergeMe | PASS | Ford–Johnson、vector/deque、3000件、正整数 |

## 3. 今回確定・修正した重要事項

### CPP05

- 既署名formへの`beSigned()`を冪等にし、gradeが十分ならsubjectどおりsigned状態を維持
- concrete action失敗前の成功風メッセージを除去し、`Bureaucrat::executeForm()`が成功後だけ`executed`を表示
- `AForm::executeAction()`をprotected、concrete overrideをprivateにし、署名・grade検査の迂回を禁止
- constructor/destructor/copyの課題外出力を削除し、Intern生成物の所有権を例外経路でも解放

### CPP06

- float literalを末尾`f`除去後にdouble空間で安全にparseし、`FLT_MAX`超をfloatへcastしない
- `strtod`のERANGEをoverflowとsubnormalに分け、表現可能なdouble subnormalを受理
- floating-to-integralは0方向への切捨て後にchar/int範囲を判定
- `isdigit`へ`unsigned char`を渡し、負の`char`での未定義動作を回避
- `identify()`の出力をsubject指定の`A`/`B`/`C`だけに整理
- `ScalarConverter`のclass宣言はprivate OCFとpublic `convert()`だけにし、解析helperをtranslation unit内へ隠蔽
- `Data`をnon-emptyな最小structへ整理し、Serializerの公開APIを2つのcast関数だけに限定

### CPP07

- 非標準zero-length arrayを除去し、`-pedantic-errors`でもC++98準拠
- `Array<T>`のcopy constructor失敗時に確保済み配列を解放
- copy-and-swap相当の代入で、allocation/copy失敗時も左辺を保持
- size constructorは`new T[n]()`でvalue-initialize
- `iter()`のlengthをPDF v10.1どおり`const size_t`で受け、callback例を提出headerから分離
- `Array<T>`の課題外`fill()`/`display()`を削除し、self-assignmentはalias経由で実行検証

### CPP08

- spanの戻り値と差分を`unsigned int`にし、`INT_MIN`〜`INT_MAX`でsigned overflowを回避
- `addRange`は入力を一度temporary vectorへ読み、single-pass InputIteratorを二重走査しない
- Spanの診断用公開APIとMutantStackの重複`size/empty`・表示helperを削除

### CPP09

- BitcoinExchangeの日付上限2100という仕様外制限を除去。DB最終日より未来でもclosest lower dateを使用
- NaN/Infを入力値・exchange rateとして拒否
- fixed小数10桁をやめ、有効桁precisionで極小の正の計算結果も0へ丸めない
- RPNを`std::stack<int, std::list<int> >`へ統一し、各演算段階で整数除算。decimal tokenは拒否
- RPNの加減乗除overflowを実演算前に検出
- `RPN::reset()`をprivate helperにし、公開APIから内部stack操作を分離
- PmergeMeはPDFのpositive integer要件に従い`0`を拒否

## 4. 検証結果

2026-07-21に検証スクリプトへ「subject実行例の完全一致照合」「禁止パターン静的sweep」「PmergeMe 4行出力の構造検証」「コンパイル実行コマンドの必須フラグ検証」の計21ケースを追加した(既存ケース不変)。二次モデルレビュー(Codex gpt-5.6-sol)の指摘3件—Makefileフラグのgrepのみ検査・禁止構文の空白バリエーション見逃し・PmergeMe出力の分割substring検査—を反映した最終形。以下は追加後の実測。

### macOS(2026-07-21)

- macOS 26.5.2、arm64
- Apple clang 21.0.0 / libc++
- `scripts/verify_cpp05_09.sh`: **159 PASS / 0 FAIL / 1 SKIP**(追加前ベースラインでも138/0/1を同日再実証)
- Valgrindだけ未導入のためSKIP
- ASan + UBSan build/run: **16/16 binary PASS**(2026-07-21再実行)

### Linux（Docker Ubuntu 24.04、2026-07-21）

- Docker 27.4.0、ubuntu:24.04コンテナ、aarch64ネイティブ(qemuなし)
- g++ 13.3.0 / libstdc++、GNU Make 4.3、Valgrind 3.22.0
- リポジトリをread-onlyマウントし、コンテナ内`/work`へコピーして実行(ホスト作業ツリー非汚染)
- `scripts/verify_cpp05_09.sh`: **176 PASS / 0 FAIL / 0 SKIP**(追加前ベースラインでも155/0/0を同日再実証)
- Valgrind: Array例外経路 + 全16 binary、17/17 PASS
- 追加スモーク: `--platform linux/amd64`(qemu、Valgrindなし)でも **159 PASS / 0 FAIL / 1 SKIP**

### Linux（UTM Ubuntu、2026-07-20実測・履歴）

- UTM Ubuntu 24.04、Linux 6.8.0-134-generic
- architecture: aarch64
- g++ 13.3.0 / libstdc++
- GNU Make 4.3
- Valgrind 3.22.0
- `COPYFILE_DISABLE=1`でAppleDoubleを除外したarchiveを使用
- 転送元/guestのbyte size一致とguestでの展開成功を確認してから検証
- `scripts/verify_cpp05_09.sh`: **155 PASS / 0 FAIL / 0 SKIP**
- 通常build 16/16、no-relink 16/16
- `-pedantic-errors` build 16/16
- standalone header 26/26
- Valgrind: Array例外経路 + 全16 binary PASS

### PmergeMe

- 3000個の降順入力を正しくsort
- 重複を含む500 deterministic property cases（n=1〜100、各5件）を正しくsort
- 値比較箇所を一時instrumentし、n=1〜10の全4,037,913 permutationを総当たり
- 実測worst comparisons: `0, 1, 3, 5, 7, 10, 13, 16, 19, 22`
- `sum(k=1..n, ceil(log2(3k/4)))`と全nで一致
- instrumentは監査用一時copyだけに適用し、提出コードには残していない

## 5. 提出時の注意

- 各Moduleの提出対象は各subjectの`Files to turn in`に従う
- CPP07 ex02のPDF掲載mainは`srand/rand/time`用の`<cstdlib>`/`<ctime>`が不足している。提出headerの欠陥ではなく、検証用copyでは2 includeを補完済み
- CPP09 ex00は`data.csv`をcurrent working directoryから読むため、`cpp09/ex00`で実行する
- 実行生成物は`.gitignore`と検証scriptの`fclean`で管理する
- このレポートはCPP05〜CPP09だけを現在確認したもの。CPP00〜CPP04の品質を2026-07監査済みとは主張しない

## 6. 最終判定

CPP05〜CPP09の全16 Exerciseについて、現在確認できるblockerはありません。公式subject準拠(実行例ブロックの完全一致を含む)、C++98 strict build、macOS/Linuxの動作、Linux Valgrind、ASan+UBSan、境界値、defense説明の整合性を2026-07-21に確認済みです。
