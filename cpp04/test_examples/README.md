# C++ Module 04 - テストケース集

このディレクトリには、評価時に使用できる実践的なテストケースが含まれています。

## 📋 テスト一覧

### Ex00: Polymorphism

#### `test_constructor_order.cpp`

**目的**: コンストラクタ/デストラクタの呼び出し順序を確認
**確認内容**:

- 基底クラス → 派生クラス の順でコンストラクタが呼ばれる
- 派生クラス → 基底クラス の順でデストラクタが呼ばれる

**実行方法**:

```bash
make test_constructor
```

**期待される出力**:

```
Animal Dog constructor called
Dog constructor called
Dog destructor called
Animal Dog destructor called
```

---

### Ex01: Brain & Deep Copy

#### `test_deep_copy_scope.cpp`

**目的**: ディープコピーが正しく動作することを確認（評価項目指定のテスト）
**確認内容**:

- スコープ内でコピーしたオブジェクトが破棄された後も、元のオブジェクトが使用可能
- シャローコピーの場合、ダングリングポインタによりクラッシュする

**実行方法**:

```bash
make test_scope
```

**成功条件**:

- プログラムがクラッシュしない
- スコープを抜けた後も元のオブジェクトの Brain が正しく動作する

---

#### `test_brain_address.cpp`

**目的**: Brain のアドレスを比較してディープコピーを確認
**確認内容**:

- コピーコンストラクタで Brain が新規作成される
- 代入演算子で Brain が新規作成される
- 元のオブジェクトとコピーが独立している

**実行方法**:

```bash
make test_address
```

**期待される結果**:

```
✅ PASS: Deep copy confirmed!
✅ PASS: Deep copy in assignment!
```

---

#### `test_virtual_destructor.cpp`

**目的**: virtual デストラクタの重要性を確認
**確認内容**:

- Animal\*経由で delete した際に、Dog/Cat のデストラクタが呼ばれる
- Brain が正しく解放される

**実行方法**:

```bash
make test_destructor
```

**期待される出力**:

```
Dog destructor called
Brain destructor called
Animal Dog destructor called
```

**もし virtual でない場合**:

- Dog デストラクタが呼ばれない
- Brain デストラクタが呼ばれない
- メモリリーク発生

---

### Ex03: Interface

#### `test_self_assignment.cpp`

**目的**: 自己代入が正しく処理されることを確認
**確認内容**:

- `character = character;` でクラッシュしない
- 自己代入後も Materia が正しく動作する

**実行方法**:

```bash
make test_assignment
```

**成功条件**:

- プログラムがクラッシュしない
- 自己代入後も Materia が使用可能

**実装のポイント**:

```cpp
Character& Character::operator=(const Character& other) {
    if (this != &other) {  // ← この自己代入チェックが必須
        // ...
    }
    return *this;
}
```

---

## 🚀 全テスト実行

すべてのテストを一度に実行:

```bash
make run_all
```

---

## 📊 テスト結果の見方

### ✅ 成功パターン

- プログラムが正常終了する
- 期待される出力が表示される
- 「✅ PASS」メッセージが表示される

### ❌ 失敗パターン

#### シャローコピーの場合:

```
Segmentation fault (core dumped)  # クラッシュ
```

#### virtual デストラクタがない場合:

```
# Dogデストラクタが表示されない
# Brainデストラクタが表示されない
# メモリリーク
```

#### 自己代入チェックがない場合:

```
Segmentation fault (core dumped)  # クラッシュ
```

---

## 🔍 メモリリークチェック

### macOS (leaks)

```bash
# 実行中のプロセスをチェック
./test_name &
leaks $!
```

### Linux (valgrind)

```bash
valgrind --leak-check=full ./test_name
```

---

## 📝 評価時の使用方法

1. **テストをコンパイル**:

   ```bash
   cd test_examples
   make test_scope
   ```

2. **結果を確認**:

   - 出力を見て、期待される動作をしているか確認
   - メモリリークがないか確認

3. **コードを確認**:
   - テストファイルを開いて、何をテストしているか説明
   - 実装がどうなっているべきか議論

---

## 🎯 よくある質問への回答確認

### Ex00: コンストラクタの順序

**質問**: 「Dog を作成すると、どの順序でコンストラクタが呼ばれますか？」
**確認**: `make test_constructor` の出力を見せる

### Ex01: ディープコピーの必要性

**質問**: 「なぜディープコピーが必要ですか？」
**確認**: `make test_scope` でシャローコピーだとクラッシュすることを説明

### Ex01: virtual デストラクタ

**質問**: 「なぜデストラクタを virtual にする必要がありますか？」
**確認**: `make test_destructor` で正しくデストラクタが呼ばれることを示す

### Ex03: 自己代入

**質問**: 「自己代入のチェックは必要ですか？」
**確認**: `make test_assignment` で自己代入が正しく処理されることを示す

---

## 🛠️ トラブルシューティング

### コンパイルエラー

```bash
# 各エクササイズが正しくコンパイルされているか確認
cd ../ex00 && make
cd ../ex01 && make
cd ../ex02 && make
cd ../ex03 && make
```

### テストが動作しない

- パスが正しいか確認（`../ex00/`, `../ex01/` など）
- 必要なクラスがすべて実装されているか確認

---

## 📚 参考情報

評価時の詳細な質問と模範解答は、親ディレクトリの `評価項目＋質問.md` を参照してください。

このファイルには以下が含まれます:

- 評価項目の詳細
- 想定問答集
- よくある実装ミス
- 追加の技術的説明（vtable、Rule of Three、Prototype パターンなど）
