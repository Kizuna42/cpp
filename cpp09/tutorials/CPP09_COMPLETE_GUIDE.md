# CPP09 完全理解ガイド - 高度な STL アルゴリズムとデータ処理

## 🎯 学習目標

**高度な STL アルゴリズムと実世界のデータ処理問題を解決し、C++プログラミングの総合力を完成**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Bitcoin Exchange - ファイル処理とデータ管理

**所要時間**: 45 分
**核心概念**: **std::map**、CSV パース、日付処理、エラーハンドリング

### 📖 ex01: Reverse Polish Notation - スタックアルゴリズム

**所要時間**: 35 分
**核心概念**: **std::stack**、数式解析、逆ポーランド記法

### 📖 ex02: PmergeMe - 高度なソートアルゴリズム

**所要時間**: 60 分
**核心概念**: **Ford-Johnson アルゴリズム**、性能測定、複数コンテナ比較

---

## 🔥 高度な STL 活用パターン

### std::map による高速データ検索

```cpp
class BitcoinExchange {
private:
    std::map<std::string, double> exchangeRates;

public:
    void loadDatabase(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        std::getline(file, line);  // ヘッダーをスキップ

        while (std::getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string date = line.substr(0, commaPos);
                double rate = std::stod(line.substr(commaPos + 1));
                exchangeRates[date] = rate;
            }
        }
    }

    double getRate(const std::string& date) {
        auto it = exchangeRates.lower_bound(date);
        if (it == exchangeRates.begin()) {
            return it->second;
        }
        --it;
        return it->second;
    }
};
```

### std::stack による数式処理

```cpp
class RPN {
public:
    static double evaluate(const std::string& expression) {
        std::stack<double> stack;
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (isOperator(token)) {
                if (stack.size() < 2) {
                    throw std::invalid_argument("Invalid expression");
                }

                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();

                double result = calculate(a, b, token[0]);
                stack.push(result);
            } else {
                stack.push(std::stod(token));
            }
        }

        if (stack.size() != 1) {
            throw std::invalid_argument("Invalid expression");
        }

        return stack.top();
    }
};
```

### Ford-Johnson ソートアルゴリズム

```cpp
template<typename Container>
class PmergeMe {
public:
    static void fordJohnsonSort(Container& container) {
        if (container.size() <= 1) return;

        // ペア作成フェーズ
        std::vector<std::pair<typename Container::value_type,
                             typename Container::value_type>> pairs;

        // マージ・挿入フェーズ
        Container mainChain;
        Container pending;

        // Jacobsthal数列に基づく最適挿入順序
        std::vector<size_t> insertionOrder = generateJacobsthalOrder(pending.size());

        for (size_t idx : insertionOrder) {
            auto pos = std::lower_bound(mainChain.begin(), mainChain.end(),
                                       pending[idx]);
            mainChain.insert(pos, pending[idx]);
        }

        container = mainChain;
    }
};
```

---

## 🎯 効率的学習法

### Phase 1: ファイル処理とデータ管理（45 分）

1. **std::map**による効率的なデータ検索を理解
2. **CSV パース**とデータバリデーション技法を学習
3. **エラーハンドリング**の包括的な実装

### Phase 2: スタック・アルゴリズム（35 分）

1. **std::stack**を活用した数式処理を理解
2. **逆ポーランド記法**の解析アルゴリズムを学習
3. **文字列パース**とトークン処理技法

### Phase 3: 高度なソートアルゴリズム（60 分）

1. **Ford-Johnson アルゴリズム**の理論と実装を理解
2. **Jacobsthal 数列**を活用した最適化を学習
3. **性能測定**とコンテナ比較手法

---

## 📊 アルゴリズム複雑度比較

| アルゴリズム        | 時間複雑度 | 空間複雑度 | 特徴               |
| ------------------- | ---------- | ---------- | ------------------ |
| **std::sort**       | O(n log n) | O(log n)   | 標準的な高速ソート |
| **Ford-Johnson**    | O(n log n) | O(n)       | 比較回数を最小化   |
| **std::map 検索**   | O(log n)   | O(n)       | 平衡二分探索木     |
| **std::stack 操作** | O(1)       | O(n)       | LIFO 構造          |

---

## 🔍 実世界への応用

### 金融データ処理

```cpp
// 時系列データの効率的な管理
std::map<std::string, double> priceHistory;

// 最近接日付検索
auto findClosestDate = [&](const std::string& targetDate) {
    auto it = priceHistory.lower_bound(targetDate);
    if (it == priceHistory.begin()) return it;

    auto prev = std::prev(it);
    if (it == priceHistory.end()) return prev;

    // より近い日付を選択
    return (targetDate - prev->first < it->first - targetDate) ? prev : it;
};
```

### 計算機エンジンの設計

```cpp
class AdvancedCalculator {
    std::map<std::string, std::function<double(double, double)>> operators;

public:
    AdvancedCalculator() {
        operators["+"] = [](double a, double b) { return a + b; };
        operators["-"] = [](double a, double b) { return a - b; };
        operators["*"] = [](double a, double b) { return a * b; };
        operators["/"] = [](double a, double b) {
            if (b == 0) throw std::domain_error("Division by zero");
            return a / b;
        };
    }

    double evaluate(const std::string& expression) {
        // RPN評価ロジック
    }
};
```

**🎯 成功指標**: 実世界のデータ処理問題を効率的に解決できる包括的な C++スキル

**⏱️ 目標時間**: 2.5 時間で CPP09 完全マスター、C++総合力完成達成




