# CPP06 完全理解ガイド - 型変換・キャスト演算子

## 🎯 学習目標

**C++の型変換システムとキャスト演算子の完全理解と ROI 安全な実装**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Conversion of scalar types

**所要時間**: 40 分
**核心概念**: スカラー型変換、静的キャスト、型検出と変換

### 📖 ex01: Serialization

**所要時間**: 25 分
**核心概念**: **reinterpret_cast**、ポインタ変換、シリアライゼーション

### 📖 ex02: Identify real type

**所要時間**: 30 分
**核心概念**: **dynamic_cast**、RTTI、実行時型識別

---

## 🔥 C++キャストの核心概念

### 4 つのキャスト演算子

```cpp
// 1. static_cast - 明示的な型変換
double d = 3.14;
int i = static_cast<int>(d);  // 3

// 2. reinterpret_cast - ポインタ/参照の再解釈
int value = 42;
void* ptr = &value;
int* intPtr = reinterpret_cast<int*>(ptr);

// 3. dynamic_cast - 安全なダウンキャスト
Base* basePtr = new Derived();
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

// 4. const_cast - const属性の除去
const int constValue = 100;
int* nonConstPtr = const_cast<int*>(&constValue);
```

### C 言語的キャストとの違い

```cpp
// C言語的キャスト（危険）
int i = (int)3.14;
char* str = (char*)&i;

// C++的キャスト（安全・明示的）
int i = static_cast<int>(3.14);
char* str = reinterpret_cast<char*>(&i);
```

---

## 🔧 スカラー型変換の詳細実装

### 型検出システム

```cpp
class ScalarConverter {
private:
    enum Type {
        CHAR_TYPE,
        INT_TYPE,
        FLOAT_TYPE,
        DOUBLE_TYPE,
        PSEUDO_LITERAL,
        INVALID_TYPE
    };

    static Type detectType(const std::string& literal) {
        if (isPseudoLiteral(literal)) return PSEUDO_LITERAL;
        if (isChar(literal)) return CHAR_TYPE;
        if (isInt(literal)) return INT_TYPE;
        if (isFloat(literal)) return FLOAT_TYPE;
        if (isDouble(literal)) return DOUBLE_TYPE;
        return INVALID_TYPE;
    }

public:
    static void convert(const std::string& literal) {
        Type type = detectType(literal);

        switch (type) {
            case CHAR_TYPE:
                convertFromChar(parseChar(literal));
                break;
            case INT_TYPE:
                convertFromInt(parseInt(literal));
                break;
            // ... 他の型
        }
    }
};
```

### 安全な型変換の実装

```cpp
template<typename From, typename To>
class SafeCast {
public:
    static bool canCast(From value) {
        return value >= std::numeric_limits<To>::min() &&
               value <= std::numeric_limits<To>::max();
    }

    static To cast(From value) {
        if (!canCast<From, To>(value)) {
            throw std::overflow_error("Cast would cause overflow");
        }
        return static_cast<To>(value);
    }
};
```

---

## 💾 シリアライゼーションと reinterpret_cast

### 基本的なシリアライゼーション

```cpp
class Serializer {
public:
    // ポインタを整数値に変換
    static uintptr_t serialize(Data* ptr) {
        return reinterpret_cast<uintptr_t>(ptr);
    }

    // 整数値をポインタに復元
    static Data* deserialize(uintptr_t raw) {
        return reinterpret_cast<Data*>(raw);
    }
};
```

### 高度なシリアライゼーション例

```cpp
class AdvancedSerializer {
private:
    struct SerializedData {
        uint64_t pointer;
        uint32_t checksum;
        uint32_t typeId;
    };

public:
    template<typename T>
    static SerializedData serialize(T* object) {
        SerializedData data;
        data.pointer = reinterpret_cast<uintptr_t>(object);
        data.checksum = calculateChecksum(object, sizeof(T));
        data.typeId = getTypeId<T>();
        return data;
    }

    template<typename T>
    static T* deserialize(const SerializedData& data) {
        if (data.typeId != getTypeId<T>()) {
            throw std::runtime_error("Type mismatch in deserialization");
        }

        T* object = reinterpret_cast<T*>(data.pointer);

        if (calculateChecksum(object, sizeof(T)) != data.checksum) {
            throw std::runtime_error("Checksum mismatch");
        }

        return object;
    }
};
```

---

## 🔍 実行時型識別（RTTI）

### dynamic_cast の動作原理

```cpp
class Base {
public:
    virtual ~Base() {}  // 仮想デストラクタが必要
};

class Derived : public Base {
public:
    void specificMethod() { /* Derived固有のメソッド */ }
};

void identifyType(Base* obj) {
    // ポインタ版dynamic_cast
    Derived* derived = dynamic_cast<Derived*>(obj);
    if (derived != nullptr) {
        std::cout << "Object is Derived" << std::endl;
        derived->specificMethod();
    } else {
        std::cout << "Object is not Derived" << std::endl;
    }
}

void identifyTypeByReference(Base& obj) {
    try {
        // 参照版dynamic_cast（例外を投出）
        Derived& derived = dynamic_cast<Derived&>(obj);
        std::cout << "Reference is Derived" << std::endl;
        derived.specificMethod();
    } catch (const std::bad_cast& e) {
        std::cout << "Reference is not Derived: " << e.what() << std::endl;
    }
}
```

### typeid による型情報取得

```cpp
#include <typeinfo>

void analyzeType(Base* obj) {
    std::cout << "Static type: " << typeid(Base*).name() << std::endl;

    if (obj) {
        std::cout << "Dynamic type: " << typeid(*obj).name() << std::endl;

        // 型の比較
        if (typeid(*obj) == typeid(Derived)) {
            std::cout << "Object is exactly Derived type" << std::endl;
        }
    }
}
```

---

## 🎯 効率的学習法

### Phase 1: 基礎型変換（40 分）

1. **ex00 ScalarConverter**で基本的な型変換を理解
2. **static_cast**の使用方法を習得
3. **型検出アルゴリズム**の実装を学習
4. **オーバーフロー検出**の実装を理解

### Phase 2: ポインタ変換（25 分）

1. **ex01 Serializer**で reinterpret_cast を理解
2. **ポインタのシリアライゼーション**を学習
3. **メモリレイアウト**の理解を深める

### Phase 3: 動的型識別（30 分）

1. **ex02 Base hierarchy**で dynamic_cast を理解
2. **RTTI**の仕組みを学習
3. **実行時型安全性**を習得

---

## 📊 理解度チェックリスト

### ✅ 基礎レベル（必須）

- [ ] 4 つのキャスト演算子の違いを理解している
- [ ] static_cast の適切な使用場面を知っている
- [ ] reinterpret_cast の危険性を理解している
- [ ] dynamic_cast の条件（仮想関数が必要）を知っている

### ✅ 応用レベル（推奨）

- [ ] 型変換での精度損失を検出できる
- [ ] シリアライゼーションの実装ができる
- [ ] RTTI を使った安全な型識別ができる
- [ ] const_cast の適切な使用ができる

### ✅ 発展レベル（理想）

- [ ] 型安全なプログラム設計ができる
- [ ] テンプレートを使った汎用的な型変換ができる
- [ ] パフォーマンスを考慮したキャスト選択ができる

---

## ⚠️ よくある間違いと対策

### 1. C 言語的キャストの乱用

```cpp
// ❌ 危険なC言語的キャスト
double d = 3.14;
int* ptr = (int*)&d;  // 未定義動作の可能性

// ✅ 適切なC++キャスト
double d = 3.14;
int* ptr = reinterpret_cast<int*>(&d);  // 意図が明確
```

### 2. dynamic_cast の誤用

```cpp
// ❌ 仮想関数なしでdynamic_cast
class NonPolymorphic {
    // 仮想関数なし
};

NonPolymorphic* obj = new NonPolymorphic();
// dynamic_cast<AnotherType*>(obj);  // コンパイルエラー

// ✅ 正しいポリモーフィッククラス
class Polymorphic {
public:
    virtual ~Polymorphic() {}  // 仮想デストラクタ
};
```

### 3. const_cast の悪用

```cpp
// ❌ const_castの悪用
const int constValue = 42;
int* ptr = const_cast<int*>(&constValue);
*ptr = 100;  // 未定義動作！

// ✅ 適切なconst_cast使用
void legacyFunction(char* str);  // 古いAPI

void modernWrapper(const std::string& str) {
    // 読み取り専用であることがわかっている場合のみ
    legacyFunction(const_cast<char*>(str.c_str()));
}
```

---

## 🚀 学習の優先順位

### 🔥 最優先（必須理解）

1. **static_cast**: 最も頻繁に使用する安全なキャスト
2. **dynamic_cast**: ポリモーフィズムでの型安全性
3. **型変換の安全性**: オーバーフロー・精度損失の検出

### ⭐ 高優先（推奨理解）

1. **reinterpret_cast**: 低レベルプログラミングでの使用
2. **RTTI**: 実行時型情報の活用
3. **シリアライゼーション**: データの永続化

### 📚 中優先（発展学習）

1. **const_cast**: const 修飾の操作
2. **テンプレート型変換**: 汎用的な型操作
3. **パフォーマンス最適化**: キャストのコスト

---

## 🎓 実践的な応用例

### ファクトリーパターンでの型変換

```cpp
class ObjectFactory {
public:
    enum ObjectType { TYPE_A, TYPE_B, TYPE_C };

    template<typename T>
    static T* create(ObjectType type) {
        Base* obj = createBase(type);

        T* result = dynamic_cast<T*>(obj);
        if (!result) {
            delete obj;
            throw std::runtime_error("Invalid type conversion");
        }

        return result;
    }

private:
    static Base* createBase(ObjectType type) {
        switch (type) {
            case TYPE_A: return new DerivedA();
            case TYPE_B: return new DerivedB();
            case TYPE_C: return new DerivedC();
            default: return nullptr;
        }
    }
};
```

---

**🎯 成功指標**: 適切なキャスト演算子を選択し、型安全なプログラムを設計・実装できること

**⏱️ 目標時間**: 1.5 時間で CPP06 完全マスター達成




