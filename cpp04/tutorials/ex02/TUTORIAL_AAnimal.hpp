/*
 * ====================================================================
 * CPP04 ex02: AAnimal - 抽象基底クラス（Abstract Base Class）解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 抽象基底クラス（ABC: Abstract Base Class）の設計と実装
 * - 純粋仮想関数（Pure Virtual Function）の理解と使用
 * - インターフェース設計による強制的な実装保証
 * - 抽象化による設計の柔軟性と型安全性の確保
 * - 多態性の高度な活用パターン
 * 
 * 【重要概念】
 * - 純粋仮想関数 = 0 による抽象化
 * - インスタンス化不可能なクラスの意義
 * - 派生クラスでの強制実装メカニズム
 * - インターフェース継承 vs 実装継承
 * - 抽象基底クラスの設計パターン
 */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>
#include <iostream>

/*
 * ====================================================================
 * 抽象基底クラス設計の理念
 * ====================================================================
 * 
 * 【なぜAnimalからAAnimalに変更するのか？】
 * 
 * ex00/ex01のAnimalクラスの問題点：
 * - makeSound()が空の実装または意味のない実装
 * - Animalクラス自体をインスタンス化できてしまう
 * - "動物"という抽象概念を具象クラスとして扱う矛盾
 * - 派生クラスでの実装忘れをコンパイル時に検出できない
 * 
 * AAnimalクラスによる改善：
 * - 純粋仮想関数により抽象化を強制
 * - インスタンス化を不可能にして概念的整合性を確保
 * - 派生クラスでの実装を強制してバグを防止
 * - より明確なインターフェース設計の実現
 * 
 * 【抽象基底クラスの設計原則】
 * 
 * 1. 概念的抽象化
 *    - 具体的なオブジェクトではなく概念を表現
 *    - "動物"は抽象概念、"犬"や"猫"は具体的存在
 * 
 * 2. インターフェース強制
 *    - 派生クラスで必ず実装すべき機能を定義
 *    - コンパイル時での実装忘れ検出
 * 
 * 3. 多態性の基盤
 *    - ポインタ・参照による統一的操作
 *    - 実行時の動的バインディング活用
 * 
 * 4. 拡張性の確保
 *    - 新しい動物の追加が容易
 *    - 既存コードの変更なしに機能拡張
 */
class AAnimal {
protected:
    /*
     * ====================================================================
     * protected メンバ変数
     * ====================================================================
     */
    
    /*
     * 【動物の種類識別子】
     * std::string type;
     * 
     * protectedアクセス修飾子の選択理由：
     * - 派生クラスからの直接アクセスを許可
     * - 外部からの不正な変更を防止
     * - 継承階層内での情報共有
     * 
     * 使用目的：
     * - 動物の種類（"Dog", "Cat", etc.）を保存
     * - デバッグ・ログ出力での識別
     * - getType()関数での値返却
     * - 派生クラスでの初期化制御
     */
    std::string type;

public:
    /*
     * ====================================================================
     * コンストラクタ・デストラクタ
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * AAnimal();
     * 
     * 抽象基底クラスでのコンストラクタの意義：
     * 
     * 直接インスタンス化は不可：
     * - AAnimal animal; // コンパイルエラー
     * - 純粋仮想関数があるため
     * 
     * 派生クラスからの呼び出しは可能：
     * - Dog dog; // OK - Dogコンストラクタ内でAAnimalコンストラクタ呼び出し
     * - 基底クラス部分の初期化を担当
     * 
     * 実装での考慮点：
     * - 共通の初期化処理を記述
     * - typeの初期値設定
     * - デバッグ情報の出力
     */
    AAnimal();
    
    /*
     * 【コピーコンストラクタ】
     * AAnimal(const AAnimal& other);
     * 
     * 抽象基底クラスでのコピーコンストラクタ：
     * 
     * 必要性：
     * - 派生クラスのコピー時に基底部分をコピー
     * - スライシング問題の回避支援
     * - Orthodox Canonical Formの完全性
     * 
     * 実装での注意点：
     * - typeメンバの適切なコピー
     * - 仮想関数テーブル（vtable）の考慮
     * - 派生クラスでの呼び出し保証
     */
    AAnimal(const AAnimal& other);
    
    /*
     * 【代入演算子】
     * AAnimal& operator=(const AAnimal& other);
     * 
     * 抽象基底クラスでの代入演算子：
     * 
     * 実装の必要性：
     * - 派生クラスでの代入時の基底部分処理
     * - 自己代入チェックの共通処理
     * - 基底クラス部分の状態管理
     * 
     * スライシング問題：
     * ```cpp
     * Dog dog("Buddy");
     * Cat cat("Kitty");
     * AAnimal& animal1 = dog;
     * AAnimal& animal2 = cat;
     * animal1 = animal2;  // 基底部分のみ代入
     * ```
     */
    AAnimal& operator=(const AAnimal& other);
    
    /*
     * 【仮想デストラクタ】
     * virtual ~AAnimal();
     * 
     * virtualの重要性：
     * 
     * 多態性での正しい削除：
     * ```cpp
     * AAnimal* animal = new Dog("Buddy");
     * delete animal;  // Dog::~Dog() → AAnimal::~AAnimal() の順で呼ばれる
     * ```
     * 
     * virtualがない場合の問題：
     * - 基底クラスのデストラクタのみ呼ばれる
     * - 派生クラスのリソースが解放されない
     * - メモリリークやリソースリークの原因
     * 
     * 抽象基底クラスでの追加意義：
     * - 多態性使用の前提条件
     * - 派生クラスでのvirtualデストラクタ強制
     * - RAII原則の継承階層での適用
     */
    virtual ~AAnimal();
    
    /*
     * ====================================================================
     * 純粋仮想関数（Pure Virtual Functions）
     * ====================================================================
     */
    
    /*
     * 【純粋仮想関数：makeSound】
     * virtual void makeSound() const = 0;
     * 
     * 純粋仮想関数の構文解説：
     * - virtual: 仮想関数指定子
     * - void makeSound() const: 関数シグネチャ
     * - = 0: 純粋仮想指定子（pure specifier）
     * 
     * = 0 の意味：
     * - この関数は基底クラスで実装を持たない
     * - 派生クラスで必ず実装（オーバーライド）が必要
     * - クラスを抽象化する（インスタンス化不可）
     * 
     * const 指定の理由：
     * - 音を出す行為はオブジェクトの状態を変更しない
     * - constオブジェクトからも呼び出し可能
     * - 読み取り専用メソッドとしての明確化
     * 
     * 派生クラスでの実装要求：
     * ```cpp
     * class Dog : public AAnimal {
     * public:
     *     void makeSound() const override {  // 必須実装
     *         std::cout << "Woof!" << std::endl;
     *     }
     * };
     * ```
     * 
     * 実装しない場合のエラー：
     * ```cpp
     * class BrokenDog : public AAnimal {
     *     // makeSound()を実装しない
     * };
     * BrokenDog dog;  // コンパイルエラー！
     * ```
     */
    virtual void makeSound() const = 0;
    
    /*
     * ====================================================================
     * 通常の仮想関数（実装あり）
     * ====================================================================
     */
    
    /*
     * 【getType関数】
     * virtual std::string getType() const;
     * 
     * 純粋仮想関数でない理由：
     * - 共通の実装が可能（typeメンバの返却）
     * - 派生クラスでオーバーライドは任意
     * - デフォルト動作を提供しつつ拡張可能性を保持
     * 
     * virtual指定の理由：
     * - 派生クラスでの特殊化を許可
     * - 多態性での正しい関数呼び出し
     * - 将来の拡張可能性確保
     * 
     * const指定の理由：
     * - 読み取り専用操作
     * - オブジェクトの状態変更なし
     * - constオブジェクトからの呼び出し対応
     * 
     * 使用例：
     * ```cpp
     * AAnimal* animal = new Dog("Buddy");
     * std::cout << animal->getType() << std::endl;  // "Dog"
     * delete animal;
     * ```
     */
    virtual std::string getType() const;
};

#endif

/*
 * ====================================================================
 * 抽象基底クラスの理論と実践
 * ====================================================================
 * 
 * 【抽象化レベルの階層】
 * 
 * レベル1: 具象クラス（Concrete Class）
 * - すべてのメソッドが実装されている
 * - インスタンス化可能
 * - 例: Dog, Cat（ex00/ex01）
 * 
 * レベル2: 抽象基底クラス（Abstract Base Class）
 * - 1つ以上の純粋仮想関数を持つ
 * - インスタンス化不可能
 * - インターフェースの定義が主目的
 * - 例: AAnimal（ex02）
 * 
 * レベル3: 純粋インターフェース（Pure Interface）
 * - すべてのメソッドが純粋仮想関数
 * - 実装を一切持たない
 * - Java的なインターフェース概念に近い
 * 
 * 【C++98でのインターフェース設計パターン】
 * 
 * パターン1: 抽象基底クラス（現在の設計）
 * ```cpp
 * class AAnimal {
 * public:
 *     virtual ~AAnimal() {}
 *     virtual void makeSound() const = 0;  // 純粋仮想
 *     virtual std::string getType() const { return type; }  // 実装あり
 * protected:
 *     std::string type;
 * };
 * ```
 * 
 * パターン2: 純粋インターフェース
 * ```cpp
 * class IAnimal {
 * public:
 *     virtual ~IAnimal() {}
 *     virtual void makeSound() const = 0;
 *     virtual std::string getType() const = 0;
 *     virtual void eat() const = 0;
 *     virtual void sleep() const = 0;
 * };
 * ```
 * 
 * パターン3: ミックスイン（Mixin）
 * ```cpp
 * template<typename Derived>
 * class AnimalBase {
 * public:
 *     void makeSound() const {
 *         static_cast<const Derived*>(this)->makeSound();
 *     }
 * };
 * 
 * class Dog : public AnimalBase<Dog> {
 * public:
 *     void makeSound() const { std::cout << "Woof!" << std::endl; }
 * };
 * ```
 */

/*
 * ====================================================================
 * 設計パターンとの関連
 * ====================================================================
 * 
 * 【Template Method パターン】
 * ```cpp
 * class AAnimal {
 * public:
 *     void dailyRoutine() const {  // Template Method
 *         wakeUp();      // 共通実装
 *         makeSound();   // 派生クラス実装
 *         eat();         // 共通実装
 *         sleep();       // 共通実装
 *     }
 * 
 * protected:
 *     virtual void makeSound() const = 0;  // Hook Method
 *     void wakeUp() const { std::cout << "Waking up..." << std::endl; }
 *     void eat() const { std::cout << "Eating..." << std::endl; }
 *     void sleep() const { std::cout << "Sleeping..." << std::endl; }
 * };
 * ```
 * 
 * 【Strategy パターン】
 * ```cpp
 * class SoundStrategy {
 * public:
 *     virtual ~SoundStrategy() {}
 *     virtual void makeSound() const = 0;
 * };
 * 
 * class AAnimal {
 * private:
 *     SoundStrategy* soundStrategy;
 * 
 * public:
 *     AAnimal(SoundStrategy* strategy) : soundStrategy(strategy) {}
 *     void makeSound() const { soundStrategy->makeSound(); }
 * };
 * ```
 * 
 * 【Factory Method パターン】
 * ```cpp
 * class AnimalFactory {
 * public:
 *     virtual ~AnimalFactory() {}
 *     virtual AAnimal* createAnimal() const = 0;
 * };
 * 
 * class DogFactory : public AnimalFactory {
 * public:
 *     AAnimal* createAnimal() const override {
 *         return new Dog();
 *     }
 * };
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ 純粋仮想関数（= 0）の構文と意味
 * □ 抽象基底クラスの設計思想
 * □ インスタンス化不可能性の理解
 * □ 派生クラスでの強制実装メカニズム
 * □ 仮想デストラクタの重要性
 * □ protectedアクセス修飾子の活用
 * □ インターフェース設計の基本原則
 * □ Orthodox Canonical Formの抽象クラス版
 * □ 多態性とvtableの関係
 * □ const correctnessの継承での適用
 * 
 * 【実習課題】
 * 1. 新しい純粋仮想関数の追加（eat, sleep等）
 * 2. 純粋インターフェースクラスの設計
 * 3. Template Methodパターンの実装
 * 4. 複数の抽象基底クラスからの多重継承
 * 5. ファクトリーパターンとの組み合わせ
 */

/*
 * ====================================================================
 * よくある抽象クラス設計のミスと対策
 * ====================================================================
 * 
 * 【ミス1：デストラクタのvirtual忘れ】
 * 
 * 間違い例：
 * ```cpp
 * class AAnimal {
 * public:
 *     ~AAnimal() {}  // virtualがない！
 *     virtual void makeSound() const = 0;
 * };
 * ```
 * 
 * 問題：
 * - 多態性での削除時に派生クラスのデストラクタが呼ばれない
 * - メモリリークやリソースリーク
 * 
 * 正解：
 * ```cpp
 * virtual ~AAnimal() {}
 * ```
 * 
 * 【ミス2：純粋仮想関数の実装提供】
 * 
 * 混乱例：
 * ```cpp
 * class AAnimal {
 * public:
 *     virtual void makeSound() const = 0 {  // エラー！
 *         std::cout << "Some sound" << std::endl;
 *     }
 * };
 * ```
 * 
 * 正しい理解：
 * - = 0 は実装がないことを意味
 * - 実装を提供したい場合は通常の仮想関数にする
 * 
 * 【ミス3：protected継承の誤用】
 * 
 * 間違い例：
 * ```cpp
 * class Dog : protected AAnimal {  // protectedは通常適切でない
 * public:
 *     void makeSound() const override { /* ... */ }
 * };
 * ```
 * 
 * 問題：
 * - is-a関係が成立しない
 * - 多態性が使用できない
 * 
 * 通常の正解：
 * ```cpp
 * class Dog : public AAnimal {
 * ```
 * 
 * 【ミス4：const correctnessの不一致】
 * 
 * 間違い例：
 * ```cpp
 * class AAnimal {
 * public:
 *     virtual void makeSound() const = 0;
 * };
 * 
 * class Dog : public AAnimal {
 * public:
 *     void makeSound() override {  // constがない！
 *         std::cout << "Woof!" << std::endl;
 *     }
 * };
 * ```
 * 
 * 問題：
 * - シグネチャが一致しないためオーバーライドにならない
 * - コンパイルエラーまたは意図しない関数隠蔽
 * 
 * 正解：
 * ```cpp
 * void makeSound() const override {
 * ```
 */

/*
 * ====================================================================
 * 発展的な抽象クラス設計
 * ====================================================================
 * 
 * 【設計1: 階層的抽象化】
 * ```cpp
 * class AAnimal {
 * public:
 *     virtual ~AAnimal() {}
 *     virtual void makeSound() const = 0;
 *     virtual void move() const = 0;
 * };
 * 
 * class AMammal : public AAnimal {
 * public:
 *     void breathe() const { std::cout << "Breathing air" << std::endl; }
 *     virtual void giveMilk() const = 0;  // 哺乳類特有の純粋仮想関数
 * };
 * 
 * class Dog : public AMammal {
 * public:
 *     void makeSound() const override { std::cout << "Woof!" << std::endl; }
 *     void move() const override { std::cout << "Running" << std::endl; }
 *     void giveMilk() const override { std::cout << "Nursing puppies" << std::endl; }
 * };
 * ```
 * 
 * 【設計2: 複数インターフェースの実装】
 * ```cpp
 * class IMovable {
 * public:
 *     virtual ~IMovable() {}
 *     virtual void move() const = 0;
 * };
 * 
 * class ISoundMaker {
 * public:
 *     virtual ~ISoundMaker() {}
 *     virtual void makeSound() const = 0;
 * };
 * 
 * class Dog : public AAnimal, public IMovable, public ISoundMaker {
 * public:
 *     void makeSound() const override { std::cout << "Woof!" << std::endl; }
 *     void move() const override { std::cout << "Running" << std::endl; }
 * };
 * ```
 * 
 * 【設計3: CRTP（Curiously Recurring Template Pattern）】
 * ```cpp
 * template<typename Derived>
 * class AnimalCRTP {
 * public:
 *     void makeSound() const {
 *         static_cast<const Derived*>(this)->makeSoundImpl();
 *     }
 * 
 * protected:
 *     ~AnimalCRTP() = default;  // protected destructor
 * };
 * 
 * class Dog : public AnimalCRTP<Dog> {
 * public:
 *     void makeSoundImpl() const {
 *         std::cout << "Woof!" << std::endl;
 *     }
 * };
 * ```
 * 
 * 【設計4: Policy-based Design】
 * ```cpp
 * template<typename SoundPolicy, typename MovementPolicy>
 * class Animal : public SoundPolicy, public MovementPolicy {
 * public:
 *     void performActions() const {
 *         SoundPolicy::makeSound();
 *         MovementPolicy::move();
 *     }
 * };
 * 
 * class BarkingPolicy {
 * public:
 *     void makeSound() const { std::cout << "Woof!" << std::endl; }
 * };
 * 
 * class RunningPolicy {
 * public:
 *     void move() const { std::cout << "Running" << std::endl; }
 * };
 * 
 * using Dog = Animal<BarkingPolicy, RunningPolicy>;
 * ```
 */