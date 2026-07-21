# AGENTS.md

42 School の C++ モジュール課題（cpp00〜cpp09）向けの規則。`.cursor/rules/*.mdc` を統合したもの。

## 42 C++ 全般ルール

### コンパイル要件

- 常に `c++` コマンドとフラグ `-Wall -Wextra -Werror` でコンパイルする
- `-std=c++98` フラグでコンパイル可能であること
- Makefile は clean, fclean, re ターゲットを含む適切な構造にする

### ファイル・ディレクトリ構造

- 課題ディレクトリ: `ex00`, `ex01`, `ex02` など
- クラスファイルは UpperCamelCase（例: `ClassName.hpp`, `ClassName.cpp`、`BrickWall.hpp`, `BrickWall.cpp`）

### 禁止関数

- 使用禁止: `*printf()`, `*alloc()`, `free()`
- 使用禁止: `using namespace <ns_name>`（明示的に許可されない限り）
- 使用禁止: `friend` キーワード（明示的に許可されない限り）
- 使用禁止: STL コンテナ/アルゴリズム（Module 08-09 まで）

### メモリ管理

- `new` を使う場合はメモリリークを避ける
- 適切なデストラクタと RAII 原則を実装する
- Module 02-09 ではクラスは Orthodox Canonical Form に従う必要がある

### ヘッダーファイル

- インクルードガード必須: `#ifndef CLASSNAME_HPP` / `#define CLASSNAME_HPP`
- ヘッダーは独立して使用可能にする（依存関係をすべて含める）
- ヘッダー内に関数実装を書かない（テンプレートを除く）

### 出力フォーマット

- すべての出力メッセージは改行文字で終わる
- 指定がない限り標準出力に表示する

### コード品質

- ピアレビュー向けに読みやすいコードを書く
- 一貫した命名規則に従う
- 作業開始前に該当モジュールのガイドラインを完全に読む

## Common C++ Patterns（42 課題向け）

### Header Guard Pattern

```cpp
#ifndef CLASSNAME_HPP
#define CLASSNAME_HPP

// class declaration

#endif
```

### Orthodox Canonical Form Pattern

```cpp
class MyClass {
private:
    // member variables

public:
    MyClass();                           // Default constructor
    MyClass(const MyClass& other);       // Copy constructor
    MyClass& operator=(const MyClass& other); // Assignment operator
    ~MyClass();                          // Destructor

    // other member functions
};
```

### Exception Class Pattern

```cpp
class MyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Error message";
    }
};
```

### Template Class Pattern

```cpp
template<typename T>
class MyTemplate {
private:
    T* _data;
    size_t _size;

public:
    MyTemplate();
    MyTemplate(size_t size);
    MyTemplate(const MyTemplate& other);
    MyTemplate& operator=(const MyTemplate& other);
    ~MyTemplate();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
};
```

### Virtual Function Pattern (Polymorphism)

```cpp
class Base {
public:
    virtual void doSomething() = 0;  // Pure virtual
    virtual ~Base();                 // Virtual destructor
};

class Derived : public Base {
public:
    void doSomething() override;     // Override implementation
};
```

### Static Member Pattern

```cpp
class MyClass {
private:
    static int _count;               // Static member variable

public:
    static int getCount();           // Static member function
};

// Definition in .cpp file
int MyClass::_count = 0;
int MyClass::getCount() { return _count; }
```

## モジュール別ルール

### Module 00-01: Basic C++ Concepts

- クラス、メンバー関数、コンストラクタ/デストラクタに焦点を当てる
- C 文字列ではなく `std::string` を使う
- private/public セクションで適切なカプセル化を実装する
- STL コンテナはまだ使わない（配列を使う）

### Module 02-09: Orthodox Canonical Form

すべてのクラスで必須：

- デフォルトコンストラクタ
- コピーコンストラクタ
- コピー代入演算子
- デストラクタ

```cpp
class MyClass {
private:
    // member variables

public:
    MyClass();                    // Default constructor
    MyClass(const MyClass& other); // Copy constructor
    MyClass& operator=(const MyClass& other); // Assignment operator
    ~MyClass();                   // Destructor
};
```

### Module 03: Inheritance

- ポリモーフィックな関数には `virtual` キーワードを使う
- 適切なコンストラクタ/デストラクタチェーンを実装する
- ダイヤモンド継承は virtual inheritance で処理する

### Module 04: Abstract Classes

- 純粋仮想関数を使う: `virtual void func() = 0;`
- インターフェースを適切に実装する
- 動的メモリを持つクラスはディープコピーを実装する

### Module 05: Exceptions

- カスタム例外クラスを作成する
- `try-catch` ブロックを適切に使う
- エラー条件では例外を投げる

### Module 06: Casts

- 適切な C++ キャストを使う: `static_cast`, `dynamic_cast`, `reinterpret_cast`
- C スタイルキャストは避ける

### Module 07: Templates

- テンプレートクラス・関数を実装する
- テンプレートのインスタンス化を適切に処理する
- 必要に応じてテンプレート特殊化を使う

### Module 08-09: STL

- STL コンテナ・アルゴリズムの使用が解禁される
- `std::vector`, `std::map`, `std::stack` などを使う
- イテレータを適切に実装する

## プロジェクト構造

### ディレクトリ構成

```
cpp/
├── cpp00/           # Module 00: Basic C++ concepts
│   ├── ex00/        # Exercise 00: Megaphone
│   ├── ex01/        # Exercise 01: PhoneBook
│   ├── ex02/        # Exercise 02: Account
│   ├── cpp00/       # Assignment PDF images
│   └── ng_4_cpp_module_00/  # Evaluation criteria
├── cpp01/           # Module 01: Memory allocation
├── cpp02/           # Module 02: Operator overloading
├── cpp03/           # Module 03: Inheritance
├── cpp04/           # Module 04: Polymorphism
├── cpp05/           # Module 05: Exceptions
├── cpp06/           # Module 06: C++ Casts
├── cpp07/           # Module 07: Templates
├── cpp08/           # Module 08: STL containers
├── cpp09/           # Module 09: STL algorithms
└── COMPREHENSIVE_EVALUATION.md
```

### Key Files

- `COMPREHENSIVE_EVALUATION.md` - Complete project evaluation
- `README.md` - Project overview
- 各モジュールは以下を含む:
  - `cppXX/` - Assignment requirements（画像）
  - `ng_4_cpp_module_XX/` - Evaluation criteria
  - `ex00/`, `ex01/` など - Exercise implementations

### Exercise Structure

各課題ディレクトリの構成：

- `Makefile` - ビルド設定
- `*.hpp` - ヘッダーファイル（クラス宣言）
- `*.cpp` - ソースファイル（クラス実装）
- `main.cpp` - テスト/デモプログラム
- 実行ファイル（コンパイル後）

### Assignment Requirements

- 課題の詳細は `cpp00/cpp00/images/` を確認する
- 評価基準は `cpp00/ng_4_cpp_module_00/images/` を確認する
- PDF 画像の仕様に正確に従う

## テストと検証

### コンパイルテスト

提出前に以下を確認する：

1. クリーンなコンパイル: `make re` が警告なく成功する
2. C++98 準拠: `-std=c++98` でコンパイルできる
3. すべてのフラグ: `-Wall -Wextra -Werror` を通過する

### よくある確認事項

- ソースファイルの不足（例: `PresidentialPardonForm.cpp`）
- 自己代入の警告（`-Wself-assign-overloaded`）
- `new`/`delete` によるメモリリーク
- インクルードガードの不足
- ヘッダー内の関数実装

### テスト戦略

1. すべての課題をコンパイルする（全モジュールを体系的にテスト）
2. 基本テストを実行する（クラッシュせず動作することを確認）
3. 出力フォーマットを確認する（改行終端を確認）
4. 課題要件をすべて満たしているか検証する

### 品質保証

- 全 10 モジュール・43 課題がすべてコンパイル成功すること
- 禁止関数（`*printf`, `*alloc`, `free`）を使用していないこと
- Orthodox Canonical Form に従った適切なクラス設計
- ピアレビュー向けの読みやすいコード

### ドキュメント

- テスト結果で評価レポートを更新する
- 修正・改善内容を記録する
- プロジェクトの状況を包括的に維持する
