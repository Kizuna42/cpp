# 42 School C++ Modules 00-04

## 概要

42スクールのC++カリキュラムプロジェクトです。C++98標準に準拠し、オブジェクト指向プログラミングの基礎から応用まで段階的に学習します。

## プロジェクト構成

```
cpp/
├── cpp00/          # Module 00: 名前空間、クラス、メンバ関数 ✅
│   ├── ex00/       # Megaphone
│   ├── ex01/       # PhoneBook  
│   └── ex02/       # Account
├── cpp01/          # Module 01: メモリ割り当て、ポインタ、参照 🚧
├── cpp02/          # Module 02: 多態性、演算子オーバーロード 🚧
├── cpp03/          # Module 03: 継承 🚧
├── cpp04/          # Module 04: サブタイプ多態性、抽象クラス 🚧
├── CLAUDE.md       # Claude Code ガイド（英語）
├── CLAUDE_JP.md    # Claude Code ガイド（日本語）
└── README.md       # このファイル
```

## 開発環境

### 必要ツール
- **コンパイラ**: g++ または clang++ (C++98サポート)
- **make**: GNU Make
- **Git**: バージョン管理

### 開発環境
- **macOS**: 主要開発環境
- **Ubuntu**: valgrindによるメモリテスト環境

## ビルド方法

各モジュールの演習ディレクトリで：

```bash
# ビルド
make

# クリーンビルド
make re

# クリーンアップ
make fclean
```

## コンパイル仕様

- **標準**: C++98
- **フラグ**: `-Wall -Wextra -Werror -std=c++98`
- **警告**: ゼロ警告必須

## 開発制約

### 禁止項目
- C++11以降の機能
- STLコンテナ（Module 08まで）
- `using namespace`文
- `printf()`, `malloc()`, `free()`
- `friend`キーワード

### 必須項目
- Orthodox Canonical Form（Module 02から）
- メモリリーク防止
- RAII原則
- インクルードガード

## テスト戦略

### macOS（開発）
```bash
# 静的解析
cppcheck --enable=all --std=c++98 src/

# 追加警告付きコンパイル
clang++ -Wall -Wextra -Werror -std=c++98 -Weverything
```

### Ubuntu（検証）
```bash
# メモリリーク検出
valgrind --leak-check=full ./program

# アドレスサニタイザー
g++ -fsanitize=address -g
```

## ブランチ戦略

```
main
├── feature/cpp01-implementation
├── feature/cpp02-implementation  
├── feature/cpp03-implementation
├── feature/cpp04-implementation
└── docs/enhance-cpp00-documentation
```

## 学習目標

### Module 00: C++基礎
- 名前空間とクラス
- メンバ関数
- stdio streams
- 初期化リスト
- static, const

### Module 01: メモリとポインタ
- メモリ割り当て
- ポインタと参照
- switch文

### Module 02: 多態性
- Ad-hoc多態性
- 演算子オーバーロード
- Orthodox Canonical Form

### Module 03: 継承
- 継承概念
- 仮想関数

### Module 04: 抽象化
- サブタイプ多態性
- 抽象クラス
- インターフェース

## 品質基準

- ✅ コンパイル警告ゼロ
- ✅ メモリリークゼロ
- ✅ 全機能要件満足
- ✅ C++98標準準拠

## ドキュメント

- [CLAUDE.md](CLAUDE.md) - 開発ガイド（英語）
- [CLAUDE_JP.md](CLAUDE_JP.md) - 開発ガイド（日本語）
- 各モジュールの`docs/`ディレクトリに学習資料

## ライセンス

このプロジェクトは42スクールの教育目的で作成されています。

---

**Status**: 🚧 開発中  
**Last Updated**: 2025-07-29