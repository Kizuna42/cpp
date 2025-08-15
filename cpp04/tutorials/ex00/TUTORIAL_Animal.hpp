/*
 * ====================================================================
 * CPP04 ex00: Animal - 仮想関数と多態性の基礎解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 仮想関数（Virtual Function）の概念と実装
 * - 多態性（Polymorphism）の実践的理解
 * - 動的バインディング（Dynamic Binding）の仕組み
 * - vtable（Virtual Function Table）の基本理解
 * - 継承階層でのインターフェース統一設計
 * 
 * 【重要概念】
 * - virtual キーワードによる動的バインディング
 * - 基底クラスポインタによる派生クラス操作
 * - 仮想関数のオーバーライドメカニズム
 * - 実行時型情報（RTTI）の基礎
 * - 多態性による柔軟な設計パターン
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

/*
 * ====================================================================
 * Animal基底クラス設計思想
 * ====================================================================
 * 
 * 【なぜAnimalクラスが必要なのか？】
 * 
 * 共通インターフェースの提供：
 * - 異なる動物（Dog, Cat等）の統一操作
 * - 基底クラスポインタでの一括管理
 * - 動物共通の属性・行動の抽象化
 * 
 * 多態性の実現基盤：
 * - 同じ操作で異なる結果を得る
 * - 実行時の動的な振る舞い決定
 * - 拡張可能な動物種類対応
 * 
 * 【ex00での学習内容】
 * 
 * 基本的な仮想関数：
 * - virtual makeSound() の実装
 * - 派生クラスでのオーバーライド
 * - 動的バインディングの確認
 * 
 * 対比学習のためのWrongAnimal：
 * - virtual なしの問題点確認
 * - 静的バインディングの限界
 * - 多態性が働かない場合の動作
 */
class Animal {
protected:
    /*
     * ====================================================================
     * 基底クラスメンバ変数
     * ====================================================================
     */
    
    /*
     * 【動物種類識別子】
     * std::string type;
     * 
     * protectedアクセス修飾子の選択理由：
     * - 派生クラスからの直接アクセス許可
     * - 外部からの直接変更防止
     * - 継承階層内での情報共有
     * 
     * 使用目的：
     * - 動物の種類表示（"Dog", "Cat"等）
     * - デバッグ時の識別支援
     * - getType()での値返却
     * - ログ出力での情報提供
     */
    std::string type;

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * Animal();
     * 
     * 基底クラスコンストラクタの役割：
     * - 共通属性の初期化
     * - 派生クラスからの呼び出し対応
     * - vtable構築の準備
     * 
     * 初期化内容：
     * - type = "Animal" （基底クラス識別）
     * - デバッグ出力による動作確認
     * - 継承チェーンの開始点
     */
    Animal();
    
    /*
     * 【コピーコンストラクタ】
     * Animal(const Animal& other);
     * 
     * 多態性でのコピーの複雑性：
     * - スライシング問題の可能性
     * - 基底クラス部分のコピー
     * - vtableの適切な設定
     * 
     * 実装での注意点：
     * - typeメンバの適切なコピー
     * - 派生クラスでの呼び出し対応
     * - オブジェクト独立性の確保
     */
    Animal(const Animal& other);
    
    /*
     * 【代入演算子】
     * Animal& operator=(const Animal& other);
     * 
     * 多態性での代入の注意点：
     * - スライシング問題の回避
     * - 基底クラス部分のみの代入
     * - vtableの保持（型情報は変更されない）
     * 
     * 実装パターン：
     * - 自己代入チェック
     * - メンバ変数の適切な代入
     * - *thisの返却
     */
    Animal& operator=(const Animal& other);
    
    /*
     * 【仮想デストラクタ】
     * virtual ~Animal();
     * 
     * virtualデストラクタの極めて重要な役割：
     * 
     * 多態性での安全な削除：
     * ```cpp
     * Animal* animal = new Dog("Buddy");
     * delete animal;  // Dog::~Dog() → Animal::~Animal() の順で実行
     * ```
     * 
     * virtualがない場合の危険性：
     * ```cpp
     * delete animal;  // Animal::~Animal() のみ実行
     * // Dogクラスのデストラクタが呼ばれない！
     * // メモリリークやリソースリークの原因
     * ```
     * 
     * 継承階層での必須要件：
     * - 基底クラスでvirtual指定必須
     * - 派生クラスで自動的にvirtualになる
     * - 正しいデストラクタチェーンの保証
     */
    virtual ~Animal();
    
    /*
     * ====================================================================
     * 仮想関数インターフェース
     * ====================================================================
     */
    
    /*
     * 【仮想関数：makeSound】
     * virtual void makeSound() const;
     * 
     * 仮想関数の核心概念：
     * 
     * virtual キーワードの効果：
     * - 動的バインディングの有効化
     * - 実行時の型による関数選択
     * - 派生クラスでのオーバーライド対象
     * 
     * 動的バインディングの動作：
     * ```cpp
     * Animal* animal = new Dog("Buddy");
     * animal->makeSound();  // Dog::makeSound() が呼ばれる
     * delete animal;
     * 
     * animal = new Cat("Kitty");
     * animal->makeSound();  // Cat::makeSound() が呼ばれる
     * delete animal;
     * ```
     * 
     * vtable（仮想関数テーブル）の役割：
     * - 各クラスごとの仮想関数ポインタテーブル
     * - 実行時の関数アドレス解決
     * - 多態性の実装基盤
     * 
     * const指定の意味：
     * - 音を出す行為はオブジェクトの状態を変更しない
     * - constオブジェクトからも呼び出し可能
     * - インターフェースの安全性確保
     * 
     * 基底クラスでの実装：
     * - デフォルト動作の提供
     * - 派生クラスでのオーバーライドは任意
     * - 共通動作と特殊化のバランス
     */
    virtual void makeSound() const;
    
    /*
     * ====================================================================
     * 非仮想関数（共通機能）
     * ====================================================================
     */
    
    /*
     * 【型情報取得関数】
     * std::string getType() const;
     * 
     * 非仮想関数の選択理由：
     * - 単純なメンバ変数の返却
     * - 派生クラスでの変更不要
     * - 実装の一貫性保持
     * 
     * const指定の理由：
     * - 読み取り専用操作
     * - オブジェクトの状態変更なし
     * - const correctnessの実践
     * 
     * 使用場面：
     * - デバッグ時の型確認
     * - ログ出力での識別
     * - 条件分岐での型判定（非推奨）
     * 
     * 注意：型判定での使用は多態性に反する
     * ```cpp
     * // 悪い例：型による分岐
     * if (animal->getType() == "Dog") {
     *     // 特別処理
     * }
     * 
     * // 良い例：仮想関数による多態性
     * animal->makeSound();  // 各型で適切な動作
     * ```
     */
    std::string getType() const;
};

#endif

/*
 * ====================================================================
 * 仮想関数の詳細メカニズム
 * ====================================================================
 * 
 * 【vtable（Virtual Function Table）の構造】
 * 
 * Animal クラスのvtable：
 * ```
 * Animal_vtable:
 * +------------------+
 * | destructor       | → Animal::~Animal()
 * | makeSound()      | → Animal::makeSound()
 * +------------------+
 * ```
 * 
 * Dog クラスのvtable（派生後）：
 * ```
 * Dog_vtable:
 * +------------------+
 * | destructor       | → Dog::~Dog()
 * | makeSound()      | → Dog::makeSound()  (オーバーライド)
 * +------------------+
 * ```
 * 
 * 【動的バインディングの実行プロセス】
 * 
 * 1. オブジェクト作成時：
 *    - vtableポインタがオブジェクトに設定
 *    - 実際の型に対応するvtableを指す
 * 
 * 2. 仮想関数呼び出し時：
 *    - vtableを参照して関数アドレス取得
 *    - 実行時の型に基づく関数実行
 *    - コンパイル時ではなく実行時決定
 * 
 * 【静的バインディングとの比較】
 * 
 * 静的バインディング（virtualなし）：
 * ```cpp
 * void makeSound() const;  // virtualなし
 * 
 * Animal* animal = new Dog("Buddy");
 * animal->makeSound();  // Animal::makeSound() が呼ばれる
 * ```
 * 
 * 動的バインディング（virtualあり）：
 * ```cpp
 * virtual void makeSound() const;  // virtualあり
 * 
 * Animal* animal = new Dog("Buddy");
 * animal->makeSound();  // Dog::makeSound() が呼ばれる
 * ```
 */

/*
 * ====================================================================
 * 多態性の実用的なパターン
 * ====================================================================
 * 
 * 【パターン1：動物コレクションの統一操作】
 * ```cpp
 * std::vector<Animal*> animals;
 * animals.push_back(new Dog("Buddy"));
 * animals.push_back(new Cat("Whiskers"));
 * animals.push_back(new Dog("Rex"));
 * 
 * // 統一されたインターフェースで操作
 * for (Animal* animal : animals) {
 *     animal->makeSound();  // 各動物の固有の音
 *     std::cout << animal->getType() << std::endl;
 * }
 * 
 * // 適切なクリーンアップ
 * for (Animal* animal : animals) {
 *     delete animal;  // 各派生クラスのデストラクタが呼ばれる
 * }
 * ```
 * 
 * 【パターン2：Factory Pattern】
 * ```cpp
 * class AnimalFactory {
 * public:
 *     static Animal* createAnimal(const std::string& type) {
 *         if (type == "Dog") return new Dog("DefaultDog");
 *         if (type == "Cat") return new Cat("DefaultCat");
 *         return nullptr;
 *     }
 * };
 * 
 * Animal* animal = AnimalFactory::createAnimal("Dog");
 * animal->makeSound();  // Dog::makeSound() が実行
 * delete animal;
 * ```
 * 
 * 【パターン3：Strategy Pattern】
 * ```cpp
 * class AnimalTrainer {
 * public:
 *     void trainAnimal(Animal& animal) {
 *         std::cout << "Training " << animal.getType() << std::endl;
 *         animal.makeSound();  // 動物固有の反応
 *         std::cout << "Good " << animal.getType() << "!" << std::endl;
 *     }
 * };
 * 
 * AnimalTrainer trainer;
 * Dog dog("Buddy");
 * Cat cat("Whiskers");
 * 
 * trainer.trainAnimal(dog);  // Dog用のトレーニング
 * trainer.trainAnimal(cat);  // Cat用のトレーニング
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ virtual キーワードの意味と効果
 * □ 動的バインディングと静的バインディングの違い
 * □ vtable（仮想関数テーブル）の基本概念
 * □ 仮想デストラクタの重要性と必要性
 * □ 多態性による統一インターフェース設計
 * □ 基底クラスポインタでの派生クラス操作
 * □ スライシング問題とその回避方法
 * □ const correctness の仮想関数での適用
 * □ Orthodox Canonical Form の継承版
 * □ 実用的な多態性パターンの理解
 * 
 * 【実習課題】
 * 1. 新しい動物クラス（Bird, Fish等）の追加
 * 2. 追加の仮想関数（eat, sleep等）の実装
 * 3. 純粋仮想関数による抽象基底クラス化
 * 4. 複雑な継承階層での多態性テスト
 * 5. パフォーマンス測定（仮想関数vs通常関数）
 */

/*
 * ====================================================================
 * よくある仮想関数のミスと対策
 * ====================================================================
 * 
 * 【ミス1：仮想デストラクタの忘れ】
 * 
 * 間違い例：
 * ```cpp
 * class Animal {
 * public:
 *     ~Animal() {}  // virtualがない！
 *     virtual void makeSound() const;
 * };
 * ```
 * 
 * 問題：
 * - 基底クラスポインタ経由での削除で問題発生
 * - 派生クラスのデストラクタが呼ばれない
 * - リソースリークの原因
 * 
 * 正解：
 * ```cpp
 * virtual ~Animal() {}
 * ```
 * 
 * 【ミス2：const correctnessの不一致】
 * 
 * 間違い例：
 * ```cpp
 * class Animal {
 * public:
 *     virtual void makeSound() const;
 * };
 * 
 * class Dog : public Animal {
 * public:
 *     void makeSound() override;  // constがない
 * };
 * ```
 * 
 * 問題：
 * - シグネチャが一致しないためオーバーライドにならない
 * - 意図しない関数隠蔽が発生
 * - 多態性が正しく働かない
 * 
 * 正解：
 * ```cpp
 * void makeSound() const override;
 * ```
 * 
 * 【ミス3：スライシング問題の理解不足】
 * 
 * 問題のあるコード：
 * ```cpp
 * Dog dog("Buddy");
 * Animal animal = dog;  // スライシング発生
 * animal.makeSound();   // Animal::makeSound() が呼ばれる
 * ```
 * 
 * 改善案：
 * ```cpp
 * Dog dog("Buddy");
 * Animal& animal = dog;     // 参照使用
 * animal.makeSound();       // Dog::makeSound() が呼ばれる
 * 
 * // または
 * Animal* animal = &dog;    // ポインタ使用
 * animal->makeSound();      // Dog::makeSound() が呼ばれる
 * ```
 * 
 * 【ミス4：vtableのコストを考慮しない設計】
 * 
 * 注意点：
 * - 仮想関数は通常の関数よりわずかに遅い
 * - vtableポインタによるメモリオーバーヘッド
 * - 必要な場合のみ仮想関数を使用
 * 
 * 最適化考慮：
 * - パフォーマンス重視なら非仮想関数
 * - 設計柔軟性重視なら仮想関数
 * - プロファイリングによる実測が重要
 */

/*
 * ====================================================================
 * 発展的な仮想関数パターン
 * ====================================================================
 * 
 * 【パターン1：Template Method Pattern】
 * ```cpp
 * class Animal {
 * public:
 *     void dailyRoutine() const {  // Template Method
 *         wakeUp();        // 共通処理
 *         makeSound();     // 仮想関数（サブクラス実装）
 *         eat();           // 仮想関数
 *         play();          // 仮想関数
 *         sleep();         // 共通処理
 *     }
 * 
 * protected:
 *     virtual void makeSound() const = 0;
 *     virtual void eat() const = 0;
 *     virtual void play() const = 0;
 *     
 * private:
 *     void wakeUp() const { std::cout << "Waking up..." << std::endl; }
 *     void sleep() const { std::cout << "Going to sleep..." << std::endl; }
 * };
 * ```
 * 
 * 【パターン2：Visitor Pattern】
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
 *     virtual ~Animal() {}
 *     virtual void accept(AnimalVisitor& visitor) const = 0;
 * };
 * 
 * class Dog : public Animal {
 * public:
 *     void accept(AnimalVisitor& visitor) const override {
 *         visitor.visitDog(*this);
 *     }
 * };
 * ```
 * 
 * 【パターン3：Observer Pattern】
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
 * public:
 *     void addObserver(AnimalObserver* observer) {
 *         observers.push_back(observer);
 *     }
 *     
 *     virtual void makeSound() const {
 *         // 音を出す
 *         notifyObservers();
 *     }
 * 
 * private:
 *     void notifyObservers() const {
 *         for (AnimalObserver* observer : observers) {
 *             observer->onAnimalSound(*this);
 *         }
 *     }
 * };
 * ```
 */