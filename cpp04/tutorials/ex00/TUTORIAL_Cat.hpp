/*
 * ====================================================================
 * CPP04 ex00: Cat - 具体的動物クラス継承解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 仮想関数の実装とオーバーライドの実践
 * - 継承における基底クラスとの関係理解
 * - 多態性での具体的な動作実装
 * - Orthodox Canonical Form の継承版実装
 * - 猫固有の振る舞いと共通インターフェースの両立
 * 
 * 【重要概念】
 * - virtual関数のオーバーライドメカニズム
 * - 基底クラスコンストラクタの呼び出し
 * - 派生クラス固有の状態管理
 * - is-a関係の実践的実装
 * - 動的バインディングでの正しい関数選択
 */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include <iostream>

/*
 * ====================================================================
 * Cat クラス設計思想
 * ====================================================================
 * 
 * 【なぜCatクラスが必要なのか？】
 * 
 * 具体的動物の実装：
 * - Animalクラスの抽象的概念を具体化
 * - 猫特有の行動・特性の実装
 * - 多態性システムでの実際の動作提供
 * 
 * 継承の利点活用：
 * - 共通機能（type管理）の再利用
 * - 統一インターフェースでの操作可能性
 * - コードの重複排除
 * 
 * 【ex00での学習内容】
 * 
 * 基本的な継承実装：
 * - public継承によるis-a関係
 * - virtual関数のオーバーライド
 * - 基底クラス機能の活用
 * 
 * 多態性の実践：
 * - Animal*でのCat操作
 * - 動的バインディングの確認
 * - 仮想関数テーブルの活用
 */
class Cat : public Animal {
public:
    /*
     * ====================================================================
     * Orthodox Canonical Form（継承版）
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * Cat();
     * 
     * 継承でのコンストラクタ設計：
     * - 基底クラスコンストラクタの自動呼び出し
     * - 派生クラス固有の初期化処理
     * - typeメンバの適切な設定
     * 
     * 初期化プロセス：
     * 1. Animal::Animal() の呼び出し（type="Animal"設定）
     * 2. Cat固有の初期化処理実行
     * 3. typeを"Cat"に更新
     * 4. デバッグ出力による動作確認
     * 
     * 猫らしい初期化：
     * - 好奇心旺盛な性格の設定
     * - 独立心の表現
     * - 愛らしさの演出
     */
    Cat();
    
    /*
     * 【コピーコンストラクタ】
     * Cat(const Cat& other);
     * 
     * 継承でのコピー処理：
     * - 基底クラス部分の適切なコピー
     * - 派生クラス固有データのコピー
     * - オブジェクト独立性の確保
     * 
     * コピーチェーン：
     * 1. Animal(other) による基底部分コピー
     * 2. Cat固有データのコピー（現在は追加データなし）
     * 3. 新しいオブジェクトの完全な独立性確保
     * 
     * 将来の拡張対応：
     * - 猫固有メンバ追加時の対応準備
     * - 深いコピーの実装基盤
     * - メモリ管理の適切な処理
     */
    Cat(const Cat& other);
    
    /*
     * 【代入演算子】
     * Cat& operator=(const Cat& other);
     * 
     * 継承での代入処理：
     * - 基底クラス代入演算子の呼び出し
     * - 派生クラス固有データの代入
     * - 自己代入安全性の確保
     * 
     * 代入チェーン：
     * 1. 自己代入チェック（this != &other）
     * 2. Animal::operator=(other) 呼び出し
     * 3. Cat固有データの代入（現在は追加データなし）
     * 4. *thisの返却
     * 
     * 設計考慮：
     * - スライシング問題の回避
     * - 例外安全性の確保
     * - 効率的な実装
     */
    Cat& operator=(const Cat& other);
    
    /*
     * 【デストラクタ】
     * ~Cat();
     * 
     * 継承でのデストラクタ設計：
     * - 仮想デストラクタ（基底クラスで定義済み）
     * - 派生クラス固有のクリーンアップ
     * - 自動的な基底クラスデストラクタ呼び出し
     * 
     * 破棄順序：
     * 1. Cat::~Cat() の実行
     * 2. 派生クラス固有のクリーンアップ
     * 3. Animal::~Animal() の自動実行
     * 4. オブジェクトメモリの解放
     * 
     * virtualの重要性：
     * - 多態性での正しい削除処理
     * - メモリリークの防止
     * - リソース管理の完全性
     */
    ~Cat();
    
    /*
     * ====================================================================
     * 仮想関数のオーバーライド
     * ====================================================================
     */
    
    /*
     * 【仮想関数：makeSound のオーバーライド】
     * void makeSound() const override;
     * 
     * 猫特有の音の実装：
     * - "Meow! Meow!" という典型的な猫の鳴き声
     * - Animal::makeSound() の抽象的実装を具体化
     * - 多態性での正しい関数選択を実現
     * 
     * virtual機能の活用：
     * ```cpp
     * Animal* animal = new Cat();
     * animal->makeSound();  // Cat::makeSound() が呼ばれる
     * delete animal;
     * ```
     * 
     * override キーワード（C++11以降、42では不使用）:
     * - 仮想関数のオーバーライドを明示
     * - タイプミスによるバグ防止
     * - コンパイラによる検証支援
     * 
     * C++98での実装注意点：
     * - override キーワード不使用
     * - シグネチャの完全一致が必要
     * - const correctness の維持
     * 
     * const指定の重要性：
     * - 基底クラスとの一致（const void makeSound() const）
     * - 猫の音を出す行為は状態を変更しない
     * - constオブジェクトからの呼び出し対応
     */
    void makeSound() const;
};

#endif

/*
 * ====================================================================
 * 継承の詳細メカニズム
 * ====================================================================
 * 
 * 【メモリレイアウト】
 * 
 * Catオブジェクトの構造：
 * ```
 * Cat オブジェクト:
 * +------------------+
 * | Animal 部分      |
 * | - vtable ptr     | → Cat の vtable
 * | - type (string)  | → "Cat"
 * +------------------+
 * | Cat 固有部分     |
 * | (現在は空)       |
 * +------------------+
 * ```
 * 
 * 【vtable の構造】
 * 
 * Animal の vtable：
 * ```
 * Animal_vtable:
 * +------------------+
 * | destructor       | → Animal::~Animal()
 * | makeSound()      | → Animal::makeSound()
 * +------------------+
 * ```
 * 
 * Cat の vtable（継承後）：
 * ```
 * Cat_vtable:
 * +------------------+
 * | destructor       | → Cat::~Cat()
 * | makeSound()      | → Cat::makeSound() (オーバーライド)
 * +------------------+
 * ```
 * 
 * 【継承チェーンでの初期化順序】
 * 
 * コンストラクタ実行順序：
 * 1. Animal::Animal() - 基底クラス初期化
 * 2. Cat::Cat() - 派生クラス初期化
 * 
 * デストラクタ実行順序：
 * 1. Cat::~Cat() - 派生クラス破棄
 * 2. Animal::~Animal() - 基底クラス破棄
 */

/*
 * ====================================================================
 * 多態性の実用的なパターン
 * ====================================================================
 * 
 * 【パターン1：動物コレクションでの統一操作】
 * ```cpp
 * std::vector<Animal*> animals;
 * animals.push_back(new Cat());
 * animals.push_back(new Dog());
 * 
 * for (Animal* animal : animals) {
 *     animal->makeSound();  // 各動物固有の音
 *     std::cout << animal->getType() << std::endl;
 * }
 * 
 * // クリーンアップ
 * for (Animal* animal : animals) {
 *     delete animal;  // 各派生クラスのデストラクタが呼ばれる
 * }
 * ```
 * 
 * 【パターン2：動物の行動シミュレーション】
 * ```cpp
 * void simulateAnimalBehavior(Animal& animal) {
 *     std::cout << "=== " << animal.getType() << " Behavior ===" << std::endl;
 *     
 *     std::cout << "Making sound: ";
 *     animal.makeSound();
 *     
 *     std::cout << "Type information: " << animal.getType() << std::endl;
 * }
 * 
 * Cat cat;
 * simulateAnimalBehavior(cat);  // Cat固有の動作
 * ```
 * 
 * 【パターン3：Factory による動物作成】
 * ```cpp
 * class AnimalFactory {
 * public:
 *     static Animal* createAnimal(const std::string& type) {
 *         if (type == "Cat") return new Cat();
 *         if (type == "Dog") return new Dog();
 *         return nullptr;
 *     }
 * };
 * 
 * Animal* animal = AnimalFactory::createAnimal("Cat");
 * if (animal) {
 *     animal->makeSound();  // Cat::makeSound() が実行
 *     delete animal;
 * }
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ public継承によるis-a関係の実装
 * □ 基底クラスコンストラクタの自動呼び出し
 * □ virtual関数のオーバーライドメカニズム
 * □ 多態性での動的バインディング活用
 * □ Orthodox Canonical Form の継承版実装
 * □ const correctness の継承での維持
 * □ vtable による関数解決の理解
 * □ メモリレイアウトでの継承構造理解
 * □ デストラクタチェーンの実行順序
 * □ 派生クラス固有機能と共通機能の分離
 * 
 * 【実習課題】
 * 1. 追加の猫固有メンバ変数の実装
 * 2. 新しい仮想関数の追加とオーバーライド
 * 3. より複雑な継承階層での多態性テスト
 * 4. パフォーマンス測定（仮想関数 vs 非仮想関数）
 * 5. 異なる動物クラスとの相互作用実装
 */

/*
 * ====================================================================
 * よくある継承実装のミスと対策
 * ====================================================================
 * 
 * 【ミス1：コンストラクタでの基底クラス初期化忘れ】
 * 
 * 間違い例：
 * ```cpp
 * Cat::Cat() {  // Animal() が自動で呼ばれるが、明示的制御なし
 *     // type設定を忘れる
 * }
 * ```
 * 
 * 正解：
 * ```cpp
 * Cat::Cat() {
 *     type = "Cat";  // 明示的なtype設定
 * }
 * ```
 * 
 * 【ミス2：仮想関数のシグネチャ不一致】
 * 
 * 間違い例：
 * ```cpp
 * void makeSound();     // constがない
 * void makeSound() const override;  // overrideはC++11
 * ```
 * 
 * 正解：
 * ```cpp
 * void makeSound() const;  // 基底クラスと完全一致
 * ```
 * 
 * 【ミス3：デストラクタの実装忘れ】
 * 
 * 問題：
 * - 基底クラスでvirtualデストラクタがあっても実装は必要
 * - 派生クラス固有のクリーンアップの機会逸失
 * 
 * 対策：
 * ```cpp
 * ~Cat() {
 *     // 派生クラス固有のクリーンアップ
 *     std::cout << "Cat destructor called" << std::endl;
 * }
 * ```
 * 
 * 【ミス4：コピー処理での基底クラス部分の処理忘れ】
 * 
 * 間違い例：
 * ```cpp
 * Cat::Cat(const Cat& other) {
 *     // 基底クラス部分がコピーされない
 * }
 * ```
 * 
 * 正解：
 * ```cpp
 * Cat::Cat(const Cat& other) : Animal(other) {
 *     // 基底クラス部分も適切にコピー
 * }
 * ```
 */

/*
 * ====================================================================
 * 発展的な継承パターン
 * ====================================================================
 * 
 * 【パターン1：Template Method Pattern の活用】
 * ```cpp
 * class Animal {
 * public:
 *     void dailyRoutine() const {  // Template Method
 *         wakeUp();
 *         makeSound();    // 仮想関数（サブクラス実装）
 *         eat();          // 仮想関数
 *         play();         // 仮想関数
 *         sleep();
 *     }
 * 
 * protected:
 *     virtual void eat() const = 0;
 *     virtual void play() const = 0;
 *     
 * private:
 *     void wakeUp() const { std::cout << "Waking up..." << std::endl; }
 *     void sleep() const { std::cout << "Going to sleep..." << std::endl; }
 * };
 * 
 * class Cat : public Animal {
 * protected:
 *     void eat() const override {
 *         std::cout << "Cat is eating fish..." << std::endl;
 *     }
 *     
 *     void play() const override {
 *         std::cout << "Cat is playing with yarn..." << std::endl;
 *     }
 * };
 * ```
 * 
 * 【パターン2：State Pattern の組み込み】
 * ```cpp
 * class CatState {
 * public:
 *     virtual ~CatState() {}
 *     virtual void makeSound(const Cat& cat) const = 0;
 *     virtual std::string getStateName() const = 0;
 * };
 * 
 * class HappyCatState : public CatState {
 * public:
 *     void makeSound(const Cat& cat) const override {
 *         std::cout << "Purr purr! Happy meow!" << std::endl;
 *     }
 *     
 *     std::string getStateName() const override {
 *         return "Happy";
 *     }
 * };
 * 
 * class Cat : public Animal {
 * private:
 *     CatState* currentState;
 * 
 * public:
 *     Cat() : currentState(new HappyCatState()) {
 *         type = "Cat";
 *     }
 *     
 *     void makeSound() const override {
 *         currentState->makeSound(*this);
 *     }
 *     
 *     void setState(CatState* newState) {
 *         delete currentState;
 *         currentState = newState;
 *     }
 * };
 * ```
 * 
 * 【パターン3：Composite Pattern での群れ管理】
 * ```cpp
 * class AnimalGroup : public Animal {
 * private:
 *     std::vector<Animal*> animals;
 * 
 * public:
 *     void addAnimal(Animal* animal) {
 *         animals.push_back(animal);
 *     }
 *     
 *     void makeSound() const override {
 *         std::cout << "Group sound: ";
 *         for (const Animal* animal : animals) {
 *             animal->makeSound();
 *         }
 *     }
 *     
 *     std::string getType() const override {
 *         return "AnimalGroup";
 *     }
 * };
 * 
 * // 使用例
 * AnimalGroup catGroup;
 * catGroup.addAnimal(new Cat());
 * catGroup.addAnimal(new Cat());
 * catGroup.makeSound();  // 複数の猫の音が出力される
 * ```
 */