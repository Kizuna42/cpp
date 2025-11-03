/*
 * ====================================================================
 * CPP03 ex03: ダイヤモンド問題と仮想継承 - DiamondTrap実装解説版
 * ====================================================================
 * 
 * この実装では、C++で最も複雑な継承問題の実装を学習します。
 * - 多重継承での初期化リスト
 * - 曖昧性の実際の解決方法
 * - メモリレイアウトの理解
 * - OCFの複雑な実装
 */

#include "DiamondTrap.hpp"

/*
 * ====================================================================
 * デフォルトコンストラクタ - 多重継承での初期化
 * ====================================================================
 * 
 * DiamondTrap::DiamondTrap(void) 
 *     : ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), _name("default")
 * 
 * 【初期化リストの解析】
 * 
 * 1. ClapTrap("default_clap_name")
 *    - 直接的な基底クラス初期化
 *    - ダイヤモンド問題により2つのClapTrapが存在
 *    - 最初に見つかったClapTrapを初期化
 * 
 * 2. ScavTrap(), FragTrap()
 *    - 直接の基底クラス初期化
 *    - これらのコンストラクタは内部でClapTrapも初期化
 *    - 結果：ClapTrapのコンストラクタが複数回呼ばれる
 * 
 * 3. _name("default")
 *    - DiamondTrap固有のメンバ初期化
 *    - ClapTrap::_nameとは別の独立した変数
 * 
 * 【初期化順序】
 * C++の規則：宣言順序で初期化
 * 1. ScavTrap (最初の基底クラス)
 *    - 内部でClapTrapも初期化
 * 2. FragTrap (2番目の基底クラス)  
 *    - 内部で別のClapTrapも初期化
 * 3. DiamondTrap自身のメンバ (_name)
 */
DiamondTrap::DiamondTrap(void) : ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), _name("default") {
    /*
     * 【属性の明示的設定】
     * 
     * なぜ基底クラスの初期化後に再設定？
     * 
     * 問題：
     * - ScavTrapコンストラクタでHP=100, EP=50, AD=20を設定
     * - FragTrapコンストラクタでHP=100, EP=100, AD=30を設定
     * - 最後に呼ばれたFragTrapの値で上書きされる
     * 
     * 解決：
     * DiamondTrap独自の組み合わせを明示的に設定
     */
    
    /*
     * this->_hitPoints = 100;   // 100 from FragTrap
     * 
     * 【どのFragTrapから取得？】
     * ダイヤモンド問題により、技術的には複数のFragTrapが存在
     * しかし、実際のメモリレイアウトでは区別して管理
     * 
     * 設計判断：FragTrapの仕様に従ってHP=100を採用
     */
    this->_hitPoints = 100;   // 100 from FragTrap
    
    /*
     * this->_energyPoints = 50; // 50 from ScavTrap
     * 
     * ScavTrapの仕様に従ってEP=50を採用
     * FragTrapのEP=100ではなく、意図的にScavTrapを選択
     */
    this->_energyPoints = 50; // 50 from ScavTrap
    
    /*
     * this->_attackDamage = 30; // 30 from FragTrap
     * 
     * 再びFragTrapの仕様を採用
     * 
     * 【属性選択の論理】
     * DiamondTrapの設計仕様：
     * - HP: FragTrapの高い耐久力
     * - EP: ScavTrapの適度なエネルギー管理
     * - AD: FragTrapの高い攻撃力
     * 
     * これにより「各基底クラスの長所を組み合わせ」を実現
     */
    this->_attackDamage = 30; // 30 from FragTrap
    
    /*
     * デバッグ出力
     * 
     * 多重継承では初期化が複雑なため、
     * どのコンストラクタがいつ呼ばれるかを可視化
     */
    std::cout << "DiamondTrap default constructor called" << std::endl;
}

/*
 * ====================================================================
 * 名前付きコンストラクタ - 複雑な名前管理
 * ====================================================================
 * 
 * DiamondTrap::DiamondTrap(const std::string& name) 
 *     : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
 * 
 * 【名前管理戦略の詳細】
 * 
 * 1. ClapTrap(name + "_clap_name")
 *    基底クラス部分の名前を区別
 *    例：name="Hero" → ClapTrap::_name="Hero_clap_name"
 * 
 * 2. ScavTrap(name), FragTrap(name)  
 *    各中間クラスにも同じ名前を渡す
 *    内部でClapTrapを初期化するが、1.で指定した名前で上書き
 * 
 * 3. _name(name)
 *    DiamondTrap固有の名前を保持
 *    例：_name="Hero"
 * 
 * 【結果】
 * 1つのオブジェクトに3つの名前：
 * - DiamondTrap::_name = "Hero"
 * - ScavTrap::ClapTrap::_name = "Hero_clap_name"  
 * - FragTrap::ClapTrap::_name = "Hero_clap_name"
 * 
 * whoAmI()でこの区別を確認可能
 */
DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name) {
    /*
     * 属性設定（デフォルトコンストラクタと同じ）
     * 
     * 名前付きコンストラクタでも同じ組み合わせを採用
     */
    this->_hitPoints = 100;   // 100 from FragTrap
    this->_energyPoints = 50; // 50 from ScavTrap  
    this->_attackDamage = 30; // 30 from FragTrap
    
    /*
     * デバッグ出力で名前を表示
     * 初期化が正しく行われたかを確認
     */
    std::cout << "DiamondTrap " << this->_name << " constructor called" << std::endl;
}

/*
 * ====================================================================
 * コピーコンストラクタ - 多重継承でのコピー
 * ====================================================================
 * 
 * DiamondTrap::DiamondTrap(const DiamondTrap& other) 
 *     : ClapTrap(other), ScavTrap(other), FragTrap(other)
 * 
 * 【複数基底クラスからのコピー】
 * 
 * 各基底クラスのコピーコンストラクタを呼び出し
 * 1. ClapTrap(other) - ClapTrap部分をコピー
 * 2. ScavTrap(other) - ScavTrap部分をコピー（ClapTrap含む）
 * 3. FragTrap(other) - FragTrap部分をコピー（ClapTrap含む）
 * 
 * 【ダイヤモンド問題の影響】
 * ClapTrap部分が複数回コピーされる可能性
 * 実際のメモリレイアウトは複雑
 * 
 * 【代入演算子の再利用】
 * *this = other;
 * 
 * コピーコンストラクタで代入演算子を呼ぶパターン
 * DRY原則に従った実装
 */
DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other) {
    std::cout << "DiamondTrap copy constructor called" << std::endl;
    /*
     * 代入演算子を使用してコピー処理を委譲
     * 
     * これにより：
     * 1. コード重複を避ける
     * 2. 代入演算子の実装を再利用
     * 3. 保守性を向上
     */
    *this = other;
}

/*
 * ====================================================================
 * 代入演算子 - 多重継承での代入処理
 * ====================================================================
 * 
 * DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
 * 
 * 【多重継承での代入の複雑さ】
 * 
 * 単一継承の場合：
 * 基底クラスの代入演算子を1回呼ぶだけ
 * 
 * 多重継承の場合：
 * 複数の基底クラスをどう処理するか？
 * - すべての基底クラスの代入演算子を呼ぶ？
 * - 1つだけ選んで呼ぶ？
 * - カスタム実装？
 */
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    std::cout << "DiamondTrap assignment operator called" << std::endl;
    
    /*
     * 自己代入チェック（OCFの基本）
     */
    if (this != &other) {
        /*
         * ClapTrap::operator=(other);
         * 
         * 【重要な設計判断】
         * ClapTrapの代入演算子のみを呼ぶ
         * 
         * なぜScavTrapやFragTrapの代入演算子を呼ばない？
         * 1. ClapTrapが共通の基底クラス
         * 2. ScavTrapとFragTrapは追加データを持たない
         * 3. 重複した処理を避ける
         * 
         * 【代替実装】
         * より明示的なアプローチ：
         * this->_hitPoints = other._hitPoints;
         * this->_energyPoints = other._energyPoints;
         * this->_attackDamage = other._attackDamage;
         * 
         * しかし、基底クラスの代入演算子を使う方が保守性が高い
         */
        ClapTrap::operator=(other);
        
        /*
         * this->_name = other._name;
         * 
         * DiamondTrap固有のメンバの代入
         * 
         * ClapTrap::_name は基底クラスの代入演算子で処理済み
         * DiamondTrap::_name は明示的に代入が必要
         */
        this->_name = other._name;
    }
    
    /*
     * 自身への参照を返す（OCFの要件）
     * 連鎖代入を可能にする: a = b = c;
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタ - 多重継承での破棄順序
 * ====================================================================
 * 
 * ~DiamondTrap(void)
 * 
 * 【破棄順序の重要性】
 * 
 * C++の規則：
 * コンストラクタと逆順でデストラクタが呼ばれる
 * 
 * 構築順序：
 * 1. ScavTrap constructor (ClapTrapも)
 * 2. FragTrap constructor (ClapTrapも)
 * 3. DiamondTrap constructor
 * 
 * 破棄順序：
 * 1. DiamondTrap destructor (この関数)
 * 2. FragTrap destructor
 * 3. ScavTrap destructor  
 * 4. ClapTrap destructors (複数回?)
 * 
 * 【実際の動作】
 * コンソールでデストラクタの呼び出し順序を確認可能
 */
DiamondTrap::~DiamondTrap(void) {
    /*
     * DiamondTrap固有のクリーンアップ
     * 
     * 現在は特別な処理は不要
     * 基底クラスのデストラクタが自動で呼ばれる
     */
    std::cout << "DiamondTrap " << this->_name << " destructor called" << std::endl;
}

/*
 * ====================================================================
 * whoAmI() - ダイヤモンド問題の可視化
 * ====================================================================
 * 
 * void DiamondTrap::whoAmI(void)
 * 
 * 【DiamondTrap専用メソッドの意義】
 * 
 * このメソッドはダイヤモンド問題の影響を実際に見せる
 * 教育的価値が高い実装
 */
void DiamondTrap::whoAmI(void) {
    /*
     * 死亡チェック
     * 
     * ゲームロジックとして、HPが0の場合は行動不能
     * ClapTrapの仕様を継承した設計
     */
    if (this->_hitPoints == 0) {
        std::cout << "DiamondTrap is dead and cannot identify itself!" << std::endl;
        return;
    }
    
    /*
     * std::cout << "DiamondTrap name: " << this->_name << std::endl;
     * 
     * DiamondTrap固有の名前を表示
     * これは明確でシンプル
     */
    std::cout << "DiamondTrap name: " << this->_name << std::endl;
    
    /*
     * std::cout << "ClapTrap name: " << ClapTrap::_name << std::endl;
     * 
     * 【曖昧性解決の実践】
     * 
     * 単に this->_name と書けない理由：
     * DiamondTrapには複数の_nameが存在：
     * - DiamondTrap::_name (独自)
     * - ScavTrap::ClapTrap::_name (継承)
     * - FragTrap::ClapTrap::_name (継承)
     * 
     * ClapTrap::_name と明示することで曖昧性を解決
     * 
     * 【実際にはどちらのClapTrap::_nameにアクセス？】
     * コンパイラの実装依存だが、通常は最初に見つかったもの
     * 実用的にはどちらも同じ値を持つべき
     */
    std::cout << "ClapTrap name: " << ClapTrap::_name << std::endl;
}

/*
 * ====================================================================
 * getName() - オーバーライドによる名前取得
 * ====================================================================
 * 
 * std::string DiamondTrap::getName(void) const
 * 
 * 【基底クラスメソッドのオーバーライド】
 * 
 * ClapTrap::getName() はClapTrap::_name を返す
 * DiamondTrap::getName() はDiamondTrap::_name を返す
 * 
 * これにより、DiamondTrapオブジェクトでgetName()を呼ぶと
 * DiamondTrap固有の名前が取得できる
 */
std::string DiamondTrap::getName(void) const {
    /*
     * DiamondTrap::_name を返す
     * 
     * 【const correctness】
     * constメソッドなので、オブジェクトの状態を変更しない
     * const DiamondTrap からも呼び出し可能
     * 
     * 【ポリモーフィズムの限界】
     * ClapTrap::getName()がvirtualでない場合、
     * ポリモーフィズムは動作しない
     * 
     * 例：
     * ClapTrap* ptr = new DiamondTrap("Hero");
     * ptr->getName(); // ClapTrap::getName()が呼ばれる
     *                 // DiamondTrap::getName()ではない
     */
    return this->_name;
}

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このファイルから学ぶべきこと】
 * 
 * 1. 多重継承での初期化
 *    - 初期化リストでの複数基底クラス指定
 *    - 初期化順序の理解
 *    - 属性の明示的設定
 * 
 * 2. ダイヤモンド問題の実際
 *    - 曖昧性の具体的な発生場面
 *    - スコープ解決による回避
 *    - using宣言の効果
 * 
 * 3. OCFの複雑な実装
 *    - 多重継承でのコピー/代入
 *    - デストラクタの呼び出し順序
 *    - 自己代入チェックの重要性
 * 
 * 4. 実用的な設計判断
 *    - 名前管理戦略
 *    - メソッドオーバーライドの使い分け  
 *    - デバッグ支援機能の実装
 * 
 * 【次のステップ】
 * - 仮想継承での解決方法の比較
 * - より良い設計パターンの検討
 * - 実用プロジェクトでの応用
 */

/*
 * ====================================================================
 * よくある質問と回答
 * ====================================================================
 * 
 * Q: なぜClapTrapコンストラクタが複数回呼ばれる？
 * A: ダイヤモンド問題により、ScavTrapとFragTrapが
 *    それぞれClapTrapを継承しているため。
 *    仮想継承を使えば1回だけになる。
 * 
 * Q: using ScavTrap::attack; の効果は？
 * A: DiamondTrapでattack()を呼ぶ際の曖昧性を解決。
 *    ScavTrapのattack()が選択される。
 * 
 * Q: whoAmI()で表示される2つの名前の違いは？
 * A: DiamondTrap name は固有名、
 *    ClapTrap name は基底クラス部分の名前（"_clap_name"付き）。
 * 
 * Q: 代入演算子でScavTrap::operator=を呼ばない理由は？
 * A: ScavTrapは追加データを持たず、
 *    ClapTrapの代入で十分。重複処理を避ける。
 */

/*
 * ====================================================================
 * メモリレイアウトの理解
 * ====================================================================
 * 
 * DiamondTrapオブジェクトのメモリ構成（概念図）：
 * 
 * +-------------------+
 * | ScavTrap部分      |
 * |  +-------------+  |  
 * |  | ClapTrap部分|  |
 * |  | _name       |  |  "Hero_clap_name"
 * |  | _hitPoints  |  |  100
 * |  | _energyPoints|  |  50  
 * |  | _attackDamage|  |  30
 * |  +-------------+  |
 * +-------------------+
 * | FragTrap部分      |
 * |  +-------------+  |
 * |  | ClapTrap部分|  |  (重複!)
 * |  | _name       |  |  "Hero_clap_name"  
 * |  | _hitPoints  |  |  100
 * |  | _energyPoints|  |  50
 * |  | _attackDamage|  |  30
 * |  +-------------+  |
 * +-------------------+
 * | DiamondTrap部分   |
 * | _name             |  "Hero"
 * +-------------------+
 * 
 * 【問題点】
 * - ClapTrapのデータが重複
 * - メモリの無駄
 * - 曖昧性の原因
 * 
 * 【仮想継承での解決】
 * ClapTrap部分が1つだけ存在
 * メモリ効率とアクセスの明確性が向上
 */

/*
 * ====================================================================
 * 実用的な改善案
 * ====================================================================
 * 
 * 【改善1: 仮想継承の使用】
 * class ScavTrap : virtual public ClapTrap { ... };
 * class FragTrap : virtual public ClapTrap { ... };
 * 
 * 【改善2: コンポジション使用】
 * class DiamondTrap {
 *     ClapTrap base;
 *     ScavAbility scavFeatures;
 *     FragAbility fragFeatures;
 * };
 * 
 * 【改善3: インターフェース分離】
 * class IScavable { virtual void guardGate() = 0; };
 * class IFragable { virtual void highFivesGuys() = 0; };
 * class DiamondTrap : public ClapTrap, public IScavable, public IFragable {};
 * 
 * 各手法にはトレードオフがあり、
 * 要件に応じて最適な選択をする
 */