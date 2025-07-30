# C++ Modules 01-04 並行開発タスク管理

## プロジェクト概要
42 School C++カリキュラム モジュール01-04の並行実装プロジェクト。ng_4_cpp評価基準を完全統合した包括的開発計画。

## 実装戦略
- **並行開発**: 全4モジュールを同時進行で効率的に実装
- **段階的マージ**: feature/cpp0X-implementationブランチから統合テスト
- **品質重視**: メモリリーク0、C++98準拠、ng_4_cpp評価基準クリア

## タスクリスト

### 🏗️ インフラストラクチャ（High Priority）
- [x] 並行開発用featureブランチ作成 (feature/cpp01-implementation, feature/cpp02-implementation等)

### 📚 CPP01: Memory allocation, pointers to members, references, switch
#### 基本課題（High Priority）
- [x] CPP01/ex00: Zombie クラス実装 (スタック vs ヒープメモリ管理)
  - **評価要点**: new/delete正しい使用、メモリリーク検証
  - **時間予想**: 45分
- [x] CPP01/ex01: ZombieHorde 配列動的アロケーション実装
  - **評価要点**: 配列動的確保、適切な解放順序
  - **時間予想**: 30分
- [x] CPP01/ex02: ポインタと参照比較デモプログラム
  - **評価要点**: アドレス表示、&演算子理解
  - **時間予想**: 20分
- [x] CPP01/ex03: Weapon/HumanA/HumanB クラス (参照 vs ポインタ設計)
  - **評価要点**: 参照初期化、ポインタNULLチェック
  - **時間予想**: 60分
- [x] CPP01/ex04: ファイル文字列置換プログラム
  - **評価要点**: ファイルI/O、文字列操作、エラーハンドリング
  - **時間予想**: 45分
- [x] CPP01/ex05: Harl クラス (ポインタ to メンバー関数)
  - **評価要点**: メンバー関数ポインタ配列、適切な呼び出し
  - **時間予想**: 40分

#### 発展課題（Medium Priority）
- [x] CPP01/ex06: Harl フィルター (switch文実装)
  - **評価要点**: switch文フォールスルー、適切なログレベル処理
  - **時間予想**: 30分

### 🔧 CPP02: Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form
#### 基本課題（High Priority）
- [x] CPP02/ex00: Fixed クラス基本実装 (Orthodox Canonical Form)
  - **評価要点**: OCF完全実装、適切なbit操作、コンストラクタ/デストラクタメッセージ
  - **時間予想**: 60分
- [x] CPP02/ex01: Fixed クラス型変換コンストラクタ・演算子
  - **評価要点**: int/float変換、toInt/toFloat実装、精度保持
  - **時間予想**: 45分
- [x] CPP02/ex02: Fixed クラス算術・比較演算子フルセット
  - **評価要点**: 全演算子オーバーロード、前置/後置++/--, min/max静的関数
  - **時間予想**: 90分

#### 発展課題（Low Priority）
- [ ] CPP02/ex03: BSP (Binary Space Partitioning) - オプション実装
  - **評価要点**: 点と三角形の内外判定、Fixed演算活用
  - **時間予想**: 120分

### 🧬 CPP03: Inheritance
#### 継承階層構築（High Priority）
- [ ] CPP03/ex00: ClapTrap クラス実装 (基本継承の基盤)
  - **評価要点**: private属性、attack/takeDamage/beRepaired実装、適切な初期値
  - **ng_4_cpp要件**: name, hit points, energy points, attack damage属性
  - **時間予想**: 45分
- [ ] CPP03/ex01: ScavTrap クラス実装 (public継承、protected属性)
  - **評価要点**: public継承、protected変更、コンストラクタ/デストラクタ順序、guardGate()
  - **ng_4_cpp要件**: ClapTrap属性をprotectedに、異なるattack()出力
  - **時間予想**: 60分
- [ ] CPP03/ex02: FragTrap クラス実装 (継承パターン確立)
  - **評価要点**: 同様の継承パターン、highFivesGuys()実装、適切な初期値
  - **ng_4_cpp要件**: ClapTrapからの継承、属性再宣言なし
  - **時間予想**: 45分

#### 高度な継承（Medium Priority）
- [ ] CPP03/ex03: DiamondTrap クラス実装 (仮想継承、ダイヤモンド問題)
  - **評価要点**: virtual継承、ScavTrapのattack()使用、whoAmI()実装
  - **ng_4_cpp要件**: FragTrapとScavTrapからの継承、private name属性
  - **時間予想**: 90分

### 🐾 CPP04: Subtype polymorphism, abstract classes, interfaces
#### ポリモーフィズム基礎（High Priority）
- [ ] CPP04/ex00: Animal階層実装 (ポリモーフィズム基礎、virtual関数)
  - **評価要点**: Animal/Cat/Dog、virtual makeSound()、WrongAnimal例
  - **ng_4_cpp要件**: type属性、virtual makeSound()必須、OCF実装
  - **時間予想**: 60分
- [ ] CPP04/ex01: Brain付きAnimal実装 (深いコピー、仮想デストラクタ)
  - **評価要点**: Brain クラス、深いコピー、virtual デストラクタ、OCF
  - **ng_4_cpp要件**: Cat/DogのBrain属性、深いコピー検証テスト
  - **時間予想**: 90分
- [ ] CPP04/ex02: 抽象Animal クラス実装 (純粋仮想関数)
  - **評価要点**: pure virtual makeSound() = 0、インスタンス化不可
  - **ng_4_cpp要件**: Animal test; でコンパイルエラー確認
  - **時間予想**: 30分

#### インターフェース設計（Medium Priority）
- [ ] CPP04/ex03: Materia システム実装 (インターフェース、キャラクター)
  - **評価要点**: ICharacter/IMateriaSource、AMateria、Character、MateriaSource
  - **ng_4_cpp要件**: 4 Materia inventory、深いコピー、clone()実装
  - **時間予想**: 150分

### 🔍 品質保証・テスト（Medium Priority）
- [ ] 全モジュール品質検証 (コンパイル、メモリリーク、C++98準拠)
  - **検証項目**: 
    - コンパイル成功 (`-Wall -Wextra -Werror -std=c++98`)
    - メモリリーク0 (valgrind/leaks)
    - 禁止機能未使用 (using namespace, friend, C++11+)
  - **時間予想**: 120分
- [ ] 統合テストとクロスプラットフォーム検証
  - **検証項目**:
    - macOS開発環境テスト
    - Ubuntu valgrind検証
    - ng_4_cpp評価基準全項目クリア
  - **時間予想**: 90分

## 評価基準マトリックス（ng_4_cpp統合）

### CPP01 評価要件
- ✅ **メモリ管理**: new/delete適切な使用、リークなし
- ✅ **ポインタ vs 参照**: 設計選択の理由説明可能
- ✅ **ファイル操作**: エラーハンドリング実装
- ✅ **メンバー関数ポインタ**: 配列実装、適切な呼び出し

### CPP02 評価要件
- ✅ **Orthodox Canonical Form**: 4つの特殊メンバー関数完全実装
- ✅ **演算子オーバーロード**: 算術・比較・代入演算子全て
- ✅ **固定小数点**: bit操作による精度保持
- ✅ **型変換**: int/float変換の一貫性

### CPP03 評価要件
- ✅ **継承階層**: ClapTrap→ScavTrap/FragTrap→DiamondTrap
- ✅ **仮想継承**: ダイヤモンド問題解決
- ✅ **コンストラクタ順序**: 作成時親→子、削除時子→親
- ✅ **属性アクセス**: private→protected適切な変更

### CPP04 評価要件
- ✅ **ポリモーフィズム**: virtual関数による実行時型解決
- ✅ **抽象クラス**: pure virtual実装、インスタンス化不可
- ✅ **深いコピー**: Brain等のリソース管理
- ✅ **インターフェース**: 純粋抽象基底クラス設計

## 進捗追跡

### 完了統計
- **完了タスク**: 11/22 (50%)
- **CPP01**: 7/7 完了 ✅
- **CPP02**: 3/4 完了 (ex03未実装)
- **CPP03**: 0/4 完了
- **CPP04**: 0/4 完了
- **品質保証**: 0/3 完了
- **インフラ**: 1/1 完了 ✅

### 時間予想合計
- **CPP01**: 270分 (4.5時間) ✅ 完了
- **CPP02**: 315分 (5.25時間) ⚠️ 195分完了 (120分残り - ex03のみ)
- **CPP03**: 240分 (4時間) ⏳ 未着手
- **CPP04**: 330分 (5.5時間) ⏳ 未着手
- **品質保証**: 210分 (3.5時間) ⏳ 未着手
- **総計**: 22.75時間 → **進捗**: 10.75時間完了 (47%)

## 依存関係マップ
```
インフラ → CPP01/02/03/04 (並行) → 品質検証 → 統合テスト
```

## コミット戦略
- **機能単位**: 各exerciseごとにコミット
- **テスト検証**: 動作確認後にコミット
- **評価準拠**: ng_4_cpp要件満たした時点でコミット

---
**最終更新**: 2025-07-30 17:30
**ステータス**: 🔧 並行開発継続中 (CPP01完了, CPP02ほぼ完了, CPP03/04未着手)

## 次のアクション
1. **即座実行**: CPP02/ex03 BSP実装 (120分)
2. **並行開始**: CPP03継承階層実装 (240分)
3. **連続実行**: CPP04ポリモーフィズム実装 (330分)
4. **最終検証**: 統合品質保証 (210分)