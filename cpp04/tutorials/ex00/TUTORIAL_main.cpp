/*
 * ====================================================================
 * CPP04 ex00: Animal Polymorphism - 仮想関数と多態性実証プログラム
 * ====================================================================
 * 
 * 【学習目標】
 * - 仮想関数による多態性の実際の動作確認
 * - virtual ありとなしの決定的な違いの体験
 * - 動的バインディングと静的バインディングの比較
 * - vtableメカニズムの実際の動作観察
 * - 正しい設計と問題のある設計の対比学習
 * 
 * 【重要概念】
 * - 実行時型情報（RTTI）の活用と制限
 * - オブジェクト指向設計の実践的な恩恵
 * - 拡張性と保守性の実装での実現
 * - パフォーマンスと設計の適切なバランス
 * - デバッグ困難な問題の実際の体験
 */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
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
 * - 長いテスト出力の視覚的整理
 * - 各テストフェーズの明確な区別
 * - 結果比較の容易性向上
 * - デバッグ時の迅速な問題特定支援
 */
void printSection(const std::string& title) {
    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
}

/*
 * 【多態性テスト関数】
 * void testPolymorphism(Animal* animal)
 * 
 * 目的：
 * - 統一されたインターフェースでの多態性確認
 * - 異なる派生クラスでの一貫した操作
 * - 動的バインディングの実際の動作観察
 * 
 * パラメータ：
 * - Animal* animal: テスト対象オブジェクトへのポインタ
 * 
 * 確認項目：
 * - getType() の正確な型情報返却
 * - makeSound() の派生クラス固有実装実行
 * - 基底クラスポインタでの派生クラス操作
 */
void testPolymorphism(Animal* animal) {
    std::cout << "--- Polymorphism Test ---" << std::endl;
    std::cout << "Animal type: " << animal->getType() << std::endl;
    std::cout << "Animal sound: ";
    animal->makeSound();
    std::cout << std::endl;
}

/*
 * 【Wrong系多態性テスト関数】
 * void testWrongPolymorphism(WrongAnimal* animal)
 * 
 * 目的：
 * - 非仮想基底クラスでの問題動作確認
 * - 期待される動作と実際の動作の乖離観察
 * - 静的バインディングの制限実証
 * 
 * パラメータ：
 * - WrongAnimal* animal: 問題実証用オブジェクトポインタ
 * 
 * 期待される問題：
 * - getType() は正しく派生クラス型を返す
 * - makeSound() は基底クラス実装のみ実行
 * - 多態性の恩恵を受けられない
 */
void testWrongPolymorphism(WrongAnimal* animal) {
    std::cout << "--- Wrong Polymorphism Test ---" << std::endl;
    std::cout << "WrongAnimal type: " << animal->getType() << std::endl;
    std::cout << "WrongAnimal sound: ";
    animal->makeSound();
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
     * このテストプログラムの実証内容：
     * 1. 正常な仮想関数継承（Animal/Cat/Dog）の動作確認
     * 2. 問題のある非仮想継承（WrongAnimal/WrongCat）の動作確認
     * 3. 両者の直接的な比較による学習効果最大化
     * 4. 多態性の実用的なパターンの実装例
     * 5. パフォーマンスと設計のトレードオフの実感
     */
    
    std::cout << "CPP04 ex00: Virtual Functions and Polymorphism Demonstration" << std::endl;
    std::cout << "Comparing correct (virtual) vs incorrect (non-virtual) implementations" << std::endl;
    
    /*
     * ====================================================================
     * テスト1: 基本的なオブジェクト作成と直接呼び出し
     * ====================================================================
     */
    printSection("Test 1: Direct Object Creation and Method Calls");
    
    std::cout << "Creating Animal hierarchy objects:" << std::endl;
    Animal* animal = new Animal();
    Cat* cat = new Cat();
    Dog* dog = new Dog();
    
    std::cout << std::endl << "Direct method calls:" << std::endl;
    std::cout << "Animal: " << animal->getType() << " -> ";
    animal->makeSound();
    
    std::cout << "Cat: " << cat->getType() << " -> ";
    cat->makeSound();
    
    std::cout << "Dog: " << dog->getType() << " -> ";
    dog->makeSound();
    
    /*
     * 【直接呼び出しでの学習ポイント】
     * 
     * この段階では全て期待通りに動作：
     * - animal->makeSound() -> Animal::makeSound()
     * - cat->makeSound() -> Cat::makeSound()
     * - dog->makeSound() -> Dog::makeSound()
     * 
     * 重要な観察点：
     * - 各オブジェクトが正しい型情報を持つ
     * - 各クラス固有のmakeSound()が実行される
     * - virtualの効果はまだ明確でない
     */
    
    /*
     * ====================================================================
     * テスト2: 多態性による統一操作（仮想関数版）
     * ====================================================================
     */
    printSection("Test 2: Polymorphic Operations (Virtual Functions)");
    
    std::cout << "Testing polymorphism with Animal* pointers:" << std::endl;
    
    // 基底クラスポインタに派生クラスオブジェクトを代入
    Animal* polymorphicAnimal1 = cat;
    Animal* polymorphicAnimal2 = dog;
    
    std::cout << std::endl << "Polymorphic calls through Animal* pointers:" << std::endl;
    testPolymorphism(polymorphicAnimal1);  // Cat::makeSound() が期待される
    testPolymorphism(polymorphicAnimal2);  // Dog::makeSound() が期待される
    
    /*
     * 【多態性テストの学習ポイント】
     * 
     * 期待される動作：
     * - Animal* polymorphicAnimal1 = cat でも cat->makeSound() 実行
     * - Animal* polymorphicAnimal2 = dog でも dog->makeSound() 実行
     * - 基底クラスポインタ経由でも派生クラス機能が動作
     * 
     * virtualの効果：
     * - vtableを通じた動的関数解決
     * - 実行時の実際の型に基づく関数選択
     * - コンパイル時ではなく実行時の柔軟性
     */
    
    /*
     * ====================================================================
     * テスト3: Wrong系クラスでの問題実証
     * ====================================================================
     */
    printSection("Test 3: Problematic Non-Virtual Implementation");
    
    std::cout << "Creating WrongAnimal hierarchy objects:" << std::endl;
    WrongAnimal* wrongAnimal = new WrongAnimal();
    WrongCat* wrongCat = new WrongCat();
    
    std::cout << std::endl << "Direct method calls on Wrong classes:" << std::endl;
    std::cout << "WrongAnimal: " << wrongAnimal->getType() << " -> ";
    wrongAnimal->makeSound();
    
    std::cout << "WrongCat: " << wrongCat->getType() << " -> ";
    wrongCat->makeSound();
    
    std::cout << std::endl << "Polymorphic calls with WrongAnimal* pointers:" << std::endl;
    WrongAnimal* polymorphicWrongAnimal = wrongCat;
    testWrongPolymorphism(polymorphicWrongAnimal);
    
    /*
     * 【Wrong系での問題観察ポイント】
     * 
     * 直接呼び出し（期待通り）：
     * - wrongCat->makeSound() -> WrongCat::makeSound()
     * - 問題はまだ顕在化しない
     * 
     * 多態的呼び出し（問題発生）：
     * - polymorphicWrongAnimal->makeSound() -> WrongAnimal::makeSound()
     * - WrongCat::makeSound() が呼ばれない！
     * - getType() は正しく "WrongCat" を返すのにmakeSound()は違う
     * 
     * 問題の深刻さ：
     * - コンパイルエラーなし
     * - 実行時まで問題が発覚しない
     * - デバッグが非常に困難
     */
    
    /*
     * ====================================================================
     * テスト4: コレクション操作での多態性活用
     * ====================================================================
     */
    printSection("Test 4: Collection-based Polymorphic Operations");
    
    std::cout << "Creating animal collections:" << std::endl;
    std::vector<Animal*> animalCollection;
    animalCollection.push_back(new Animal());
    animalCollection.push_back(new Cat());
    animalCollection.push_back(new Dog());
    animalCollection.push_back(new Cat());
    
    std::cout << std::endl << "Processing animal collection:" << std::endl;
    for (size_t i = 0; i < animalCollection.size(); i++) {
        std::cout << "Animal " << i << " (" << animalCollection[i]->getType() << "): ";
        animalCollection[i]->makeSound();
    }
    
    std::cout << std::endl << "Creating wrong animal collection:" << std::endl;
    std::vector<WrongAnimal*> wrongAnimalCollection;
    wrongAnimalCollection.push_back(new WrongAnimal());
    wrongAnimalCollection.push_back(new WrongCat());
    wrongAnimalCollection.push_back(new WrongCat());
    
    std::cout << std::endl << "Processing wrong animal collection:" << std::endl;
    for (size_t i = 0; i < wrongAnimalCollection.size(); i++) {
        std::cout << "WrongAnimal " << i << " (" << wrongAnimalCollection[i]->getType() << "): ";
        wrongAnimalCollection[i]->makeSound();
    }
    
    /*
     * 【コレクション操作での学習ポイント】
     * 
     * 正常なコレクション（Animal*）:
     * - 各要素が正しい音を出す
     * - AnimalはAnimalの音、CatはCatの音、DogはDogの音
     * - 統一されたインターフェースで多様な動作
     * 
     * 問題のあるコレクション（WrongAnimal*）:
     * - 全て同じWrongAnimal::makeSound()が実行される
     * - 型情報（getType()）は正しいのに動作は画一的
     * - せっかくの派生クラス実装が活用されない
     * 
     * 実用的な影響：
     * - 動物園システム、ゲーム、シミュレーション等で致命的
     * - ユーザー体験の著しい劣化
     * - 拡張性・保守性の完全な破綻
     */
    
    /*
     * ====================================================================
     * テスト5: オブジェクトライフサイクルとデストラクタ
     * ====================================================================
     */
    printSection("Test 5: Object Lifecycle and Destructor Behavior");
    
    std::cout << "Testing virtual destructor behavior:" << std::endl;
    Animal* testAnimal1 = new Dog();
    std::cout << "Deleting Dog through Animal* pointer:" << std::endl;
    delete testAnimal1;  // Dog::~Dog() → Animal::~Animal() の順で実行されるはず
    
    std::cout << std::endl << "Testing non-virtual destructor behavior:" << std::endl;
    WrongAnimal* testAnimal2 = new WrongCat();
    std::cout << "Deleting WrongCat through WrongAnimal* pointer:" << std::endl;
    delete testAnimal2;  // WrongAnimal::~WrongAnimal() のみ実行される問題
    
    /*
     * 【デストラクタテストの学習ポイント】
     * 
     * 仮想デストラクタ（Animal）:
     * - 正しいデストラクタチェーンの実行
     * - 派生クラス → 基底クラスの順序
     * - メモリリークなし、リソース適切解放
     * 
     * 非仮想デストラクタ（WrongAnimal）:
     * - 基底クラスデストラクタのみ実行
     * - 派生クラスのクリーンアップがスキップ
     * - 潜在的なメモリリーク・リソースリーク
     * 
     * 実際の問題：
     * - ファイルハンドルの解放漏れ
     * - 動的メモリの解放漏れ
     * - ネットワーク接続の切断漏れ
     * - 長時間実行でのリソース枯渇
     */
    
    /*
     * ====================================================================
     * テスト6: 参照による多態性確認
     * ====================================================================
     */
    printSection("Test 6: Reference-based Polymorphism");
    
    std::cout << "Testing polymorphism with references:" << std::endl;
    
    Cat referenceCat;
    Dog referenceDog;
    
    std::cout << std::endl << "Reference-based virtual function calls:" << std::endl;
    Animal& animalRef1 = referenceCat;
    Animal& animalRef2 = referenceDog;
    
    std::cout << "Cat reference through Animal&: " << animalRef1.getType() << " -> ";
    animalRef1.makeSound();
    
    std::cout << "Dog reference through Animal&: " << animalRef2.getType() << " -> ";
    animalRef2.makeSound();
    
    std::cout << std::endl << "Reference-based non-virtual function calls:" << std::endl;
    WrongCat wrongReferenceCat;
    WrongAnimal& wrongAnimalRef = wrongReferenceCat;
    
    std::cout << "WrongCat reference through WrongAnimal&: " << wrongAnimalRef.getType() << " -> ";
    wrongAnimalRef.makeSound();
    
    /*
     * 【参照での多態性テストの学習ポイント】
     * 
     * 仮想関数での参照（Animal&）:
     * - ポインタと同様に動的バインディング動作
     * - 実際のオブジェクト型に基づく関数実行
     * - nullポインタ問題がない安全性
     * 
     * 非仮想関数での参照（WrongAnimal&）:
     * - ポインタと同様に静的バインディング
     * - 期待と異なる動作
     * - 型安全だが機能的に問題
     * 
     * 参照 vs ポインタの比較：
     * - 両方とも同じ多態性動作
     * - 参照の方が null安全
     * - ポインタの方が動的生成に便利
     */
    
    /*
     * ====================================================================
     * テスト7: 実用的なパターン実装例
     * ====================================================================
     */
    printSection("Test 7: Practical Design Pattern Implementation");
    
    std::cout << "Implementing Animal Factory pattern:" << std::endl;
    
    // 簡易ファクトリーパターンの実装
    auto createAnimal = [](const std::string& type) -> Animal* {
        if (type == "cat") return new Cat();
        if (type == "dog") return new Dog();
        return new Animal();
    };
    
    std::vector<std::string> animalTypes = {"cat", "dog", "cat", "default"};
    std::vector<Animal*> factoryAnimals;
    
    std::cout << std::endl << "Creating animals through factory:" << std::endl;
    for (const std::string& type : animalTypes) {
        Animal* factoryAnimal = createAnimal(type);
        factoryAnimals.push_back(factoryAnimal);
        std::cout << "Created " << type << " -> " << factoryAnimal->getType() << ": ";
        factoryAnimal->makeSound();
    }
    
    std::cout << std::endl << "Demonstrating strategy-like behavior:" << std::endl;
    
    // 統一されたインターフェースでの異なる動作
    auto processAnimal = [](Animal* animal, const std::string& action) {
        std::cout << action << " " << animal->getType() << ": ";
        animal->makeSound();
    };
    
    for (Animal* factoryAnimal : factoryAnimals) {
        processAnimal(factoryAnimal, "Processing");
    }
    
    /*
     * 【実用パターンでの学習ポイント】
     * 
     * Factory Pattern:
     * - 動的な型選択と生成
     * - 統一されたインターフェースの提供
     * - 実行時の柔軟性実現
     * 
     * Strategy-like Behavior:
     * - 同じ操作で異なる結果
     * - アルゴリズムの実装差の隠蔽
     * - 拡張可能な設計の実現
     * 
     * 多態性の実用価値:
     * - コードの重複削減
     * - 新しい型追加時の既存コード変更不要
     * - プラグイン的な機能拡張可能性
     */
    
    /*
     * ====================================================================
     * リソースクリーンアップ
     * ====================================================================
     */
    printSection("Cleanup Phase - Observing Destructor Behavior");
    
    std::cout << "Cleaning up Animal* objects:" << std::endl;
    delete animal;
    delete cat;
    delete dog;
    
    std::cout << std::endl << "Cleaning up WrongAnimal* objects:" << std::endl;
    delete wrongAnimal;
    delete wrongCat;
    
    std::cout << std::endl << "Cleaning up collections:" << std::endl;
    for (Animal* collectionAnimal : animalCollection) {
        delete collectionAnimal;
    }
    
    for (WrongAnimal* wrongCollectionAnimal : wrongAnimalCollection) {
        delete wrongCollectionAnimal;
    }
    
    for (Animal* factoryAnimal : factoryAnimals) {
        delete factoryAnimal;
    }
    
    /*
     * ====================================================================
     * プログラム終了時の学習まとめ
     * ====================================================================
     */
    printSection("Learning Summary and Key Takeaways");
    
    std::cout << "Key observations from this demonstration:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "1. Virtual Functions (Animal/Cat/Dog):" << std::endl;
    std::cout << "   ✅ Polymorphism works as expected" << std::endl;
    std::cout << "   ✅ Dynamic binding selects correct functions" << std::endl;
    std::cout << "   ✅ Safe destructor behavior" << std::endl;
    std::cout << "   ✅ Extensible and maintainable design" << std::endl;
    std::cout << std::endl;
    
    std::cout << "2. Non-Virtual Functions (WrongAnimal/WrongCat):" << std::endl;
    std::cout << "   ❌ Polymorphism doesn't work through base pointers" << std::endl;
    std::cout << "   ❌ Static binding ignores actual object type" << std::endl;
    std::cout << "   ❌ Potential memory leaks with destructors" << std::endl;
    std::cout << "   ❌ Limited extensibility and maintainability" << std::endl;
    std::cout << std::endl;
    
    std::cout << "3. Design Implications:" << std::endl;
    std::cout << "   • Virtual functions enable true object-oriented design" << std::endl;
    std::cout << "   • Small performance cost for significant design benefits" << std::endl;
    std::cout << "   • Essential for collections of heterogeneous objects" << std::endl;
    std::cout << "   • Foundation for advanced patterns (Factory, Strategy, etc.)" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Program completed. Review the output to understand the differences!" << std::endl;
    
    return 0;
}

/*
 * ====================================================================
 * 期待される出力の概要
 * ====================================================================
 * 
 * 【Test 1 - Direct Calls】
 * ```
 * Animal constructor called
 * Animal entity initialized (type: Animal)
 * Animal: Animal -> Some generic animal sound!
 * 
 * Cat constructor called  
 * Cat Kitty is ready to play!
 * Cat: Cat -> Meow! Meow!
 * 
 * Dog constructor called
 * Dog Buddy is ready to play!
 * Dog: Dog -> Woof! Woof!
 * ```
 * 
 * 【Test 2 - Polymorphism (Virtual)】
 * ```
 * --- Polymorphism Test ---
 * Animal type: Cat
 * Animal sound: Meow! Meow!  ← 正しく Cat の音
 * 
 * --- Polymorphism Test ---
 * Animal type: Dog  
 * Animal sound: Woof! Woof!  ← 正しく Dog の音
 * ```
 * 
 * 【Test 3 - Wrong Polymorphism (Non-Virtual)】
 * ```
 * WrongCat: Wrong Meow! Wrong Meow!  ← 直接呼び出しは正常
 * 
 * --- Wrong Polymorphism Test ---
 * WrongAnimal type: WrongCat  ← 型は正しい
 * WrongAnimal sound: Some generic wrong animal sound!  ← ❌ 音は基底クラス
 * ```
 * 
 * 【Test 4 - Collection Operations】
 * ```
 * Animal 0 (Animal): Some generic animal sound!
 * Animal 1 (Cat): Meow! Meow!      ← 各動物の固有音
 * Animal 2 (Dog): Woof! Woof!      ← 各動物の固有音
 * Animal 3 (Cat): Meow! Meow!      ← 各動物の固有音
 * 
 * WrongAnimal 0 (WrongAnimal): Some generic wrong animal sound!
 * WrongAnimal 1 (WrongCat): Some generic wrong animal sound!  ← ❌ 全て同じ
 * WrongAnimal 2 (WrongCat): Some generic wrong animal sound!  ← ❌ 全て同じ
 * ```
 * 
 * 【Test 5 - Destructors】
 * ```
 * Dog destructor called
 * Dog is going to sleep!
 * Animal destructor called          ← 正しいチェーン
 * 
 * WrongAnimal destructor called     ← ❌ WrongCat のデストラクタが呼ばれない
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このプログラムで確認すべき項目：
 * 
 * □ 仮想関数による動的バインディングの実際の動作
 * □ 非仮想関数による静的バインディングの制限
 * □ 基底クラスポインタでの派生クラス操作の可否
 * □ 参照による多態性の動作確認
 * □ コレクション操作での多態性の価値
 * □ デストラクタチェーンの実行順序と安全性
 * □ Factory パターンでの多態性活用
 * □ 実用的な設計パターンでの多態性の恩恵
 * □ パフォーマンスと設計のトレードオフ理解
 * □ デバッグの困難さと設計の重要性の実感
 * 
 * 【実習課題】
 * 1. 新しい動物クラス（Bird, Fish等）の追加と動作確認
 * 2. より複雑な継承階層での多態性テスト
 * 3. 仮想関数のパフォーマンス測定実験
 * 4. 大規模オブジェクトコレクションでの動作確認
 * 5. 実用的なアプリケーションでの多態性活用例の実装
 */

/*
 * ====================================================================
 * デバッグとトラブルシューティング
 * ====================================================================
 * 
 * 【よくある実行時問題】
 * 
 * 1. 期待と異なる関数が実行される：
 *    - 非仮想関数による静的バインディング
 *    - 基底クラスポインタでの関数解決
 *    - virtualキーワードの有無を確認
 * 
 * 2. デストラクタが完全に実行されない：
 *    - 非仮想デストラクタによる問題
 *    - 派生クラスのクリーンアップがスキップ
 *    - メモリリーク・リソースリークの原因
 * 
 * 3. コンパイルは成功するが動作が異常：
 *    - 関数隠蔽（Function Hiding）による問題
 *    - オーバーライドのつもりが新しい関数定義
 *    - const correctness の不一致
 * 
 * 【デバッグ手法】
 * 
 * 1. 詳細なログ出力：
 *    - コンストラクタ・デストラクタでの出力
 *    - 関数実行時の型情報出力
 *    - 実行パスの可視化
 * 
 * 2. 型情報の確認：
 *    - typeid().name() による実際の型確認
 *    - getType() による期待型との比較
 *    - ポインタ・参照の型と実体の型の確認
 * 
 * 3. 段階的テスト：
 *    - 直接呼び出しでの動作確認
 *    - ポインタ経由での動作確認
 *    - 参照経由での動作確認
 *    - コレクション操作での動作確認
 */