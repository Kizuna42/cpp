# 42 School C++ Modules 00-09

C++98でC++の基礎からSTLまでを学ぶ42 Schoolの演習リポジトリです。実ディレクトリ数は全10 Module・38 Exerciseです。

## 現在の検証範囲

2026-07-21にCPP05〜CPP09の全16 Exerciseを、ローカルの公式subject PDFと照合して再監査しました(2026-07-20監査の再実証+検証強化)。

- CPP05: 4 Exercise
- CPP06: 3 Exercise
- CPP07: 3 Exercise
- CPP08: 3 Exercise
- CPP09: 3 Exercise

この監査では、macOS/Apple clang 21とDocker Ubuntu 24.04 aarch64/g++ 13.3の両方でC++98ビルド・動作・境界値を確認し、UbuntuではValgrind 3.22.0も実行しています。検証スクリプトにはsubject実行例との完全一致照合と禁止パターン静的検査を追加済みです。CPP00〜CPP04は今回の監査対象外です。古い評価結果を現在の検証結果として扱わないでください。

詳細は次の資料を参照してください。

- [CPP05-09 defense notes](REVIEW_NOTES.md)
- [CPP05-09 comprehensive evaluation](COMPREHENSIVE_EVALUATION.md)
- [Reproducible verification script](scripts/verify_cpp05_09.sh)

## Exercise構成

| Module | Exercise数 | 主題 |
|---|---:|---|
| CPP00 | 3 | namespaces, classes, member functions |
| CPP01 | 7 | memory allocation, references, file I/O |
| CPP02 | 4 | OCF, operator overloading, fixed point |
| CPP03 | 4 | inheritance |
| CPP04 | 4 | subtype polymorphism, abstract classes |
| CPP05 | 4 | exceptions, forms, factory |
| CPP06 | 3 | C++ casts |
| CPP07 | 3 | function/class templates |
| CPP08 | 3 | templated containers, iterators, algorithms |
| CPP09 | 3 | STL applications, Ford–Johnson |
| 合計 | 38 | |

## 個別Exerciseのビルド

各`exXX`ディレクトリで実行します。

```bash
make
make re
make fclean
```

すべてのMakefileは次の必須フラグを使用します。

```text
c++ -Wall -Wextra -Werror -std=c++98
```

実行ファイル名は各Makefileの`NAME`を確認してください。`make test`ターゲットはありません。

## CPP05-09の一括検証

macOSまたは、g++/make/Valgrindが導入済みのLinuxでは次を実行します。

```bash
./scripts/verify_cpp05_09.sh
```

スクリプトは通常ビルド、再リンク判定、26ヘッダーのstandalone compile、subject例(実行例ブロックの完全一致照合を含む)、境界値、公開API制約、禁止パターン静的検査、`-pedantic-errors`、PmergeMe 3000件・500 property casesを実行します。Valgrindがあれば16 binaryとArrayの例外経路も検証し、終了時に生成物を`fclean`します。

DockerがあるホストではUbuntu 24.04コンテナで完全再現できます(リポジトリはread-onlyマウントで汚しません)。

```bash
docker run --rm -v /path/to/cpp:/src:ro ubuntu:24.04 bash -c \
  'apt-get update && apt-get install -y g++ make valgrind && \
   cp -a /src /work && cd /work && ./scripts/verify_cpp05_09.sh'
```

2026-07-21の実測ではこの手順(g++/make/valgrind導入済みイメージ)で実行しました。2026-07-20はUTMのUbuntu 24.04 guest内`/tmp`で同スクリプトを実行しています。

## 共通制約

- C++11以降の機能は禁止
- `*printf()`、`*alloc()`、`free()`は禁止
- `using namespace`と`friend`は禁止（subjectが明示的に許可する場合を除く）
- STLコンテナ/アルゴリズムはCPP07まで禁止、CPP08/09で使用
- Module 02以降はsubjectが除外した型を除きOrthodox Canonical Formを実装
- ヘッダーガードとstandalone includeを維持
- `new`を使う実装は例外経路を含めてリークさせない

## 最新監査結果

| 環境 | 結果 |
|---|---|
| macOS 26.5.2 arm64 / Apple clang 21 | 159 PASS / 0 FAIL / Valgrindのみ1 SKIP |
| macOS ASan + UBSan | 16/16 binary PASS |
| Docker Ubuntu 24.04 aarch64 / g++ 13.3.0 / Valgrind 3.22.0 | 176 PASS / 0 FAIL / 0 SKIP(Valgrind 17/17) |
| Docker Ubuntu 24.04 amd64(qemu、build+機能のみ) | 159 PASS / 0 FAIL / Valgrindのみ1 SKIP |

監査日: 2026-07-21(前回2026-07-20のUTM Ubuntu実測 155/0/0 は検証ケース追加前の値)
