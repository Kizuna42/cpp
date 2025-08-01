/*
 * ====================================================================
 * CPP04 ex00: ポリモーフィズムの基礎 - Animal基底クラス解説版
 * ====================================================================
 * 
 * この演習では、C++ポリモーフィズムの基本概念を学習します。
 * 
 * 【学習目標】
 * - 仮想関数（virtual function）の仕組み
 * - 動的束縛（dynamic binding）の理解
 * - 仮想デストラクタの重要性
 * - protected メンバの適切な使用
 * - ポリモーフィズムによる設計の利点
 * 
 * Animal クラスは Dog, Cat の基底クラスとして、
 * ポリモーフィズムの基盤を提供します。
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

/*
 * ====================================================================
 * Animal クラス - ポリモーフィズムの基盤
 * ====================================================================
 * 
 * 【ポリモーフィズムとは？】
 * 
 * "多態性" - 同じインターフェースで異なる実装を実現
 * 
 * 実用例:
 * Animal* animals[] = {new Dog(), new Cat()};
 * for (Animal* animal : animals) {
 *     animal->makeSound();  // Dog は "Woof!", Cat は "Meow!"
 * }
 * 
 * 【なぜ重要なのか？】
 * 
 * 1. コードの再利用性
 *    - 基底クラスのインターフェースで統一処理
 *    - 新しい派生クラスを追加しても既存コードは変更不要
 * 
 * 2. 拡張性
 *    - Open/Closed Principle の実現
 *    - 拡張に開き、修正に閉じる
 * 
 * 3. 抽象化
 *    - 具体的な実装の詳細を隠蔽
 *    - より高レベルでの設計思考
 */
class Animal {
protected:
    /*
     * std::string type;
     * 
     * 【protected の選択理由】
     * 
     * private vs protected の比較:
     * 
     * private:
     * - 外部からも派生クラスからもアクセス不可
     * - 最も厳格な情報隠蔽
     * - getter/setter が必要
     * 
     * protected:
     * - 派生クラスからアクセス可能
     * - 外部からはアクセス不可
     * - 継承階層内での共有
     * 
     * 【なぜ protected を選択？】
     * 
     * 派生クラスでの利用頻度:
     * Dog, Cat のコンストラクタで type を設定
     * 頻繁なアクセスで getter のオーバーヘッドを回避
     * 
     * 使用例:
     * class Dog : public Animal {
     * public:
     *     Dog() {
     *         type = "Dog";  // protected なので直接アクセス可能
     *     }
     * };
     * 
     * 【type の役割】
     * 
     * - 動物の種類を識別
     * - getType() での外部向け情報提供
     * - ログメッセージでの表示
     * - デバッグ時の型確認
     */
    std::string type;

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form - ポリモーフィック版
     * ====================================================================
     * 
     * ポリモーフィズムを使用するクラスでは
     * OCF の実装により慎重な配慮が必要
     */
    
    /*
     * Animal(void);
     * 
     * デフォルトコンストラクタ
     * 
     * 【基底クラスでの初期化】
     * 
     * type = "Animal" で初期化
     * 派生クラスで適切な値に変更される前提
     * 
     * 【派生クラスからの呼び出し】
     * 
     * class Dog : public Animal {
     * public:
     *     Dog() {  // 暗黙的に Animal() が先に呼ばれる
     *         type = "Dog";  // その後で型を設定
     *     }
     * };
     * 
     * 実行順序:
     * 1. Animal のコンストラクタ (type = "Animal")
     * 2. Dog のコンストラクタ (type = "Dog")
     */
    Animal(void);
    
    /*
     * Animal(const std::string& type);
     * 
     * 型指定コンストラクタ
     * 
     * 【派生クラスでの利用】
     * 
     * class Cat : public Animal {
     * public:
     *     Cat() : Animal("Cat") {  // 基底クラスを明示的に初期化
     *         // より効率的な初期化方法
     *     }
     * };
     * 
     * 利点:
     * - 一度の初期化で完了
     * - 無駄な代入処理なし
     * - より明示的な意図表現
     */
    Animal(const std::string& type);
    
    /*
     * Animal(const Animal& other);
     * Animal& operator=(const Animal& other);
     * 
     * コピーコンストラクタと代入演算子
     * 
     * 【ポリモーフィズムでのコピー問題】
     * 
     * スライシング問題:
     * Dog dog;
     * Animal animal = dog;  // Dog の固有情報が失われる
     * 
     * 対策:
     * 1. 適切なコピー実装
     * 2. クローンパターンの使用
     * 3. スマートポインタの活用
     * 
     * 基底クラスでは基本的なコピーを実装
     * 派生クラスで適切にオーバーライド
     */
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    
    /*
     * virtual ~Animal(void);
     * 
     * 仮想デストラクタ - ポリモーフィズムの必須要素
     * 
     * 【なぜ virtual が必要？】
     * 
     * ポリモーフィックな削除の例:
     * Animal* animal = new Dog();
     * delete animal;  // どのデストラクタが呼ばれる？
     * 
     * 非仮想デストラクタの場合:
     * Animal のデストラクタのみ実行
     * → Dog の固有リソースがリークする可能性
     * 
     * 仮想デストラクタの場合:
     * 実際のオブジェクト型（Dog）のデストラクタが実行
     * → 適切なクリーンアップが保証される
     * 
     * 【実行順序】
     * 
     * delete animal; の場合:
     * 1. Dog のデストラクタ実行
     * 2. Animal のデストラクタ実行（自動）
     * 
     * 派生 → 基底の順序で実行される
     * 
     * 【パフォーマンス考慮】
     * 
     * 仮想関数テーブル（vtable）によるわずかなオーバーヘッド
     * しかしポリモーフィズム使用時は必須
     * 
     * 【設計原則】
     * 「基底クラスのデストラクタは常に virtual にする」
     * ポリモーフィズムを使用する場合の鉄則
     */
    virtual ~Animal(void);  // Virtual destructor for proper polymorphism
    
    /*
     * ====================================================================
     * 仮想関数 - ポリモーフィズムの核心
     * ====================================================================
     */
    
    /*
     * virtual void makeSound(void) const;
     * 
     * 【仮想関数の仕組み】
     * 
     * virtual キーワードにより：
     * 1. 仮想関数テーブル（vtable）にエントリ作成
     * 2. 実行時に実際のオブジェクト型を判定
     * 3. 適切な派生クラスのメソッドを呼び出し
     * 
     * 【動的束縛の実現】
     * 
     * Animal* animal = new Dog();
     * animal->makeSound();  // Dog::makeSound() が呼ばれる
     * 
     * コンパイル時: Animal::makeSound のアドレス不明
     * 実行時: Dog::makeSound のアドレスを vtable から取得
     * 
     * 【基底クラスでの実装】
     * 
     * 選択肢:
     * 1. デフォルト実装を提供
     * 2. 純粋仮想関数にする (= 0)
     * 
     * 現在の設計: デフォルト実装
     * Animal 自体もインスタンス化可能
     * 汎用的な動物の鳴き声を実装
     * 
     * 【const 修飾の意味】
     * 
     * const メソッド:
     * - オブジェクトの状態を変更しない
     * - const Animal からも呼び出し可能
     * - 「鳴く」行為は状態変更を伴わない
     * 
     * 【派生クラスでのオーバーライド】
     * 
     * class Dog : public Animal {
     * public:
     *     void makeSound(void) const override {  // C++11 の override
     *         std::cout << "Woof!" << std::endl;
     *     }
     * };
     * 
     * override キーワード（C++11）:
     * - 仮想関数のオーバーライドを明示
     * - タイポ等のエラーを検出
     * - より安全なオーバーライド
     */
    virtual void makeSound(void) const;  // Virtual function for polymorphism
    
    /*
     * std::string getType(void) const;
     * 
     * 【非仮想関数の設計判断】
     * 
     * なぜ virtual ではない？
     * - type の取得は全クラス共通の動作
     * - オーバーライドする必要がない
     * - 仮想関数のオーバーヘッドを回避
     * 
     * 【戻り値設計】
     * 
     * std::string (値返し):
     * - 安全（外部からの変更不可）
     * - protected メンバへの間接アクセス
     * - コピーコストは許容範囲
     * 
     * 【使用場面】
     * - オブジェクトの型確認
     * - ログメッセージでの表示
     * - デバッグ情報の提供
     * - 型ベースの処理分岐
     */
    std::string getType(void) const;
};

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このクラスから学ぶべきこと】
 * 
 * 1. ポリモーフィズムの基盤設計
 *    - 仮想関数の適切な使用
 *    - 仮想デストラクタの必要性
 *    - protected メンバの戦略的活用
 * 
 * 2. 動的束縛の理解
 *    - vtable による実行時解決
 *    - コンパイル時 vs 実行時の違い
 *    - パフォーマンスとの トレードオフ
 * 
 * 3. 継承階層の設計
 *    - 基底クラスの責任範囲
 *    - 派生クラスとの協調
 *    - 拡張可能な構造
 * 
 * 4. const correctness
 *    - const メソッドの適切な使用
 *    - オブジェクトの不変性保証
 *    - インターフェースの明確化
 * 
 * 【実用スキル】
 * - ポリモーフィズムを使った設計ができる
 * - 仮想関数の動作を正確に理解している
 * - 適切な基底クラスを設計できる
 * - メモリ安全なポリモーフィックコードが書ける
 */

#endif

/*
 * ====================================================================
 * ポリモーフィズムの実用例
 * ====================================================================
 * 
 * 【ゲーム開発での応用】
 * 
 * class GameObject {
 * protected:
 *     Vector2 position;
 *     float health;
 * 
 * public:
 *     virtual ~GameObject() = default;
 *     virtual void update(float deltaTime) = 0;
 *     virtual void render(Renderer& renderer) = 0;
 *     virtual void onCollision(GameObject& other) {}
 * };
 * 
 * class Player : public GameObject {
 * public:
 *     void update(float deltaTime) override {
 *         // プレイヤー固有の更新処理
 *     }
 * };
 * 
 * class Enemy : public GameObject {
 * public:
 *     void update(float deltaTime) override {
 *         // 敵キャラ固有の更新処理
 *     }
 * };
 * 
 * // 統一処理
 * std::vector<std::unique_ptr<GameObject>> gameObjects;
 * for (auto& obj : gameObjects) {
 *     obj->update(deltaTime);  // それぞれの実装が呼ばれる
 * }
 * 
 * 【GUI システムでの応用】
 * 
 * class Widget {
 * public:
 *     virtual ~Widget() = default;
 *     virtual void draw(Canvas& canvas) = 0;
 *     virtual void handleEvent(Event& event) {}
 *     virtual Size getPreferredSize() const = 0;
 * };
 * 
 * class Button : public Widget {
 * public:
 *     void draw(Canvas& canvas) override {
 *         // ボタンの描画処理
 *     }
 * };
 * 
 * class TextBox : public Widget {
 * public:
 *     void draw(Canvas& canvas) override {
 *         // テキストボックスの描画処理
 *     }
 * };
 * 
 * 【データ処理での応用】
 * 
 * class DataProcessor {
 * public:
 *     virtual ~DataProcessor() = default;
 *     virtual void process(const Data& input, Data& output) = 0;
 *     virtual std::string getProcessorName() const = 0;
 * };
 * 
 * class ImageProcessor : public DataProcessor {
 * public:
 *     void process(const Data& input, Data& output) override {
 *         // 画像処理
 *     }
 * };
 * 
 * class AudioProcessor : public DataProcessor {
 * public:
 *     void process(const Data& input, Data& output) override {
 *         // 音声処理
 *     }
 * };
 * 
 * これらの例では、基底クラスのインターフェースで
 * 統一的な処理を実現しつつ、各派生クラスが
 * 固有の実装を提供している
 */

/*
 * ====================================================================
 * よくある間違いと解決法
 * ====================================================================
 * 
 * 【間違い1: 仮想デストラクタの忘れ】
 * 
 * ❌ 危険なコード:
 * class Animal {
 * public:
 *     ~Animal() {}  // virtual なし
 * };
 * 
 * Animal* animal = new Dog();
 * delete animal;  // Dog のデストラクタが呼ばれない！
 * 
 * ✅ 正しいコード:
 * class Animal {
 * public:
 *     virtual ~Animal() {}
 * };
 * 
 * 【間違い2: スライシング問題】
 * 
 * ❌ 問題のあるコード:
 * Dog dog;
 * Animal animal = dog;  // スライシング発生
 * animal.makeSound();   // Animal::makeSound が呼ばれる
 * 
 * ✅ 適切なコード:
 * Dog dog;
 * Animal* animal = &dog;  // ポインタまたは参照を使用
 * animal->makeSound();    // Dog::makeSound が呼ばれる
 * 
 * 【間違い3: 仮想関数の誤解】
 * 
 * ❌ 間違った理解:
 * "virtual を付けるとメソッドが遅くなる"
 * 
 * ✅ 正しい理解:
 * - わずかなオーバーヘッドはある（通常1回の間接参照）
 * - ポリモーフィズムの利益がコストを上回る
 * - 現代CPUでは影響は最小限
 * 
 * 【間違い4: protected の乱用】
 * 
 * ❌ 良くない設計:
 * class Animal {
 * protected:
 *     int secretData;  // 本当に派生クラスで必要？
 * };
 * 
 * ✅ 良い設計:
 * 派生クラスで本当に必要なもののみ protected にする
 * 可能なら private + protected getter/setter
 */

/*
 * ====================================================================
 * 発展的なトピック
 * ====================================================================
 * 
 * 【純粋仮想関数（抽象クラス）】
 * 
 * class AbstractAnimal {
 * public:
 *     virtual ~AbstractAnimal() = default;
 *     virtual void makeSound() const = 0;  // 純粋仮想関数
 *     virtual void move() const = 0;
 * };
 * 
 * // AbstractAnimal animal;  // エラー：インスタンス化不可
 * 
 * 【多重継承での仮想継承】
 * 
 * class Animal { virtual void makeSound() = 0; };
 * class Mammal : virtual public Animal {};
 * class Bird : virtual public Animal {};
 * class Bat : public Mammal, public Bird {};  // ダイヤモンド問題解決
 * 
 * 【現代C++での改善】
 * 
 * C++11以降:
 * - override キーワード
 * - final キーワード
 * - default/delete
 * - スマートポインタ
 * 
 * class Animal {
 * public:
 *     virtual ~Animal() = default;
 *     virtual void makeSound() const = 0;
 * };
 * 
 * class Dog final : public Animal {  // final: 継承禁止
 * public:
 *     void makeSound() const override {  // override: 明示的
 *         std::cout << "Woof!" << std::endl;
 *     }
 * };
 * 
 * これらの発展的な機能は、基本的なポリモーフィズムを
 * 完全理解してから学習することを推奨
 */