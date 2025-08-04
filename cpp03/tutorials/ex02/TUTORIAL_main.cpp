/*
 * ====================================================================
 * CPP03 ex02: FragTrap - 複数継承と戦術比較テスト解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 複数の派生クラス間での機能比較
 * - 継承ツリーの拡張による設計理解
 * - 異なる戦術特性を持つクラスの実用比較
 * - チーム編成と戦術選択の実践
 * - 継承による機能差別化の体験
 * 
 * 【重要概念】
 * - 兄弟クラス間での特性比較
 * - 戦術的バランスの実験的確認
 * - 継承による機能拡張パターン
 * - オブジェクト指向設計の実用性
 * - 多態性の基礎理解
 */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <vector>

/*
 * ====================================================================
 * テスト用補助関数
 * ====================================================================
 */

/*
 * 【セクション区切り表示関数】
 */
void printSection(const std::string& title) {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

/*
 * 【詳細ステータス表示関数】
 * void showDetailedStatus(const ClapTrap& unit, const std::string& unitType)
 * 
 * 目的：
 * - 各クラスの詳細な状態表示
 * - 能力値の比較促進
 * - 戦術的分析の支援
 */
void showDetailedStatus(const ClapTrap& unit, const std::string& unitType) {
    std::cout << "=== " << unitType << " Status ===" << std::endl;
    std::cout << "  Name: " << unit.getName() << std::endl;
    std::cout << "  Hit Points: " << unit.getHitPoints() << "/100" << std::endl;
    std::cout << "  Energy Points: " << unit.getEnergyPoints() 
              << " (max: " << (unitType == "FragTrap" ? "100" : 
                             unitType == "ScavTrap" ? "50" : "10") << ")" << std::endl;
    std::cout << "  Attack Damage: " << unit.getAttackDamage() << std::endl;
    std::cout << "  Unit Type: " << unitType << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << std::endl;
}

/*
 * 【戦闘効率計算関数】
 * void calculateCombatEfficiency(const ClapTrap& unit, const std::string& unitType)
 * 
 * 目的：
 * - 各クラスの戦闘効率分析
 * - 理論値による性能比較
 * - 戦術選択の参考データ提供
 */
void calculateCombatEfficiency(const ClapTrap& unit, const std::string& unitType) {
    int hp = unit.getHitPoints();
    int energy = unit.getEnergyPoints();
    int attack = unit.getAttackDamage();
    
    int maxActions = energy;  // 最大行動回数
    int totalDamage = maxActions * attack;  // 理論最大ダメージ
    double efficiency = hp > 0 ? (double)totalDamage / hp : 0;  // 効率値
    
    std::cout << "=== " << unitType << " Combat Analysis ===" << std::endl;
    std::cout << "  Survivability (HP): " << hp << std::endl;
    std::cout << "  Action Capacity (Energy): " << energy << std::endl;
    std::cout << "  Damage Per Action: " << attack << std::endl;
    std::cout << "  Max Theoretical Damage: " << totalDamage << std::endl;
    std::cout << "  Combat Efficiency Ratio: " << efficiency << std::endl;
    
    // 戦術的評価
    if (unitType == "FragTrap") {
        std::cout << "  Tactical Role: High-damage attacker, team supporter" << std::endl;
    } else if (unitType == "ScavTrap") {
        std::cout << "  Tactical Role: Balanced fighter, area defender" << std::endl;
    } else {
        std::cout << "  Tactical Role: Basic unit, support role" << std::endl;
    }
    std::cout << "============================" << std::endl;
    std::cout << std::endl;
}

/*
 * ====================================================================
 * main関数とテストシナリオ
 * ====================================================================
 */

int main() {
    /*
     * 【プログラムの概要】
     * 
     * このテストでは以下を検証：
     * 1. 3つのクラス（ClapTrap, ScavTrap, FragTrap）の能力比較
     * 2. 継承ツリーの拡張確認
     * 3. 各クラスの特殊能力テスト
     * 4. 戦術的シミュレーション
     * 5. チーム編成での相乗効果
     * 6. Orthodox Canonical Formの動作確認
     */
    
    std::cout << "CPP03 ex02: FragTrap Multi-Class Inheritance Demonstration" << std::endl;
    std::cout << "Testing inheritance expansion, tactical diversity, and object-oriented design" << std::endl;
    
    /*
     * ====================================================================
     * テスト1: 3クラス同時作成とコンストラクタチェーン確認
     * ====================================================================
     */
    printSection("Test 1: Three-Class Constructor Chain Demonstration");
    
    std::cout << "Creating ClapTrap 'BasicUnit':" << std::endl;
    ClapTrap basicUnit("BasicUnit");
    std::cout << std::endl;
    
    std::cout << "Creating ScavTrap 'GuardUnit':" << std::endl;
    ScavTrap guardUnit("GuardUnit");
    std::cout << std::endl;
    
    std::cout << "Creating FragTrap 'AttackUnit':" << std::endl;
    FragTrap attackUnit("AttackUnit");
    std::cout << std::endl;
    
    /*
     * 【コンストラクタチェーンの観察】
     * 
     * 期待される順序：
     * ClapTrap: ClapTrapコンストラクタのみ
     * ScavTrap: ClapTrap → ScavTrapコンストラクタ
     * FragTrap: ClapTrap → FragTrapコンストラクタ
     * 
     * 学習ポイント：
     * - 各派生クラスで基底クラスが先に初期化される
     * - 同じ基底クラスからの複数派生確認
     */
    
    /*
     * ====================================================================
     * テスト2: 詳細能力値比較とバランス分析
     * ====================================================================
     */
    printSection("Test 2: Detailed Stats Comparison and Balance Analysis");
    
    std::cout << "Comparing all three classes side by side:" << std::endl;
    std::cout << std::endl;
    
    showDetailedStatus(basicUnit, "ClapTrap");
    showDetailedStatus(guardUnit, "ScavTrap");
    showDetailedStatus(attackUnit, "FragTrap");
    
    std::cout << "Combat efficiency analysis:" << std::endl;
    calculateCombatEfficiency(basicUnit, "ClapTrap");
    calculateCombatEfficiency(guardUnit, "ScavTrap");
    calculateCombatEfficiency(attackUnit, "FragTrap");
    
    /*
     * 【能力値比較の学習ポイント】
     * 
     * ClapTrap (10/10/0):
     * - 最も基本的な能力
     * - 低リスク・低リターン
     * - 学習・テスト用途
     * 
     * ScavTrap (100/50/20):
     * - バランス型の中級ユニット
     * - 防御特化の特殊能力
     * - 持久戦向け
     * 
     * FragTrap (100/100/30):
     * - 攻撃特化の上級ユニット
     * - チーム支援の特殊能力
     * - 短期決戦向け
     */
    
    /*
     * ====================================================================
     * テスト3: 攻撃機能の差別化確認
     * ====================================================================
     */
    printSection("Test 3: Attack Function Differentiation");
    
    std::cout << "Comparing attack behaviors across all classes:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "ClapTrap attack:" << std::endl;
    basicUnit.attack("TestTarget");
    std::cout << std::endl;
    
    std::cout << "ScavTrap attack:" << std::endl;
    guardUnit.attack("TestTarget");
    std::cout << std::endl;
    
    std::cout << "FragTrap attack:" << std::endl;
    attackUnit.attack("TestTarget");
    std::cout << std::endl;
    
    /*
     * 【攻撃の差別化確認】
     * 
     * メッセージの違い：
     * - ClapTrap: "attacks" (基本的)
     * - ScavTrap: "fiercely attacks" (威圧的)
     * - FragTrap: "explosively attacks" (爆発的)
     * 
     * ダメージの違い：
     * - ClapTrap: 0ダメージ
     * - ScavTrap: 20ダメージ
     * - FragTrap: 30ダメージ
     * 
     * オーバーライドによる個性表現の確認
     */
    
    /*
     * ====================================================================
     * テスト4: 特殊能力の機能比較
     * ====================================================================
     */
    printSection("Test 4: Unique Abilities Comparison");
    
    std::cout << "Testing unique abilities of derived classes:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "ClapTrap has no unique abilities (base class functionality only)" << std::endl;
    std::cout << "Available functions: attack(), takeDamage(), beRepaired()" << std::endl;
    std::cout << std::endl;
    
    std::cout << "ScavTrap unique ability - Gate Keeping:" << std::endl;
    guardUnit.guardGate();
    std::cout << std::endl;
    
    std::cout << "FragTrap unique ability - Team Morale Boost:" << std::endl;
    attackUnit.highFivesGuys();
    std::cout << std::endl;
    
    /*
     * 【特殊能力の設計比較】
     * 
     * ScavTrap::guardGate():
     * - 個人的な防御能力
     * - 陣地・門の防御特化
     * - 静的・持久戦向け
     * 
     * FragTrap::highFivesGuys():
     * - チーム支援能力
     * - 士気向上・連携強化
     * - 動的・協力戦向け
     * 
     * 機能の差別化による戦術的多様性確認
     */
    
    /*
     * ====================================================================
     * テスト5: 戦闘シミュレーション - クラス間バトル
     * ====================================================================
     */
    printSection("Test 5: Inter-Class Combat Simulation");
    
    std::cout << "Scenario: ScavTrap vs FragTrap Combat" << std::endl;
    std::cout << std::endl;
    
    // 新しいユニット作成（戦闘用）
    std::cout << "Deploying combat units:" << std::endl;
    ScavTrap defender("Guardian");
    FragTrap attacker("Demolisher");
    std::cout << std::endl;
    
    std::cout << "Pre-combat status:" << std::endl;
    showDetailedStatus(defender, "ScavTrap Defender");
    showDetailedStatus(attacker, "FragTrap Attacker");
    
    std::cout << "Combat Round 1:" << std::endl;
    std::cout << "Guardian prepares defensive position:" << std::endl;
    defender.guardGate();
    std::cout << std::endl;
    
    std::cout << "Demolisher boosts team morale:" << std::endl;
    attacker.highFivesGuys();
    std::cout << std::endl;
    
    std::cout << "Combat Round 2 - Direct confrontation:" << std::endl;
    defender.attack("Demolisher");
    attacker.attack("Guardian");
    std::cout << std::endl;
    
    std::cout << "Applying damage:" << std::endl;
    attacker.takeDamage(20);  // ScavTrapの攻撃ダメージ
    defender.takeDamage(30);  // FragTrapの攻撃ダメージ
    std::cout << std::endl;
    
    std::cout << "Post-combat status:" << std::endl;
    showDetailedStatus(defender, "ScavTrap Defender");
    showDetailedStatus(attacker, "FragTrap Attacker");
    
    /*
     * 【戦闘結果の分析】
     * 
     * 理論的結果：
     * - Guardian (ScavTrap): 100 - 30 = 70 HP
     * - Demolisher (FragTrap): 100 - 20 = 80 HP
     * 
     * 戦術的示唆：
     * - FragTrapの高火力が有効
     * - ScavTrapも十分な戦闘力を維持
     * - 特殊能力による戦術的優位性
     * - 長期戦ではエネルギー効率が重要
     */
    
    /*
     * ====================================================================
     * テスト6: エネルギー効率と持久力比較
     * ====================================================================
     */
    printSection("Test 6: Energy Efficiency and Endurance Comparison");
    
    std::cout << "Testing energy efficiency and combat endurance:" << std::endl;
    std::cout << std::endl;
    
    // エネルギー消費テスト用の新しいユニット
    ScavTrap enduranceGuard("Fortress");
    FragTrap rapidFire("Barrage");
    
    std::cout << "Starting continuous combat test:" << std::endl;
    std::cout << "Both units will attack repeatedly until energy depleted" << std::endl;
    std::cout << std::endl;
    
    int scavActions = 0, fragActions = 0;
    
    std::cout << "ScavTrap endurance test:" << std::endl;
    while (enduranceGuard.getEnergyPoints() > 0) {
        enduranceGuard.attack("DummyTarget");
        scavActions++;
        if (scavActions % 10 == 0) {
            std::cout << "ScavTrap completed " << scavActions << " actions" << std::endl;
        }
    }
    std::cout << "ScavTrap total actions: " << scavActions << std::endl;
    std::cout << std::endl;
    
    std::cout << "FragTrap endurance test:" << std::endl;
    while (rapidFire.getEnergyPoints() > 0) {
        rapidFire.attack("DummyTarget");
        fragActions++;
        if (fragActions % 20 == 0) {
            std::cout << "FragTrap completed " << fragActions << " actions" << std::endl;
        }
    }
    std::cout << "FragTrap total actions: " << fragActions << std::endl;
    std::cout << std::endl;
    
    std::cout << "Endurance comparison results:" << std::endl;
    std::cout << "ScavTrap: " << scavActions << " actions, " << (scavActions * 20) << " total damage" << std::endl;
    std::cout << "FragTrap: " << fragActions << " actions, " << (fragActions * 30) << " total damage" << std::endl;
    std::cout << "FragTrap advantage: " << (fragActions - scavActions) << " extra actions, " 
              << ((fragActions * 30) - (scavActions * 20)) << " extra damage" << std::endl;
    std::cout << std::endl;
    
    /*
     * 【持久力テストの学習ポイント】
     * 
     * 期待される結果：
     * - ScavTrap: 50回の行動、1000ダメージ
     * - FragTrap: 100回の行動、3000ダメージ
     * - FragTrapが2倍の持続力と3倍の総ダメージ
     * 
     * 戦術的含意：
     * - 長期戦でのFragTrapの圧倒的優位性
     * - エネルギー効率の重要性
     * - 短期決戦vs持久戦の戦略選択
     */
    
    /*
     * ====================================================================
     * テスト7: Orthodox Canonical Form完全テスト
     * ====================================================================
     */
    printSection("Test 7: Complete Orthodox Canonical Form Test");
    
    std::cout << "Testing OCF for all classes with inheritance:" << std::endl;
    std::cout << std::endl;
    
    // コピーコンストラクタテスト
    std::cout << "Copy constructor tests:" << std::endl;
    ClapTrap basicCopy(basicUnit);
    ScavTrap guardCopy(guardUnit);
    FragTrap attackCopy(attackUnit);
    std::cout << std::endl;
    
    // 代入演算子テスト
    std::cout << "Assignment operator tests:" << std::endl;
    ClapTrap basicAssigned("TempBasic");
    ScavTrap guardAssigned("TempGuard");
    FragTrap attackAssigned("TempAttack");
    
    basicAssigned = basicUnit;
    guardAssigned = guardUnit;
    attackAssigned = attackUnit;
    std::cout << std::endl;
    
    // コピーされたオブジェクトの状態確認
    std::cout << "Verifying copied and assigned objects:" << std::endl;
    showDetailedStatus(basicCopy, "ClapTrap (copied)");
    showDetailedStatus(guardCopy, "ScavTrap (copied)");
    showDetailedStatus(attackCopy, "FragTrap (copied)");
    
    showDetailedStatus(basicAssigned, "ClapTrap (assigned)");
    showDetailedStatus(guardAssigned, "ScavTrap (assigned)");
    showDetailedStatus(attackAssigned, "FragTrap (assigned)");
    
    /*
     * ====================================================================
     * テスト8: チーム編成シミュレーション
     * ====================================================================
     */
    printSection("Test 8: Team Composition Simulation");
    
    std::cout << "Testing different team compositions:" << std::endl;
    std::cout << std::endl;
    
    // バランス型チーム
    std::cout << "Team 1 - Balanced Composition:" << std::endl;
    ClapTrap support1("Medic");
    ScavTrap tank1("Tank");
    FragTrap dps1("DPS");
    
    std::cout << "Team roles:" << std::endl;
    std::cout << "  " << support1.getName() << " (ClapTrap): Support/Utility" << std::endl;
    std::cout << "  " << tank1.getName() << " (ScavTrap): Defender/Guard" << std::endl;
    std::cout << "  " << dps1.getName() << " (FragTrap): Attacker/Damage" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Team coordination:" << std::endl;
    tank1.guardGate();
    dps1.highFivesGuys();
    std::cout << "Support unit stands ready for repairs and assistance" << std::endl;
    std::cout << std::endl;
    
    // 攻撃特化チーム
    std::cout << "Team 2 - Attack Specialized Composition:" << std::endl;
    FragTrap striker1("Alpha");
    FragTrap striker2("Beta");
    FragTrap striker3("Gamma");
    
    std::cout << "Triple FragTrap assault team:" << std::endl;
    striker1.highFivesGuys();
    striker2.highFivesGuys();
    striker3.highFivesGuys();
    std::cout << "Combined morale boost effect!" << std::endl;
    std::cout << "Total team damage potential: " << (30 * 3) << " per round" << std::endl;
    std::cout << "Total team actions: " << (100 * 3) << " theoretical maximum" << std::endl;
    std::cout << std::endl;
    
    /*
     * 【チーム編成の戦略分析】
     * 
     * バランス型チーム：
     * - 多様な役割分担
     * - 様々な状況への対応力
     * - 安定した戦闘継続能力
     * 
     * 攻撃特化チーム：
     * - 圧倒的な火力集中
     * - 短期決戦での優位性
     * - チーム支援効果の重複
     */
    
    /*
     * ====================================================================
     * テスト9: ポリモーフィズムの基礎実験
     * ====================================================================
     */
    printSection("Test 9: Basic Polymorphism Experiment");
    
    std::cout << "Testing polymorphic behavior with base class pointers:" << std::endl;
    std::cout << std::endl;
    
    // 基底クラスポインタの配列
    std::cout << "Creating polymorphic unit array:" << std::endl;
    ClapTrap* units[3];
    units[0] = new ClapTrap("PolyBasic");
    units[1] = new ScavTrap("PolyGuard");
    units[2] = new FragTrap("PolyAttack");
    std::cout << std::endl;
    
    std::cout << "Calling common functions through base pointers:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Unit " << i << " (" << units[i]->getName() << "):" << std::endl;
        units[i]->attack("CommonTarget");
        units[i]->takeDamage(5);
        units[i]->beRepaired(2);
        std::cout << std::endl;
    }
    
    std::cout << "Note: Unique abilities cannot be called through base pointers:" << std::endl;
    std::cout << "  - guardGate() is only available for ScavTrap objects directly" << std::endl;
    std::cout << "  - highFivesGuys() is only available for FragTrap objects directly" << std::endl;
    std::cout << "  - This demonstrates the interface limitation of polymorphism" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Cleaning up polymorphic objects:" << std::endl;
    for (int i = 0; i < 3; i++) {
        delete units[i];
    }
    std::cout << std::endl;
    
    /*
     * 【ポリモーフィズムの学習ポイント】
     * 
     * 可能な操作：
     * - 基底クラスのpublic関数呼び出し
     * - オーバーライドされた関数の動的実行
     * - 統一されたインターフェースでの操作
     * 
     * 制限事項：
     * - 派生クラス固有の関数は呼び出せない
     * - キャストが必要（危険性あり）
     * - virtual関数でないとオーバーライドが効かない
     */
    
    /*
     * ====================================================================
     * テスト10: パフォーマンス比較と最適化確認
     * ====================================================================
     */
    printSection("Test 10: Performance Comparison and Optimization");
    
    std::cout << "Comparing memory usage and performance characteristics:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Memory footprint analysis:" << std::endl;
    std::cout << "sizeof(ClapTrap): " << sizeof(ClapTrap) << " bytes" << std::endl;
    std::cout << "sizeof(ScavTrap): " << sizeof(ScavTrap) << " bytes" << std::endl;
    std::cout << "sizeof(FragTrap): " << sizeof(FragTrap) << " bytes" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Inheritance overhead:" << std::endl;
    std::cout << "ScavTrap overhead: " << (sizeof(ScavTrap) - sizeof(ClapTrap)) << " bytes" << std::endl;
    std::cout << "FragTrap overhead: " << (sizeof(FragTrap) - sizeof(ClapTrap)) << " bytes" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Construction/destruction timing test:" << std::endl;
    std::cout << "Creating and destroying 1000 objects of each type..." << std::endl;
    
    // 簡単なタイミングテスト（概念実証）
    for (int i = 0; i < 1000; i++) {
        ClapTrap temp1("test");
        ScavTrap temp2("test");
        FragTrap temp3("test");
        // オブジェクトはスコープ終了で自動破棄
    }
    
    std::cout << "Performance test completed - observe constructor/destructor patterns" << std::endl;
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * プログラム終了とデストラクタチェーン観察
     * ====================================================================
     */
    printSection("Program End - Complete Destructor Chain Observation");
    
    std::cout << "Program ending - observe complete destructor chain:" << std::endl;
    std::cout << "Multiple objects of each class will be destroyed" << std::endl;
    std::cout << "Expected order: reverse of creation order" << std::endl;
    std::cout << "Each derived class shows both derived and base destructors" << std::endl;
    std::cout << std::endl;
    
    /*
     * 【期待されるデストラクタ順序】
     * 
     * 作成順序の逆：
     * 1. 最後に作成されたオブジェクトから
     * 2. FragTrap: FragTrap destructor → ClapTrap destructor
     * 3. ScavTrap: ScavTrap destructor → ClapTrap destructor  
     * 4. ClapTrap: ClapTrap destructor のみ
     * 
     * 大量のオブジェクトが一度に破棄される様子を観察
     */
    
    return 0;
}

/*
 * ====================================================================
 * 期待される出力の要約
 * ====================================================================
 * 
 * 【コンストラクタチェーン】
 * ```
 * ClapTrap constructor called for BasicUnit
 * 
 * ClapTrap constructor called for GuardUnit  
 * ScavTrap constructor called for GuardUnit
 * ScavTrap GuardUnit is equipped with enhanced gate-keeping abilities!
 * 
 * ClapTrap constructor called for AttackUnit
 * FragTrap constructor called for AttackUnit
 * FragTrap AttackUnit is armed with explosive capabilities!
 * ```
 * 
 * 【能力値比較】
 * ```
 * ClapTrap: HP=10, Energy=10, Attack=0
 * ScavTrap: HP=100, Energy=50, Attack=20
 * FragTrap: HP=100, Energy=100, Attack=30
 * ```
 * 
 * 【攻撃の差別化】
 * ```
 * ClapTrap BasicUnit attacks TestTarget, causing 0 points of damage!
 * ScavTrap GuardUnit fiercely attacks TestTarget, causing 20 points of damage!
 * FragTrap AttackUnit explosively attacks TestTarget, causing 30 points of damage!
 * ```
 * 
 * 【特殊能力】
 * ```
 * ScavTrap GuardUnit is now in Gate keeper mode!
 * 
 * FragTrap AttackUnit requests positive high fives!
 * ✋ Team morale boost activated! ✋
 * ```
 * 
 * 【持久力テスト結果】
 * ```
 * ScavTrap total actions: 50
 * FragTrap total actions: 100
 * FragTrap advantage: 50 extra actions, 2000 extra damage
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このテストで確認すべき項目：
 * 
 * □ 複数派生クラスの同時動作確認
 * □ 兄弟クラス間での能力値比較理解
 * □ 戦術的差別化の実証確認
 * □ 特殊能力による機能拡張確認
 * □ エネルギー効率と持久力の違い理解
 * □ OCF の継承版完全動作確認
 * □ チーム編成による戦術多様性確認
 * □ ポリモーフィズムの基礎理解
 * □ メモリ使用量と継承オーバーヘッド確認
 * □ 継承ツリー拡張の設計理解
 * 
 * 【発展課題】
 * 1. 4つ目の派生クラス（例：MageTrap）の追加
 * 2. 仮想関数を使った真のポリモーフィズム実装
 * 3. ファクトリーパターンによるオブジェクト生成
 * 4. チーム戦闘システムの完全実装
 * 5. 設定ファイルによる能力値カスタマイズ
 */

/*
 * ====================================================================
 * よくあるテスト実装のミスと改善案
 * ====================================================================
 * 
 * 【ミス1：比較テストの不十分性】
 * 
 * 改良案：
 * ```cpp
 * struct CombatStats {
 *     int totalDamage;
 *     int actionsPerformed;
 *     double efficiency;
 * };
 * 
 * CombatStats performCombatTest(ClapTrap& unit, int rounds) {
 *     CombatStats stats = {0, 0, 0.0};
 *     for (int i = 0; i < rounds && unit.getEnergyPoints() > 0; i++) {
 *         unit.attack("TestTarget");
 *         stats.totalDamage += unit.getAttackDamage();
 *         stats.actionsPerformed++;
 *     }
 *     stats.efficiency = unit.getHitPoints() > 0 ? 
 *         (double)stats.totalDamage / unit.getHitPoints() : 0;
 *     return stats;
 * }
 * ```
 * 
 * 【ミス2：エラー状態のテスト不足】
 * 
 * 改良案：
 * ```cpp
 * void testErrorConditions() {
 *     FragTrap testUnit("ErrorTest");
 *     
 *     // HP0状態のテスト
 *     testUnit.takeDamage(150);
 *     testUnit.attack("Target");        // 失敗するはず
 *     testUnit.highFivesGuys();         // 動作するかテスト
 *     
 *     // エネルギー0状態のテスト
 *     FragTrap energyTest("EnergyTest");
 *     for (int i = 0; i < 101; i++) {
 *         energyTest.attack("Target");
 *     }
 *     energyTest.attack("FinalTarget");  // 失敗するはず
 * }
 * ```
 * 
 * 【ミス3：メモリ管理テストの不足】
 * 
 * 改良案：
 * ```cpp
 * void testMemoryManagement() {
 *     // 動的配列でのテスト
 *     std::vector<ClapTrap*> units;
 *     
 *     for (int i = 0; i < 100; i++) {
 *         switch (i % 3) {
 *             case 0: units.push_back(new ClapTrap("Unit" + std::to_string(i))); break;
 *             case 1: units.push_back(new ScavTrap("Guard" + std::to_string(i))); break;
 *             case 2: units.push_back(new FragTrap("Frag" + std::to_string(i))); break;
 *         }
 *     }
 *     
 *     // 使用後の適切な削除
 *     for (ClapTrap* unit : units) {
 *         delete unit;
 *     }
 * }
 * ```
 * 
 * 【ミス4：継承関係の視覚化不足】
 * 
 * 改良案：
 * ```cpp
 * void visualizeInheritanceTree() {
 *     std::cout << "Inheritance Tree:" << std::endl;
 *     std::cout << "    ClapTrap" << std::endl;
 *     std::cout << "    /      \\" << std::endl;
 *     std::cout << "ScavTrap   FragTrap" << std::endl;
 *     std::cout << std::endl;
 *     
 *     std::cout << "Memory Layout:" << std::endl;
 *     ClapTrap base("base");
 *     ScavTrap derived1("derived1");
 *     FragTrap derived2("derived2");
 *     
 *     std::cout << "ClapTrap address: " << &base << std::endl;
 *     std::cout << "ScavTrap address: " << &derived1 << std::endl;
 *     std::cout << "FragTrap address: " << &derived2 << std::endl;
 *     
 *     std::cout << "ClapTrap part of ScavTrap: " << static_cast<ClapTrap*>(&derived1) << std::endl;
 *     std::cout << "ClapTrap part of FragTrap: " << static_cast<ClapTrap*>(&derived2) << std::endl;
 * }
 * ```
 */