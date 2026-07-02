# CPP05 完全理解ガイド - 例外処理・エラーハンドリング

## 🎯 学習目標

**C++例外処理システムの完全理解とエラーハンドリングのベストプラクティス習得**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Mommy, when I grow up, I want to be a bureaucrat!

**所要時間**: 30 分
**核心概念**: 基本的な例外処理、try-catch 文、カスタム例外クラス

### 📖 ex01: Form up, maggots!

**所要時間**: 35 分
**核心概念**: オブジェクト間の例外処理、相互作用、例外の伝播

### 📖 ex02: No, you need form 28B, not 28C...

**所要時間**: 40 分
**核心概念**: 抽象クラス、純粋仮想関数、ポリモーフィックな例外処理

### 📖 ex03: At least this beats coffee-making

**所要時間**: 35 分
**核心概念**: **ファクトリーパターン**、例外安全なオブジェクト生成

---

## 🔥 例外処理の核心概念

### 例外とは何か？

```cpp
// 従来のエラー処理（C言語的）
int divide(int a, int b) {
    if (b == 0) {
        return -1;  // エラーコード
    }
    return a / b;
}

// C++の例外処理
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}
```

### try-catch-throw の基本構造

```cpp
try {
    // 例外が発生する可能性のあるコード
    int result = divide(10, 0);
    std::cout << "Result: " << result << std::endl;
} catch (const std::runtime_error& e) {
    // 特定の例外をキャッチ
    std::cout << "Runtime error: " << e.what() << std::endl;
} catch (const std::exception& e) {
    // より一般的な例外をキャッチ
    std::cout << "General error: " << e.what() << std::endl;
} catch (...) {
    // 全ての例外をキャッチ
    std::cout << "Unknown error occurred" << std::endl;
}
```

---

## 🏗️ カスタム例外クラスの設計

### 基本的な例外クラス

```cpp
class GradeTooHighException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Grade is too high! (minimum grade is 1)";
    }
};

class GradeTooLowException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Grade is too low! (maximum grade is 150)";
    }
};
```

### より詳細な例外クラス

```cpp
class BureaucratException : public std::exception {
protected:
    std::string _message;
    int _grade;
    std::string _name;

public:
    BureaucratException(const std::string& name, int grade, const std::string& reason)
        : _name(name), _grade(grade) {
        _message = "Bureaucrat " + name + " (grade " +
                   std::to_string(grade) + "): " + reason;
    }

    virtual const char* what() const throw() {
        return _message.c_str();
    }

    const std::string& getName() const { return _name; }
    int getGrade() const { return _grade; }
};
```

---

## 🎯 効率的学習法

### Phase 1: 基礎例外処理（30 分）

1. **ex00 Bureaucrat**で基本的な例外処理を理解
2. **throw 文**の使い方を習得
3. **try-catch 文**の構造を理解
4. **カスタム例外クラス**の作成方法を学習

### Phase 2: オブジェクト間例外処理（35 分）

1. **ex01 Form**でオブジェクト間の例外伝播を理解
2. **例外安全性**の基本概念を学習
3. **RAII**パターンとの組み合わせを理解

### Phase 3: 高度な例外処理（75 分）

1. **ex02 AForm**で抽象クラスと例外処理を学習
2. **ex03 Intern**でファクトリーパターンと例外処理を理解
3. **例外安全なプログラム設計**を習得

---

## 🔧 重要な実装パターン

### RAII (Resource Acquisition Is Initialization)

```cpp
class FileHandler {
private:
    std::ofstream file;

public:
    FileHandler(const std::string& filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();  // 自動的にリソースを解放
        }
    }

    void write(const std::string& data) {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        file << data;
    }
};

// 使用例
void processFile(const std::string& filename) {
    try {
        FileHandler handler(filename);  // ファイルを開く
        handler.write("Hello, World!");
        // スコープ終了時に自動的にファイルが閉じられる
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

### 例外安全性のレベル

```cpp
class ExceptionSafeClass {
private:
    int* data;
    size_t size;

public:
    // 基本保証：例外発生時でもオブジェクトは有効な状態
    void basicGuarantee() {
        int* newData = new int[size * 2];
        // もしここで例外が発生しても、元のdataは有効
        try {
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            size *= 2;
        } catch (...) {
            delete[] newData;  // リソースをクリーンアップ
            throw;             // 例外を再送
        }
    }

    // 強い保証：例外発生時でも状態は変更されない
    void strongGuarantee() {
        int* newData = new int[size * 2];
        try {
            std::copy(data, data + size, newData);
            // 全ての操作が成功した場合のみ状態を変更
            delete[] data;
            data = newData;
            size *= 2;
        } catch (...) {
            delete[] newData;
            throw;
        }
    }

    // 非投出保証：例外を投出しない
    void noThrowGuarantee() throw() {
        // 例外を投出しない操作のみ
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
            size = 0;
        }
    }
};
```

---

## 📊 理解度チェックリスト

### ✅ 基礎レベル（必須）

- [ ] try-catch 文の基本構文を理解している
- [ ] throw 文を使った例外の投出ができる
- [ ] std::exception を継承したカスタム例外クラスを作成できる
- [ ] what()関数の実装方法を理解している

### ✅ 応用レベル（推奨）

- [ ] 例外の種類に応じた適切な処理ができる
- [ ] RAII パターンを使った例外安全なクラス設計ができる
- [ ] 例外安全性の 3 つのレベルを理解している
- [ ] ファクトリーパターンでの例外処理ができる

### ✅ 発展レベル（理想）

- [ ] 例外安全なプログラム全体の設計ができる
- [ ] パフォーマンスを考慮した例外処理ができる
- [ ] 複雑なオブジェクト階層での例外処理ができる

---

## ⚠️ よくある間違いと対策

### 1. 例外をキャッチして無視する

```cpp
// ❌ 間違い
try {
    dangerousOperation();
} catch (...) {
    // 何もしない - 問題を隠蔽してしまう
}

// ✅ 正しい
try {
    dangerousOperation();
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    // 適切な復旧処理またはログ記録
    throw;  // 必要に応じて例外を再送
}
```

### 2. リソースリークの発生

```cpp
// ❌ 問題のあるコード
void problematicFunction() {
    int* data = new int[1000];

    riskyOperation();  // 例外が発生する可能性

    delete[] data;  // 例外発生時に実行されない
}

// ✅ 正しい実装
void safeFunction() {
    std::unique_ptr<int[]> data(new int[1000]);

    riskyOperation();  // 例外が発生してもデストラクタで自動削除
}
```

### 3. 例外仕様の誤用

```cpp
// ❌ C++11以降では非推奨
void oldStyleFunction() throw(std::runtime_error) {
    // throw仕様は使わない
}

// ✅ 現代的なアプローチ
void modernFunction() noexcept(false) {
    // noexceptを適切に使用
}

void noThrowFunction() noexcept {
    // 例外を投出しない関数
}
```

---

## 🚀 学習の優先順位

### 🔥 最優先（必須理解）

1. **基本的な例外処理**: try-catch-throw
2. **カスタム例外クラス**: std::exception の継承
3. **RAII**: 自動リソース管理

### ⭐ 高優先（推奨理解）

1. **例外安全性**: 基本保証・強い保証
2. **例外の種類**: 適切な例外タイプの選択
3. **ファクトリーパターン**: 安全なオブジェクト生成

### 📚 中優先（発展学習）

1. **パフォーマンス考慮**: 例外処理のコスト
2. **デザインパターン**: 例外安全な設計手法

---

## 🎓 実践的な応用例

### ログシステムでの例外処理

```cpp
class Logger {
public:
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };

    class LogException : public std::exception {
    private:
        std::string message;
    public:
        LogException(const std::string& msg) : message(msg) {}
        const char* what() const throw() { return message.c_str(); }
    };

    void log(LogLevel level, const std::string& message) {
        try {
            writeToFile(formatMessage(level, message));
        } catch (const std::ios_base::failure& e) {
            throw LogException("Failed to write log: " + std::string(e.what()));
        }
    }

private:
    void writeToFile(const std::string& formattedMessage) {
        // ファイル書き込み処理
        // std::ios_base::failure が投出される可能性
    }

    std::string formatMessage(LogLevel level, const std::string& message) {
        // メッセージフォーマット処理
        return "[" + levelToString(level) + "] " + message;
    }
};
```

---

**🎯 成功指標**: 複雑なシステムで適切な例外処理を設計し、例外安全なプログラムを作成できること

**⏱️ 目標時間**: 2.5 時間で CPP05 完全マスター達成




