/*
 * ====================================================================
 * CPP03 ex02: FragTrap - 多重継承と特殊能力実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 複数の派生クラスからの共通基底クラス継承理解
 * - 異なる特殊能力を持つ派生クラスの実装
 * - ScavTrapとFragTrapの設計比較と差異理解
 * - 継承による機能拡張パターンの実践
 * - 戦闘ユニットの多様性実現
 * 
 * 【重要概念】
 * - 継承ツリーの拡張（ClapTrap → ScavTrap/FragTrap）
 * - 兄弟クラス間での設計の一貫性
 * - 特殊能力による差別化戦略
 * - コンストラクタパラメータの戦略的設定
 * - 機能的多態性の実現
 */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <string>
#include <iostream>

/*
 * ====================================================================
 * FragTrap クラス設計思想
 * ====================================================================
 * 
 * 【ScavTrapとの関係性】
 * 
 * 継承ツリー：
 * ```
 *        ClapTrap
 *        /      \
 *   ScavTrap   FragTrap
 * ```
 * 
 * 兄弟クラスとしての位置：
 * - 両方ともClapTrapから直接継承
 * - 互いに独立した特殊化
 * - 異なる戦術的役割を担う
 * 
 * 【FragTrapの特性設計】
 * 
 * ScavTrap (門番特化):
 * - HP: 100, Energy: 50, Attack: 20
 * - 特殊能力: guardGate() (防御特化)
 * - 役割: 防御・門番・持久戦
 * 
 * FragTrap (攻撃特化):
 * - HP: 100, Energy: 100, Attack: 30
 * - 特殊能力: highFivesGuys() (士気向上)
 * - 役割: 攻撃・チーム支援・高機動
 * 
 * 設計の意図：
 * - エネルギーが高い：多くの行動可能
 * - 攻撃力が最高：高火力アタッカー
 * - 特殊能力：チーム支援・士気向上
 * 
 * 【命名の由来】
 * 
 * "Frag" = Fragment（破片）/Fragmentation（破砕）
 * - FPS用語での「フラグ」（敵を倒す）
 * - 爆発物・グレネードの破片攻撃
 * - 高火力・範囲攻撃のイメージ
 */
class FragTrap : public ClapTrap {
public:
    /*
     * ====================================================================
     * コンストラクタ・デストラクタ
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * FragTrap();
     * 
     * FragTrap専用の初期値設定：
     * - name: "DefaultFrag"
     * - hitPoints: 100 (ScavTrapと同じ - 高い耐久性)
     * - energyPoints: 100 (ScavTrapより大幅に高い - 高機動性)
     * - attackDamage: 30 (ScavTrapより高い - 最高火力)
     * 
     * 戦術的意味：
     * - 攻撃特化型の戦闘ユニット
     * - 多くの行動を連続実行可能
     * - 短期決戦での圧倒的優位性
     * 
     * コンストラクタチェーン：
     * 1. ClapTrap("DefaultFrag", 100, 100, 30)
     * 2. FragTrap固有の初期化処理
     */
    FragTrap();
    
    /*
     * 【パラメータ付きコンストラクタ】
     * FragTrap(const std::string& name);
     * 
     * 名前指定でのFragTrap作成：
     * 
     * 実装パターン：
     * ```cpp
     * FragTrap::FragTrap(const std::string& name) 
     *     : ClapTrap(name, 100, 100, 30) {
     *     // FragTrap固有の初期化
     * }
     * ```
     * 
     * パラメータの戦略的選択：
     * - HP 100: 高い生存性（ScavTrapと同等）
     * - Energy 100: 最高の行動力（ScavTrapの2倍）
     * - Attack 30: 最高の火力（ScavTrapの1.5倍）
     * 
     * ゲームバランス考慮：
     * - 高火力だが防御的特殊能力なし
     * - エネルギー効率が良いが消耗戦に弱い
     * - チーム支援で真価を発揮
     */
    FragTrap(const std::string& name);
    
    /*
     * 【コピーコンストラクタ】
     * FragTrap(const FragTrap& other);
     * 
     * 継承でのコピーコンストラクタ実装：
     * 
     * 基底クラス部分のコピー：
     * - ClapTrap(other) で基底部分を適切にコピー
     * - FragTrap固有メンバがあれば個別処理
     * 
     * 実装例：
     * ```cpp
     * FragTrap::FragTrap(const FragTrap& other) 
     *     : ClapTrap(other) {
     *     // FragTrap固有のコピー処理
     *     // 現在は基底クラスのコピーのみで十分
     * }
     * ```
     */
    FragTrap(const FragTrap& other);
    
    /*
     * 【代入演算子】
     * FragTrap& operator=(const FragTrap& other);
     * 
     * 継承での代入演算子実装：
     * 
     * 実装の要点：
     * - 自己代入チェック
     * - 基底クラス代入演算子の呼び出し
     * - FragTrap固有メンバの代入
     * 
     * 実装パターン：
     * ```cpp
     * FragTrap& FragTrap::operator=(const FragTrap& other) {
     *     if (this != &other) {
     *         ClapTrap::operator=(other);
     *         // FragTrap固有の代入処理
     *     }
     *     return *this;
     * }
     * ```
     */
    FragTrap& operator=(const FragTrap& other);
    
    /*
     * 【デストラクタ】
     * ~FragTrap();
     * 
     * 継承でのデストラクタ特性：
     * 
     * 実行順序：
     * 1. FragTrapデストラクタ実行
     * 2. ClapTrapデストラクタ自動実行
     * 
     * virtual指定の重要性：
     * - 多態性使用時の正しいデストラクタ呼び出し
     * - メモリリーク防止
     * - 基底クラスでのvirtual指定が必要
     */
    ~FragTrap();
    
    /*
     * ====================================================================
     * オーバーライド関数
     * ====================================================================
     */
    
    /*
     * 【attack関数のオーバーライド】
     * void attack(const std::string& target);
     * 
     * FragTrap専用の攻撃実装：
     * 
     * ClapTrap版との違い：
     * - "ClapTrap" → "FragTrap"
     * - より爆発的・破壊的な表現
     * - 高火力をアピールするメッセージ
     * 
     * ScavTrap版との違い：
     * - ScavTrap: "fiercely attacks" (威圧的)
     * - FragTrap: "explosively attacks" (爆発的)
     * - 攻撃スタイルの差別化
     * 
     * 実装例：
     * ```cpp
     * void FragTrap::attack(const std::string& target) {
     *     if (energyPoints > 0 && hitPoints > 0) {
     *         std::cout << "FragTrap " << name 
     *                   << " explosively attacks " << target 
     *                   << ", causing " << attackDamage 
     *                   << " points of damage!" << std::endl;
     *         energyPoints--;
     *     } else {
     *         // エラーメッセージ
     *     }
     * }
     * ```
     */
    void attack(const std::string& target);
    
    /*
     * ====================================================================
     * FragTrap固有機能
     * ====================================================================
     */
    
    /*
     * 【High Five 機能】
     * void highFivesGuys();
     * 
     * FragTrap専用の特殊能力：
     * 
     * 機能コンセプト：
     * - チーム士気向上
     * - 仲間との連携強化
     * - 戦闘前の士気向上
     * - ポジティブな特殊能力
     * 
     * ScavTrapとの対比：
     * - ScavTrap: guardGate() (防御的・個人的)
     * - FragTrap: highFivesGuys() (支援的・集団的)
     * 
     * 実装の特徴：
     * - エネルギー消費なし（設計選択）
     * - HP状態に関係なく使用可能（設計選択）
     * - チーム全体への効果（概念的）
     * 
     * 実装例：
     * ```cpp
     * void FragTrap::highFivesGuys() {
     *     std::cout << "FragTrap " << name 
     *               << " requests positive high fives!" << std::endl;
     *     std::cout << "Team morale boost activated!" << std::endl;
     * }
     * ```
     * 
     * 拡張可能な実装：
     * - 他のユニットへの実際の効果適用
     * - 一定時間の攻撃力・防御力向上
     * - エネルギー回復効果
     * - クールダウン時間の導入
     */
    void highFivesGuys();
};

#endif

/*
 * ====================================================================
 * FragTrapとScavTrapの設計比較
 * ====================================================================
 * 
 * 【能力値比較表】
 * 
 * | 項目          | ClapTrap | ScavTrap | FragTrap |
 * |---------------|----------|----------|----------|
 * | Hit Points    | 10       | 100      | 100      |
 * | Energy Points | 10       | 50       | 100      |
 * | Attack Damage | 0        | 20       | 30       |
 * | 特殊能力      | なし     | 門番     | 士気向上 |
 * | 戦術役割      | 基本     | 防御     | 攻撃     |
 * 
 * 【戦術的特性比較】
 * 
 * ScavTrap（防御型）:
 * - 中程度のエネルギー効率
 * - 門番による防御専念
 * - 持久戦・陣地防御に適合
 * - 個人技による戦術優位
 * 
 * FragTrap（攻撃型）:
 * - 高いエネルギー効率
 * - 高火力による速攻戦術
 * - チーム連携・士気向上
 * - 集団戦術における中核
 * 
 * 【使い分けシナリオ】
 * 
 * ScavTrap適用場面：
 * - 重要拠点の防御
 * - 長期戦での持久力発揮
 * - 単独行動での生存性重視
 * - 侵入者検知・迎撃
 * 
 * FragTrap適用場面：
 * - 攻撃作戦の先鋒
 * - 短期決戦での火力集中
 * - チーム戦での士気管理
 * - 高機動作戦の実行
 */

/*
 * ====================================================================
 * 継承設計パターンの学習ポイント
 * ====================================================================
 * 
 * 【共通基底クラスからの分岐】
 * 
 * 設計原則：
 * - 基底クラス（ClapTrap）：共通機能
 * - 派生クラス：特殊化された機能
 * - is-a関係の維持：どちらもClapTrapの一種
 * 
 * 利点：
 * - コードの再利用性
 * - 一貫したインターフェース
 * - 多態性による柔軟な操作
 * - 拡張性の確保
 * 
 * 【特殊化戦略】
 * 
 * 能力値による差別化：
 * - 同じ項目で異なる値
 * - 戦術的役割の明確化
 * - バランス調整の容易さ
 * 
 * 機能による差別化：
 * - 独自の特殊能力追加
 * - 使用場面の明確化
 * - プレイヤーの選択肢拡大
 * 
 * 【インターフェース一貫性】
 * 
 * 共通インターフェース：
 * - attack(), takeDamage(), beRepaired()
 * - どの派生クラスでも同じ方法で操作
 * - ポリモーフィズムの基盤
 * 
 * 個別インターフェース：
 * - guardGate() (ScavTrapのみ)
 * - highFivesGuys() (FragTrapのみ)
 * - クラス固有の価値提供
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ 複数派生クラスでの共通基底クラス継承
 * □ 兄弟クラス間での設計一貫性
 * □ 戦術的差別化による特殊化戦略
 * □ コンストラクタパラメータの戦略的選択
 * □ オーバーライドによる表現の差別化
 * □ 特殊能力による機能的差別化
 * □ Orthodox Canonical Formの継承実装
 * □ 継承ツリーの拡張設計
 * □ ゲームバランス考慮の能力値設計
 * □ is-a関係の実践的理解
 * 
 * 【実習課題】
 * 1. 新しい派生クラス（例：MageTrap）の設計
 * 2. 特殊能力の相互作用システム実装
 * 3. チーム戦闘でのクラス連携システム
 * 4. 能力値バランス調整とテスト
 * 5. ファクトリーパターンでの統一生成
 */

/*
 * ====================================================================
 * よくある継承設計のミスと対策
 * ====================================================================
 * 
 * 【ミス1：能力値設定の一貫性欠如】
 * 
 * 問題例：
 * - ScavTrap: HP 100, Energy 50, Attack 20
 * - FragTrap: HP 200, Energy 25, Attack 50
 * → バランスが取れていない
 * 
 * 改善策：
 * - 総合能力値の合計を一定に保つ
 * - 特化型vs万能型の明確な差別化
 * - テストによる調整
 * 
 * 【ミス2：特殊能力の設計思想不一致】
 * 
 * 問題例：
 * - guardGate(): 実用的効果あり
 * - highFivesGuys(): メッセージのみ
 * → 価値の不平等
 * 
 * 改善策：
 * - 同等の価値を持つ特殊能力設計
 * - 使用条件・効果の統一感
 * - 戦術的意味の明確化
 * 
 * 【ミス3：命名の一貫性不足】
 * 
 * 問題例：
 * - ScavTrap (役割ベース)
 * - FragTrap (機能ベース)
 * → 命名基準の不統一
 * 
 * 改善策：
 * - 統一された命名規則
 * - 機能・役割・特性の明確な表現
 * - 覚えやすい名前選択
 * 
 * 【ミス4：継承階層の過度な複雑化】
 * 
 * 問題例：
 * ```
 * ClapTrap → ScavTrap → SuperScavTrap → UltraScavTrap
 * ```
 * → 深すぎる継承階層
 * 
 * 改善策：
 * - 浅い継承階層の維持
 * - コンポジションの検討
 * - 機能の水平分割
 */

/*
 * ====================================================================
 * 発展的な継承パターン
 * ====================================================================
 * 
 * 【パターン1：Abstract Factory Pattern】
 * ```cpp
 * class TrapFactory {
 * public:
 *     virtual ~TrapFactory() {}
 *     virtual ClapTrap* createBasicTrap(const std::string& name) = 0;
 *     virtual ClapTrap* createGuardTrap(const std::string& name) = 0;
 *     virtual ClapTrap* createFragTrap(const std::string& name) = 0;
 * };
 * 
 * class StandardTrapFactory : public TrapFactory {
 * public:
 *     ClapTrap* createBasicTrap(const std::string& name) override {
 *         return new ClapTrap(name);
 *     }
 *     ClapTrap* createGuardTrap(const std::string& name) override {
 *         return new ScavTrap(name);
 *     }
 *     ClapTrap* createFragTrap(const std::string& name) override {
 *         return new FragTrap(name);
 *     }
 * };
 * ```
 * 
 * 【パターン2：Strategy Pattern with Inheritance】
 * ```cpp
 * class AttackStrategy {
 * public:
 *     virtual ~AttackStrategy() {}
 *     virtual void execute(ClapTrap& attacker, const std::string& target) = 0;
 * };
 * 
 * class ExplosiveAttack : public AttackStrategy {
 * public:
 *     void execute(ClapTrap& attacker, const std::string& target) override {
 *         // FragTrap用の爆発攻撃
 *     }
 * };
 * 
 * class GuardAttack : public AttackStrategy {
 * public:
 *     void execute(ClapTrap& attacker, const std::string& target) override {
 *         // ScavTrap用の門番攻撃
 *     }
 * };
 * ```
 * 
 * 【パターン3：Decorator Pattern】
 * ```cpp
 * class TrapDecorator : public ClapTrap {
 * protected:
 *     ClapTrap* wrappedTrap;
 * 
 * public:
 *     TrapDecorator(ClapTrap* trap) : wrappedTrap(trap) {}
 *     virtual ~TrapDecorator() { delete wrappedTrap; }
 * };
 * 
 * class ArmoredTrap : public TrapDecorator {
 * public:
 *     ArmoredTrap(ClapTrap* trap) : TrapDecorator(trap) {}
 *     
 *     void takeDamage(unsigned int amount) override {
 *         // 装甲による軽減処理
 *         wrappedTrap->takeDamage(amount / 2);
 *     }
 * };
 * ```
 * 
 * 【パターン4：Template Method Pattern】
 * ```cpp
 * class ClapTrap {
 * public:
 *     void performCombatAction() {  // Template Method
 *         prepare();
 *         executeSpecialAbility();  // 派生クラスで実装
 *         attack();
 *         cleanup();
 *     }
 * 
 * protected:
 *     virtual void executeSpecialAbility() = 0;
 *     void prepare() { /* 共通準備処理 */ }
 *     void cleanup() { /* 共通終了処理 */ }
 * };
 * 
 * class FragTrap : public ClapTrap {
 * protected:
 *     void executeSpecialAbility() override {
 *         highFivesGuys();
 *     }
 * };
 * ```
 */