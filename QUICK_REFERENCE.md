# C++学習クイックリファレンス - 即座参照用

## 🚀 注釈付きチュートリアルファイル一覧

### 📚 CPP01: メモリ管理・ポインタ・参照
**Location**: `cpp01/tutorials/`

| File | 概要 | 所要時間 | 重要度 |
|------|------|----------|--------|
| `CPP01_COMPLETE_GUIDE.md` | 全体ガイド | 15分 | ⭐⭐⭐ |
| `ex00/TUTORIAL_Zombie.hpp` | クラス設計理論 | 15分 | ⭐⭐⭐ |
| `ex00/TUTORIAL_Zombie.cpp` | 実装とRAII | 15分 | ⭐⭐⭐ |
| `ex00/TUTORIAL_newZombie.cpp` | ヒープ管理 | 10分 | ⭐⭐⭐ |
| `ex00/TUTORIAL_randomChump.cpp` | スタック管理 | 10分 | ⭐⭐⭐ |
| `ex00/TUTORIAL_main.cpp` | 使用例・比較 | 15分 | ⭐⭐ |
| `ex01/TUTORIAL_zombieHorde.cpp` | 動的配列 | 15分 | ⭐⭐⭐ |

**合計所要時間**: 95分（1時間35分）

---

## ⚡ 核心概念チートシート

### 🧠 CPP01: メモリ管理
```cpp
// スタック（自動管理）
{
    Zombie zombie("Alice");  // コンストラクタ呼び出し
    zombie.announce();       // 使用
}   // ← デストラクタ自動呼び出し

// ヒープ（手動管理）
Zombie* zombie = new Zombie("Bob");  // コンストラクタ呼び出し
zombie->announce();                  // 使用
delete zombie;                       // デストラクタ手動呼び出し

// 動的配列
Zombie* horde = new Zombie[5];       // デフォルトコンストラクタ×5
// ... 使用 ...
delete[] horde;                      // デストラクタ×5 + メモリ解放
```

### 🎯 使い分け判断基準
| 場面 | 選択 | 理由 |
|------|------|------|
| 関数内での一時使用 | スタック変数 | 自動管理、高速 |
| 関数をまたぐ使用 | ヒープ変数 | 生存期間制御可能 |
| サイズが実行時決定 | 動的配列 | 柔軟性 |
| 常に有効な参照 | 参照 | シンプル、安全 |
| null可能性あり | ポインタ | 柔軟性 |

### 🚫 よくある間違い
```cpp
// ❌ 間違い
Zombie* horde = new Zombie[5];
delete horde;        // 配列なのにdelete（未定義動作）

// ❌ 間違い  
Zombie* zombie = new Zombie("Test");
delete[] zombie;     // 単体なのにdelete[]（未定義動作）

// ❌ 間違い
{
    Zombie* zombie = new Zombie("Test");
}   // delete忘れ（メモリリーク）

// ✅ 正しい
Zombie* horde = new Zombie[5];
delete[] horde;      // 配列はdelete[]

Zombie* zombie = new Zombie("Test");  
delete zombie;       // 単体はdelete
```

---

## 📊 理解度確認チェックリスト

### ✅ 即答できるべき質問
- [ ] スタック変数はいつ削除されるか？
- [ ] ヒープ変数はいつ削除されるか？
- [ ] new[]で確保したメモリはどう解放するか？
- [ ] ポインタと参照の構文的違いは？
- [ ] RAIIとは何か？
- [ ] メモリリークはなぜ起こるか？

### ✅ 実装できるべきタスク
- [ ] スタック変数でのZombie作成・使用
- [ ] ヒープ変数でのZombie作成・使用・削除
- [ ] 動的配列でのZombieHorde作成・初期化・削除
- [ ] 参照とポインタの使い分け実装

---

## 🔧 デバッグ・確認コマンド

### コンパイル（厳密チェック）
```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```

### メモリリーク検出（macOS）
```bash
# AddressSanitizer使用
c++ -fsanitize=address -g *.cpp -o program
./program
```

### メモリリーク検出（Linux）
```bash
# valgrind使用  
valgrind --leak-check=full ./program
```

### 実行時ログ確認
```bash
./program 2>&1 | tee output.log
# "created" と "destroyed" の数を比較
grep "created" output.log | wc -l
grep "destroyed" output.log | wc -l
```

---

## 🎯 学習の優先順位

### 🔥 最優先（必須理解）
1. **ex00 Zombie基礎**: スタック vs ヒープの本質
2. **ex01 ZombieHorde**: 動的配列の管理
3. **RAII概念**: 自動リソース管理

### ⭐ 高優先（推奨理解）  
1. **ポインタ vs 参照**: 設計判断基準
2. **メンバ関数ポインタ**: 動的処理選択
3. **エラーハンドリング**: 堅牢性向上

### 📚 中優先（発展学習）
1. **ファイル処理**: 実用的スキル
2. **制御構造**: 効率的な分岐処理

---

## 🚀 効率的学習の進め方

### Step 1: 理論理解（60分）
1. `CPP01_COMPLETE_GUIDE.md` で全体把握
2. 各TUTORIAL_*.hppでクラス設計理解  
3. 各TUTORIAL_*.cppで実装詳細理解

### Step 2: 実践確認（30分）
1. 実際のコンパイル・実行
2. デバッガーでメモリ状態確認
3. 意図的エラーでメモリリーク体験

### Step 3: 理解度確認（5分）
1. チェックリスト項目の確認
2. 口頭での説明練習
3. 他の人への教授準備

---

## 💡 学習加速のコツ

### 🎯 集中力維持
- **一つずつ完全理解**: 中途半端に次に進まない
- **実際に動かす**: 理論だけでなく実践で確認
- **なぜを重視**: 実装の理由を常に考える

### 🧠 記憶定着
- **声に出す**: 理解した内容を声に出して説明
- **図解作成**: メモリレイアウトを図で描く
- **類推活用**: 既知の概念との類似点を見つける

---

**🎉 成功指標**: このクイックリファレンスを見ずに、全ての概念を他の人に教えることができる状態

**⏰ 目標時間**: 2時間でCPP01完全マスター達成