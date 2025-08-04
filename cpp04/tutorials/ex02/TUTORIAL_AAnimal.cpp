/*
 * ====================================================================
 * CPP04 ex02: AAnimal - 抽象基底クラス実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 抽象基底クラスの実装部分の理解
 * - 純粋仮想関数を持つクラスでの実装可能な部分
 * - 仮想デストラクタの実装とその重要性
 * - Orthodox Canonical Formの抽象クラス版実装
 * - 多態性の基盤となる実装の詳細理解
 * 
 * 【重要概念】
 * - 抽象クラスでも実装可能な関数の存在
 * - 派生クラスからの基底クラス機能呼び出し
 * - vtable構築のための実装の役割
 * - RAII原則の抽象クラスでの適用
 * - デバッグ支援のための実装パターン
 */

#include "AAnimal.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * AAnimal::AAnimal()
 * 
 * 抽象基底クラスでのコンストラクタの役割：
 * 
 * 直接呼び出しは不可能：
 * - AAnimal animal; // コンパイルエラー
 * - 純粋仮想関数があるためインスタンス化不可
 * 
 * 派生クラスからの間接呼び出し：
 * - Dog::Dog() : AAnimal() { ... } // OK
 * - 基底クラス部分の初期化を担当
 * 
 * 実装の責任：
 * - 共通メンバ変数の初期化
 * - デバッグ情報の出力
 * - vtable構築のための準備
 */
AAnimal::AAnimal() : type("AAnimal") {
    /*
     * 【基底クラスの初期化処理】
     * 
     * type = "AAnimal" の設定理由：
     * - デフォルト値として抽象基底クラス名を設定
     * - 派生クラスで適切にオーバーライドされることを期待
     * - デバッグ時の識別支援
     * 
     * なぜ他の値でないのか？
     * - 空文字列: 不完全な初期化の印象
     * - "Unknown": 派生クラスでの設定忘れを隠蔽する可能性
     * - "AAnimal": 基底クラスでの初期化を明確に示す
     */
    
    /*
     * 【デバッグ出力による動作確認】
     * 
     * コンストラクタチェーンの可視化：
     * - AAnimalコンストラクタが呼ばれたことを明示
     * - 派生クラス作成時の基底部分初期化確認
     * - オブジェクトライフサイクルの追跡支援
     * 
     * 出力タイミング：
     * 1. 派生クラスのコンストラクタ開始時
     * 2. AAnimalのコンストラクタ実行
     * 3. 派生クラスの追加初期化実行
     */
    std::cout << "AAnimal constructor called" << std::endl;
    std::cout << "Abstract animal entity initialized (type: " << type << ")" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * AAnimal::AAnimal(const AAnimal& other)
 * 
 * 抽象基底クラスでのコピーコンストラクタ実装：
 * 
 * 直接使用の不可能性：
 * - AAnimal animal1; // エラー - インスタンス化不可
 * - AAnimal animal2(animal1); // エラー - 上と同じ理由
 * 
 * 派生クラスでの間接使用：
 * - Dog dog1("Buddy");
 * - Dog dog2(dog1); // Dog(const Dog&) : AAnimal(dog1) で呼び出される
 * 
 * スライシング問題への対処：
 * - 基底クラス部分の適切なコピー
 * - vtableポインタの正しい設定
 * - 派生クラス情報の保持
 */
AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
    /*
     * 【メンバ変数のコピー処理】
     * 
     * type(other.type) の意味：
     * - コピー元のtype値を新しいオブジェクトに設定
     * - 動物の種類情報の継承
     * - 識別情報の一貫性確保
     * 
     * なぜ代入ではなく初期化リストか？
     * - 効率性: 初期化は代入より高速
     * - const/referenceメンバ対応: 代入不可能なメンバへの対応
     * - 例外安全性: 初期化失敗時の状態保証
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * コピー操作の可視化：
     * - AAnimalレベルでのコピーが実行されたことを確認
     * - コピー元とコピー先の情報表示
     * - オブジェクト複製プロセスの追跡
     */
    std::cout << "AAnimal copy constructor called" << std::endl;
    std::cout << "Copying abstract animal (type: " << type << ")" << std::endl;
}

/*
 * 【代入演算子】
 * AAnimal& AAnimal::operator=(const AAnimal& other)
 * 
 * 抽象基底クラスでの代入演算子実装：
 * 
 * 使用シナリオの制限：
 * - 直接代入は不可能（インスタンス化不可のため）
 * - 派生クラス間での基底部分代入で使用
 * - 多態性での参照・ポインタ経由代入で使用
 * 
 * 実装の重要性：
 * - 派生クラスでの代入演算子から呼び出される
 * - 基底クラス部分の適切な代入処理
 * - Orthodox Canonical Formの完全性確保
 */
AAnimal& AAnimal::operator=(const AAnimal& other) {
    /*
     * 【自己代入チェック】
     * 
     * if (this != &other) の必要性：
     * - 同一オブジェクトへの代入防止
     * - 無駄な処理の回避
     * - 自己破壊の防止（リソース管理がある場合）
     * 
     * 抽象基底クラスでの特別な意味：
     * - 派生クラスでの代入時の基底部分処理
     * - 多態性での安全な代入操作
     * - vtableの保持（代入後も正しい型情報を維持）
     */
    if (this != &other) {
        /*
         * 【メンバ変数の代入】
         * 
         * type = other.type の実行：
         * - コピー元のtype値を現在のオブジェクトに設定
         * - 動物種類の変更（通常は発生しないが理論的には可能）
         * - 状態の一貫性確保
         * 
         * 注意点：
         * - vtableは変更されない（オブジェクトの実際の型は不変）
         * - 派生クラス固有のメンバは別途処理が必要
         * - const/referenceメンバがある場合は代入不可
         */
        type = other.type;
        
        /*
         * 【デバッグ出力による確認】
         * 
         * 代入操作の可視化：
         * - 基底クラスレベルでの代入実行確認
         * - 代入前後の状態変化表示
         * - オブジェクト更新プロセスの追跡
         */
        std::cout << "AAnimal assignment operator called" << std::endl;
        std::cout << "Assigning abstract animal (new type: " << type << ")" << std::endl;
    }
    
    /*
     * 【*this の返却】
     * 
     * 戻り値の意義：
     * - 連鎖代入の有効化: a = b = c
     * - 標準的なC++代入演算子の慣例
     * - 一貫したプログラミングインターフェース
     * 
     * 参照返却の理由：
     * - コピーコストの回避
     * - 左辺値としての使用可能性
     * - 元のオブジェクトとの同一性保証
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタの実装
 * ====================================================================
 */

/*
 * 【仮想デストラクタ】
 * AAnimal::~AAnimal()
 * 
 * virtualデストラクタの極めて重要な役割：
 * 
 * 多態性での正しい削除処理：
 * ```cpp
 * AAnimal* animal = new Dog("Buddy");
 * delete animal;  // 正しい順序: Dog::~Dog() → AAnimal::~AAnimal()
 * ```
 * 
 * virtualがない場合の危険性：
 * ```cpp
 * // 仮想でないデストラクタの場合
 * delete animal;  // 間違った動作: AAnimal::~AAnimal() のみ呼ばれる
 * // → Dogクラスのリソースが解放されない
 * // → メモリリーク、リソースリークの原因
 * ```
 * 
 * vtableでの位置：
 * - デストラクタもvtableに含まれる
 * - virtualにより動的バインディング
 * - 実行時の正しい型でのデストラクタ選択
 */
AAnimal::~AAnimal() {
    /*
     * 【抽象基底クラスでのクリーンアップ】
     * 
     * 実行される処理：
     * - 基底クラス固有のリソース解放
     * - デバッグ情報の出力
     * - 共通クリーンアップ処理
     * 
     * 実行タイミング：
     * 1. 派生クラスのデストラクタ実行完了後
     * 2. 基底クラスのデストラクタ自動実行
     * 3. オブジェクトメモリの解放前
     * 
     * 派生クラスとの協調：
     * - 派生クラス固有のクリーンアップは派生クラスデストラクタで
     * - 共通部分のクリーンアップは基底クラスデストラクタで
     * - 正しい順序での実行保証
     */
    
    /*
     * 【デバッグ出力による確認】
     * 
     * デストラクタチェーンの可視化：
     * - AAnimalデストラクタの実行確認
     * - オブジェクト破棄プロセスの追跡
     * - メモリ管理の正確性検証支援
     */
    std::cout << "AAnimal destructor called" << std::endl;
    std::cout << "Abstract animal entity destroyed (type: " << type << ")" << std::endl;
}

/*
 * ====================================================================
 * 通常の仮想関数の実装
 * ====================================================================
 */

/*
 * 【getType関数】
 * std::string AAnimal::getType() const
 * 
 * 純粋仮想関数でない仮想関数の実装：
 * 
 * 実装を提供する理由：
 * - 共通の動作を定義可能
 * - 派生クラスでのオーバーライドは任意
 * - デフォルト動作の提供
 * 
 * virtual指定の効果：
 * - 派生クラスでオーバーライド可能
 * - 多態性での動的バインディング
 * - vtableを通じた正しい関数呼び出し
 * 
 * const指定の意味：
 * - オブジェクトの状態を変更しない
 * - constオブジェクトからも呼び出し可能
 * - 読み取り専用操作であることを明示
 */
std::string AAnimal::getType() const {
    /*
     * 【typeメンバの返却】
     * 
     * return type の動作：
     * - protectedメンバへのアクセス
     * - std::stringのコピーコンストラクタ呼び出し
     * - 呼び出し元への値渡し
     * 
     * なぜ参照でないのか？
     * - 内部実装の隠蔽
     * - 返却後の値の安全性保証
     * - constオブジェクトからの呼び出し対応
     * 
     * 派生クラスでのオーバーライド可能性：
     * ```cpp
     * class Dog : public AAnimal {
     * public:
     *     std::string getType() const override {
     *         return "Dog (specialized)";  // カスタマイズ可能
     *     }
     * };
     * ```
     */
    return type;
}

/*
 * ====================================================================
 * 実装の詳細解説と設計判断
 * ====================================================================
 * 
 * 【なぜmakeSound()は実装しないのか？】
 * 
 * 純粋仮想関数の制約：
 * - = 0 指定により実装不可（概念的に）
 * - 各派生クラスで必ず実装が必要
 * - 基底クラスでの汎用実装が不適切
 * 
 * 設計思想：
 * - "動物"という抽象概念には具体的な音がない
 * - 各動物固有の実装を強制
 * - インターフェース契約の明確化
 * 
 * 実装可能だが実装しない選択：
 * ```cpp
 * // 技術的には可能だが、設計上不適切
 * void AAnimal::makeSound() const {
 *     std::cout << "Some generic animal sound" << std::endl;
 * }
 * ```
 * 
 * 【実装ありとなしの使い分け基準】
 * 
 * 実装を提供すべき場合：
 * - 共通の合理的なデフォルト動作がある
 * - 派生クラスでの実装が任意で良い
 * - 基底クラスの実装で十分な場合が多い
 * 
 * 純粋仮想にすべき場合：
 * - 基底クラスでの実装が概念的に不適切
 * - 派生クラスでの実装が必須
 * - インターフェース契約を強制したい
 * 
 * 【vtableと実装の関係】
 * 
 * AAnimalのvtable（概念的）:
 * ```
 * AAnimal vtable:
 * +------------------+
 * | ~AAnimal()       | → AAnimal::~AAnimal()
 * | getType()        | → AAnimal::getType()  
 * | makeSound()      | → [純粋仮想 - 実装なし]
 * +------------------+
 * ```
 * 
 * Dogのvtable（派生後）:
 * ```
 * Dog vtable:
 * +------------------+
 * | ~AAnimal()       | → Dog::~Dog()
 * | getType()        | → AAnimal::getType() (継承)
 * | makeSound()      | → Dog::makeSound() (実装)
 * +------------------+
 * ```
 */

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【派生クラス作成時のコンストラクタチェーン】
 * 
 * コード：
 * ```cpp
 * Dog dog("Buddy");
 * ```
 * 
 * 出力：
 * ```
 * AAnimal constructor called
 * Abstract animal entity initialized (type: AAnimal)
 * Dog constructor called
 * Dog Buddy is ready to play!
 * ```
 * 
 * 【多態性による関数呼び出し】
 * 
 * コード：
 * ```cpp
 * AAnimal* animal = new Dog("Buddy");
 * std::cout << animal->getType() << std::endl;
 * animal->makeSound();
 * delete animal;
 * ```
 * 
 * 出力：
 * ```
 * AAnimal constructor called
 * Abstract animal entity initialized (type: AAnimal)  
 * Dog constructor called
 * Dog Buddy is ready to play!
 * Dog
 * Woof! Woof!
 * Dog destructor called
 * Dog Buddy is going to sleep!
 * AAnimal destructor called
 * Abstract animal entity destroyed (type: Dog)
 * ```
 * 
 * 【コピーコンストラクタの動作】
 * 
 * コード：
 * ```cpp
 * Dog original("Buddy");
 * Dog copy(original);
 * ```
 * 
 * 出力：
 * ```
 * AAnimal constructor called
 * Abstract animal entity initialized (type: AAnimal)
 * Dog constructor called
 * Dog Buddy is ready to play!
 * AAnimal copy constructor called
 * Copying abstract animal (type: Dog)
 * Dog copy constructor called
 * Copying dog: Buddy
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ 抽象基底クラスでのコンストラクタ実装理解
 * □ 仮想デストラクタの実装とその重要性
 * □ Orthodox Canonical Formの抽象クラス版実装
 * □ 純粋仮想関数と通常仮想関数の使い分け
 * □ protectedメンバ変数の適切な管理
 * □ vtableと関数実装の関係理解
 * □ 多態性での動的バインディング実装
 * □ const correctnessの実装への適用
 * □ デバッグ支援のための出力実装
 * □ 派生クラスからの基底クラス機能利用パターン
 * 
 * 【実習課題】
 * 1. 新しい通常仮想関数の追加と実装
 * 2. より複雑な初期化処理の実装
 * 3. リソース管理を含むデストラクタ実装
 * 4. 例外安全性を考慮した実装
 * 5. パフォーマンス最適化された実装
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：純粋仮想関数の実装試行】
 * 
 * 間違い例：
 * ```cpp
 * void AAnimal::makeSound() const {
 *     std::cout << "Generic sound" << std::endl;
 * }
 * ```
 * 
 * 問題：
 * - 純粋仮想関数なのに実装がある混乱
 * - ヘッダーの= 0と実装の矛盾
 * 
 * 対策：
 * - 純粋仮想関数は実装しない
 * - 共通実装が必要なら通常の仮想関数にする
 * 
 * 【ミス2：仮想デストラクタの実装忘れ】
 * 
 * 間違い例：
 * ```cpp
 * // デストラクタの実装がない
 * virtual ~AAnimal();  // 宣言のみ
 * ```
 * 
 * 問題：
 * - リンクエラーが発生
 * - vtableが完成しない
 * 
 * 対策：
 * - virtualでも実装は必要
 * - 空の実装でも必ず提供する
 * 
 * 【ミス3：コンストラクタでの仮想関数呼び出し】
 * 
 * 危険な例：
 * ```cpp
 * AAnimal::AAnimal() : type("AAnimal") {
 *     makeSound();  // 危険！未定義動作の可能性
 * }
 * ```
 * 
 * 問題：
 * - コンストラクタ中では派生クラス部分が未初期化
 * - 純粋仮想関数の場合は未定義動作
 * 
 * 対策：
 * - コンストラクタ内では仮想関数を呼び出さない
 * - 初期化完了後に仮想関数を使用する
 * 
 * 【ミス4：const correctnessの不一致】
 * 
 * 間違い例：
 * ```cpp
 * std::string AAnimal::getType() {  // constがない
 *     return type;
 * }
 * ```
 * 
 * 問題：
 * - ヘッダーの宣言と実装の不一致
 * - constオブジェクトから呼び出せない
 * 
 * 対策：
 * - ヘッダーと実装でconst指定を一致させる
 * - 状態を変更しない関数は必ずconst指定
 */

/*
 * ====================================================================
 * 発展的な実装パターン
 * ====================================================================
 * 
 * 【パターン1：リソース管理付きの抽象基底クラス】
 * ```cpp
 * class AAnimal {
 * private:
 *     mutable std::string* debugInfo;  // デバッグ用動的メモリ
 * 
 * public:
 *     AAnimal() : type("AAnimal"), debugInfo(new std::string("Debug")) {}
 *     
 *     AAnimal(const AAnimal& other) 
 *         : type(other.type), debugInfo(new std::string(*other.debugInfo)) {}
 *     
 *     AAnimal& operator=(const AAnimal& other) {
 *         if (this != &other) {
 *             type = other.type;
 *             delete debugInfo;
 *             debugInfo = new std::string(*other.debugInfo);
 *         }
 *         return *this;
 *     }
 *     
 *     virtual ~AAnimal() { delete debugInfo; }
 * };
 * ```
 * 
 * 【パターン2：シングルトンパターンの組み込み】
 * ```cpp
 * class AAnimal {
 * private:
 *     static int instanceCount;
 * 
 * protected:
 *     AAnimal() : type("AAnimal") { 
 *         ++instanceCount;
 *         std::cout << "Total animals: " << instanceCount << std::endl;
 *     }
 *     
 * public:
 *     virtual ~AAnimal() { 
 *         --instanceCount;
 *         std::cout << "Remaining animals: " << instanceCount << std::endl;
 *     }
 *     
 *     static int getInstanceCount() { return instanceCount; }
 * };
 * 
 * int AAnimal::instanceCount = 0;
 * ```
 * 
 * 【パターン3：Observer パターン対応】
 * ```cpp
 * class AnimalObserver {
 * public:
 *     virtual ~AnimalObserver() {}
 *     virtual void onAnimalSound(const AAnimal& animal) = 0;
 * };
 * 
 * class AAnimal {
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
 *     
 *     void removeObserver(AnimalObserver* observer) {
 *         observers.erase(std::remove(observers.begin(), observers.end(), observer), 
 *                        observers.end());
 *     }
 * };
 * ```
 * 
 * 【パターン4：Factory Method の基盤】
 * ```cpp
 * class AAnimal {
 * protected:
 *     AAnimal(const std::string& animalType) : type(animalType) {}
 * 
 * public:
 *     static AAnimal* create(const std::string& animalType) {
 *         if (animalType == "Dog") return new Dog();
 *         if (animalType == "Cat") return new Cat();
 *         return nullptr;
 *     }
 *     
 *     virtual AAnimal* clone() const = 0;  // Prototype pattern
 * };
 * ```
 */