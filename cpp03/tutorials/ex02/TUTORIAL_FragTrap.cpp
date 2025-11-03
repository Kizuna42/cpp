/*
 * ====================================================================
 * CPP03 ex02: FragTrap - 攻撃特化型継承実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 高火力・高機動戦闘ユニットの実装
 * - ScavTrapとの実装比較による設計理解
 * - チーム支援機能の実装パターン
 * - 攻撃型ユニットの特殊能力設計
 * - 継承による差別化戦略の実践
 * 
 * 【重要概念】
 * - 兄弟クラス間での実装一貫性
 * - 戦術的役割による機能差別化
 * - 高エネルギー効率の戦闘システム
 * - ポジティブ支援機能の実装
 * - バランス調整された能力値設定
 */

#include "FragTrap.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * FragTrap::FragTrap()
 * 
 * FragTrap専用の能力値設定：
 * 
 * 戦略的パラメータ選択：
 * - HP 100: ScavTrapと同等の高い生存性
 * - Energy 100: ScavTrapの2倍、最高の行動力
 * - Attack 30: ScavTrapより50%向上、最高火力
 * 
 * バランス設計の意図：
 * - 攻撃特化だが防御も十分
 * - 多くの行動を連続実行可能
 * - 短期決戦での圧倒的優位性
 * - エネルギー効率による戦術的多様性
 */
FragTrap::FragTrap() : ClapTrap("DefaultFrag", 100, 100, 30) {
    /*
     * 【基底クラス初期化の詳細】
     * 
     * ClapTrap("DefaultFrag", 100, 100, 30) の効果：
     * 1. name = "DefaultFrag"
     * 2. hitPoints = 100
     * 3. energyPoints = 100
     * 4. attackDamage = 30
     * 
     * 他の派生クラスとの比較：
     * - ClapTrap: (10, 10, 0) - 基本型
     * - ScavTrap: (100, 50, 20) - 防御型
     * - FragTrap: (100, 100, 30) - 攻撃型
     */
    
    /*
     * 【FragTrap固有の初期化】
     * 
     * 現在は追加メンバ変数なし
     * 将来の拡張可能性：
     * - 爆発範囲設定
     * - 特殊弾薬タイプ
     * - クリティカル率設定
     * - チーム支援効果レベル
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * コンストラクタチェーンの可視化：
     * 1. ClapTrap constructor: 基底クラス初期化確認
     * 2. FragTrap constructor: 派生クラス初期化確認
     * 3. 能力値と特性の説明
     */
    std::cout << "FragTrap default constructor called for " << name << std::endl;
    std::cout << "FragTrap " << name << " is ready for explosive combat!" << std::endl;
    std::cout << "High-energy, high-damage unit deployed!" << std::endl;
}

/*
 * 【パラメータ付きコンストラクタ】
 * FragTrap::FragTrap(const std::string& name)
 * 
 * 名前指定でのFragTrap作成：
 * 
 * メンバ初期化リストによる効率的初期化：
 * - ClapTrap(name, 100, 100, 30) で基底クラス初期化
 * - コピーではなく直接初期化
 * - const メンバや参照メンバにも対応
 */
FragTrap::FragTrap(const std::string& name) : ClapTrap(name, 100, 100, 30) {
    /*
     * 【戦術的能力値の説明】
     * 
     * HP 100 の意味：
     * - 高い生存性で前線での活動可能
     * - 3-4回の攻撃に耐える耐久性
     * - 攻撃型だが防御も考慮した設計
     * 
     * Energy 100 の意味：
     * - 100回の行動が可能（理論値）
     * - 長期戦での継続活動能力
     * - 攻撃・回復・特殊能力の組み合わせ自由
     * 
     * Attack 30 の意味：
     * - 最高クラスの火力
     * - 3-4発でScavTrapを撃破可能
     * - 短期決戦での決定力
     */
    
    /*
     * 【デバッグ出力による状態確認】
     * 
     * FragTrap専用のメッセージ：
     * - 攻撃型であることの強調
     * - 爆発的な戦闘能力のアピール
     * - チーム支援機能の言及
     */
    std::cout << "FragTrap constructor called for " << name << std::endl;
    std::cout << "FragTrap " << name << " is armed with explosive capabilities!" << std::endl;
    std::cout << "Ready to boost team morale and deliver devastating attacks!" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * FragTrap::FragTrap(const FragTrap& other)
 * 
 * 継承でのコピーコンストラクタ実装：
 * 
 * 基底クラス部分の適切なコピー：
 * - ClapTrap(other) による基底部分コピー
 * - otherのClapTrap部分が正しくコピーされる
 * - スライシング問題の回避
 */
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    /*
     * 【コピー処理の詳細】
     * 
     * ClapTrap(other) による処理：
     * 1. other.name のコピー
     * 2. other.hitPoints のコピー
     * 3. other.energyPoints のコピー
     * 4. other.attackDamage のコピー
     * 
     * FragTrap固有メンバのコピー：
     * 現在は追加メンバなし
     * 将来的な拡張では個別コピー処理を追加
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * コピー操作の可視化：
     * - どのオブジェクトからコピーされたか
     * - コピー後のオブジェクト状態
     * - 独立性の確保確認
     */
    std::cout << "FragTrap copy constructor called" << std::endl;
    std::cout << "FragTrap " << name << " has been cloned with full combat capabilities!" << std::endl;
    std::cout << "New explosive unit ready for deployment!" << std::endl;
}

/*
 * 【代入演算子】
 * FragTrap& FragTrap::operator=(const FragTrap& other)
 * 
 * 継承での代入演算子の適切な実装：
 * 
 * 実装の完全性：
 * - 自己代入チェック
 * - 基底クラス代入演算子呼び出し
 * - 派生クラス固有メンバの代入
 * - 例外安全性の考慮
 */
FragTrap& FragTrap::operator=(const FragTrap& other) {
    /*
     * 【自己代入チェック】
     * 
     * if (this != &other) の重要性：
     * - 同じオブジェクトへの代入を防止
     * - 不要な処理の回避
     * - 自己破壊の防止（リソース管理がある場合）
     * 
     * アドレス比較による判定：
     * - オブジェクトの一意性をアドレスで確認
     * - 確実で効率的な自己代入検出
     */
    if (this != &other) {
        /*
         * 【基底クラス代入演算子の呼び出し】
         * 
         * ClapTrap::operator=(other) の実行：
         * - ClapTrap部分の適切な代入
         * - name, hitPoints, energyPoints, attackDamage の代入
         * - 基底クラスのロジックを再利用
         */
        ClapTrap::operator=(other);
        
        /*
         * 【FragTrap固有メンバの代入】
         * 
         * 現在は追加メンバなし
         * 将来の拡張例：
         * ```cpp
         * this->explosiveType = other.explosiveType;
         * this->teamBoostLevel = other.teamBoostLevel;
         * this->criticalRate = other.criticalRate;
         * ```
         */
        
        /*
         * 【デバッグ出力による確認】
         * 
         * 代入操作の可視化：
         * - 代入が実行されたことの確認
         * - 新しい状態の取得確認
         * - オブジェクトの更新通知
         */
        std::cout << "FragTrap assignment operator called" << std::endl;
        std::cout << "FragTrap " << name << " has acquired new combat parameters!" << std::endl;
        std::cout << "Updated explosive capabilities loaded!" << std::endl;
    }
    
    /*
     * 【*this の返却】
     * 
     * 戻り値の重要性：
     * - 連鎖代入の有効化: a = b = c
     * - 一貫したインターフェース提供
     * - 標準ライブラリとの互換性
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタの実装
 * ====================================================================
 */

/*
 * 【デストラクタ】
 * FragTrap::~FragTrap()
 * 
 * 継承でのデストラクタ実装：
 * 
 * 実行順序の理解：
 * 1. FragTrapデストラクタ実行（明示的）
 * 2. ClapTrapデストラクタ実行（自動）
 * 
 * クリーンアップの責任分担：
 * - FragTrap: 派生クラス固有のクリーンアップ
 * - ClapTrap: 基底クラス共通のクリーンアップ
 */
FragTrap::~FragTrap() {
    /*
     * 【FragTrap固有のクリーンアップ】
     * 
     * 現在の処理：
     * - デバッグメッセージの出力
     * - オブジェクト破棄の通知
     * 
     * 将来の拡張可能性：
     * - 爆発エフェクトのクリーンアップ
     * - チーム効果の解除
     * - 特殊リソースの解放
     * - ログファイルへの記録
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * デストラクタチェーンの可視化：
     * - FragTrapデストラクタの実行確認
     * - 戦闘能力の終了通知
     * - オブジェクトライフサイクルの完了
     */
    std::cout << "FragTrap destructor called for " << name << std::endl;
    std::cout << "FragTrap " << name << " has finished explosive combat operations!" << std::endl;
    std::cout << "High-energy unit decommissioned!" << std::endl;
}

/*
 * ====================================================================
 * オーバーライド関数の実装
 * ====================================================================
 */

/*
 * 【attack関数のオーバーライド】
 * void FragTrap::attack(const std::string& target)
 * 
 * FragTrap専用の攻撃実装：
 * 
 * 他のクラスとの表現差別化：
 * - ClapTrap: "attacks" (基本的)
 * - ScavTrap: "fiercely attacks" (威圧的)
 * - FragTrap: "explosively attacks" (爆発的)
 * 
 * 高火力の表現：
 * - 爆発的・破壊的な語彙使用
 * - 30ダメージの威力をアピール
 * - 攻撃型としての特性表現
 */
void FragTrap::attack(const std::string& target) {
    /*
     * 【攻撃可能性のチェック】
     * 
     * 攻撃実行の条件：
     * - energyPoints > 0: エネルギーが残っている
     * - hitPoints > 0: 生存している
     * 
     * protectedメンバへのアクセス：
     * - 継承により基底クラスのprotectedメンバにアクセス可能
     * - name, hitPoints, energyPoints, attackDamage を直接使用
     */
    if (energyPoints > 0 && hitPoints > 0) {
        /*
         * 【FragTrap専用攻撃メッセージ】
         * 
         * "explosively attacks" の選択理由：
         * - "Frag" = Fragment（破片）からの連想
         * - 爆発物・グレネードのイメージ
         * - 高火力・範囲攻撃の示唆
         * - 攻撃特化型としての個性表現
         */
        std::cout << "FragTrap " << name << " explosively attacks " << target 
                  << ", causing " << attackDamage << " points of damage!" << std::endl;
        
        /*
         * 【エネルギー消費処理】
         * 
         * 1エネルギーポイント消費：
         * - ClapTrap系統共通のコスト
         * - 100エネルギーで100回攻撃可能
         * - ScavTrapの2倍の持続力
         */
        energyPoints--;
        
        /*
         * 【攻撃成功時の追加情報】
         * 
         * ユーザビリティとデバッグ支援：
         * - 残りエネルギーの表示
         * - 戦闘継続能力の確認
         * - 戦術判断の材料提供
         */
        std::cout << "FragTrap " << name << " has " << energyPoints 
                  << " energy points remaining for more explosive action!" << std::endl;
        
        /*
         * 【追加効果の可能性】
         * 
         * 将来的な拡張例：
         * - クリティカルヒット判定
         * - 範囲攻撃効果
         * - チーム支援効果の発動
         * - 特殊弾薬の使用
         */
    } else {
        /*
         * 【攻撃不可能時の処理】
         * 
         * エラー状態の詳細分岐：
         * - HP0: 戦闘不能状態
         * - エネルギー0: 行動不能状態
         * 
         * FragTrap専用エラーメッセージ：
         * - 爆発的な表現を維持
         * - 攻撃型としての特性を反映
         */
        if (hitPoints == 0) {
            std::cout << "FragTrap " << name 
                      << " cannot attack - the explosive unit is down!" << std::endl;
            std::cout << "Need repairs to restore combat capabilities!" << std::endl;
        } else {
            std::cout << "FragTrap " << name 
                      << " cannot attack - insufficient energy for explosive operations!" << std::endl;
            std::cout << "Energy recharge required for continued combat!" << std::endl;
        }
    }
}

/*
 * ====================================================================
 * FragTrap固有機能の実装
 * ====================================================================
 */

/*
 * 【High Five機能】
 * void FragTrap::highFivesGuys()
 * 
 * FragTrap専用の特殊能力：
 * 
 * 機能設計の思想：
 * - ScavTraP: guardGate() (個人的・防御的)
 * - FragTrap: highFivesGuys() (集団的・支援的)
 * 
 * ポジティブ支援機能：
 * - チーム士気の向上
 * - 仲間との絆強化
 * - 戦闘前の雰囲気作り
 * - 協調性の表現
 */
void FragTrap::highFivesGuys() {
    /*
     * 【使用条件の設計選択】
     * 
     * 現在の実装：無条件で使用可能
     * 
     * 設計理由：
     * - ポジティブな機能なのでペナルティなし
     * - いつでも士気向上可能
     * - エネルギー消費なし（精神的支援）
     * - HP状態に関係なく実行可能
     * 
     * 代替設計案：
     * - エネルギー消費あり（よりバランス重視）
     * - HP最低値の設定（生存時のみ）
     * - クールダウン時間の導入
     */
    
    /*
     * 【FragTrap専用メッセージ】
     * 
     * "positive high fives" の表現：
     * - 明るく前向きな雰囲気
     * - チーム結束の象徴
     * - 攻撃型だが協調性もある
     * - ScavTrapの厳格さとの対比
     */
    std::cout << "FragTrap " << name << " requests positive high fives!" << std::endl;
    std::cout << "✋ Team morale boost activated! ✋" << std::endl;
    std::cout << "Everyone feels more energized and ready for action!" << std::endl;
    
    /*
     * 【効果の表現と説明】
     * 
     * 視覚的効果：
     * - 絵文字（✋）による視覚的インパクト
     * - 明るいメッセージによる雰囲気作り
     * - チーム全体への影響を示唆
     * 
     * 実際のゲーム効果（概念的）：
     * - 味方ユニットの攻撃力一時向上
     * - エネルギー回復効果
     * - 命中率向上
     * - 防御力向上
     */
    
    /*
     * 【拡張可能な実装例】
     * 
     * より実用的な効果実装：
     * ```cpp
     * void FragTrap::highFivesGuys(std::vector<ClapTrap*>& allies) {
     *     std::cout << "FragTrap " << name << " boosts team morale!" << std::endl;
     *     
     *     for (ClapTrap* ally : allies) {
     *         if (ally && ally->getHitPoints() > 0) {
     *             ally->gainAttackBoost(5);  // 攻撃力+5
     *             ally->gainEnergyBoost(10); // エネルギー+10
     *             std::cout << ally->getName() << " feels inspired!" << std::endl;
     *         }
     *     }
     * }
     * ```
     * 
     * 時間制限付き効果：
     * ```cpp
     * void FragTrap::highFivesGuys() {
     *     if (lastHighFiveTime + COOLDOWN_TIME <= getCurrentTime()) {
     *         // 効果実行
     *         lastHighFiveTime = getCurrentTime();
     *     } else {
     *         std::cout << "High five is on cooldown!" << std::endl;
     *     }
     * }
     * ```
     */
    
    /*
     * 【チーム連携の可能性】
     * 
     * 他のユニットとの相互作用：
     * - ScavTrapとの連携: 攻防一体の戦術
     * - 複数FragTrapでの効果重複
     * - ClapTrapの基本能力底上げ
     * - 新しい派生クラスとの組み合わせ
     */
    
    /*
     * 【士気システムの拡張案】
     * 
     * モラルゲージシステム：
     * ```cpp
     * class TeamMorale {
     * private:
     *     static int globalMorale;
     * 
     * public:
     *     static void boostMorale(int amount) {
     *         globalMorale += amount;
     *         if (globalMorale > 100) globalMorale = 100;
     *     }
     *     
     *     static bool isHighMorale() { return globalMorale > 70; }
     *     static int getMoraleBonus() { return globalMorale / 10; }
     * };
     * 
     * void FragTrap::highFivesGuys() {
     *     TeamMorale::boostMorale(20);
     *     std::cout << "Team morale: " << TeamMorale::globalMorale << "%" << std::endl;
     * }
     * ```
     */
}

/*
 * ====================================================================
 * 実装の詳細解説と設計判断
 * ====================================================================
 * 
 * 【FragTrapの戦術的位置づけ】
 * 
 * 攻撃特化型の特徴：
 * - 最高の攻撃力（30ダメージ）
 * - 最高のエネルギー効率（100ポイント）
 * - 同等の生存力（100HP）
 * - チーム支援能力（highFivesGuys）
 * 
 * 戦場での役割：
 * - 敵の主力を迅速に撃破
 * - 長期戦での継続活動
 * - チーム全体の士気管理
 * - 戦術的機動性の確保
 * 
 * 【ScavTrapとの差別化】
 * 
 * 能力値による差別化：
 * - エネルギー: 50 → 100 (2倍の行動力)
 * - 攻撃力: 20 → 30 (1.5倍の火力)
 * - HP: 100 → 100 (同等の生存性)
 * 
 * 特殊能力による差別化：
 * - ScavTrap: 個人的防御（guardGate）
 * - FragTrap: チーム支援（highFivesGuys）
 * 
 * 戦術的役割の差別化：
 * - ScavTrap: 守備・持久戦・陣地確保
 * - FragTrap: 攻撃・機動戦・チーム連携
 * 
 * 【バランス調整の考慮】
 * 
 * 強力な能力に対する制約：
 * - 特殊能力に防御効果なし
 * - エネルギー消費は他と同じ
 * - HP回復効率は基底クラスと同じ
 * - 特殊能力の実用効果は限定的
 * 
 * ゲームバランスの維持：
 * - 一方的な優位性の回避
 * - 各クラスの存在意義確保
 * - 状況による使い分けの促進
 * - プレイヤーの戦術選択肢拡大
 */

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【オブジェクト作成の例】
 * 
 * コード：
 * ```cpp
 * FragTrap bomber("Demolisher");
 * ```
 * 
 * 出力：
 * ```
 * ClapTrap constructor called for Demolisher
 * FragTrap constructor called for Demolisher
 * FragTrap Demolisher is armed with explosive capabilities!
 * Ready to boost team morale and deliver devastating attacks!
 * ```
 * 
 * 【攻撃の例】
 * 
 * コード：
 * ```cpp
 * bomber.attack("Enemy");
 * ```
 * 
 * 出力：
 * ```
 * FragTrap Demolisher explosively attacks Enemy, causing 30 points of damage!
 * FragTrap Demolisher has 99 energy points remaining for more explosive action!
 * ```
 * 
 * 【特殊能力の例】
 * 
 * コード：
 * ```cpp
 * bomber.highFivesGuys();
 * ```
 * 
 * 出力：
 * ```
 * FragTrap Demolisher requests positive high fives!
 * ✋ Team morale boost activated! ✋
 * Everyone feels more energized and ready for action!
 * ```
 * 
 * 【エネルギー不足の例】
 * 
 * コード：
 * ```cpp
 * // 100回攻撃後
 * bomber.attack("Target");
 * ```
 * 
 * 出力：
 * ```
 * FragTrap Demolisher cannot attack - insufficient energy for explosive operations!
 * Energy recharge required for continued combat!
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ 戦略的能力値設定の理解
 * □ 兄弟クラス間での実装一貫性
 * □ オーバーライドによる個性的な表現
 * □ チーム支援機能の実装パターン
 * □ protectedメンバへの適切なアクセス
 * □ エラーハンドリングの差別化
 * □ コンストラクタチェーンの正しい実装
 * □ Orthodox Canonical Formの継承版
 * □ デストラクタチェーンの理解
 * □ 戦術的バランスの考慮
 * 
 * 【実習課題】
 * 1. highFivesGuysに実際のゲーム効果を追加
 * 2. クリティカルヒットシステムの実装
 * 3. エネルギー効率の最適化テスト
 * 4. チーム戦闘システムでの連携実装
 * 5. 新しい特殊能力の追加設計
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：能力値設定の根拠不足】
 * 
 * 問題例：
 * ```cpp
 * FragTrap::FragTrap() : ClapTrap("DefaultFrag", 200, 200, 50) {
 *     // 他のクラスとのバランス無視
 * }
 * ```
 * 
 * 改善策：
 * - 他のクラスとの相対的バランス確認
 * - 総合能力値の制限設定
 * - 実際のテストによる調整
 * 
 * 【ミス2：メッセージの一貫性不足】
 * 
 * 問題例：
 * ```cpp
 * std::cout << "FragTrap gently attacks...";  // 攻撃型らしくない
 * ```
 * 
 * 改善策：
 * - クラスの特性に合った表現選択
 * - 他のクラスとの差別化明確化
 * - 一貫したトーンの維持
 * 
 * 【ミス3：特殊能力の価値不足】
 * 
 * 問題例：
 * ```cpp
 * void FragTrap::highFivesGuys() {
 *     std::cout << "High five!" << std::endl;  // 効果が薄い
 * }
 * ```
 * 
 * 改善策：
 * - 視覚的・説明的な効果の充実
 * - 将来の拡張可能性を考慮
 * - 他の特殊能力との価値バランス
 * 
 * 【ミス4：エラー処理の手抜き】
 * 
 * 問題例：
 * ```cpp
 * void FragTrap::attack(const std::string& target) {
 *     if (energyPoints > 0 && hitPoints > 0) {
 *         // 攻撃処理
 *     }
 *     // else文なし → エラー時の動作不明
 * }
 * ```
 * 
 * 改善策：
 * - 全ての状態に対する適切な処理
 * - 分かりやすいエラーメッセージ
 * - デバッグとユーザビリティの両立
 */

/*
 * ====================================================================
 * 発展的な実装アイデア
 * ====================================================================
 * 
 * 【アイデア1：爆発範囲システム】
 * ```cpp
 * class FragTrap : public ClapTrap {
 * private:
 *     int explosionRadius;
 * 
 * public:
 *     void attack(const std::string& target) override {
 *         if (canAttack()) {
 *             std::cout << "FragTrap " << name << " launches explosive attack!" << std::endl;
 *             // 範囲内の敵にダメージ
 *             dealAreaDamage(target, explosionRadius);
 *         }
 *     }
 * 
 * private:
 *     void dealAreaDamage(const std::string& center, int radius) {
 *         // 範囲攻撃の実装
 *     }
 * };
 * ```
 * 
 * 【アイデア2：チーム効果システム】
 * ```cpp
 * class TeamEffectManager {
 * private:
 *     static std::map<std::string, int> activeEffects;
 * 
 * public:
 *     static void applyMoraleBoost(const std::string& source, int duration) {
 *         activeEffects["morale_boost"] = duration;
 *     }
 *     
 *     static bool hasMoraleBoost() {
 *         return activeEffects["morale_boost"] > 0;
 *     }
 *     
 *     static void updateEffects() {
 *         for (auto& effect : activeEffects) {
 *             if (effect.second > 0) effect.second--;
 *         }
 *     }
 * };
 * 
 * void FragTrap::highFivesGuys() {
 *     TeamEffectManager::applyMoraleBoost(name, 5);  // 5ターン持続
 *     std::cout << "Team receives morale boost!" << std::endl;
 * }
 * ```
 * 
 * 【アイデア3：特殊弾薬システム】
 * ```cpp
 * enum AmmoType {
 *     STANDARD,
 *     EXPLOSIVE,
 *     INCENDIARY,
 *     ARMOR_PIERCING
 * };
 * 
 * class FragTrap : public ClapTrap {
 * private:
 *     AmmoType currentAmmo;
 *     std::map<AmmoType, int> ammoCount;
 * 
 * public:
 *     void switchAmmo(AmmoType type) {
 *         if (ammoCount[type] > 0) {
 *             currentAmmo = type;
 *             std::cout << "Switched to " << getAmmoTypeName(type) << std::endl;
 *         }
 *     }
 *     
 *     void attack(const std::string& target) override {
 *         if (canAttack()) {
 *             int damage = calculateDamage(currentAmmo);
 *             applySpecialEffect(target, currentAmmo);
 *             ammoCount[currentAmmo]--;
 *         }
 *     }
 * };
 * ```
 * 
 * 【アイデア4：レベルアップシステム】
 * ```cpp
 * class FragTrap : public ClapTrap {
 * private:
 *     int level;
 *     int experience;
 *     int nextLevelExp;
 * 
 * public:
 *     void gainExperience(int exp) {
 *         experience += exp;
 *         while (experience >= nextLevelExp) {
 *             levelUp();
 *         }
 *     }
 *     
 * private:
 *     void levelUp() {
 *         level++;
 *         experience -= nextLevelExp;
 *         nextLevelExp = calculateNextLevelExp(level);
 *         
 *         // 能力値向上
 *         hitPoints += 10;
 *         energyPoints += 5;
 *         attackDamage += 3;
 *         
 *         std::cout << "FragTrap " << name << " reached level " << level << "!" << std::endl;
 *     }
 * };
 * ```
 */