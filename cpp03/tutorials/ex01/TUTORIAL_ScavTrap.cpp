/*
 * ====================================================================
 * CPP03 ex01: ScavTrap - 継承実装の詳細解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 継承でのコンストラクタ・デストラクタ実装
 * - 基底クラスのメンバ初期化リスト使用法
 * - メンバ関数のオーバーライド実装
 * - Orthodox Canonical Formの継承版
 * - protectedメンバへのアクセス実践
 * 
 * 【重要概念】
 * - 基底クラスコンストラクタの明示的呼び出し
 * - コンストラクタ・デストラクタチェーン
 * - 仮想関数による動的バインディング
 * - 継承での代入演算子の適切な実装
 * - スライシング問題の回避
 */

#include "ScavTrap.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * ScavTrap::ScavTrap()
 * 
 * 継承でのデフォルトコンストラクタの特徴：
 * 
 * 実行順序：
 * 1. ClapTrap のデフォルトコンストラクタ自動呼び出し
 * 2. ScavTrap の初期化処理実行
 * 
 * 基底クラス初期化の選択肢：
 * - 何も指定しない → ClapTrap() が呼ばれる
 * - 明示的指定 → ClapTrap(パラメータ) を呼び出す
 * 
 * ScavTrap用の初期値設定：
 * - hitPoints: 100 (ClapTrapより強化)
 * - energyPoints: 50 (ClapTrapより強化)
 * - attackDamage: 20 (ClapTrapより強化)
 */
ScavTrap::ScavTrap() : ClapTrap("DefaultScav", 100, 50, 20) {
    /*
     * 【基底クラス初期化の解説】
     * 
     * ClapTrap("DefaultScav", 100, 50, 20) の呼び出し：
     * 1. name を "DefaultScav" に設定
     * 2. hitPoints を 100 に設定
     * 3. energyPoints を 50 に設定
     * 4. attackDamage を 20 に設定
     * 
     * なぜこの値なのか？
     * - ScavTrapは門番として設計された戦闘ユニット
     * - ClapTrapよりも強力である必要がある
     * - 守備に特化した能力値設定
     */
    
    /*
     * 【ScavTrap固有の初期化】
     * 
     * 追加メンバ変数があれば、ここで初期化
     * 現在は基底クラスの能力値変更のみ
     */
    
    /*
     * 【デバッグ出力】
     * 
     * コンストラクタチェーンの確認：
     * - ClapTrapコンストラクタの出力が先に表示される
     * - その後にScavTrapコンストラクタの出力
     * - 実行順序の理解を助ける
     */
    std::cout << "ScavTrap default constructor called for " << name << std::endl;
    std::cout << "ScavTrap " << name << " is ready to guard the gate!" << std::endl;
}

/*
 * 【パラメータ付きコンストラクタ】
 * ScavTrap::ScavTrap(const std::string& name)
 * 
 * 名前指定での ScavTrap 作成：
 * 
 * メンバ初期化リストの使用：
 * - ClapTrap(name, 100, 50, 20) で基底クラス初期化
 * - 適切なコンストラクタを選択して呼び出し
 * - 効率的で安全な初期化方法
 */
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name, 100, 50, 20) {
    /*
     * 【メンバ初期化リストの重要性】
     * 
     * 以下のような実装は推奨されない：
     * ```cpp
     * ScavTrap::ScavTrap(const std::string& name) {
     *     this->name = name;           // 代入（効率的でない）
     *     this->hitPoints = 100;       // 代入（効率的でない）
     *     this->energyPoints = 50;     // 代入（効率的でない）
     *     this->attackDamage = 20;     // 代入（効率的でない）
     * }
     * ```
     * 
     * メンバ初期化リストの利点：
     * - 初期化と代入の区別
     * - const メンバの初期化可能
     * - 参照メンバの初期化可能
     * - 効率的（代入ではなく初期化）
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * コンストラクタチェーンの可視化：
     * 1. ClapTraP コンストラクタ: "ClapTrap constructor called for <name>"
     * 2. ScavTrap コンストラクタ: "ScavTrap constructor called for <name>"
     */
    std::cout << "ScavTrap constructor called for " << name << std::endl;
    std::cout << "ScavTrap " << name << " is equipped with enhanced gate-keeping abilities!" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * ScavTrap::ScavTrap(const ScavTrap& other)
 * 
 * 継承でのコピーコンストラクタの実装：
 * 
 * 基底クラス部分のコピー：
 * - ClapTrap(other) で基底クラスのコピーコンストラクタ呼び出し
 * - otherオブジェクトのClapTrap部分が適切にコピーされる
 * - スライシングを避けた正しいコピー
 */
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    /*
     * 【基底クラスコピーの仕組み】
     * 
     * ClapTrap(other) の動作：
     * 1. other オブジェクトの ClapTrap 部分を参照
     * 2. ClapTrap のコピーコンストラクタを呼び出し
     * 3. name, hitPoints, energyPoints, attackDamage をコピー
     * 
     * 型の安全性：
     * - ScavTrap& other から ClapTrap& への安全な変換
     * - is-a 関係による自然な変換
     */
    
    /*
     * 【ScavTrap固有メンバのコピー】
     * 
     * 現在は追加メンバ変数がないため特別な処理は不要
     * 将来的に追加メンバがある場合：
     * ```cpp
     * this->guardMode = other.guardMode;
     * this->specialAbility = other.specialAbility;
     * ```
     */
    
    /*
     * 【デバッグ出力】
     * 
     * コピー操作の確認：
     * - どのオブジェクトがコピーされたかを表示
     * - コピーコンストラクタの呼び出し確認
     */
    std::cout << "ScavTrap copy constructor called" << std::endl;
    std::cout << "ScavTrap " << name << " has been cloned with gate-keeping knowledge!" << std::endl;
}

/*
 * 【代入演算子】
 * ScavTrap& ScavTrap::operator=(const ScavTrap& other)
 * 
 * 継承での代入演算子の適切な実装：
 * 
 * 実装のポイント：
 * 1. 自己代入チェック
 * 2. 基底クラスの代入演算子呼び出し
 * 3. 派生クラス固有メンバの代入
 * 4. *this の返却
 */
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    /*
     * 【自己代入チェック】
     * 
     * if (this != &other) の重要性：
     * - 同じオブジェクトへの代入を防止
     * - 効率性の向上
     * - 自己破壊の防止（リソース管理がある場合）
     * 
     * アドレス比較による判定：
     * - this: 現在のオブジェクトのアドレス
     * - &other: 代入元オブジェクトのアドレス
     */
    if (this != &other) {
        /*
         * 【基底クラスの代入演算子呼び出し】
         * 
         * ClapTrap::operator=(other) の実行：
         * - ClapTrap部分の適切な代入
         * - name, hitPoints, energyPoints, attackDamage の代入
         * - 基底クラスのロジックを再利用
         */
        ClapTrap::operator=(other);
        
        /*
         * 【ScavTrap固有メンバの代入】
         * 
         * 現在は追加メンバなし、将来の拡張例：
         * ```cpp
         * this->guardMode = other.guardMode;
         * this->gatePosition = other.gatePosition;
         * this->specialAbilities = other.specialAbilities;
         * ```
         */
        
        /*
         * 【デバッグ出力】
         * 
         * 代入操作の確認：
         * - 代入が実行されたことを通知
         * - オブジェクトの状態変更を可視化
         */
        std::cout << "ScavTrap assignment operator called" << std::endl;
        std::cout << "ScavTrap " << name << " has learned new gate-keeping techniques!" << std::endl;
    }
    
    /*
     * 【*this の返却】
     * 
     * 戻り値の重要性：
     * - 連鎖代入の有効化: a = b = c
     * - 一貫性のあるインターフェース
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
 * ScavTrap::~ScavTrap()
 * 
 * 継承でのデストラクタの特徴：
 * 
 * 実行順序（コンストラクタの逆）：
 * 1. ScavTrap のデストラクタ実行
 * 2. ClapTrap のデストラクタ自動実行
 * 
 * 仮想デストラクタの重要性：
 * - 基底クラスポインタ経由の削除で正しく動作
 * - 多態性を使用する場合は必須
 * - メモリリークの防止
 */
ScavTrap::~ScavTrap() {
    /*
     * 【ScavTrap固有のクリーンアップ】
     * 
     * 実行される処理：
     * - ScavTrap専用リソースの解放
     * - 特殊能力の無効化
     * - 門番モードの解除
     * 
     * 基底クラスのクリーンアップ：
     * - ClapTrapのデストラクタが自動実行される
     * - 手動で呼び出す必要はない
     * - 呼び出し順序は C++ が保証
     */
    
    /*
     * 【デバッグ出力】
     * 
     * デストラクタチェーンの確認：
     * 1. ScavTrap デストラクタ: "ScavTrap destructor called"
     * 2. ClapTrap デストラクタ: "ClapTrap destructor called"
     */
    std::cout << "ScavTrap destructor called for " << name << std::endl;
    std::cout << "ScavTrap " << name << " has finished gate-keeping duties!" << std::endl;
}

/*
 * ====================================================================
 * オーバーライド関数の実装
 * ====================================================================
 */

/*
 * 【attack関数のオーバーライド】
 * void ScavTrap::attack(const std::string& target)
 * 
 * ClapTrap::attack() のオーバーライド：
 * 
 * オーバーライドの目的：
 * - ScavTrap専用の攻撃メッセージ
 * - より威圧的で門番らしい表現
 * - 基本的なロジックは同じだが、表現を変更
 * 
 * 実装の選択肢：
 * 1. 完全に新規実装（現在の方法）
 * 2. 基底クラス呼び出し + 追加処理
 * 3. Template Method パターンの活用
 */
void ScavTrap::attack(const std::string& target) {
    /*
     * 【攻撃可能性のチェック】
     * 
     * ClapTrap::attack() と同じ条件：
     * - energyPoints > 0: エネルギーが残っている
     * - hitPoints > 0: 生きている（HP > 0）
     * 
     * protectedメンバへのアクセス：
     * - name, hitPoints, energyPoints, attackDamage
     * - 継承により派生クラスからアクセス可能
     */
    if (energyPoints > 0 && hitPoints > 0) {
        /*
         * 【ScavTrap専用攻撃メッセージ】
         * 
         * ClapTrap版との違い：
         * - "ClapTrap" → "ScavTrap"
         * - "attacks" → "fiercely attacks"
         * - より威圧的で強力な印象
         * - 門番としての威厳を表現
         */
        std::cout << "ScavTrap " << name << " fiercely attacks " << target 
                  << ", causing " << attackDamage << " points of damage!" << std::endl;
        
        /*
         * 【エネルギーポイントの消費】
         * 
         * ClapTrapと同じ仕組み：
         * - 攻撃には1エネルギーポイント必要
         * - エネルギーが0になると攻撃不可
         * - リソース管理の一貫性
         */
        energyPoints--;
        
        /*
         * 【攻撃後の状態表示】
         * 
         * デバッグ・学習目的の情報：
         * - 残りエネルギーポイントの表示
         * - 攻撃の成功確認
         * - 戦闘状況の可視化
         */
        std::cout << "ScavTrap " << name << " has " << energyPoints 
                  << " energy points remaining" << std::endl;
    } else {
        /*
         * 【攻撃不可能時の処理】
         * 
         * エラー条件：
         * - energyPoints == 0: エネルギー不足
         * - hitPoints == 0: 戦闘不能状態
         * 
         * ScavTrap専用メッセージ：
         * - 門番らしい表現
         * - 攻撃不可の理由を暗示
         */
        if (hitPoints == 0) {
            std::cout << "ScavTrap " << name 
                      << " cannot attack - the gate guardian has fallen!" << std::endl;
        } else {
            std::cout << "ScavTrap " << name 
                      << " cannot attack - insufficient energy to guard the gate!" << std::endl;
        }
    }
}

/*
 * ====================================================================
 * ScavTrap固有機能の実装
 * ====================================================================
 */

/*
 * 【Gate keeper mode機能】
 * void ScavTrap::guardGate()
 * 
 * ScavTrap専用の特殊能力：
 * 
 * 機能の詳細：
 * - 門番モードの有効化
 * - 特殊な防御状態への移行
 * - 戦術的な優位性の獲得
 * 
 * 実装の考慮点：
 * - 生存確認（hitPoints > 0）
 * - エネルギー消費の有無
 * - 状態変更の通知
 */
void ScavTrap::guardGate() {
    /*
     * 【使用可能性のチェック】
     * 
     * 基本条件：
     * - hitPoints > 0: 生きている必要がある
     * - 戦闘不能状態では門番不可
     * 
     * 拡張可能な条件：
     * - energyPoints >= requiredEnergy: エネルギー要件
     * - !alreadyGuarding: 重複防止
     * - locationIsGate: 門の近くにいる必要
     */
    if (hitPoints > 0) {
        /*
         * 【門番モード有効化】
         * 
         * 現在の実装：
         * - メッセージ出力のみ
         * - 状態変更なし（シンプル実装）
         * 
         * 拡張可能な実装：
         * ```cpp
         * this->guardingMode = true;
         * this->defenseBonus = 5;
         * this->energyPoints -= GUARD_ENERGY_COST;
         * ```
         */
        std::cout << "ScavTrap " << name << " is now in Gate keeper mode!" << std::endl;
        std::cout << "The gate is under the fierce protection of " << name << "!" << std::endl;
        
        /*
         * 【特殊効果の説明】
         * 
         * 門番モードの効果（概念的）：
         * - 防御力向上
         * - 特定エリアの制御
         * - 侵入者の検出強化
         * - 威嚇効果による心理的優位性
         */
        std::cout << "Warning: Unauthorized access will be met with fierce resistance!" << std::endl;
    } else {
        /*
         * 【使用不可時の処理】
         * 
         * 戦闘不能状態での処理：
         * - 明確なエラーメッセージ
         * - 状態の説明
         * - 復活の必要性を示唆
         */
        std::cout << "ScavTrap " << name 
                  << " cannot guard the gate - the guardian has fallen!" << std::endl;
        std::cout << "The gate remains unprotected until " << name 
                  << " is repaired!" << std::endl;
    }
}

/*
 * ====================================================================
 * 実装の詳細解説と学習ポイント
 * ====================================================================
 * 
 * 【コンストラクタチェーンの実際の動作】
 * 
 * ScavTrap scav("Guardian"); の実行時：
 * 
 * 1. メモリ確保
 *    - ScavTrapオブジェクト用のメモリ確保
 *    - ClapTrap部分 + ScavTrap部分
 * 
 * 2. ClapTrapコンストラクタ実行
 *    - ClapTrap("Guardian", 100, 50, 20) 呼び出し
 *    - "ClapTrap constructor called for Guardian" 出力
 *    - メンバ変数の初期化
 * 
 * 3. ScavTrapコンストラクタ実行
 *    - "ScavTrap constructor called for Guardian" 出力
 *    - 追加の初期化処理
 * 
 * 4. オブジェクト使用可能
 *    - 全ての初期化完了
 *    - ClapTrapとScavTrapの機能利用可能
 * 
 * 【デストラクタチェーンの実際の動作】
 * 
 * スコープ終了時またはdelete時：
 * 
 * 1. ScavTrapデストラクタ実行
 *    - "ScavTrap destructor called for Guardian" 出力
 *    - ScavTrap固有のクリーンアップ
 * 
 * 2. ClapTrapデストラクタ自動実行
 *    - "ClapTrap destructor called for Guardian" 出力
 *    - 基底クラスのクリーンアップ
 * 
 * 3. メモリ解放
 *    - オブジェクト用メモリの自動解放
 *    - RAIIパターンの完了
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
 * ScavTrap guard("Fortress");
 * ```
 * 
 * 出力：
 * ```
 * ClapTrap constructor called for Fortress
 * ScavTrap constructor called for Fortress
 * ScavTrap Fortress is equipped with enhanced gate-keeping abilities!
 * ```
 * 
 * 【攻撃の例】
 * 
 * コード：
 * ```cpp
 * guard.attack("Intruder");
 * ```
 * 
 * 出力：
 * ```
 * ScavTrap Fortress fiercely attacks Intruder, causing 20 points of damage!
 * ScavTrap Fortress has 49 energy points remaining
 * ```
 * 
 * 【門番モードの例】
 * 
 * コード：
 * ```cpp
 * guard.guardGate();
 * ```
 * 
 * 出力：
 * ```
 * ScavTrap Fortress is now in Gate keeper mode!
 * The gate is under the fierce protection of Fortress!
 * Warning: Unauthorized access will be met with fierce resistance!
 * ```
 * 
 * 【コピーの例】
 * 
 * コード：
 * ```cpp
 * ScavTrap guard2(guard);
 * ```
 * 
 * 出力：
 * ```
 * ClapTrap copy constructor called
 * ScavTrap copy constructor called
 * ScavTrap Fortress has been cloned with gate-keeping knowledge!
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ メンバ初期化リストでの基底クラスコンストラクタ呼び出し
 * □ コンストラクタ・デストラクタチェーンの理解
 * □ protectedメンバへの適切なアクセス
 * □ オーバーライド関数の正しい実装
 * □ 自己代入チェックを含む代入演算子
 * □ 基底クラスの代入演算子呼び出し
 * □ 継承でのコピーコンストラクタ実装
 * □ ScavTrap固有機能の追加実装
 * □ エラーハンドリングとメッセージ出力
 * □ RAII原則の継承での適用
 * 
 * 【実習課題】
 * 1. guardGateにエネルギー消費を追加
 * 2. 攻撃時のクリティカルヒット実装
 * 3. 門番モード時の防御力向上
 * 4. 複数の特殊能力追加
 * 5. 状態管理システムの実装
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：基底クラスの初期化忘れ】
 * 
 * 間違い例：
 * ```cpp
 * ScavTrap::ScavTrap(const std::string& name) {
 *     // ClapTrapのデフォルトコンストラクタが呼ばれる
 *     // 意図した初期化がされない
 * }
 * ```
 * 
 * 正解：
 * ```cpp
 * ScavTrap::ScavTrap(const std::string& name) 
 *     : ClapTrap(name, 100, 50, 20) {
 *     // 意図した初期化
 * }
 * ```
 * 
 * 【ミス2：代入演算子での基底クラス呼び忘れ】
 * 
 * 間違い例：
 * ```cpp
 * ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
 *     if (this != &other) {
 *         // 基底クラス部分が代入されない！
 *         // ScavTrap固有の処理のみ
 *     }
 *     return *this;
 * }
 * ```
 * 
 * 正解：
 * ```cpp
 * ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
 *     if (this != &other) {
 *         ClapTrap::operator=(other);  // 重要！
 *         // ScavTrap固有の処理
 *     }
 *     return *this;
 * }
 * ```
 * 
 * 【ミス3：protectedメンバアクセスの誤解】
 * 
 * 間違い例：
 * ```cpp
 * void ScavTrap::someFunction() {
 *     ClapTrap other;
 *     other.name = "test";  // エラー！他のオブジェクトのprotected
 * }
 * ```
 * 
 * 理解すべき点：
 * - protectedは「同じクラスまたは派生クラス」かつ「同じオブジェクト」
 * - 他のオブジェクトのprotectedメンバは直接アクセス不可
 * 
 * 【ミス4：仮想デストラクタの理解不足】
 * 
 * 問題のあるコード：
 * ```cpp
 * ClapTrap* ptr = new ScavTrap("Guard");
 * delete ptr;  // ScavTrapのデストラクタが呼ばれない可能性
 * ```
 * 
 * 対策：
 * ```cpp
 * class ClapTrap {
 * public:
 *     virtual ~ClapTrap();  // 仮想デストラクタ
 * };
 * ```
 */

/*
 * ====================================================================
 * 発展的な継承テクニック
 * ====================================================================
 * 
 * 【テクニック1：基底クラス機能の拡張】
 * ```cpp
 * void ScavTrap::attack(const std::string& target) {
 *     // 前処理
 *     std::cout << "ScavTrap prepares for fierce attack!" << std::endl;
 *     
 *     // 基底クラスの機能を呼び出し
 *     ClapTrap::attack(target);
 *     
 *     // 後処理
 *     std::cout << "ScavTrap attack complete!" << std::endl;
 * }
 * ```
 * 
 * 【テクニック2：Template Method パターン】
 * ```cpp
 * class ClapTrap {
 * protected:
 *     virtual void performSpecialEffect() {}  // フック関数
 * 
 * public:
 *     void attack(const std::string& target) {
 *         if (canAttack()) {
 *             std::cout << "Basic attack message" << std::endl;
 *             performSpecialEffect();  // 派生クラスで実装
 *             consumeEnergy();
 *         }
 *     }
 * };
 * 
 * class ScavTrap : public ClapTrap {
 * protected:
 *     void performSpecialEffect() override {
 *         std::cout << "Gate guardian's fierce strike!" << std::endl;
 *     }
 * };
 * ```
 * 
 * 【テクニック3：CRTP（Curiously Recurring Template Pattern）】
 * ```cpp
 * template<typename Derived>
 * class ClapTrapBase {
 * public:
 *     void attack(const std::string& target) {
 *         static_cast<Derived*>(this)->doAttack(target);
 *     }
 * };
 * 
 * class ScavTrap : public ClapTrapBase<ScavTrap> {
 * public:
 *     void doAttack(const std::string& target) {
 *         // ScavTrap固有の攻撃実装
 *     }
 * };
 * ```
 * 
 * 【テクニック4：Mixin パターン】
 * ```cpp
 * template<typename Base>
 * class GuardAbility : public Base {
 * public:
 *     template<typename... Args>
 *     GuardAbility(Args&&... args) : Base(std::forward<Args>(args)...) {}
 *     
 *     void guardGate() {
 *         std::cout << "Guarding with enhanced abilities!" << std::endl;
 *     }
 * };
 * 
 * using ScavTrap = GuardAbility<ClapTrap>;
 * ```
 */