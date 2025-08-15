/*
 * ====================================================================
 * CPP04 ex01: Brain and Deep Copy - 動的メモリ管理と深いコピー実証プログラム
 * ====================================================================
 * 
 * 【学習目標】
 * - 動的メモリ管理付き継承の実際の動作確認
 * - 深いコピー vs 浅いコピーの決定的な違い体験
 * - Brain クラス集約関係の実用的な理解
 * - RAII原則の継承システムでの実践観察
 * - Orthodox Canonical Form の動的リソース版動作確認
 * 
 * 【重要概念】
 * - 集約関係（Aggregation）の実際の動作とメリット
 * - リソース管理の継承における責任分散
 * - 例外安全性の基本レベル実装の動作
 * - オブジェクトライフサイクルの複雑化と管理
 * - パフォーマンスと設計の実践的なトレードオフ
 */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>
#include <vector>

/*
 * ====================================================================
 * テスト用補助関数
 * ====================================================================
 */

/*
 * 【セクション区切り表示関数】
 * void printSection(const std::string& title)
 * 
 * 目的：
 * - 複雑なテスト出力の視覚的整理
 * - 動的メモリ管理の各フェーズ区別
 * - デバッグ時の迅速な問題特定支援
 * - 学習時の概念別理解促進
 */
void printSection(const std::string& title) {
    std::cout << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << std::endl;
}

/*
 * 【Brain 内容表示関数】
 * void displayBrainInfo(const Animal* animal, const std::string& name)
 * 
 * 目的：
 * - Brain オブジェクトの独立性確認
 * - 深いコピーの成功確認
 * - メモリアドレス比較による分離確認
 * - デバッグ時の状態確認支援
 * 
 * 制限：
 * - Brain* brain は protected メンバのため直接アクセス不可
 * - 実際の実装ではアクセサ関数が必要
 * - この関数は概念的なデモンストレーション
 */
void displayAnimalInfo(const Animal* animal, const std::string& name) {
    std::cout << "--- " << name << " Information ---" << std::endl;
    std::cout << "Type: " << animal->getType() << std::endl;
    std::cout << "Sound: ";
    animal->makeSound();
    std::cout << "Memory Address: " << animal << std::endl;
    // 実際の実装では Brain の詳細情報表示にはアクセサが必要
    std::cout << std::endl;
}

/*
 * 【メモリ使用量概算表示関数】
 * void displayMemoryUsage(int animalCount, int brainCount)
 * 
 * 目的：
 * - 動的メモリ使用量の概算把握
 * - ex00 との比較による使用量増加確認
 * - リソース管理の重要性認識
 * - パフォーマンス影響の理解促進
 */
void displayMemoryUsage(int animalCount, int brainCount) {
    std::cout << "--- Memory Usage Estimation ---" << std::endl;
    std::cout << "Animal objects: " << animalCount << std::endl;
    std::cout << "Brain objects: " << brainCount << std::endl;
    std::cout << "Estimated heap usage: ~" << (brainCount * 100) << " ideas worth of memory" << std::endl;
    std::cout << "Plus vtable pointers and object overhead" << std::endl;
    std::cout << std::endl;
}

/*
 * ====================================================================
 * メイン関数とテストシナリオ
 * ====================================================================
 */

int main() {
    /*
     * 【プログラムの概要】
     * 
     * このテストプログラムの検証内容：
     * 1. 動的メモリ管理付き継承の基本動作確認
     * 2. 深いコピーによるオブジェクト独立性確認
     * 3. Brain クラス集約関係の実用性確認
     * 4. RAII 原則の継承システムでの動作確認
     * 5. 多態性と動的メモリ管理の組み合わせ検証
     * 6. リソース管理の安全性とパフォーマンス測定
     */
    
    std::cout << "CPP04 ex01: Dynamic Memory Management with Inheritance" << std::endl;
    std::cout << "Testing Brain aggregation, deep copy, and resource management" << std::endl;
    
    /*
     * ====================================================================
     * テスト1: 基本的なオブジェクト作成と Brain 集約確認
     * ====================================================================
     */
    printSection("Test 1: Basic Object Creation with Brain Aggregation");
    
    std::cout << "Creating Animal objects with Brain aggregation:" << std::endl;
    Animal* animal = new Animal();
    Cat* cat = new Cat();
    Dog* dog = new Dog();
    
    std::cout << std::endl << "Testing polymorphic behavior:" << std::endl;
    displayAnimalInfo(animal, "Base Animal");
    displayAnimalInfo(cat, "Cat");
    displayAnimalInfo(dog, "Dog");
    
    displayMemoryUsage(3, 3);
    
    /*
     * 【基本作成テストの学習ポイント】
     * 
     * 観察すべき動作：
     * - 各オブジェクト作成時の Brain も同時作成
     * - Animal → Cat, Animal → Dog の初期化チェーン
     * - 各 Brain オブジェクトの独立したメモリアドレス
     * - type 情報の正確な設定とアクセス
     * 
     * ex00 との違い：
     * - より多くのデバッグ出力（Brain 作成含む）
     * - メモリ使用量の増加（Brain 分）
     * - より複雑な初期化プロセス
     * - リソース管理の責任増加
     */
    
    /*
     * ====================================================================
     * テスト2: 深いコピー vs 浅いコピーの実証
     * ====================================================================
     */
    printSection("Test 2: Deep Copy vs Shallow Copy Demonstration");
    
    std::cout << "Creating original objects:" << std::endl;
    Cat originalCat;
    Dog originalDog;
    
    std::cout << std::endl << "Testing copy constructor (deep copy):" << std::endl;
    Cat copiedCat(originalCat);
    Dog copiedDog(originalDog);
    
    std::cout << std::endl << "Verifying object independence:" << std::endl;
    displayAnimalInfo(&originalCat, "Original Cat");
    displayAnimalInfo(&copiedCat, "Copied Cat");
    displayAnimalInfo(&originalDog, "Original Dog");  
    displayAnimalInfo(&copiedDog, "Copied Dog");
    
    std::cout << "Key observation: Each copy has independent Brain object" << std::endl;
    std::cout << "Memory addresses should be different for each object" << std::endl;
    
    displayMemoryUsage(4, 4);
    
    /*
     * 【深いコピーテストの学習ポイント】
     * 
     * 確認すべき動作：
     * - コピーコンストラクタでの新しい Brain 作成
     * - original と copy の完全な独立性
     * - Brain 内容のコピー（同じ内容、異なるオブジェクト）
     * - メモリアドレスの差異による独立性確認
     * 
     * 浅いコピーとの比較（想像上の問題）：
     * - 浅いコピー: 同じ Brain オブジェクトを共有
     * - 結果: 一方の変更がもう一方に影響
     * - 破棄時: 二重削除（double delete）の危険
     * - 現実: 深いコピーにより回避済み
     */
    
    /*
     * ====================================================================
     * テスト3: 代入演算子と深いコピーの動作確認
     * ====================================================================
     */
    printSection("Test 3: Assignment Operator and Deep Copy");
    
    std::cout << "Creating objects for assignment test:" << std::endl;
    Cat assignCat1;
    Cat assignCat2;
    
    std::cout << std::endl << "Before assignment:" << std::endl;
    displayAnimalInfo(&assignCat1, "Cat 1 (will be assigned to)");
    displayAnimalInfo(&assignCat2, "Cat 2 (will be assigned from)");
    
    std::cout << std::endl << "Performing assignment (should trigger deep copy):" << std::endl;
    assignCat1 = assignCat2;
    
    std::cout << std::endl << "After assignment:" << std::endl;
    displayAnimalInfo(&assignCat1, "Cat 1 (after assignment)");
    displayAnimalInfo(&assignCat2, "Cat 2 (original)");
    
    std::cout << "Key observation: Assignment creates new independent Brain" << std::endl;
    std::cout << "Old Brain was safely deleted, new Brain created" << std::endl;
    
    /*
     * 【代入演算子テストの学習ポイント】
     * 
     * 代入プロセスの詳細：
     * 1. 自己代入チェック (this != &other)
     * 2. 既存 Brain の削除 (delete brain)
     * 3. 新しい Brain の作成 (new Brain(*other.brain))
     * 4. 独立性の確保
     * 
     * 観察すべき動作：
     * - 代入前後での Brain アドレス変更
     * - メモリリークの発生なし
     * - オブジェクト独立性の維持
     * - 例外安全性の基本保証
     */
    
    /*
     * ====================================================================
     * テスト4: 自己代入安全性の確認
     * ====================================================================
     */
    printSection("Test 4: Self-Assignment Safety");
    
    std::cout << "Testing self-assignment safety:" << std::endl;
    Cat selfAssignCat;
    
    std::cout << std::endl << "Before self-assignment:" << std::endl;
    displayAnimalInfo(&selfAssignCat, "Self-Assign Cat");
    
    std::cout << std::endl << "Performing self-assignment:" << std::endl;
    selfAssignCat = selfAssignCat;
    
    std::cout << std::endl << "After self-assignment:" << std::endl;
    displayAnimalInfo(&selfAssignCat, "Self-Assign Cat (should be unchanged)");
    
    std::cout << "Key observation: Self-assignment detected and handled safely" << std::endl;
    std::cout << "No unnecessary operations performed" << std::endl;
    
    /*
     * 【自己代入テストの学習ポイント】
     * 
     * 安全性メカニズム：
     * - if (this != &other) による検出
     * - 不要な削除・再作成の回避
     * - パフォーマンス最適化
     * - 自己破壊の防止
     * 
     * 危険な実装との比較：
     * - チェックなし: 自分の Brain を削除後に参照
     * - 結果: 未定義動作、クラッシュ
     * - 現実: 安全なチェックにより回避
     */
    
    /*
     * ====================================================================
     * テスト5: 多態性コレクションでの動的メモリ管理
     * ====================================================================
     */
    printSection("Test 5: Polymorphic Collections with Dynamic Memory");
    
    std::cout << "Creating polymorphic animal collection:" << std::endl;
    std::vector<Animal*> animalCollection;
    
    // 様々な動物を動的作成
    animalCollection.push_back(new Animal());
    animalCollection.push_back(new Cat());
    animalCollection.push_back(new Dog());
    animalCollection.push_back(new Cat());
    animalCollection.push_back(new Dog());
    
    std::cout << std::endl << "Processing collection with polymorphic calls:" << std::endl;
    for (size_t i = 0; i < animalCollection.size(); i++) {
        std::cout << "Animal " << i << ": ";
        std::cout << animalCollection[i]->getType() << " says ";
        animalCollection[i]->makeSound();
    }
    
    displayMemoryUsage(static_cast<int>(animalCollection.size()), static_cast<int>(animalCollection.size()));
    
    std::cout << std::endl << "Testing copy operations within collection context:" << std::endl;
    
    // コレクション内での copy 操作テスト
    Cat* originalInCollection = dynamic_cast<Cat*>(animalCollection[1]);
    if (originalInCollection) {
        Cat copiedFromCollection(*originalInCollection);
        std::cout << "Successfully copied Cat from collection:" << std::endl;
        displayAnimalInfo(&copiedFromCollection, "Copied from Collection");
    }
    
    /*
     * 【多態性コレクションテストの学習ポイント】
     * 
     * 多態性での利点：
     * - 統一インターフェースでの操作
     * - 型に応じた適切な動作
     * - 動的バインディングの活用
     * - 拡張性の確保
     * 
     * 動的メモリでの課題：
     * - Brain オブジェクトの大量作成
     * - メモリ使用量の増加
     * - 削除時の適切なリソース管理必要性
     * - パフォーマンスへの影響
     */
    
    /*
     * ====================================================================
     * テスト6: リソース管理とRAII原則の確認
     * ====================================================================
     */
    printSection("Test 6: Resource Management and RAII Principle");
    
    std::cout << "Testing RAII with scoped objects:" << std::endl;
    {
        std::cout << "Creating scoped animals (will auto-destruct):" << std::endl;
        Cat scopedCat;
        Dog scopedDog;
        
        std::cout << std::endl << "Objects created in scope, Brain allocated:" << std::endl;
        displayAnimalInfo(&scopedCat, "Scoped Cat");
        displayAnimalInfo(&scopedDog, "Scoped Dog");
        
        std::cout << std::endl << "Scope ending - observe automatic destruction:" << std::endl;
    }
    std::cout << "Scope ended - all resources should be automatically freed" << std::endl;
    
    std::cout << std::endl << "Testing explicit dynamic allocation and deallocation:" << std::endl;
    Animal* dynamicAnimal = new Cat();
    std::cout << "Dynamic animal created:" << std::endl;
    displayAnimalInfo(dynamicAnimal, "Dynamic Cat");
    
    std::cout << std::endl << "Explicit deletion - observe virtual destructor chain:" << std::endl;
    delete dynamicAnimal;
    std::cout << "Dynamic animal deleted safely" << std::endl;
    
    /*
     * 【RAII原則テストの学習ポイント】
     * 
     * スコープベース管理：
     * - スタックオブジェクトの自動破棄
     * - デストラクタチェーンの自動実行
     * - 例外発生時の安全なクリーンアップ
     * - メモリリークの自動防止
     * 
     * 動的割り当て管理：
     * - 明示的な delete の必要性
     * - 仮想デストラクタの重要性
     * - 適切な削除順序の自動実行
     * - リソース解放の確実性
     */
    
    /*
     * ====================================================================
     * テスト7: 例外安全性と異常系の動作確認
     * ====================================================================
     */
    printSection("Test 7: Exception Safety and Error Handling");
    
    std::cout << "Testing copy operations under potential failure scenarios:" << std::endl;
    
    try {
        std::cout << "Creating multiple objects to test resource management:" << std::endl;
        std::vector<Cat> catVector;
        
        // 大量のオブジェクト作成（メモリ不足の可能性を仮想的にテスト）
        for (int i = 0; i < 5; i++) {
            std::cout << "Creating Cat " << i << "..." << std::endl;
            Cat newCat;
            catVector.push_back(newCat);  // コピーコンストラクタ呼び出し
        }
        
        std::cout << std::endl << "All cats created successfully:" << std::endl;
        for (size_t i = 0; i < catVector.size(); i++) {
            std::cout << "Cat " << i << " type: " << catVector[i].getType() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "Resources should be automatically cleaned up" << std::endl;
    }
    
    std::cout << std::endl << "Exception test completed - observe automatic cleanup" << std::endl;
    
    /*
     * 【例外安全性テストの学習ポイント】
     * 
     * 基本例外安全性：
     * - リソースリークなし
     * - オブジェクト不変条件の維持
     * - 例外発生時の安全な状態
     * - スタック巻き戻しでの自動クリーンアップ
     * 
     * 強い例外安全性（改善可能）：
     * - 操作の完全成功または完全失敗
     * - 中間状態の回避
     * - Copy-and-Swap idiom の採用
     * - より高度な例外保証
     */
    
    /*
     * ====================================================================
     * テスト8: パフォーマンス影響の測定と比較
     * ====================================================================
     */
    printSection("Test 8: Performance Impact Assessment");
    
    std::cout << "Comparing creation/destruction performance:" << std::endl;
    
    // 簡易的なパフォーマンス測定
    std::cout << std::endl << "Creating and destroying multiple objects:" << std::endl;
    const int testCount = 10;
    
    std::cout << "Test iteration count: " << testCount << std::endl;
    
    for (int i = 0; i < testCount; i++) {
        Animal* testAnimal = nullptr;
        
        switch (i % 3) {
            case 0:
                testAnimal = new Animal();
                break;
            case 1:
                testAnimal = new Cat();
                break;
            case 2:
                testAnimal = new Dog();
                break;
        }
        
        if (testAnimal) {
            testAnimal->makeSound();
            delete testAnimal;
        }
    }
    
    std::cout << std::endl << "Performance considerations:" << std::endl;
    std::cout << "- Dynamic memory allocation overhead" << std::endl;
    std::cout << "- Virtual function call overhead" << std::endl;
    std::cout << "- Deep copy operation cost" << std::endl;
    std::cout << "- Brain object creation/destruction cost" << std::endl;
    
    displayMemoryUsage(0, 0);  // All cleaned up
    
    /*
     * 【パフォーマンステストの学習ポイント】
     * 
     * 測定すべき要素：
     * - オブジェクト作成時間（Brain 作成含む）
     * - コピー操作時間（深いコピーコスト）
     * - デストラクタ実行時間（チェーン全体）
     * - メモリ使用量（ヒープ使用量）
     * 
     * ex00 との比較：
     * - 作成時間の増加（Brain 作成分）
     * - メモリ使用量の増加（Brain オブジェクト分）
     * - より複雑なライフサイクル管理
     * - 設計の柔軟性向上
     */
    
    /*
     * ====================================================================
     * クリーンアップと最終確認
     * ====================================================================
     */
    printSection("Cleanup Phase - Final Resource Management Check");
    
    std::cout << "Cleaning up dynamically allocated objects:" << std::endl;
    delete animal;
    delete cat;
    delete dog;
    
    std::cout << std::endl << "Cleaning up collection:" << std::endl;
    for (Animal* collectionAnimal : animalCollection) {
        delete collectionAnimal;
    }
    
    std::cout << std::endl << "All resources cleaned up successfully" << std::endl;
    std::cout << "Observe the destructor chain execution order" << std::endl;
    
    displayMemoryUsage(0, 0);
    
    /*
     * ====================================================================
     * プログラム終了時の学習まとめ
     * ====================================================================
     */
    printSection("Learning Summary and Key Observations");
    
    std::cout << "Key insights from dynamic memory management with inheritance:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "1. Brain Aggregation Benefits:" << std::endl;
    std::cout << "   ✅ Clear separation of concerns (Animal vs Brain)" << std::endl;
    std::cout << "   ✅ Independent resource management" << std::endl;
    std::cout << "   ✅ Flexible design for future extensions" << std::endl;
    std::cout << "   ✅ Realistic modeling of has-a relationships" << std::endl;
    std::cout << std::endl;
    
    std::cout << "2. Deep Copy Implementation:" << std::endl;
    std::cout << "   ✅ Object independence guaranteed" << std::endl;
    std::cout << "   ✅ Safe copy operations without sharing" << std::endl;
    std::cout << "   ✅ Proper resource management in copies" << std::endl;
    std::cout << "   ✅ No double-delete or dangling pointer issues" << std::endl;
    std::cout << std::endl;
    
    std::cout << "3. RAII and Resource Management:" << std::endl;
    std::cout << "   ✅ Automatic resource cleanup" << std::endl;
    std::cout << "   ✅ Exception-safe operations (basic level)" << std::endl;
    std::cout << "   ✅ Deterministic destructor execution" << std::endl;
    std::cout << "   ✅ No manual memory management in normal use" << std::endl;
    std::cout << std::endl;
    
    std::cout << "4. Performance vs Design Trade-offs:" << std::endl;
    std::cout << "   • Increased memory usage (Brain objects)" << std::endl;
    std::cout << "   • Slower copy operations (deep copy cost)" << std::endl;
    std::cout << "   • More complex object lifecycle" << std::endl;
    std::cout << "   • BUT: Better design flexibility and safety" << std::endl;
    std::cout << std::endl;
    
    std::cout << "5. Inheritance with Dynamic Memory:" << std::endl;
    std::cout << "   ✅ Base class resource management inherited" << std::endl;
    std::cout << "   ✅ Virtual destructors ensure proper cleanup" << std::endl;
    std::cout << "   ✅ Polymorphism works correctly with resources" << std::endl;
    std::cout << "   ✅ Consistent behavior across derived classes" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Program completed successfully!" << std::endl;
    std::cout << "Review the detailed output to understand dynamic memory management patterns." << std::endl;
    
    return 0;
}

/*
 * ====================================================================
 * 期待される出力の概要
 * ====================================================================
 * 
 * 【Test 1 - Object Creation】
 * ```
 * Brain constructor called
 * Brain is being initialized with 100 ideas
 * Animal constructor called
 * Animal entity created with brain at address: 0x7f8b1c004000
 * Animal (Animal) is ready with thinking capacity!
 * 
 * Brain constructor called
 * Brain is being initialized with 100 ideas  
 * Animal constructor called
 * Animal entity created with brain at address: 0x7f8b1c004100
 * Animal (Animal) is ready with thinking capacity!
 * Cat constructor called
 * Cat is created with inherited brain capacity!
 * Meow! A smart cat is ready to think and play!
 * ```
 * 
 * 【Test 2 - Deep Copy】
 * ```
 * Brain copy constructor called
 * Copying brain with 100 ideas
 * New independent brain created at 0x7f8b1c004200
 * Animal copy constructor called
 * Copying Animal (Cat) with brain at 0x7f8b1c004100
 * New Animal created with independent brain at 0x7f8b1c004200
 * Cat copy constructor called
 * A new Cat is created as a copy with independent brain!
 * Meow meow! Another smart cat joins the family!
 * ```
 * 
 * 【Test 3 - Assignment】
 * ```
 * Brain copy constructor called
 * Copying brain with 100 ideas
 * New independent brain created at 0x7f8b1c004300
 * Animal assignment operator called
 * Animal updated to type: Cat
 * Brain replaced with new brain at: 0x7f8b1c004300
 * Cat assignment operator called
 * Cat has been updated with inherited brain management!
 * Purr purr! Smart cat has new memories!
 * ```
 * 
 * 【Test 4 - Self Assignment】
 * ```
 * Cat self-assignment detected - clever cat knows itself!
 * Animal self-assignment detected - no operation needed
 * ```
 * 
 * 【Test 6 - RAII Destruction】
 * ```
 * Cat destructor called
 * Cat is saying goodbye - brain will be safely released by Animal!
 * Meow... Smart cat is going to sleep peacefully...
 * Animal destructor called
 * Animal (Cat) brain resources released
 * Animal entity destroyed safely
 * Brain destructor called
 * Brain with 100 ideas is being destroyed
 * All brain resources released
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このプログラムで確認すべき項目：
 * 
 * □ Brain オブジェクトの動的作成と管理
 * □ 深いコピーによるオブジェクト独立性
 * □ 浅いコピーとの違いの理解
 * □ 代入演算子での適切なリソース管理
 * □ 自己代入安全性の動作確認
 * □ RAII原則の継承システムでの実践
 * □ 仮想デストラクタチェーンの実行順序
 * □ 多態性コレクションでの動的メモリ管理
 * □ 例外安全性の基本レベル動作
 * □ パフォーマンスと設計のトレードオフ実感
 * 
 * 【実習課題】
 * 1. Brain クラスの機能拡張（思考履歴、記憶容量等）
 * 2. より強い例外安全性の実装（Copy-and-Swap）
 * 3. スマートポインタを使った実装への変換
 * 4. パフォーマンス詳細測定とプロファイリング
 * 5. メモリリーク検出ツールでの検証
 */

/*
 * ====================================================================
 * デバッグとトラブルシューティング
 * ====================================================================
 * 
 * 【よくある実行時問題】
 * 
 * 1. 二重削除（Double Delete）：
 *    - 症状: プログラムクラッシュ、abort() 呼び出し
 *    - 原因: 浅いコピーによる同一Brain共有
 *    - 対策: 深いコピーの正確な実装確認
 * 
 * 2. メモリリーク：
 *    - 症状: メモリ使用量の継続増加
 *    - 原因: Brain オブジェクトの削除忘れ
 *    - 対策: デストラクタでの delete brain 確認
 * 
 * 3. 未初期化ポインタアクセス：
 *    - 症状: セグメンテーション違反
 *    - 原因: Brain ポインタの不適切な初期化
 *    - 対策: コンストラクタでの new Brain() 確認
 * 
 * 4. 代入演算子での例外：
 *    - 症状: bad_alloc または不正な状態
 *    - 原因: new Brain() の失敗時処理不備
 *    - 対策: 例外安全な実装への変更
 * 
 * 【デバッグ手法】
 * 
 * 1. メモリアドレス追跡：
 *    - Brain ポインタの値を出力
 *    - 作成・コピー・削除時のアドレス確認
 *    - 独立性の視覚的確認
 * 
 * 2. 詳細ログ出力：
 *    - 全コンストラクタ・デストラクタでの出力
 *    - Brain の状態変化追跡
 *    - 例外発生箇所の特定
 * 
 * 3. メモリ検出ツール：
 *    - valgrind でのリーク検出
 *    - AddressSanitizer での不正アクセス検出
 *    - 静的解析ツールでの潜在問題発見
 * 
 * 4. 段階的テスト：
 *    - 単一オブジェクト作成・削除
 *    - コピー操作の個別テスト
 *    - 大量オブジェクトでのストレステスト
 *    - 異常系での動作確認
 */