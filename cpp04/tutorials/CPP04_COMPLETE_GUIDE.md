# CPP04 完全理解ガイド - ポリモーフィズム・抽象クラス・インターフェース

## 🎯 学習目標
**実行時ポリモーフィズム、純粋仮想関数、抽象クラス、インターフェース設計の完全理解**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Polymorphism - Animal階層の基礎
**所要時間**: 25分
**核心概念**: 仮想関数、vtable、ポリモーフィックな動作

### 📖 ex01: I don't want to set the world on fire - Brain と深いコピー
**所要時間**: 30分
**核心概念**: 深いコピー、リソース管理、コピーコンストラクタの重要性

### 📖 ex02: Abstract class - 純粋仮想関数
**所要時間**: 20分
**核心概念**: 抽象クラス、インスタンス化不可、設計の強制

### 📖 ex03: Interface & recap - Materia システム
**所要時間**: 45分
**核心概念**: **インターフェース設計**、複雑なオブジェクト関係、メモリ管理

---

## 🔥 ポリモーフィズムの核心

### コンパイル時 vs 実行時ポリモーフィズム

```cpp
// コンパイル時ポリモーフィズム（関数オーバーロード）
void print(int x);     // 異なる型
void print(float x);   // に対して
void print(string x);  // 異なる関数

// 実行時ポリモーフィズム（仮想関数）
class Animal {
public:
    virtual void makeSound() = 0;  // 純粋仮想関数
};

class Dog : public Animal {
public:
    void makeSound() override { cout << "Woof!" << endl; }
};

class Cat : public Animal {
public:
    void makeSound() override { cout << "Meow!" << endl; }
};

// 実行時に適切な関数が選択される
Animal* animal = new Dog();
animal->makeSound();  // "Woof!" が出力される
```

### vtable（仮想関数テーブル）の仕組み

```
Animal vtable:
├── makeSound() → Animal::makeSound (純粋仮想)

Dog vtable:
├── makeSound() → Dog::makeSound

Cat vtable:
├── makeSound() → Cat::makeSound

実行時：
animal->makeSound() 
  ↓
animal のvtableを参照
  ↓
Dog::makeSound を呼び出し
```

---

## 🧠 深いコピー vs 浅いコピー

### 浅いコピーの問題

```cpp
class Brain {
private:
    string* ideas;  // 動的配列
    
public:
    // デフォルトコピーコンストラクタ（浅いコピー）
    // Brain(const Brain& other) : ideas(other.ideas) {}
    //   ↑ 問題：同じアドレスを共有！
};

Brain a;
Brain b = a;  // 浅いコピー
// a と b の ideas が同じメモリを指す
// どちらかのデストラクタで削除すると、もう一方が無効なポインタを持つ
```

### 深いコピーの解決

```cpp
class Brain {
private:
    string* ideas;
    
public:
    // 深いコピーの実装
    Brain(const Brain& other) {
        ideas = new string[100];
        for (int i = 0; i < 100; i++) {
            ideas[i] = other.ideas[i];  // 値をコピー
        }
    }
    
    // 代入演算子も深いコピー
    Brain& operator=(const Brain& other) {
        if (this != &other) {
            delete[] ideas;             // 既存のメモリを解放
            ideas = new string[100];    // 新しいメモリを確保
            for (int i = 0; i < 100; i++) {
                ideas[i] = other.ideas[i];  // 値をコピー
            }
        }
        return *this;
    }
};
```

---

## 🏗️ 抽象クラス vs インターフェース

### 抽象クラス（Abstract Class）

```cpp
class AAnimal {  // 抽象クラス
protected:
    string type;
    
public:
    AAnimal(const string& type) : type(type) {}
    virtual ~AAnimal() {}
    
    // 純粋仮想関数 → 派生クラスで必ず実装
    virtual void makeSound() const = 0;
    
    // 通常の仮想関数 → オーバーライド可能
    virtual void move() const { cout << "Moving..." << endl; }
    
    // 非仮想関数 → 共通実装
    const string& getType() const { return type; }
};

// AAnimal obj;  // エラー！インスタンス化不可
```

### インターフェース（Pure Interface）

```cpp
class ICharacter {  // インターフェース
public:
    virtual ~ICharacter() {}
    virtual const string& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};

// 全てのメンバが純粋仮想関数
// 実装は一切含まない
// 契約（contract）を定義する
```

---

## 🎯 効率的学習法

### Phase 1: ポリモーフィズム基礎（25分）
1. **ex00 Animal**で仮想関数の動作を理解
2. **vtableの概念**を実際のコードで確認
3. **仮想デストラクタ**の必要性を体験

### Phase 2: リソース管理（30分）
1. **ex01 Brain**で深いコピーの重要性を理解
2. **メモリ管理**の責任を明確化
3. **RAII**の実践的応用を学習

### Phase 3: 抽象化マスター（65分）
1. **ex02 AAnimal**で抽象クラスの概念を理解
2. **ex03 Materia**で複雑なインターフェース設計を学習
3. **実際のシステム設計**での応用を体験

---

## 🔧 重要な実装パターン

### 抽象基底クラス設計

```cpp
class AMateria {
protected:
    string type;
    
public:
    AMateria(const string& type) : type(type) {}
    AMateria(const AMateria& other) : type(other.type) {}
    virtual ~AMateria() {}  // 仮想デストラクタ必須
    
    const string& getType() const { return type; }
    
    // 純粋仮想関数：派生クラスで必ず実装
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target) = 0;
};
```

### インターフェース実装

```cpp
class Character : public ICharacter {
private:
    string name;
    AMateria* inventory[4];
    
public:
    Character(const string& name) : name(name) {
        for (int i = 0; i < 4; i++) {
            inventory[i] = nullptr;
        }
    }
    
    // インターフェースの全メソッドを実装
    const string& getName() const override { return name; }
    void equip(AMateria* m) override { /* 実装 */ }
    void unequip(int idx) override { /* 実装 */ }
    void use(int idx, ICharacter& target) override { /* 実装 */ }
};
```

### Factory Pattern の実装

```cpp
class MateriaSource : public IMateriaSource {
private:
    AMateria* templates[4];
    
public:
    void learnMateria(AMateria* m) override {
        // テンプレートとして保存
        for (int i = 0; i < 4; i++) {
            if (!templates[i]) {
                templates[i] = m;
                break;
            }
        }
    }
    
    AMateria* createMateria(const string& type) override {
        // テンプレートから新しいインスタンスを作成
        for (int i = 0; i < 4; i++) {
            if (templates[i] && templates[i]->getType() == type) {
                return templates[i]->clone();  // ポリモーフィックなコピー
            }
        }
        return nullptr;
    }
};
```

---

## 📊 理解度チェックリスト

### ✅ 基礎レベル（必須）
- [ ] 仮想関数とvtableの基本概念を理解している
- [ ] 純粋仮想関数と抽象クラスの違いを理解している
- [ ] 深いコピーと浅いコピーの問題を理解している
- [ ] 仮想デストラクタの必要性を理解している

### ✅ 応用レベル（推奨）
- [ ] インターフェース分離の原則を理解している
- [ ] Factory Patternの基本的な実装ができる
- [ ] 適切なポリモーフィックな設計ができる
- [ ] メモリ管理を考慮したクラス設計ができる

### ✅ 発展レベル（理想）
- [ ] 複雑なオブジェクト関係を適切に設計できる
- [ ] SOLID原則を実践したクラス設計ができる
- [ ] 実際のプロジェクトでインターフェースを活用できる

---

## ⚠️ よくある間違いと対策

### 1. 仮想デストラクタ忘れ

```cpp
// ❌ 間違い
class Base {
public:
    ~Base() {}  // 非仮想
};

Base* obj = new Derived();
delete obj;  // Derivedのデストラクタが呼ばれない！

// ✅ 正しい
class Base {
public:
    virtual ~Base() {}  // 仮想デストラクタ
};
```

### 2. 浅いコピーによるメモリ問題

```cpp
// ❌ 問題のあるクラス
class MyClass {
    int* data;
public:
    MyClass() : data(new int[100]) {}
    ~MyClass() { delete[] data; }
    // コピーコンストラクタと代入演算子が未定義
    // → デフォルトの浅いコピーが使われる
};

MyClass a;
MyClass b = a;  // 浅いコピー！
// スコープ終了時に二重削除エラー

// ✅ 正しい実装
class MyClass {
    int* data;
public:
    MyClass() : data(new int[100]) {}
    MyClass(const MyClass& other) : data(new int[100]) {
        std::copy(other.data, other.data + 100, data);
    }
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            std::copy(other.data, other.data + 100, data);
        }
        return *this;
    }
    ~MyClass() { delete[] data; }
};
```

### 3. インターフェース違反

```cpp
// ❌ インターフェース違反
class BadCharacter : public ICharacter {
    // getName() を実装し忘れ
    // → コンパイルエラー
};

// ✅ 完全な実装
class GoodCharacter : public ICharacter {
    // インターフェースの全メソッドを実装
    const string& getName() const override { return name; }
    void equip(AMateria* m) override { /* 実装 */ }
    void unequip(int idx) override { /* 実装 */ }
    void use(int idx, ICharacter& target) override { /* 実装 */ }
};
```

---

## 🚀 学習の優先順位

### 🔥 最優先（必須理解）
1. **ポリモーフィズム**: オブジェクト指向の核心
2. **抽象クラス**: 設計の強制力
3. **深いコピー**: メモリ安全性

### ⭐ 高優先（推奨理解）
1. **インターフェース設計**: 疎結合の実現
2. **Factory Pattern**: オブジェクト生成の抽象化
3. **RAII**: リソース管理の自動化

### 📚 中優先（発展学習）
1. **SOLID原則**: 高品質なOOP設計
2. **デザインパターン**: 実用的な設計手法

---

## 🎓 実践的な応用例

### ゲームエンジンでの活用

```cpp
// 描画システムのインターフェース
class IRenderer {
public:
    virtual ~IRenderer() {}
    virtual void render(const Scene& scene) = 0;
    virtual void clear() = 0;
};

// 具体的な実装
class OpenGLRenderer : public IRenderer {
public:
    void render(const Scene& scene) override {
        // OpenGL固有の描画処理
    }
    void clear() override {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

class DirectXRenderer : public IRenderer {
public:
    void render(const Scene& scene) override {
        // DirectX固有の描画処理
    }
    void clear() override {
        // DirectX固有のクリア処理
    }
};

// 使用側はインターフェースのみに依存
class Game {
    IRenderer* renderer;
public:
    Game(IRenderer* r) : renderer(r) {}
    void update() {
        renderer->clear();
        renderer->render(currentScene);
    }
};
```

---

**🎯 成功指標**: Materiaシステムの設計意図を説明し、独自のインターフェースベースシステムを設計・実装できること

**⏱️ 目標時間**: 2時間でCPP04完全マスター達成