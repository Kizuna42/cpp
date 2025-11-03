/*
 * ====================================================================
 * CPP03 ex03: ClapTrap - 多重継承基盤クラス解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 多重継承における基底クラスの設計理解
 * - 仮想継承（Virtual Inheritance）の必要性理解
 * - ダイヤモンド継承問題とその解決策
 * - 基底クラスでの仮想関数設計
 * - 複雑な継承階層での安全な設計パターン
 * 
 * 【重要概念】
 * - ダイヤモンド継承問題（Diamond Problem）
 * - 仮想基底クラス（Virtual Base Class）
 * - 多重継承での曖昧性（Ambiguity）の解決
 * - 仮想関数による統一インターフェース
 * - 複雑な継承での Orthodox Canonical Form
 */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

/*
 * ====================================================================
 * ダイヤモンド継承問題の背景
 * ====================================================================
 * 
 * 【CPP03 ex03での継承構造】
 * 
 * 継承ダイヤグラム：
 * ```
 *         ClapTrap
 *        /        \
 *   ScavTrap    FragTrap
 *        \        /
 *      DiamondTrap
 * ```
 * 
 * 【ダイヤモンド問題とは】
 * 
 * 問題の本質：
 * - DiamondTrapがClapTrapを2つの経路で継承
 * - ScavTrap経由とFragTrap経由の2つのClapTrapインスタンス
 * - メンバ変数・関数の曖昧性発生
 * - メモリ使用量の無駄な増大
 * 
 * 具体的な問題例：
 * ```cpp
 * DiamondTrap dt("test");
 * dt.name = "newname";  // エラー：どちらのnameか曖昧
 * dt.attack("target");  // エラー：どちらのattackか曖昧
 * ```
 * 
 * 【仮想継承による解決】
 * 
 * 解決後の構造：
 * ```
 *         ClapTrap (virtual base)
 *        /        \
 *   ScavTrap    FragTrap
 *   (virtual)   (virtual)
 *        \        /
 *      DiamondTrap
 * ```
 * 
 * 仮想継承の効果：
 * - ClapTrapの単一インスタンス
 * - 曖昧性の解消
 * - メモリ効率の向上
 * - 設計意図の明確化
 */
class ClapTrap {
protected:
    /*
     * ====================================================================
     * 多重継承対応のメンバ変数設計
     * ====================================================================
     */
    
    /*
     * 【基本属性メンバ】
     * 
     * protectedアクセス修飾子の重要性：
     * - 派生クラスからの直接アクセス許可
     * - 外部からの不正アクセス防止
     * - 継承階層内での情報共有
     * - 仮想継承での単一実体保証
     */
    std::string name;        // オブジェクト識別名
    int hitPoints;          // 生命力・耐久度
    int energyPoints;       // 行動力・エネルギー
    int attackDamage;       // 攻撃力・与ダメージ

public:
    /*
     * ====================================================================
     * 多重継承対応コンストラクタ設計
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * ClapTrap();
     * 
     * 仮想継承での役割：
     * - DiamondTrapから直接呼び出される可能性
     * - 中間派生クラス（ScavTrap/FragTrap）からの呼び出し
     * - 単一の初期化プロセス保証
     * 
     * 初期値設定：
     * - name: "ClapTrap_Default"
     * - hitPoints: 10
     * - energyPoints: 10
     * - attackDamage: 0
     */
    ClapTrap();
    
    /*
     * 【パラメータ付きコンストラクタ】
     * ClapTrap(const std::string& name);
     * 
     * 多重継承での柔軟性：
     * - DiamondTrapからの名前指定初期化
     * - 派生クラス固有の命名規則対応
     * - 統一された初期化インターフェース
     */
    ClapTrap(const std::string& name);
    
    /*
     * 【完全パラメータコンストラクタ】
     * ClapTrap(const std::string& name, int hp, int energy, int attack);
     * 
     * 派生クラス用の詳細初期化：
     * - ScavTrap用の能力値設定
     * - FragTrap用の能力値設定
     * - DiamondTrap用のカスタム設定
     * - 統一されたパラメータ化初期化
     */
    ClapTrap(const std::string& name, int hp, int energy, int attack);
    
    /*
     * 【コピーコンストラクタ】
     * ClapTrap(const ClapTrap& other);
     * 
     * 仮想継承での複雑性：
     * - 単一の基底クラスインスタンスのコピー
     * - 派生クラスからの適切な呼び出し
     * - Orthodox Canonical Formの維持
     */
    ClapTrap(const ClapTrap& other);
    
    /*
     * 【代入演算子】
     * ClapTrap& operator=(const ClapTrap& other);
     * 
     * 多重継承での代入の複雑性：
     * - 基底クラス部分の単一更新
     * - スライシング問題の回避
     * - 仮想継承での安全な代入
     */
    ClapTrap& operator=(const ClapTrap& other);
    
    /*
     * 【仮想デストラクタ】
     * virtual ~ClapTrap();
     * 
     * 多態性での重要性：
     * - 多重継承での正しい破棄順序
     * - 仮想継承での適切なクリーンアップ
     * - 複雑な継承階層での安全性確保
     * - vtable整合性の維持
     */
    virtual ~ClapTrap();
    
    /*
     * ====================================================================
     * 仮想関数インターフェース
     * ====================================================================
     */
    
    /*
     * 【仮想攻撃関数】
     * virtual void attack(const std::string& target);
     * 
     * 多重継承での仮想関数設計：
     * - ScavTrap、FragTrapでのオーバーライド対象
     * - DiamondTrapでの最終実装選択
     * - 統一されたインターフェース提供
     * - 動的バインディングによる多態性
     * 
     * 仮想指定の理由：
     * - 派生クラスでの特殊化許可
     * - 多態性での正しい関数選択
     * - 将来の拡張可能性確保
     */
    virtual void attack(const std::string& target);
    
    /*
     * 【ダメージ受け取り関数】
     * void takeDamage(unsigned int amount);
     * 
     * 非仮想関数の選択理由：
     * - 基本的なダメージ処理は共通
     * - 派生クラスでの変更不要
     * - 実装の一貫性保持
     * - 複雑性の削減
     */
    void takeDamage(unsigned int amount);
    
    /*
     * 【回復関数】
     * void beRepaired(unsigned int amount);
     * 
     * 非仮想関数の選択理由：
     * - 回復処理の標準化
     * - 全クラス共通の動作
     * - エネルギー消費の統一
     * - 設計の簡素化
     */
    void beRepaired(unsigned int amount);
    
    /*
     * ====================================================================
     * アクセサ関数（const correctness対応）
     * ====================================================================
     */
    
    /*
     * 【状態取得関数群】
     * 
     * const指定の重要性：
     * - 読み取り専用操作の明示
     * - constオブジェクトからの呼び出し対応
     * - インターフェースの安全性確保
     * - 多重継承での一貫性保持
     */
    std::string getName() const;
    int getHitPoints() const;
    int getEnergyPoints() const;
    int getAttackDamage() const;
};

#endif

/*
 * ====================================================================
 * 仮想継承の実装詳細
 * ====================================================================
 * 
 * 【派生クラスでの仮想継承宣言】
 * 
 * ScavTrap での宣言例：
 * ```cpp
 * class ScavTrap : virtual public ClapTrap {
 *     // ...
 * };
 * ```
 * 
 * FragTrap での宣言例：
 * ```cpp
 * class FragTrap : virtual public ClapTrap {
 *     // ...
 * };
 * ```
 * 
 * DiamondTrap での多重継承：
 * ```cpp
 * class DiamondTrap : public ScavTrap, public FragTrap {
 *     // ClapTrapは単一インスタンス
 * };
 * ```
 * 
 * 【仮想継承のメモリレイアウト】
 * 
 * 通常の多重継承（問題あり）：
 * ```
 * DiamondTrapオブジェクト:
 * +------------------+
 * | ClapTrap (ScavTrap経由) |
 * +------------------+
 * | ScavTrap固有     |
 * +------------------+
 * | ClapTrap (FragTrap経由) | ← 重複！
 * +------------------+
 * | FragTrap固有     |
 * +------------------+
 * | DiamondTrap固有  |
 * +------------------+
 * ```
 * 
 * 仮想継承（解決後）：
 * ```
 * DiamondTrapオブジェクト:
 * +------------------+
 * | ClapTrap (shared) |
 * +------------------+
 * | ScavTrap固有     |
 * +------------------+
 * | FragTrap固有     |
 * +------------------+
 * | DiamondTrap固有  |
 * +------------------+
 * ```
 */

/*
 * ====================================================================
 * 多重継承での設計原則
 * ====================================================================
 * 
 * 【原則1：仮想基底クラスの適切な使用】
 * 
 * 適用場面：
 * - ダイヤモンド継承構造
 * - 共通基底クラスの単一インスタンス必要
 * - 曖昧性回避が必要
 * 
 * 注意点：
 * - パフォーマンスオーバーヘッド
 * - 複雑なコンストラクタ呼び出し
 * - デバッグの困難さ
 * 
 * 【原則2：インターフェースの統一】
 * 
 * 仮想関数の活用：
 * - 派生クラス間の一貫したインターフェース
 * - 多態性による柔軟な操作
 * - 将来の拡張可能性確保
 * 
 * 【原則3：複雑性の管理】
 * 
 * 設計の簡素化：
 * - 必要最小限の仮想関数
 * - 明確な責任分担
 * - 理解しやすい継承構造
 * 
 * 【原則4：テストの重要性】
 * 
 * 多重継承での検証項目：
 * - 曖昧性の解消確認
 * - 正しいコンストラクタ・デストラクタ呼び出し
 * - 仮想関数の適切な解決
 * - メモリレイアウトの確認
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ ダイヤモンド継承問題の本質理解
 * □ 仮想継承の概念と必要性
 * □ 多重継承での曖昧性問題
 * □ 仮想基底クラスの設計方法
 * □ 複雑な継承での仮想関数設計
 * □ メモリレイアウトの違い理解
 * □ コンストラクタ呼び出し順序の変化
 * □ 多態性と仮想継承の組み合わせ
 * □ Orthodox Canonical Formの複雑化
 * □ 設計トレードオフの理解
 * 
 * 【実習課題】
 * 1. より複雑な多重継承階層の設計
 * 2. 仮想継承のパフォーマンス測定
 * 3. 曖昧性が発生するケースの実験
 * 4. 代替設計手法（委譲等）との比較
 * 5. 実用的な多重継承パターンの研究
 */

/*
 * ====================================================================
 * よくある多重継承の設計ミス
 * ====================================================================
 * 
 * 【ミス1：仮想継承の忘れ】
 * 
 * 間違い例：
 * ```cpp
 * class ScavTrap : public ClapTrap {  // virtualなし
 *     // ...
 * };
 * class FragTrap : public ClapTrap {  // virtualなし
 *     // ...
 * };
 * class DiamondTrap : public ScavTrap, public FragTrap {
 *     // 曖昧性エラーが発生
 * };
 * ```
 * 
 * 正解：
 * ```cpp
 * class ScavTrap : virtual public ClapTrap {
 *     // ...
 * };
 * ```
 * 
 * 【ミス2：仮想デストラクタの不備】
 * 
 * 問題：
 * - 多重継承での削除時に問題発生
 * - 適切なデストラクタ順序が保証されない
 * 
 * 対策：
 * - 基底クラスでの仮想デストラクタ必須
 * - 全派生クラスでの適切な実装
 * 
 * 【ミス3：コンストラクタの初期化順序理解不足】
 * 
 * 仮想継承での特殊な順序：
 * 1. 仮想基底クラス（ClapTrap）
 * 2. 通常の基底クラス（ScavTrap, FragTrap）
 * 3. 派生クラス（DiamondTrap）
 * 
 * 注意点：
 * - 最派生クラスが仮想基底クラスを直接初期化
 * - 中間クラスの初期化は無視される場合がある
 */

/*
 * ====================================================================
 * 代替設計手法との比較
 * ====================================================================
 * 
 * 【手法1：コンポジション（委譲）】
 * ```cpp
 * class DiamondTrap {
 * private:
 *     ClapTrap clapTrap;
 *     ScavTrapBehavior scavBehavior;
 *     FragTrapBehavior fragBehavior;
 * 
 * public:
 *     void attack(const std::string& target) {
 *         // どちらかの行動を選択
 *         scavBehavior.attack(target);
 *     }
 * };
 * ```
 * 
 * 利点：
 * - 複雑性の削減
 * - 明確な責任分担
 * - 実行時の動作選択可能
 * 
 * 欠点：
 * - is-a関係の喪失
 * - 多態性の活用困難
 * - インターフェース統一の複雑化
 * 
 * 【手法2：ミックスイン（CRTP）】
 * ```cpp
 * template<typename Derived>
 * class ScavTrapMixin {
 * public:
 *     void guardGate() {
 *         static_cast<Derived*>(this)->guardGateImpl();
 *     }
 * };
 * 
 * class DiamondTrap : public ClapTrap, 
 *                     public ScavTrapMixin<DiamondTrap>,
 *                     public FragTrapMixin<DiamondTrap> {
 *     // ...
 * };
 * ```
 * 
 * 【手法3：ストラテジーパターン】
 * ```cpp
 * class AttackStrategy {
 * public:
 *     virtual ~AttackStrategy() {}
 *     virtual void attack(const std::string& target) = 0;
 * };
 * 
 * class DiamondTrap : public ClapTrap {
 * private:
 *     AttackStrategy* attackStrategy;
 * 
 * public:
 *     void attack(const std::string& target) override {
 *         attackStrategy->attack(target);
 *     }
 * };
 * ```
 */