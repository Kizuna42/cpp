/*
 * ====================================================================
 * CPP04 ex00: Dog - 具体的動物クラス継承解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 異なる派生クラスでの仮想関数実装比較
 * - 同一基底クラスからの複数派生の理解
 * - 多態性での異なる動作実装の実践
 * - 継承の一貫性と多様性の両立
 * - 犬固有の特性と共通インターフェースの調和
 * 
 * 【重要概念】
 * - 兄弟クラス（Sibling Classes）としてのCat・Dog関係
 * - 同一vtableエントリでの異なる実装
 * - 多態性コレクションでの混在使用
 * - 継承階層での水平拡張パターン
 * - 型安全性を保持した機能多様化
 */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include <iostream>

/*
 * ====================================================================
 * Dog クラス設計思想
 * ====================================================================
 * 
 * 【なぜDogクラスが独立して必要なのか？】
 * 
 * 犬特有の行動実装：
 * - 忠実で社交的な性格の表現
 * - 猫とは異なる鳴き声・行動パターン
 * - 人間との関係性の違いを反映
 * 
 * 多態性システムでの多様性提供：
 * - Animal*配列での混在操作
 * - 統一インターフェースでの異なる結果
 * - 実行時の動的な行動選択
 * 
 * 【CatクラスとのDesign比較】
 * 
 * 共通点：
 * - 同じAnimal基底クラスから継承
 * - makeSound()の実装義務
 * - Orthodox Canonical Formの実装
 * 
 * 相違点：
 * - 鳴き声の実装内容
 * - デバッグメッセージの表現
 * - 将来的な拡張の方向性
 * 
 * 【ex00での学習重点】
 * 
 * 水平継承の理解：
 * - 複数の兄弟クラスの実装
 * - 基底クラス機能の共有活用
 * - 個別特化と共通化のバランス
 */
class Dog : public Animal {
public:
    /*
     * ====================================================================
     * Orthodox Canonical Form（継承版）
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * Dog();
     * 
     * 犬らしい初期化処理：
     * - 基底クラス初期化の継承活用
     * - typeを"Dog"に設定
     * - 忠実で活発な性格の表現
     * 
     * 初期化チェーン：
     * 1. Animal::Animal() 自動呼び出し（type="Animal"）
     * 2. Dog固有の初期化処理実行
     * 3. type="Dog"への更新
     * 4. 犬らしいメッセージ出力
     * 
     * Catとの実装比較：
     * - 基本構造は同一（継承パターンの一貫性）
     * - メッセージ内容で犬らしさを表現
     * - 将来的な犬固有メンバ追加への準備
     */
    Dog();
    
    /*
     * 【コピーコンストラクタ】
     * Dog(const Dog& other);
     * 
     * 犬オブジェクトのコピー生成：
     * - 基底クラス部分の完全コピー
     * - 犬固有データの複製（現在は無し）
     * - 新しい犬オブジェクトの独立性確保
     * 
     * 実装パターン：
     * ```cpp
     * Dog(const Dog& other) : Animal(other) {
     *     // 犬固有のコピー処理
     * }
     * ```
     * 
     * 多態性での使用例：
     * ```cpp
     * Dog original;
     * Dog copy(original);           // 直接コピー
     * Animal* animalCopy = new Dog(original);  // 多態的コピー
     * ```
     */
    Dog(const Dog& other);
    
    /*
     * 【代入演算子】
     * Dog& operator=(const Dog& other);
     * 
     * 犬オブジェクトの状態更新：
     * - 基底クラス代入演算子の活用
     * - 自己代入安全性の継承
     * - 犬固有データの代入処理
     * 
     * 代入プロセス：
     * 1. 自己代入チェック
     * 2. Animal::operator=(other) 呼び出し
     * 3. Dog固有メンバの代入（将来の拡張対応）
     * 4. *thisの返却
     * 
     * 使用シナリオ：
     * ```cpp
     * Dog dog1, dog2, dog3;
     * dog1 = dog2 = dog3;  // 連鎖代入
     * ```
     */
    Dog& operator=(const Dog& other);
    
    /*
     * 【デストラクタ】
     * ~Dog();
     * 
     * 犬オブジェクトの破棄処理：
     * - 仮想デストラクタの継承恩恵
     * - 犬固有リソースのクリーンアップ
     * - 基底クラスデストラクタの自動呼び出し
     * 
     * 多態性での重要性：
     * ```cpp
     * Animal* animal = new Dog();
     * delete animal;  // Dog::~Dog() → Animal::~Animal()
     * ```
     * 
     * 破棄メッセージ：
     * - 犬らしい別れの表現
     * - デバッグ時の実行確認
     * - オブジェクトライフサイクルの完了通知
     */
    ~Dog();
    
    /*
     * ====================================================================
     * 仮想関数のオーバーライド
     * ====================================================================
     */
    
    /*
     * 【仮想関数：makeSound のオーバーライド】
     * void makeSound() const;
     * 
     * 犬特有の鳴き声実装：
     * - "Woof! Woof!" という典型的な犬の鳴き声
     * - Catの"Meow! Meow!"との明確な差別化
     * - 多態性での動的な音の選択実現
     * 
     * vtableでの位置：
     * ```
     * Dog_vtable:
     * +------------------+
     * | destructor       | → Dog::~Dog()
     * | makeSound()      | → Dog::makeSound() ←これ
     * +------------------+
     * ```
     * 
     * 多態性での使用例：
     * ```cpp
     * std::vector<Animal*> animals;
     * animals.push_back(new Dog());
     * animals.push_back(new Cat());
     * 
     * for (Animal* animal : animals) {
     *     animal->makeSound();  // 各動物固有の音
     * }
     * // 出力: "Woof! Woof!" "Meow! Meow!"
     * ```
     * 
     * const correctness の維持：
     * - 基底クラスとの完全な一致
     * - 鳴く行為はオブジェクト状態を変更しない
     * - constオブジェクトからの呼び出し対応
     * 
     * 実装時の考慮事項：
     * - 犬らしい表現の選択
     * - 他の動物との差別化
     * - 将来的な拡張可能性（品種による違い等）
     */
    void makeSound() const;
};

#endif

/*
 * ====================================================================
 * 兄弟クラス関係の詳細
 * ====================================================================
 * 
 * 【Cat と Dog の関係図】
 * 
 * 継承階層：
 * ```
 *       Animal
 *      /      \
 *    Cat      Dog
 * ```
 * 
 * 共通基盤：
 * - 同じvtableエントリ数
 * - 同じメモリレイアウト基本構造
 * - 同じ基底クラス機能セット
 * 
 * 個別特化：
 * - makeSound() の異なる実装
 * - type値の違い（"Cat" vs "Dog"）
 * - デバッグメッセージの表現差
 * 
 * 【メモリレイアウト比較】
 * 
 * Cat オブジェクト：
 * ```
 * +------------------+
 * | vtable ptr       | → Cat_vtable
 * | type = "Cat"     |
 * +------------------+
 * | Cat固有領域      |
 * +------------------+
 * ```
 * 
 * Dog オブジェクト：
 * ```
 * +------------------+
 * | vtable ptr       | → Dog_vtable
 * | type = "Dog"     |
 * +------------------+
 * | Dog固有領域      |
 * +------------------+
 * ```
 * 
 * サイズの同一性：
 * - sizeof(Cat) == sizeof(Dog) （現在の実装では）
 * - 基底クラスサイズ + 各派生クラス固有サイズ
 * - vtableポインタは共通のオーバーヘッド
 */

/*
 * ====================================================================
 * 多態性での使用パターン
 * ====================================================================
 * 
 * 【パターン1：動物園シミュレーション】
 * ```cpp
 * class Zoo {
 * private:
 *     std::vector<Animal*> animals;
 * 
 * public:
 *     void addAnimal(Animal* animal) {
 *         animals.push_back(animal);
 *     }
 *     
 *     void feedingTime() {
 *         std::cout << "=== Feeding Time ===" << std::endl;
 *         for (Animal* animal : animals) {
 *             std::cout << animal->getType() << ": ";
 *             animal->makeSound();
 *         }
 *     }
 *     
 *     ~Zoo() {
 *         for (Animal* animal : animals) {
 *             delete animal;  // 各派生クラスのデストラクタが呼ばれる
 *         }
 *     }
 * };
 * 
 * Zoo zoo;
 * zoo.addAnimal(new Dog());
 * zoo.addAnimal(new Cat());
 * zoo.addAnimal(new Dog());
 * zoo.feedingTime();
 * ```
 * 
 * 【パターン2：動物の特性比較】
 * ```cpp
 * void compareAnimals(const Animal& animal1, const Animal& animal2) {
 *     std::cout << "=== Animal Comparison ===" << std::endl;
 *     
 *     std::cout << "Animal 1 (" << animal1.getType() << "): ";
 *     animal1.makeSound();
 *     
 *     std::cout << "Animal 2 (" << animal2.getType() << "): ";
 *     animal2.makeSound();
 *     
 *     if (animal1.getType() == animal2.getType()) {
 *         std::cout << "Same species!" << std::endl;
 *     } else {
 *         std::cout << "Different species!" << std::endl;
 *     }
 * }
 * 
 * Dog dog;
 * Cat cat;
 * compareAnimals(dog, cat);
 * ```
 * 
 * 【パターン3：動物ファクトリーでの生成】
 * ```cpp
 * class AnimalFactory {
 * public:
 *     enum AnimalType { DOG, CAT, UNKNOWN };
 *     
 *     static Animal* createAnimal(AnimalType type) {
 *         switch (type) {
 *             case DOG: return new Dog();
 *             case CAT: return new Cat();
 *             default: return nullptr;
 *         }
 *     }
 *     
 *     static Animal* createRandomAnimal() {
 *         int random = rand() % 2;
 *         return createAnimal(random == 0 ? DOG : CAT);
 *     }
 * };
 * 
 * // ランダムな動物を作成
 * Animal* randomAnimal = AnimalFactory::createRandomAnimal();
 * randomAnimal->makeSound();  // DogまたはCatの音
 * delete randomAnimal;
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ 兄弟クラス（Sibling Classes）の実装パターン
 * □ 同一基底クラスからの複数派生理解
 * □ 異なる派生クラスでの一貫した実装方法
 * □ 多態性での混在オブジェクト操作
 * □ vtableでの異なる関数実装の解決
 * □ メモリレイアウトの共通性と相違点
 * □ コレクションでの多型オブジェクト管理
 * □ ファクトリーパターンでの動的生成
 * □ 実行時型情報（RTTI）の基本理解
 * □ 継承階層での水平拡張パターン
 * 
 * 【実習課題】
 * 1. 新しい動物クラス（Bird, Fish等）の追加
 * 2. 動物固有の追加メンバ変数・関数の実装
 * 3. より複雑な多態性シナリオの作成
 * 4. パフォーマンス測定（Cat vs Dog vs Animal）
 * 5. 大規模な動物コレクションでの操作実装
 */

/*
 * ====================================================================
 * よくある多派生クラス実装のミス
 * ====================================================================
 * 
 * 【ミス1：不一致な実装パターン】
 * 
 * 問題例：
 * ```cpp
 * // Cat.hpp
 * void makeSound() const;
 * 
 * // Dog.hpp  
 * void makeSound();  // constがない！
 * ```
 * 
 * 影響：
 * - オーバーライドが成功しない
 * - 多態性が正しく働かない
 * - 予期しない基底クラス関数の呼び出し
 * 
 * 対策：
 * - 全兄弟クラスで統一したシグネチャ
 * - const correctnessの一貫性
 * - コンパイラ警告への注意
 * 
 * 【ミス2：基底クラス初期化の不一致】
 * 
 * 問題例：
 * ```cpp
 * Cat::Cat() {
 *     type = "Cat";  // 基底クラス初期化後に設定
 * }
 * 
 * Dog::Dog() : Animal() {
 *     type = "Dog";  // 明示的な基底クラス呼び出し
 * }
 * ```
 * 
 * 問題：
 * - 初期化タイミングの違い
 * - デバッグ出力の順序不整合
 * - 将来的な拡張での問題発生
 * 
 * 対策：
 * - 統一された初期化パターン採用
 * - 明示的な基底クラス呼び出し
 * - 一貫したtype設定タイミング
 * 
 * 【ミス3：vtableの理解不足】
 * 
 * 誤解例：
 * ```cpp
 * // "static"を使って仮想関数を置き換えようとする
 * class Dog : public Animal {
 * public:
 *     static void makeSound() {  // static！
 *         std::cout << "Woof!" << std::endl;
 *     }
 * };
 * ```
 * 
 * 問題：
 * - static関数は仮想関数をオーバーライドしない
 * - 多態性が働かない
 * - Animal*経由での呼び出しで基底クラス関数が実行される
 * 
 * 対策：
 * - virtual/static の違いを正確に理解
 * - オーバーライドの正しい構文使用
 * - テストによる動作確認
 * 
 * 【ミス4：メモリ管理の不整合】
 * 
 * 問題例：
 * ```cpp
 * class Dog : public Animal {
 * private:
 *     std::string* breed;  // 動的メモリ
 * 
 * public:
 *     Dog() : breed(new std::string("Unknown")) {}
 *     ~Dog() {}  // delete忘れ！
 * };
 * ```
 * 
 * 問題：
 * - メモリリークの発生
 * - 兄弟クラス間でのメモリ管理不整合
 * - RAII原則の破綻
 * 
 * 対策：
 * - 統一されたリソース管理戦略
 * - RAIIパターンの徹底
 * - 全兄弟クラスでの一貫した実装
 */

/*
 * ====================================================================
 * 発展的な兄弟クラス設計パターン
 * ====================================================================
 * 
 * 【パターン1：Visitor Pattern による型別処理】
 * ```cpp
 * class AnimalVisitor {
 * public:
 *     virtual ~AnimalVisitor() {}
 *     virtual void visitDog(const Dog& dog) = 0;
 *     virtual void visitCat(const Cat& cat) = 0;
 * };
 * 
 * class Animal {
 * public:
 *     virtual void accept(AnimalVisitor& visitor) const = 0;
 * };
 * 
 * class Dog : public Animal {
 * public:
 *     void accept(AnimalVisitor& visitor) const override {
 *         visitor.visitDog(*this);
 *     }
 * };
 * 
 * class Cat : public Animal {
 * public:
 *     void accept(AnimalVisitor& visitor) const override {
 *         visitor.visitCat(*this);
 *     }
 * };
 * 
 * class FeedingVisitor : public AnimalVisitor {
 * public:
 *     void visitDog(const Dog& dog) override {
 *         std::cout << "Feeding dog with meat" << std::endl;
 *     }
 *     
 *     void visitCat(const Cat& cat) override {
 *         std::cout << "Feeding cat with fish" << std::endl;
 *     }
 * };
 * ```
 * 
 * 【パターン2：Command Pattern による行動制御】
 * ```cpp
 * class AnimalCommand {
 * public:
 *     virtual ~AnimalCommand() {}
 *     virtual void execute(Animal& animal) const = 0;
 * };
 * 
 * class MakeSoundCommand : public AnimalCommand {
 * public:
 *     void execute(Animal& animal) const override {
 *         animal.makeSound();
 *     }
 * };
 * 
 * class AnimalController {
 * private:
 *     std::vector<AnimalCommand*> commands;
 * 
 * public:
 *     void addCommand(AnimalCommand* command) {
 *         commands.push_back(command);
 *     }
 *     
 *     void executeCommands(Animal& animal) const {
 *         for (const AnimalCommand* command : commands) {
 *             command->execute(animal);
 *         }
 *     }
 * };
 * ```
 * 
 * 【パターン3：Observer Pattern による状態監視】
 * ```cpp
 * class AnimalObserver {
 * public:
 *     virtual ~AnimalObserver() {}
 *     virtual void onAnimalSound(const Animal& animal) = 0;
 * };
 * 
 * class Animal {
 * private:
 *     std::vector<AnimalObserver*> observers;
 * 
 * protected:
 *     void notifyObservers() const {
 *         for (AnimalObserver* observer : observers) {
 *             observer->onAnimalSound(*this);
 *         }
 *     }
 * 
 * public:
 *     void addObserver(AnimalObserver* observer) {
 *         observers.push_back(observer);
 *     }
 * };
 * 
 * class Dog : public Animal {
 * public:
 *     void makeSound() const override {
 *         std::cout << "Woof! Woof!" << std::endl;
 *         notifyObservers();  // 観察者に通知
 *     }
 * };
 * 
 * class VeterinarianObserver : public AnimalObserver {
 * public:
 *     void onAnimalSound(const Animal& animal) override {
 *         std::cout << "Vet: " << animal.getType() 
 *                   << " seems healthy!" << std::endl;
 *     }
 * };
 * ```
 */