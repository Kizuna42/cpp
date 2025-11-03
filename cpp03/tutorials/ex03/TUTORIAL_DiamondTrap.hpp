/*
 * ====================================================================
 * CPP03 ex03: ダイヤモンド問題と仮想継承 - DiamondTrapヘッダー解説版
 * ====================================================================
 * 
 * この演習はC++継承の最も複雑な問題「ダイヤモンド問題」を学習します。
 * 
 * 継承階層:
 *        ClapTrap
 *       /        \
 *  ScavTrap    FragTrap
 *       \        /
 *      DiamondTrap
 * 
 * この構造で発生する問題と解決方法を完全理解します。
 */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

/*
 * ====================================================================
 * ダイヤモンド問題とは何か？
 * ====================================================================
 * 
 * 【問題の発生原因】
 * 
 * 継承階層:
 *        ClapTrap (基底クラス)
 *       /        \
 *  ScavTrap    FragTrap (中間クラス)
 *       \        /
 *      DiamondTrap (最終クラス)
 * 
 * DiamondTrap は ScavTrap と FragTrap の両方を継承
 * → ScavTrap と FragTrap はそれぞれ ClapTrap を継承
 * → DiamondTrap には ClapTrap が2つ存在する！
 * 
 * 【具体的な問題】
 * 
 * 1. 曖昧性（Ambiguity）
 *    diamond._name にアクセスするとき、
 *    ScavTrap::_name か FragTrap::_name か判断不能
 * 
 * 2. メモリの無駄
 *    ClapTrap のメンバが2重に存在
 * 
 * 3. 論理的矛盾
 *    「1つのオブジェクトに2つの基底クラス」は不自然
 */

/*
 * ====================================================================
 * 解決方法1: 仮想継承 (Virtual Inheritance)
 * ====================================================================
 * 
 * 【理想的な解決】
 * ScavTrap と FragTrap で virtual 継承を使用:
 * 
 * class ScavTrap : virtual public ClapTrap { ... };
 * class FragTrap : virtual public ClapTrap { ... };
 * 
 * 効果: ClapTrap のインスタンスが1つだけ存在
 * 
 * 【42スクールでの制約】
 * 既存のex01, ex02のコードを変更禁止
 * → 仮想継承を使用できない
 * → 代替解決策が必要
 */

/*
 * ====================================================================
 * 解決方法2: 明示的な曖昧性解決（42スクール採用）
 * ====================================================================
 * 
 * 仮想継承を使わずに問題を回避:
 * 1. using宣言で特定の基底クラスを選択
 * 2. 独自の名前属性で識別問題を解決
 * 3. 明示的なスコープ解決でアクセス
 * 
 * これは「問題の完全解決」ではなく「問題の回避」
 * 実際のプロジェクトでは仮想継承を推奨
 */

/*
 * ====================================================================
 * DiamondTrap クラス - 多重継承の実践
 * ====================================================================
 * 
 * class DiamondTrap : public ScavTrap, public FragTrap
 * 
 * 【継承の順序】
 * public ScavTrap, public FragTrap
 * 
 * 継承順序が重要な理由:
 * 1. コンストラクタの呼び出し順序
 * 2. メンバの初期化順序
 * 3. メモリレイアウト
 * 
 * 【アクセス権限】
 * public継承により、基底クラスのpublicメンバは
 * DiamondTrapのpublicメンバとして継承
 */
class DiamondTrap : public ScavTrap, public FragTrap {
private:
    /*
     * std::string _name;
     * 
     * 【なぜ独自の_nameが必要？】
     * 
     * 問題: ClapTrap::_name が2つ存在
     * - ScavTrap::ClapTrap::_name
     * - FragTrap::ClapTrap::_name
     * 
     * 解決: DiamondTrap独自の_nameで識別
     * 
     * 【設計判断】
     * private修飾の理由:
     * 1. カプセル化の原則
     * 2. 基底クラスの_nameとの区別
     * 3. whoAmI()での明確な識別
     * 
     * 【メモリレイアウト】
     * DiamondTrapのメモリ構成:
     * - ScavTrap部分（ClapTrapを含む）
     * - FragTrap部分（ClapTrapを含む）
     * - DiamondTrap::_name (独自)
     * 
     * 結果: ClapTrapのデータが2重に存在
     */
    std::string _name;  // Private name attribute separate from ClapTrap::_name

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form (OCF)
     * ====================================================================
     * 
     * 多重継承でもOCFの4要素は必要
     * ただし、実装がより複雑になる
     */
    
    /*
     * DiamondTrap(void);
     * 
     * デフォルトコンストラクタ
     * 
     * 【初期化の課題】
     * 複数の基底クラスを初期化する必要
     * どの基底クラスのコンストラクタをどの順序で呼ぶか
     * 
     * 【属性の統合】
     * DiamondTrapの属性は各基底クラスから選択:
     * - HP: FragTrap (100)
     * - EP: ScavTrap (50)  
     * - AD: FragTrap (30)
     * 
     * これらを明示的に設定する必要
     */
    DiamondTrap(void);
    
    /*
     * DiamondTrap(const std::string& name);
     * 
     * 名前付きコンストラクタ
     * 
     * 【名前の管理戦略】
     * DiamondTrap::_name = name
     * ClapTrap::_name = name + "_clap_name"
     * 
     * この戦略により:
     * 1. DiamondTrap固有の名前を保持
     * 2. ClapTrap部分の名前も明確
     * 3. whoAmI()で両方を表示可能
     */
    DiamondTrap(const std::string& name);
    
    /*
     * コピーコンストラクタと代入演算子
     * 
     * 【多重継承での複雑さ】
     * 複数の基底クラスからのコピーが必要
     * どの基底クラスのデータをどうコピーするか
     */
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    
    /*
     * ~DiamondTrap(void);
     * 
     * デストラクタ
     * 
     * 【破棄順序】
     * C++の規則：派生→基底の順序で破棄
     * 1. DiamondTrap destructor
     * 2. FragTrap destructor
     * 3. ScavTrap destructor
     * 4. ClapTrap destructors (2回)
     */
    ~DiamondTrap(void);
    
    /*
     * ====================================================================
     * 曖昧性解決 - using宣言
     * ====================================================================
     * 
     * using ScavTrap::attack;
     * 
     * 【問題】
     * DiamondTrapは2つのattack()を継承:
     * - ScavTrap::attack()
     * - FragTrap::attack() (実際はClapTrap::attack())
     * 
     * diamond.attack("target"); // ← どちらが呼ばれる？
     * 
     * 【解決】
     * using宣言でScavTrap::attack()を選択
     * 
     * 【using宣言の効果】
     * - ScavTrap::attack()をDiamondTrapのスコープに導入
     * - 曖昧性を解決
     * - 明示的な選択の表現
     * 
     * 【代替方法】
     * using宣言を使わない場合:
     * diamond.ScavTrap::attack("target"); // 明示的スコープ解決
     */
    using ScavTrap::attack;  // Use ScavTrap's attack method
    
    /*
     * ====================================================================
     * DiamondTrap固有機能
     * ====================================================================
     */
    
    /*
     * void whoAmI(void);
     * 
     * 【DiamondTrap専用メソッド】
     * 
     * 機能:
     * - DiamondTrap::_name を表示
     * - ClapTrap::_name を表示  
     * - 2つの名前の違いを明確にする
     * 
     * 【ダイヤモンド問題の可視化】
     * このメソッドでダイヤモンド問題の影響を確認:
     * - DiamondTrap名: "Diamond1"
     * - ClapTrap名: "Diamond1_clap_name"
     * 
     * 【実装での注意点】
     * ClapTrap::_nameへのアクセス方法:
     * - 曖昧性があるため明示的スコープ解決が必要
     * - this->ClapTrap::_name または
     * - ScavTrap::_name か FragTrap::_name
     */
    void whoAmI(void);
    
    /*
     * std::string getName(void) const;
     * 
     * 【基底クラスメソッドのオーバーライド】
     * 
     * ClapTrap::getName() をオーバーライド
     * DiamondTrap::_name を返すように変更
     * 
     * 【なぜオーバーライドが必要？】
     * デフォルトではClapTrap::getName()が呼ばれ、
     * ClapTrap::_name ("name_clap_name") が返される
     * 
     * DiamondTrap固有の名前を返したい場合、
     * オーバーライドが必要
     * 
     * 【仮想関数ではない問題】
     * ClapTrap::getName()がvirtualでない場合、
     * ポリモーフィズムは動作しない
     * 静的バインディングのみ
     */
    std::string getName(void) const;
};

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このヘッダーから学ぶべきこと】
 * 
 * 1. ダイヤモンド問題の本質
 *    - 多重継承での基底クラス重複
 *    - 曖昧性の発生原因
 *    - メモリレイアウトへの影響
 * 
 * 2. 問題解決の手法
 *    - 仮想継承（理想的解決）
 *    - using宣言（曖昧性回避）
 *    - 明示的スコープ解決
 * 
 * 3. 多重継承の設計原則
 *    - 継承順序の重要性
 *    - 名前管理戦略
 *    - OCFの適切な実装
 * 
 * 4. 実用的な設計判断
 *    - いつ多重継承を使うべきか
 *    - 代替設計パターン
 *    - 保守性との トレードオフ
 * 
 * 【次のステップ】
 * - TUTORIAL_DiamondTrap.cpp で実装詳細を学習
 * - 仮想継承との比較
 * - より良い設計パターンの検討
 */

#endif

/*
 * ====================================================================
 * ダイヤモンド問題の完全解決案
 * ====================================================================
 * 
 * 【42スクール制約なしの理想的設計】
 * 
 * // 基底クラス（変更なし）
 * class ClapTrap { ... };
 * 
 * // 中間クラス（仮想継承使用）
 * class ScavTrap : virtual public ClapTrap { ... };
 * class FragTrap : virtual public ClapTrap { ... };
 * 
 * // 最終クラス（問題解決）
 * class DiamondTrap : public ScavTrap, public FragTrap {
 *     // ClapTrapは1つだけ存在
 *     // 曖昧性なし
 *     // メモリ効率良い
 * };
 * 
 * 【仮想継承のコスト】
 * - わずかなパフォーマンスオーバーヘッド
 * - より複雑な初期化構文
 * - デバッグの困難さ増加
 * 
 * しかし、多重継承が必要な場合は必須の技術
 */

/*
 * ====================================================================
 * 多重継承 vs 代替設計パターン
 * ====================================================================
 * 
 * 【多重継承の問題点】
 * 1. ダイヤモンド問題
 * 2. 複雑な初期化
 * 3. デバッグの困難
 * 4. 保守性の低下
 * 
 * 【代替パターン1: コンポジション】
 * class DiamondTrap {
 *     ScavTrap scavPart;
 *     FragTrap fragPart;
 *     // 委譲による機能実現
 * };
 * 
 * 【代替パターン2: インターフェース継承】
 * class IScavInterface { virtual void guardGate() = 0; };
 * class IFragInterface { virtual void highFivesGuys() = 0; };
 * class DiamondTrap : public ClapTrap, public IScavInterface, public IFragInterface {};
 * 
 * 【代替パターン3: テンプレート】
 * template<typename Base1, typename Base2>
 * class MultiTrap : public Base1, public Base2 {};
 * 
 * 各手法にはトレードオフがあり、用途に応じて選択
 */

/*
 * ====================================================================
 * 実用性の考察
 * ====================================================================
 * 
 * 【多重継承が有効な場面】
 * 1. ミックスイン（機能の組み合わせ）
 * 2. インターフェースの多重実装
 * 3. レガシーコードとの統合
 * 
 * 【避けるべき場面】
 * 1. 代替設計が可能な場合
 * 2. チーム開発での複雑性回避
 * 3. 保守性を重視する場合
 * 
 * 【C++コミュニティの傾向】
 * - 多重継承は慎重に使用
 * - インターフェース継承は積極的
 * - コンポジションを優先
 * 
 * 「継承よりもコンポジションを優先」は
 * 現代C++の重要な設計原則
 */