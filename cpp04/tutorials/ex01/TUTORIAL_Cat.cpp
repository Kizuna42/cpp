/*
 * ====================================================================
 * CPP04 ex01: Cat - 動的メモリ管理付き派生クラス実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 継承と動的メモリ管理の組み合わせ実装
 * - 基底クラスの動的リソース管理の継承
 * - 派生クラスでの追加リソース管理なしパターン
 * - 継承チェーンでのRAII原則の一貫適用
 * - 仮想関数オーバーライドと動的メモリの協調
 * 
 * 【重要概念】
 * - 基底クラス機能の適切な再利用
 * - 継承での複雑性を増やさない設計判断
 * - 動的メモリ管理の責任の継承
 * - Orthodox Canonical Form の継承版実装
 * - シンプルな派生クラスでの最適実装パターン
 */

#include "Cat.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * Cat::Cat()
 * 
 * 派生クラスでの動的メモリ管理継承：
 * 
 * 継承における初期化チェーン：
 * 1. Animal::Animal() の自動呼び出し
 *    - Brain オブジェクトの動的作成
 *    - type = "Animal" の初期設定
 * 2. Cat 固有の初期化処理
 *    - type = "Cat" への更新
 *    - 猫固有のデバッグ出力
 * 
 * シンプルな実装の価値：
 * - 基底クラスの Brain 管理を完全に信頼
 * - 新しい動的リソースの追加なし
 * - 継承の恩恵を最大限活用
 * - 複雑性の不要な増大を回避
 */
Cat::Cat() {
    /*
     * 【基底クラス初期化の信頼】
     * 
     * Animal::Animal() により既に実行済み：
     * - brain = new Brain() の実行完了
     * - type = "Animal" の設定完了
     * - デバッグ出力の完了
     * 
     * Cat でやるべきこと：
     * - type の適切な更新
     * - 猫らしい初期化メッセージ
     * - 基底クラス機能の有効活用確認
     */
    
    /*
     * 【型情報の特化】
     * 
     * type = "Cat" の重要性：
     * - getType() での正しい型返却
     * - デバッグ時の識別支援
     * - 多態性での型確認用途
     * - 実行時型情報（RTTI）の補完
     */
    type = "Cat";
    
    /*
     * 【猫らしい初期化メッセージ】
     * 
     * デバッグ出力の教育効果：
     * - コンストラクタ実行順序の可視化
     * - 基底クラスとの区別明確化
     * - オブジェクト作成プロセスの理解支援
     * - 猫らしい個性の表現
     */
    std::cout << "Cat constructor called" << std::endl;
    std::cout << "Cat is created with inherited brain capacity!" << std::endl;
    std::cout << "Meow! A smart cat is ready to think and play!" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * Cat::Cat(const Cat& other) : Animal(other)
 * 
 * 継承での深いコピー実装：
 * 
 * 基底クラス部分のコピー：
 * - Animal(other) による Animal::Animal(const Animal&) 呼び出し
 * - other.brain の内容を新しい Brain オブジェクトにコピー
 * - type メンバのコピーも自動実行
 * - 完全に独立した Cat オブジェクトの作成
 * 
 * 派生クラスでの追加処理：
 * - type は既に正しく "Cat" にコピー済み
 * - 追加の動的リソースなしのため処理不要
 * - デバッグ出力のみ実装
 */
Cat::Cat(const Cat& other) : Animal(other) {
    /*
     * 【継承でのコピー処理の効率性】
     * 
     * Animal(other) の効果：
     * - Animal::Animal(const Animal& other) の実行
     * - other.type ("Cat") の this->type へのコピー
     * - new Brain(*other.brain) による独立Brain作成
     * - デバッグ出力による動作確認
     * 
     * Cat での追加作業：
     * - 基底クラス処理で既に完了
     * - type は正しく "Cat" になっている
     * - brain は独立したコピーが作成済み
     * - 追加のメンバ変数なしのため処理不要
     */
    
    /*
     * 【コピー操作の記録】
     * 
     * デバッグ出力の価値：
     * - Cat レベルでのコピー実行確認
     * - 継承チェーンでの処理順序理解
     * - オブジェクト独立性の確認支援
     * - 猫らしい表現での処理完了通知
     */
    std::cout << "Cat copy constructor called" << std::endl;
    std::cout << "A new Cat is created as a copy with independent brain!" << std::endl;
    std::cout << "Meow meow! Another smart cat joins the family!" << std::endl;
}

/*
 * 【代入演算子】
 * Cat& Cat::operator=(const Cat& other)
 * 
 * 継承での代入演算子実装：
 * 
 * 基底クラス代入の活用：
 * - Animal::operator=(other) による基底部分代入
 * - 既存 brain の削除と新しい brain の作成
 * - type メンバの適切な更新
 * - 自己代入安全性の継承
 */
Cat& Cat::operator=(const Cat& other) {
    /*
     * 【基底クラス代入演算子の呼び出し】
     * 
     * Animal::operator=(other) の効果：
     * - this != &other による自己代入チェック
     * - delete this->brain による既存リソース解放
     * - this->type = other.type による型情報更新
     * - this->brain = new Brain(*other.brain) による新リソース作成
     * - デバッグ出力による処理確認
     * 
     * 継承での利点：
     * - 複雑なリソース管理ロジックの再利用
     * - 例外安全性の継承（基本レベル）
     * - 自己代入安全性の継承
     * - コードの重複排除
     */
    if (this != &other) {
        /*
         * 【基底クラス部分の代入実行】
         * 
         * Animal::operator=(other) の明示的呼び出し：
         * - 静的バインディングによる確実な基底クラス実行
         * - 仮想関数の問題（代入演算子は通常非仮想）回避
         * - 基底クラス機能の完全活用
         */
        Animal::operator=(other);
        
        /*
         * 【Cat 固有の代入処理】
         * 
         * 現在の実装では：
         * - 追加の動的リソースなし
         * - type は基底クラス代入で正しく設定済み
         * - 特別な処理不要
         * 
         * 将来の拡張対応：
         * - Cat 固有メンバ追加時の処理場所確保
         * - 一貫した実装パターンの維持
         */
        
        /*
         * 【代入操作の記録】
         * 
         * デバッグ出力による確認：
         * - Cat レベルでの代入実行通知
         * - 基底クラス代入との区別
         * - 猫らしい表現での完了報告
         */
        std::cout << "Cat assignment operator called" << std::endl;
        std::cout << "Cat has been updated with inherited brain management!" << std::endl;
        std::cout << "Purr purr! Smart cat has new memories!" << std::endl;
    } else {
        /*
         * 【自己代入の検出と処理】
         * 
         * 基底クラスでも同様のチェックが実行されるが：
         * - 派生クラスレベルでの明確な処理
         * - デバッグ時の実行フロー確認
         * - 一貫した実装パターンの維持
         */
        std::cout << "Cat self-assignment detected - clever cat knows itself!" << std::endl;
    }
    
    /*
     * 【*this の返却】
     * 
     * 継承での戻り値：
     * - Cat& として返却（共変戻り値型ではない）
     * - 連鎖代入の対応
     * - 基底クラスとの一貫性
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタの実装
 * ====================================================================
 */

/*
 * 【デストラクタ】
 * Cat::~Cat()
 * 
 * 継承でのデストラクタ実装：
 * 
 * 自動実行される処理：
 * - Cat::~Cat() の実行（明示的実装部分）
 * - Animal::~Animal() の自動実行
 * - delete brain による Brain オブジェクト削除
 * - Brain::~Brain() による Brain リソース解放
 * 
 * 派生クラスでの責任：
 * - Cat 固有リソースの解放（現在は無し）
 * - デバッグ出力による破棄確認
 * - 基底クラスへの適切な制御移行
 */
Cat::~Cat() {
    /*
     * 【派生クラス固有のクリーンアップ】
     * 
     * 現在の実装：
     * - 追加の動的リソースなし
     * - 特別なクリーンアップ不要
     * - デバッグ出力のみ実装
     * 
     * 将来の拡張対応：
     * - Cat 固有の動的リソース追加時の解放場所
     * - ファイルハンドル、ネットワーク接続等のクリーンアップ
     * - 例外安全なリソース解放
     */
    
    /*
     * 【デストラクタ実行の記録】
     * 
     * デバッグ出力の重要性：
     * - デストラクタチェーンの実行順序確認
     * - Cat::~Cat() → Animal::~Animal() の順序可視化
     * - メモリリーク検出の支援
     * - オブジェクトライフサイクルの完了確認
     */
    std::cout << "Cat destructor called" << std::endl;
    std::cout << "Cat is saying goodbye - brain will be safely released by Animal!" << std::endl;
    std::cout << "Meow... Smart cat is going to sleep peacefully..." << std::endl;
}

/*
 * ====================================================================
 * 仮想関数のオーバーライド
 * ====================================================================
 */

/*
 * 【makeSound 関数のオーバーライド】
 * void Cat::makeSound() const
 * 
 * 猫固有の鳴き声実装：
 * 
 * オーバーライドの効果：
 * - Animal* cat = new Cat(); cat->makeSound() で Cat::makeSound() 実行
 * - 動的バインディングによる正しい関数選択
 * - 多態性の恩恵を受けた猫らしい動作
 * - ex00 からの一貫した実装パターン継続
 */
void Cat::makeSound() const {
    /*
     * 【猫らしい鳴き声の実装】
     * 
     * "Meow! Meow!" の選択理由：
     * - 典型的で分かりやすい猫の鳴き声
     * - Dog の "Woof! Woof!" との明確な差別化
     * - ex00 との一貫性維持
     * - 国際的に理解されやすい表現
     * 
     * const correctness の維持：
     * - 鳴く行為はオブジェクトの状態を変更しない
     * - brain の内容は変更されない（思考と発声は別）
     * - 基底クラスとの完全なシグネチャ一致
     * - constオブジェクトからの呼び出し対応
     */
    std::cout << "Meow! Meow!" << std::endl;
}

/*
 * ====================================================================
 * 実装の総括と設計判断
 * ====================================================================
 * 
 * 【継承における設計の妥当性】
 * 
 * シンプルな派生クラスの価値：
 * - 基底クラスの複雑な機能の完全継承
 * - 不要な複雑性の追加回避
 * - 継承の恩恵の最大限活用
 * - 保守性・理解しやすさの確保
 * 
 * 基底クラス機能の信頼：
 * - Animal の Brain 管理への完全依存
 * - 深いコピー・代入の基底クラス実装活用
 * - デストラクタチェーンの自動実行信頼
 * - RAII 原則の継承による恩恵
 * 
 * 【ex00 からの進化の一貫性】
 * 
 * 変わらない部分：
 * - makeSound() のオーバーライドパターン
 * - type メンバによる型識別
 * - デバッグ出力による動作確認
 * - 猫らしい個性の表現
 * 
 * 進化した部分：
 * - 動的メモリ管理の基底クラス継承
 * - より複雑なコピー・代入処理
 * - リソース管理の責任継承
 * - より詳細なデバッグ情報出力
 * 
 * 【将来の拡張可能性】
 * 
 * Cat 固有機能追加の容易性：
 * ```cpp
 * class Cat : public Animal {
 * private:
 *     std::string breed;          // 品種情報
 *     int playfulness;           // 遊び好き度
 *     ToyBox* toyBox;           // 猫用おもちゃ箱
 * 
 * public:
 *     Cat() : Animal(), breed("Unknown"), playfulness(50), toyBox(new ToyBox()) {
 *         type = "Cat";
 *         // ... 初期化処理
 *     }
 *     
 *     ~Cat() {
 *         delete toyBox;  // Cat固有リソースの解放
 *         // Animal::~Animal() は自動実行
 *     }
 *     
 *     void play() const {         // Cat固有の機能
 *         std::cout << "Cat is playing with toys!" << std::endl;
 *     }
 * };
 * ```
 * 
 * 拡張時の考慮事項：
 * - Cat 固有動的リソースの適切な管理
 * - コピー・代入演算子での追加処理
 * - 例外安全性の維持
 * - デバッグ出力の一貫性保持
 */

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【基本的な Cat オブジェクト作成】
 * 
 * コード：
 * ```cpp
 * Cat cat;
 * ```
 * 
 * 出力：
 * ```
 * Brain constructor called
 * Brain is being initialized with 100 ideas
 * Animal constructor called
 * Animal entity created with brain at address: 0x...
 * Animal (Animal) is ready with thinking capacity!
 * Cat constructor called
 * Cat is created with inherited brain capacity!
 * Meow! A smart cat is ready to think and play!
 * ```
 * 
 * 【多態性による使用】
 * 
 * コード：
 * ```cpp
 * Animal* animal = new Cat();
 * animal->makeSound();
 * std::cout << animal->getType() << std::endl;
 * delete animal;
 * ```
 * 
 * 出力：
 * ```
 * [Cat作成の出力]
 * Meow! Meow!
 * Cat
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
 * 
 * 【コピー操作】
 * 
 * コード：
 * ```cpp
 * Cat original;
 * Cat copy(original);
 * ```
 * 
 * 出力：
 * ```
 * [original作成の出力]
 * Brain copy constructor called
 * Copying brain with 100 ideas
 * New independent brain created at 0x...
 * Animal copy constructor called
 * Copying Animal (Cat) with brain at 0x...
 * New Animal created with independent brain at 0x...
 * Cat copy constructor called
 * A new Cat is created as a copy with independent brain!
 * Meow meow! Another smart cat joins the family!
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ 継承による動的メモリ管理の適切な継承
 * □ 基底クラス機能の効率的な再利用
 * □ Orthodox Canonical Form の継承版実装
 * □ 仮想関数オーバーライドと動的メモリの協調
 * □ デストラクタチェーンの正しい実行順序
 * □ 深いコピーの継承による正しい実装
 * □ 自己代入安全性の継承
 * □ const correctness の一貫した維持
 * □ シンプルな派生クラス設計の価値
 * □ 多態性と動的メモリ管理の組み合わせ動作
 * 
 * 【実習課題】
 * 1. Cat 固有の動的リソース（ToyBox等）の追加
 * 2. より複雑な Cat 階層（PersianCat, SiameseCat等）の実装
 * 3. Brain の猫用特化版（CatBrain）の実装
 * 4. パフォーマンス測定（継承 vs 集約）
 * 5. 例外安全性の強化実装
 */

/*
 * ====================================================================
 * よくある継承実装のミスと対策
 * ====================================================================
 * 
 * 【ミス1：基底クラスコンストラクタ呼び出し忘れ】
 * 
 * 間違い例：
 * ```cpp
 * Cat::Cat(const Cat& other) {  // Animal(other) がない
 *     type = other.type;         // 浅いコピー
 *     // brain のコピーが行われない！
 * }
 * ```
 * 
 * 問題：
 * - brain がコピーされずに nullptr または不正値
 * - 基底クラスの初期化がスキップされる
 * - 深いコピーが実装されない
 * 
 * 対策：
 * - 明示的な Animal(other) 呼び出し
 * - 初期化リストでの基底クラス指定
 * - テストでの独立性確認
 * 
 * 【ミス2：代入演算子での基底クラス代入忘れ】
 * 
 * 間違い例：
 * ```cpp
 * Cat& Cat::operator=(const Cat& other) {
 *     if (this != &other) {
 *         type = other.type;  // 基底クラス代入を呼ばない
 *     }
 *     return *this;
 * }
 * ```
 * 
 * 問題：
 * - brain の適切な更新が行われない
 * - 古い brain がリークする可能性
 * - 基底クラスの複雑なロジックが活用されない
 * 
 * 対策：
 * - Animal::operator=(other) の明示的呼び出し
 * - 基底クラス機能のテスト
 * - リソース管理の正確性確認
 * 
 * 【ミス3：デストラクタでの基底クラス呼び出し試行】
 * 
 * 間違い例：
 * ```cpp
 * Cat::~Cat() {
 *     // Cat固有の処理
 *     Animal::~Animal();  // ❌ 明示的呼び出し不要
 * }
 * ```
 * 
 * 問題：
 * - デストラクタは自動で基底クラスを呼び出す
 * - 明示的呼び出しは二重実行を引き起こす可能性
 * - 未定義動作や二重削除のリスク
 * 
 * 対策：
 * - デストラクタは自動実行に任せる
 * - 派生クラス固有の処理のみ実装
 * - 実行順序の理解（派生→基底）
 * 
 * 【ミス4：仮想関数のシグネチャ不一致】
 * 
 * 間違い例：
 * ```cpp
 * void makeSound();          // const がない
 * void makeSound() const;    // ✅ 正しい
 * ```
 * 
 * 問題：
 * - オーバーライドにならない（関数隠蔽）
 * - 多態性が期待通りに動作しない
 * - Animal::makeSound() が呼ばれる
 * 
 * 対策：
 * - 基底クラスとの完全なシグネチャ一致
 * - const correctness の徹底
 * - コンパイラ警告への注意
 */