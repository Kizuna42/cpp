# CPP08 完全理解ガイド - STL コンテナとアルゴリズム

## 🎯 学習目標

**STL コンテナとアルゴリズムの実践的活用法を習得し、現代的な C++プログラミングスタイルをマスター**

---

## 📚 学習構成（推奨順序）

### 📖 ex00: Easy find - STL アルゴリズム活用

**所要時間**: 20 分
**核心概念**: **std::find**、イテレータ、汎用検索アルゴリズム

### 📖 ex01: Span - カスタムコンテナ設計

**所要時間**: 35 分
**核心概念**: **std::vector**、カスタム例外、統計処理

### 📖 ex02: Mutated abomination - STL 拡張

**所要時間**: 30 分
**核心概念**: **継承による STL 拡張**、イテレータ公開、std::stack

---

## 🔥 STL の核心概念

### STL アルゴリズムの活用

```cpp
#include <algorithm>
#include <vector>
#include <list>

template<typename Container>
typename Container::iterator easyfind(Container& container, int value) {
    typename Container::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw std::exception();
    }
    return it;
}

// 使用例
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = easyfind(vec, 3);  // 3を検索
```

### カスタムコンテナ設計

```cpp
class Span {
private:
    std::vector<int> numbers;
    unsigned int maxSize;

public:
    Span(unsigned int N) : maxSize(N) {}

    void addNumber(int number) {
        if (numbers.size() >= maxSize) {
            throw TooManyNumbersException();
        }
        numbers.push_back(number);
    }

    unsigned int shortestSpan() const {
        if (numbers.size() < 2) {
            throw NotEnoughNumbersException();
        }

        std::vector<int> sorted = numbers;
        std::sort(sorted.begin(), sorted.end());

        unsigned int minSpan = UINT_MAX;
        for (size_t i = 1; i < sorted.size(); ++i) {
            unsigned int span = sorted[i] - sorted[i-1];
            if (span < minSpan) {
                minSpan = span;
            }
        }
        return minSpan;
    }
};
```

### STL 継承による機能拡張

```cpp
template<typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};

// 使用例
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);

// イテレータでアクセス可能
for (auto it = mstack.begin(); it != mstack.end(); ++it) {
    std::cout << *it << std::endl;
}
```

---

## 🎯 効率的学習法

### Phase 1: STL アルゴリズム基礎（20 分）

1. **std::find**と基本的な検索アルゴリズムを理解
2. **イテレータ**の概念と使用方法を学習
3. **例外処理**を含む汎用関数設計

### Phase 2: カスタムコンテナ設計（35 分）

1. **std::vector**を活用したデータ管理
2. **カスタム例外クラス**の設計と活用
3. **STL アルゴリズム**（std::sort）の実践的使用

### Phase 3: STL 拡張テクニック（30 分）

1. **継承による STL 拡張**の設計パターン
2. **protected メンバーアクセス**の理解
3. **イテレータ公開**による機能追加

---

## 📊 重要な STL コンテナ比較

| コンテナ        | 特徴         | 適用場面                       | アクセス時間 |
| --------------- | ------------ | ------------------------------ | ------------ |
| **std::vector** | 動的配列     | 順次アクセス、ランダムアクセス | O(1)         |
| **std::list**   | 双方向リスト | 挿入・削除が頻繁               | O(n)         |
| **std::deque**  | 両端キュー   | 前後からの挿入・削除           | O(1)         |
| **std::stack**  | LIFO 構造    | 後入れ先出し処理               | O(1)         |
| **std::map**    | 連想配列     | キー検索、ソート済み           | O(log n)     |

---

## 🔍 高度な STL テクニック

### Lambda 式との組み合わせ

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};

// 条件に合う要素を検索
auto it = std::find_if(numbers.begin(), numbers.end(),
                       [](int n) { return n > 3; });

// 変換処理
std::transform(numbers.begin(), numbers.end(), numbers.begin(),
               [](int n) { return n * 2; });
```

### アルゴリズムチェーン

```cpp
std::vector<int> data = {5, 2, 8, 1, 9};

// ソート → 重複削除 → 出力
std::sort(data.begin(), data.end());
auto last = std::unique(data.begin(), data.end());
data.erase(last, data.end());

std::for_each(data.begin(), data.end(),
              [](int n) { std::cout << n << " "; });
```

**🎯 成功指標**: STL を活用した効率的なデータ処理と、独自コンテナ設計ができること

**⏱️ 目標時間**: 1.5 時間で CPP08 完全マスター達成




