# CPP07 完全理解ガイド - テンプレートプログラミング

## 🎯 学習目標

**C++テンプレートシステムの完全理解とジェネリックプログラミング技法の習得**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Start with a few functions - テンプレート関数

**所要時間**: 25 分
**核心概念**: 関数テンプレート、型推論、テンプレート特殊化

### 📖 ex01: Iter - 配列操作テンプレート

**所要時間**: 30 分
**核心概念**: テンプレート関数、イテレータ、関数オブジェクト

### 📖 ex02: Array - テンプレートクラス

**所要時間**: 40 分
**核心概念**: **クラステンプレート**、型安全なコンテナ、RAII

---

## 🔥 テンプレートの核心概念

### 関数テンプレート

```cpp
// 基本的な関数テンプレート
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 使用例
int x = 1, y = 2;
swap(x, y);  // 型推論: swap<int>

std::string s1 = "hello", s2 = "world";
swap(s1, s2);  // 型推論: swap<std::string>
```

### クラステンプレート

```cpp
template<typename T>
class Array {
private:
    T* elements;
    size_t size;

public:
    Array(size_t n) : elements(new T[n]), size(n) {}
    ~Array() { delete[] elements; }

    T& operator[](size_t index) { return elements[index]; }
    const T& operator[](size_t index) const { return elements[index]; }
};

// 使用例
Array<int> intArray(10);
Array<std::string> stringArray(5);
```

---

## 🎯 効率的学習法

### Phase 1: 関数テンプレート基礎（25 分）

1. **基本構文**と型推論を理解
2. **複数型引数**の使用方法を学習
3. **明示的インスタンス化**を理解

### Phase 2: 高度な関数テンプレート（30 分）

1. **関数オブジェクト**との組み合わせを理解
2. **配列操作**の汎用化を学習
3. **const 正確性**を保つテンプレート設計

### Phase 3: クラステンプレート（40 分）

1. **型安全なコンテナ**の設計を学習
2. **RAII 原則**をテンプレートで実装
3. **例外安全性**を考慮した設計

---

## 📊 重要な実装パターン

### SFINAE (Substitution Failure Is Not An Error)

```cpp
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
process(T value) {
    // 算術型のみ処理
    std::cout << "Processing arithmetic: " << value << std::endl;
}
```

### 型特性（Type Traits）

```cpp
template<typename T>
void smartFunction(T& obj) {
    if (std::is_pointer<T>::value) {
        // ポインタ型の処理
    } else if (std::is_reference<T>::value) {
        // 参照型の処理
    } else {
        // その他の型の処理
    }
}
```

**🎯 成功指標**: 汎用的で再利用可能なテンプレートコードを設計・実装できること

**⏱️ 目標時間**: 1.5 時間で CPP07 完全マスター達成




