/*
 * ====================================================================
 * CPP04 ex00: WrongCat - 非仮想継承による問題実証版
 * ====================================================================
 * 
 * 【学習目標】
 * - 非仮想基底クラスからの継承での問題体験
 * - 多態性が期待通りに働かない具体例理解
 * - static bindingによる実行時の予期しない動作確認
 * - 正しい設計（Cat）との直接比較による学習
 * - virtualの重要性を実体験による理解
 * 
 * 【重要概念】
 * - 関数隠蔽（Function Hiding）の実際の問題
 * - 基底クラス設計ミスの派生クラスへの影響
 * - コンパイル時の正常とランタイムの異常の乖離
 * - 設計修正の困難さと初期設計の重要性
 * - デバッグが困難になる原因の理解
 */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"
#include <iostream>

/*
 * ====================================================================
 * WrongCat クラス設計思想（問題実証目的）
 * ====================================================================
 * 
 * 【このクラスの教育的意義】
 * 
 * 問題の実証：
 * - Cat クラスと同じ構造で virtual なし版を実装
 * - 実際に動かして問題を体験する
 * - 理論だけでなく実践で学習する
 * 
 * 対比学習：
 * - Cat::makeSound() は期待通りに動作
 * - WrongCat::makeSound() は期待通りに動作しない
 * - 同じコードパターンでも結果が全く異なる
 * 
 * 【Cat との実装比較】
 * 
 * 共通点：
 * - 同じ継承構造（public inheritance）
 * - 同じメンバ関数セット
 * - 同じOrthodox Canonical Form
 * 
 * 相違点：
 * - 基底クラスがvirtualなし（WrongAnimal）
 * - makeSound() がオーバーライドされない
 * - 多態性が働かない
 * 
 * 【予想される問題シナリオ】
 * 
 * 1. 多態的な使用：
 * ```cpp
 * WrongAnimal* animal = new WrongCat("Kitty");
 * animal->makeSound();  // WrongAnimal::makeSound() が実行される
 * ```
 * 
 * 2. コレクションでの混在：
 * ```cpp
 * std::vector<WrongAnimal*> animals;
 * animals.push_back(new WrongCat("Cat1"));
 * animals.push_back(new WrongCat("Cat2"));
 * // 全て同じWrongAnimal::makeSound()が実行される
 * ```
 * 
 * 3. デストラクタ問題：
 * ```cpp
 * delete animal;  // WrongCat::~WrongCat() が呼ばれない
 * ```
 */
class WrongCat : public WrongAnimal {
public:
    /*
     * ====================================================================
     * Orthodox Canonical Form（非仮想継承版）
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * WrongCat();
     * 
     * 基本的な猫の初期化：
     * - WrongAnimal::WrongAnimal() の自動呼び出し
     * - type を "WrongCat" に設定
     * - 猫らしい初期化メッセージ出力
     * 
     * 実装上はCatと同じ：
     * - 基底クラス呼び出し
     * - type設定
     * - デバッグ出力
     * 
     * 違いは実行時に明らかになる：
     * - makeSound() の動作差
     * - 多態性での動作差
     * - デストラクタ実行差
     */
    WrongCat();
    
    /*
     * 【コピーコンストラクタ】
     * WrongCat(const WrongCat& other);
     * 
     * 標準的なコピー処理：
     * - WrongAnimal(other) による基底部分コピー
     * - WrongCat固有データのコピー（現在は無し）
     * - 独立したオブジェクトの作成
     * 
     * スライシング問題への感受性：
     * ```cpp
     * WrongCat cat("Kitty");
     * WrongAnimal animal = cat;  // スライシング発生
     * animal.makeSound();        // WrongAnimal::makeSound()
     * ```
     */
    WrongCat(const WrongCat& other);
    
    /*
     * 【代入演算子】
     * WrongCat& operator=(const WrongCat& other);
     * 
     * 標準的な代入処理：
     * - 自己代入チェック
     * - WrongAnimal::operator=(other) 呼び出し
     * - WrongCat固有データの代入
     * - *thisの返却
     * 
     * 基底クラス代入との関係：
     * ```cpp
     * WrongCat cat1, cat2;
     * WrongAnimal& animal = cat1;
     * animal = cat2;  // スライシング代入
     * ```
     */
    WrongCat& operator=(const WrongCat& other);
    
    /*
     * 【デストラクタ】
     * ~WrongCat();
     * 
     * 猫固有のクリーンアップ：
     * - WrongCat固有リソースの解放
     * - デバッグメッセージ出力
     * - WrongAnimal::~WrongAnimal() の自動呼び出し
     * 
     * ⚠️  多態性での重大な問題：
     * ```cpp
     * WrongAnimal* animal = new WrongCat("Kitty");
     * delete animal;  // WrongCat::~WrongCat() が呼ばれない！
     * ```
     * 
     * 期待される動作（でも実際は起こらない）：
     * 1. WrongCat::~WrongCat() 実行
     * 2. WrongAnimal::~WrongAnimal() 実行
     * 
     * 実際の動作：
     * 1. WrongAnimal::~WrongAnimal() のみ実行
     */
    ~WrongCat();
    
    /*
     * ====================================================================
     * 非仮想関数の「オーバーライド」（実際は関数隠蔽）
     * ====================================================================
     */
    
    /*
     * 【makeSound関数の実装】
     * void makeSound() const;
     * 
     * ⚠️  これは「オーバーライド」ではなく「関数隠蔽」：
     * 
     * 技術的詳細：
     * - WrongAnimal::makeSound() は virtual でない
     * - この関数は新しい関数として定義される
     * - 基底クラス関数を「隠す」（hide）だけ
     * - vtable に登録されない
     * 
     * 実際の動作問題：
     * ```cpp
     * WrongCat cat;
     * cat.makeSound();          // ✅ WrongCat::makeSound() 実行
     * 
     * WrongAnimal* animal = &cat;
     * animal->makeSound();      // ❌ WrongAnimal::makeSound() 実行
     * ```
     * 
     * なぜ期待通りに動かないのか：
     * - コンパイル時にポインタ型で関数が決定される
     * - WrongAnimal* なので WrongAnimal::makeSound() が選択
     * - 実際のオブジェクト型（WrongCat）は無視される
     * 
     * 猫らしい鳴き声の実装：
     * - "Wrong Meow! Wrong Meow!" で Catとの差別化
     * - しかし多態性では呼ばれない悲しい運命
     * - 直接呼び出しでのみ動作確認可能
     * 
     * const correctnessの維持：
     * - 基底クラスとの一致は維持
     * - 関数シグネチャは正確に一致
     * - それでもオーバーライドにはならない
     */
    void makeSound() const;
};

#endif

/*
 * ====================================================================
 * 関数隠蔽（Function Hiding）の詳細メカニズム
 * ====================================================================
 * 
 * 【オーバーライド vs 関数隠蔽の比較】
 * 
 * 仮想関数オーバーライド（Cat）：
 * ```
 * Cat_vtable:
 * +------------------+
 * | destructor       | → Cat::~Cat()
 * | makeSound()      | → Cat::makeSound()  ← 動的バインディング
 * +------------------+
 * ```
 * 
 * 非仮想関数隠蔽（WrongCat）：
 * ```
 * WrongCat（vtableなし）:
 * +------------------+
 * | type             |
 * +------------------+
 * 
 * 関数解決：
 * - 直接呼び出し: WrongCat::makeSound()
 * - ポインタ経由: WrongAnimal::makeSound()  ← 静的バインディング
 * ```
 * 
 * 【実行時の関数選択過程】
 * 
 * 仮想関数の場合（動的）：
 * 1. オブジェクトのvtableを参照
 * 2. 実際の型の関数アドレス取得
 * 3. その関数を実行
 * 
 * 非仮想関数の場合（静的）：
 * 1. ポインタ・参照の型を確認
 * 2. その型の関数アドレスを取得
 * 3. その関数を実行（実際のオブジェクト型無視）
 */

/*
 * ====================================================================
 * 具体的な問題実例とデバッグの困難さ
 * ====================================================================
 * 
 * 【実例1：動物園システムでの問題】
 * 
 * 問題のあるコード：
 * ```cpp
 * class WrongZoo {
 * private:
 *     std::vector<WrongAnimal*> animals;
 * 
 * public:
 *     void addAnimal(WrongAnimal* animal) {
 *         animals.push_back(animal);
 *     }
 *     
 *     void feedingTime() {
 *         for (WrongAnimal* animal : animals) {
 *             std::cout << animal->getType() << ": ";
 *             animal->makeSound();  // 問題発生箇所
 *         }
 *     }
 * };
 * 
 * WrongZoo zoo;
 * zoo.addAnimal(new WrongCat("Kitty"));
 * zoo.addAnimal(new WrongCat("Fluffy"));
 * zoo.feedingTime();
 * ```
 * 
 * 実際の出力：
 * ```
 * WrongCat: Some generic wrong animal sound!
 * WrongCat: Some generic wrong animal sound!
 * ```
 * 
 * 期待していた出力：
 * ```
 * WrongCat: Wrong Meow! Wrong Meow!
 * WrongCat: Wrong Meow! Wrong Meow!
 * ```
 * 
 * デバッグの困難点：
 * - getType() は正しく "WrongCat" を返す
 * - オブジェクト作成も正常
 * - makeSound() だけが期待と違う
 * - コンパイルエラーは一切なし
 * 
 * 【実例2：設定ファイル駆動システムでの問題】
 * 
 * 問題のあるコード：
 * ```cpp
 * WrongAnimal* createAnimal(const std::string& type) {
 *     if (type == "cat") {
 *         return new WrongCat();
 *     }
 *     return new WrongAnimal();
 * }
 * 
 * void processAnimals(const std::vector<std::string>& animalTypes) {
 *     for (const std::string& type : animalTypes) {
 *         WrongAnimal* animal = createAnimal(type);
 *         
 *         std::cout << "Processing " << animal->getType() << std::endl;
 *         animal->makeSound();  // 全て同じ音になる
 *         
 *         delete animal;  // メモリリークの可能性
 *     }
 * }
 * ```
 * 
 * 運用での問題：
 * - ユーザーは猫の音を期待
 * - 実際は汎用的な音のみ
 * - バグレポートが理解困難
 * - 再現が困難（コードは「正しく」見える）
 */

/*
 * ====================================================================
 * Cat vs WrongCat の実行比較表
 * ====================================================================
 * 
 * | 操作 | Cat | WrongCat | 説明 |
 * |------|-----|----------|------|
 * | 直接呼び出し | Cat::makeSound() | WrongCat::makeSound() | 両方とも期待通り |
 * | Animal*経由 | Cat::makeSound() | WrongAnimal::makeSound() | ❌ 期待と異なる |
 * | Animal&経由 | Cat::makeSound() | WrongAnimal::makeSound() | ❌ 期待と異なる |
 * | delete Animal* | Cat::~Cat() → Animal::~Animal() | WrongAnimal::~WrongAnimal() | ❌ リーク可能性 |
 * | スライシング | 一部機能失うが安全 | 完全に機能失う | ❌ より深刻 |
 * | vtableサイズ | +8 bytes | 0 bytes | メモリ使用量差 |
 * | 実行速度 | わずかに遅い | 高速 | パフォーマンス差 |
 * | デバッグ性 | 良い | 悪い | 問題特定の容易さ |
 * 
 * 【動作確認用テストケース】
 * 
 * ```cpp
 * void demonstrateDifference() {
 *     std::cout << "=== Direct Call Test ===" << std::endl;
 *     Cat cat;
 *     WrongCat wrongCat;
 *     cat.makeSound();        // "Meow! Meow!"
 *     wrongCat.makeSound();   // "Wrong Meow! Wrong Meow!"
 *     
 *     std::cout << "=== Polymorphic Call Test ===" << std::endl;
 *     Animal* animal1 = &cat;
 *     WrongAnimal* animal2 = &wrongCat;
 *     animal1->makeSound();   // "Meow! Meow!" ✅
 *     animal2->makeSound();   // "Some generic wrong animal sound!" ❌
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
 * □ 非仮想継承での関数隠蔽（Function Hiding）理解
 * □ オーバーライドと関数隠蔽の違い
 * □ 静的バインディングによる予期しない動作
 * □ デストラクタ問題の具体的な発生条件
 * □ vtableの有無による実行時動作の違い
 * □ スライシング問題の深刻度の違い
 * □ デバッグが困難になる原因の理解
 * □ コンパイル時正常・実行時異常の事例
 * □ 設計ミスの影響範囲の大きさ
 * □ 多態性の利点を実感する対比学習
 * 
 * 【実習課題】
 * 1. Cat vs WrongCat の動作比較実験
 * 2. 大規模コレクションでの問題の顕在化確認
 * 3. デストラクタ問題の実際の検証
 * 4. パフォーマンス測定と設計トレードオフ分析
 * 5. WrongAnimal系をAnimal系に変換する手順作成
 */

/*
 * ====================================================================
 * 実世界での教訓と対策
 * ====================================================================
 * 
 * 【Legacy Code での実例】
 * 
 * よく見つかる問題パターン：
 * ```cpp
 * // 古いコードベース（C++98初期）
 * class Shape {  // virtualなし時代の設計
 * public:
 *     void draw() const;  // 各図形で実装したいが...
 *     double area() const;  // 計算方法が図形により異なる
 * };
 * 
 * class Circle : public Shape {
 * public:
 *     void draw() const;     // 隠蔽（オーバーライドのつもり）
 *     double area() const;   // 隠蔽（オーバーライドのつもり）
 * };
 * 
 * // 多態的使用で問題発生
 * std::vector<Shape*> shapes;
 * shapes.push_back(new Circle(5.0));
 * for (Shape* shape : shapes) {
 *     shape->draw();  // Shape::draw() が実行される
 * }
 * ```
 * 
 * 【リファクタリング戦略】
 * 
 * 段階的修正アプローチ：
 * 
 * Phase 1: 現状把握
 * ```cpp
 * // 影響範囲の調査
 * grep -r "Shape\*" src/  // ポインタ使用箇所
 * grep -r "Shape&" src/   // 参照使用箇所
 * ```
 * 
 * Phase 2: テスト強化
 * ```cpp
 * // 問題を検出するテスト
 * void testPolymorphism() {
 *     Shape* shape = new Circle(5.0);
 *     // 期待値と実際の動作を比較
 *     EXPECT_EQ(shape->area(), 78.54);  // これが失敗する
 * }
 * ```
 * 
 * Phase 3: 段階的修正
 * ```cpp
 * class Shape {
 * public:
 *     virtual void draw() const;    // virtual追加
 *     virtual double area() const;  // virtual追加
 *     virtual ~Shape();             // virtual追加
 * };
 * ```
 * 
 * 【予防策】
 * 
 * コーディング規約での対策：
 * 1. 継承を使う基底クラスのデストラクタは必ずvirtual
 * 2. 派生クラスで変更される可能性がある関数はvirtual
 * 3. 新規コードではvirtualを基本とする
 * 4. パフォーマンス最適化は測定結果に基づいて実施
 * 
 * レビューでのチェックポイント：
 * 1. 基底クラス設計での将来拡張の考慮
 * 2. 多態的使用の想定と設計の整合性
 * 3. テストでの多態性動作の確認
 * 4. ドキュメントでの設計意図の明確化
 */

/*
 * ====================================================================
 * 発展学習：設計パターンでの対策
 * ====================================================================
 * 
 * 【Strategy Pattern による回避】
 * ```cpp
 * class SoundStrategy {
 * public:
 *     virtual ~SoundStrategy() {}
 *     virtual void makeSound() const = 0;
 * };
 * 
 * class CatSoundStrategy : public SoundStrategy {
 * public:
 *     void makeSound() const override {
 *         std::cout << "Meow! Meow!" << std::endl;
 *     }
 * };
 * 
 * class WrongAnimal {
 * private:
 *     SoundStrategy* soundStrategy;
 * 
 * public:
 *     WrongAnimal(SoundStrategy* strategy) : soundStrategy(strategy) {}
 *     
 *     void makeSound() const {
 *         soundStrategy->makeSound();  // 委譲により多態性実現
 *     }
 * };
 * ```
 * 
 * 【Template Method Pattern による構造化】
 * ```cpp
 * class AnimalTemplate {
 * public:
 *     void dailyRoutine() const {  // Template Method
 *         wakeUp();
 *         makeSound();    // サブクラス実装
 *         eat();          // サブクラス実装
 *         sleep();
 *     }
 * 
 * protected:
 *     virtual void makeSound() const = 0;  // 必ず実装が必要
 *     virtual void eat() const = 0;
 *     
 * private:
 *     void wakeUp() const { std::cout << "Waking up..." << std::endl; }
 *     void sleep() const { std::cout << "Going to sleep..." << std::endl; }
 * };
 * ```
 * 
 * 【CRTP (Curiously Recurring Template Pattern) の活用】
 * ```cpp
 * template<typename Derived>
 * class AnimalCRTP {
 * public:
 *     void makeSound() const {
 *         static_cast<const Derived*>(this)->makeSoundImpl();
 *     }
 * };
 * 
 * class Cat : public AnimalCRTP<Cat> {
 * public:
 *     void makeSoundImpl() const {
 *         std::cout << "Meow! Meow!" << std::endl;
 *     }
 * };
 * 
 * // 使用時は仮想関数と同様だが、コンパイル時解決で高速
 * ```
 */