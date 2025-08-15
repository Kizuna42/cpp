/*
 * ====================================================================
 * CPP04 ex01: Animal - 動的メモリ管理付き基底クラス実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 仮想関数と動的メモリ管理の組み合わせ実装
 * - RAIIパターンの仮想継承での適用
 * - Brain クラスとの集約関係実装
 * - 深いコピーとコピーコンストラクタの実装
 * - リソース管理の継承階層での一貫性確保
 * 
 * 【重要概念】
 * - 集約（Aggregation）による has-a 関係実装
 * - 動的メモリ管理の責任分散と集約
 * - 仮想関数と動的リソース管理の協調
 * - Orthodox Canonical Form のリソース管理版
 * - RAII原則の継承システムでの実践
 */

#include "Animal.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * Animal::Animal()
 * 
 * 動的メモリ管理付きの基底クラス初期化：
 * 
 * 初期化の責任：
 * - type メンバの基本設定
 * - Brain オブジェクトの動的作成
 * - メモリ割り当ての成功確認
 * - デバッグ情報の出力
 * 
 * ex00 からの進化ポイント：
 * - 単純なメンバ初期化から動的リソース管理へ
 * - has-a 関係（Brain）の実装
 * - メモリ管理の責任の明確化
 */
Animal::Animal() : type("Animal"), brain(new Brain()) {
    /*
     * 【メンバ初期化リストでの動的メモリ割り当て】
     * 
     * brain(new Brain()) の設計判断：
     * - 例外安全性: new が失敗した場合の自動クリーンアップ
     * - 初期化の確実性: コンストラクタ本体実行前の初期化完了
     * - パフォーマンス: 代入ではなく直接初期化
     * 
     * 代替実装（推奨されない）：
     * ```cpp
     * Animal::Animal() : type("Animal") {
     *     brain = new Brain();  // 代入（初期化リストより劣る）
     * }
     * ```
     * 
     * 例外安全性の考慮：
     * - new Brain() が失敗（bad_alloc）した場合
     * - Animal オブジェクトの構築が中断される
     * - type メンバは既に初期化済みだが問題なし
     * - メモリリークは発生しない（Animalオブジェクト未完成のため）
     */
    
    /*
     * 【デバッグ出力による動作確認】
     * 
     * 動的メモリ管理でのデバッグの重要性：
     * - Brain オブジェクトの作成成功確認
     * - Animal オブジェクト作成の完了通知
     * - メモリ使用量の推移追跡支援
     * - 継承チェーンでの初期化順序確認
     */
    std::cout << "Animal constructor called" << std::endl;
    std::cout << "Animal entity created with brain at address: " << brain << std::endl;
    std::cout << "Animal (" << type << ") is ready with thinking capacity!" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * Animal::Animal(const Animal& other)
 * 
 * 深いコピー（Deep Copy）の実装：
 * 
 * 深いコピーの必要性：
 * - brain ポインタの値コピーは浅いコピー（危険）
 * - 新しい Brain オブジェクトの作成が必要
 * - 元オブジェクトとの完全な独立性確保
 * 
 * 浅いコピーの問題例：
 * ```cpp
 * // 危険な実装例
 * Animal::Animal(const Animal& other) : type(other.type), brain(other.brain) {
 *     // 問題: 同じBrainオブジェクトを2つのAnimalが所有
 *     // 結果: 一方のデストラクタで二重削除（double delete）
 * }
 * ```
 */
Animal::Animal(const Animal& other) : type(other.type), brain(new Brain(*other.brain)) {
    /*
     * 【深いコピーの実装詳細】
     * 
     * brain(new Brain(*other.brain)) の動作：
     * 1. other.brain が指すBrainオブジェクトにアクセス
     * 2. Brain(const Brain& other) コピーコンストラクタ呼び出し
     * 3. 新しい Brain オブジェクトを動的作成
     * 4. this->brain に新しいオブジェクトのアドレス設定
     * 
     * 独立性の確保：
     * - this->brain != other.brain （異なるアドレス）
     * - *this->brain == *other.brain （同じ内容）
     * - 一方の変更が他方に影響しない
     * 
     * 例外安全性：
     * - new Brain(*other.brain) が失敗した場合
     * - Animal オブジェクトの構築中断
     * - 自動的なクリーンアップ（typeはスタック変数）
     * - メモリリークなし
     */
    
    /*
     * 【コピー操作の記録】
     * 
     * デバッグ出力の内容：
     * - コピー元オブジェクトの情報
     * - 新しく作成されたBrainアドレス
     * - コピー操作の成功確認
     * - 独立性の確認支援
     */
    std::cout << "Animal copy constructor called" << std::endl;
    std::cout << "Copying Animal (" << other.type << ") with brain at " << other.brain << std::endl;
    std::cout << "New Animal created with independent brain at " << brain << std::endl;
}

/*
 * 【代入演算子】
 * Animal& Animal::operator=(const Animal& other)
 * 
 * 動的メモリ管理での代入演算子実装：
 * 
 * 実装の複雑性：
 * - 既存リソースの適切な解放
 * - 新しいリソースの割り当て
 * - 自己代入安全性の確保
 * - 例外安全性の保証
 */
Animal& Animal::operator=(const Animal& other) {
    /*
     * 【自己代入チェック】
     * 
     * if (this != &other) の重要性：
     * - 同一オブジェクトへの代入検出
     * - 不要なリソース解放・再割り当ての回避
     * - パフォーマンスの向上
     * - 自己破壊の防止
     * 
     * 自己代入が危険な理由：
     * ```cpp
     * // 自己代入チェックなしの危険な例
     * delete brain;                    // 自分のbrainを削除
     * brain = new Brain(*other.brain); // 削除済みのbrainを参照！
     * ```
     */
    if (this != &other) {
        /*
         * 【リソース管理の実装】
         * 
         * ステップ1: 既存リソースの解放
         * - delete brain によるメモリ解放
         * - Brain::~Brain() の自動実行
         * - メモリリークの防止
         */
        delete brain;
        
        /*
         * ステップ2: 新しいリソースの割り当て
         * - type メンバの単純代入
         * - brain の深いコピー作成
         * - 独立性の確保
         */
        type = other.type;
        brain = new Brain(*other.brain);
        
        /*
         * 【例外安全性の考慮】
         * 
         * new Brain(*other.brain) が失敗した場合：
         * - bad_alloc 例外が発生
         * - この時点で brain = nullptr になる
         * - オブジェクトは不正な状態になる
         * 
         * より安全な実装（参考）：
         * ```cpp
         * Brain* newBrain = new Brain(*other.brain);  // 先に作成
         * delete brain;                               // 成功後に削除
         * brain = newBrain;                           // 代入
         * ```
         */
        
        /*
         * 【代入操作の記録】
         * 
         * デバッグ出力による確認：
         * - 代入操作の実行通知
         * - 古いbrainと新しいbrainの情報
         * - オブジェクト更新の透明性確保
         */
        std::cout << "Animal assignment operator called" << std::endl;
        std::cout << "Animal updated to type: " << type << std::endl;
        std::cout << "Brain replaced with new brain at: " << brain << std::endl;
    } else {
        /*
         * 【自己代入時の処理】
         * 
         * 処理内容：
         * - 何もしない（効率的）
         * - デバッグ情報のみ出力
         * - 安全性の確保
         */
        std::cout << "Animal self-assignment detected - no operation needed" << std::endl;
    }
    
    /*
     * 【*thisの返却】
     * 
     * 戻り値の意義：
     * - 連鎖代入の有効化: a = b = c
     * - 標準的なoperator=の実装パターン
     * - 一貫したプログラミングインターフェース
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
 * Animal::~Animal()
 * 
 * 動的メモリ管理でのデストラクタ実装：
 * 
 * デストラクタの責任：
 * - 所有するリソース（Brain）の解放
 * - メモリリークの防止
 * - 仮想デストラクタとしての役割
 * - デバッグ情報の出力
 */
Animal::~Animal() {
    /*
     * 【リソース解放処理】
     * 
     * delete brain の実行：
     * - Brain::~Brain() の自動呼び出し
     * - 動的メモリの解放
     * - brain ポインタの無効化（自動）
     * 
     * null ポインタ安全性：
     * - delete nullptr は安全（何もしない）
     * - brain が null の場合でも問題なし
     * - 例外安全性の確保
     */
    delete brain;
    
    /*
     * 【デストラクタの記録】
     * 
     * デバッグ出力の重要性：
     * - オブジェクト破棄の確認
     * - リソース解放の確認
     * - メモリリーク検出の支援
     * - 継承チェーンでの実行順序確認
     */
    std::cout << "Animal destructor called" << std::endl;
    std::cout << "Animal (" << type << ") brain resources released" << std::endl;
    std::cout << "Animal entity destroyed safely" << std::endl;
}

/*
 * ====================================================================
 * 仮想関数の実装
 * ====================================================================
 */

/*
 * 【仮想関数：makeSound】
 * void Animal::makeSound() const
 * 
 * 基底クラスでの仮想関数実装：
 * 
 * 実装の目的：
 * - デフォルト動作の提供
 * - 派生クラスでのオーバーライド対象
 * - 多態性の基盤提供
 * - テスト・デバッグでの識別支援
 */
void Animal::makeSound() const {
    /*
     * 【基底クラス実装の役割】
     * 
     * なぜ実装するのか：
     * - 純粋仮想関数ではない選択
     * - 汎用的な動物音の提供
     * - 派生クラス実装忘れへの対策
     * - テスト時のフォールバック
     * 
     * 実装内容の選択：
     * - 汎用的で識別可能なメッセージ
     * - 派生クラスとの明確な差別化
     * - デバッグ時の動作確認支援
     */
    std::cout << "Some generic animal sound!" << std::endl;
}

/*
 * 【型情報取得関数】
 * std::string Animal::getType() const
 * 
 * 非仮想関数での基本機能実装：
 * 
 * 実装の安定性：
 * - 単純なメンバ変数返却
 * - 派生クラスでの変更不要
 * - 一貫した動作保証
 */
std::string Animal::getType() const {
    return type;
}

/*
 * ====================================================================
 * 実装の総括と設計判断
 * ====================================================================
 * 
 * 【ex00からex01への進化ポイント】
 * 
 * 追加された複雑性：
 * - 動的メモリ管理の導入
 * - 深いコピーの実装
 * - リソース管理の責任
 * - 例外安全性の考慮
 * 
 * 設計の一貫性：
 * - 仮想関数インターフェースの維持
 * - Orthodox Canonical Form の拡張
 * - RAII 原則の厳格な適用
 * - デバッグ支援の継続
 * 
 * 【Brain集約の設計判断】
 * 
 * has-a 関係の選択理由：
 * - Brain は Animal の一部ではなく所有物
 * - 動的な思考能力の表現
 * - 将来的な拡張（異なるBrain型等）への対応
 * - メモリ管理の明確な責任分散
 * 
 * 代替設計の検討：
 * ```cpp
 * class Animal {
 * private:
 *     Brain brain;  // 値メンバ（has-a の別実装）
 * };
 * ```
 * 
 * 利点: 動的メモリ管理不要、例外安全性向上
 * 欠点: 多態的Brain、null Brain等の柔軟性なし
 * 
 * 【パフォーマンス vs 設計のトレードオフ】
 * 
 * 動的メモリのコスト：
 * - ヒープ割り当ての時間コスト
 * - 間接参照の実行時コスト
 * - キャッシュ効率の潜在的低下
 * 
 * 設計の利点：
 * - 柔軟なリソース管理
 * - 大きなオブジェクトのコピー回避可能性
 * - 多態的な Brain 実装への拡張性
 * - null Brain による状態表現
 * 
 * 【例外安全性のレベル】
 * 
 * 現在の実装レベル：
 * - 基本例外安全性（Basic Exception Safety）
 * - リソースリークなし
 * - オブジェクト状態の一貫性は一部保証
 * 
 * 強い例外安全性への改善案：
 * ```cpp
 * Animal& Animal::operator=(const Animal& other) {
 *     if (this != &other) {
 *         Animal temp(other);  // Copy-and-Swap idiom
 *         std::swap(type, temp.type);
 *         std::swap(brain, temp.brain);
 *     }
 *     return *this;
 * }
 * ```
 */

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【基本的な使用例】
 * 
 * コード：
 * ```cpp
 * Animal animal;
 * ```
 * 
 * 出力：
 * ```
 * Brain constructor called
 * Brain is being initialized with 100 ideas
 * Animal constructor called
 * Animal entity created with brain at address: 0x...
 * Animal (Animal) is ready with thinking capacity!
 * ```
 * 
 * 【コピーコンストラクタの動作】
 * 
 * コード：
 * ```cpp
 * Animal original;
 * Animal copy(original);
 * ```
 * 
 * 出力：
 * ```
 * [original作成の出力]
 * Brain copy constructor called
 * Copying brain with 100 ideas
 * New independent brain created at 0x...
 * Animal copy constructor called
 * Copying Animal (Animal) with brain at 0x...
 * New Animal created with independent brain at 0x...
 * ```
 * 
 * 【デストラクタチェーン】
 * 
 * コード：
 * ```cpp
 * {
 *     Animal animal;
 * }  // スコープ終了
 * ```
 * 
 * 出力：
 * ```
 * [コンストラクタ出力]
 * Animal destructor called
 * Animal (Animal) brain resources released
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
 * この実装で確認すべき項目：
 * 
 * □ 動的メモリ管理と仮想関数の組み合わせ理解
 * □ 深いコピー vs 浅いコピーの実装と違い
 * □ RAII 原則の動的リソース管理での適用
 * □ 例外安全性の基本レベル実装
 * □ 集約関係（has-a）の適切な実装
 * □ Orthodox Canonical Form の拡張版実装
 * □ 仮想デストラクタの動的メモリでの重要性
 * □ 自己代入安全性の動的リソースでの実装
 * □ const correctness の一貫した適用
 * □ デバッグ支援機能の継続的実装
 * 
 * 【実習課題】
 * 1. 例外安全性の強化（Copy-and-Swap idiom）
 * 2. Brain の多態性対応（IBrain インターフェース）
 * 3. メモリ使用量の測定と最適化
 * 4. より複雑な集約関係の実装
 * 5. リソース管理の自動テスト実装
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：浅いコピーの実装】
 * 
 * 間違い例：
 * ```cpp
 * Animal(const Animal& other) : type(other.type), brain(other.brain) {}
 * ```
 * 
 * 問題：
 * - 同じBrainオブジェクトを複数のAnimalが所有
 * - デストラクタで二重削除（double delete）
 * - 一方の変更がもう一方に影響
 * 
 * 対策：
 * - new Brain(*other.brain) による独立コピー作成
 * - アドレス比較によるコピー成功確認
 * - テストでの独立性確認
 * 
 * 【ミス2：代入演算子での自己代入未対応】
 * 
 * 間違い例：
 * ```cpp
 * Animal& operator=(const Animal& other) {
 *     delete brain;
 *     brain = new Brain(*other.brain);  // otherが自分自身なら危険
 *     return *this;
 * }
 * ```
 * 
 * 問題：
 * - 自己代入時に自分のbrainを削除後に参照
 * - 削除済みメモリへのアクセス
 * - 未定義動作の発生
 * 
 * 対策：
 * - if (this != &other) による自己代入チェック
 * - Copy-and-Swap idiom の採用
 * - 自己代入テストの実装
 * 
 * 【ミス3：例外安全性の未考慮】
 * 
 * 間違い例：
 * ```cpp
 * Animal& operator=(const Animal& other) {
 *     if (this != &other) {
 *         delete brain;
 *         brain = new Brain(*other.brain);  // 失敗時の状態不整合
 *     }
 *     return *this;
 * }
 * ```
 * 
 * 問題：
 * - new が失敗した場合、brain = nullptr
 * - オブジェクトが不正な状態になる
 * - 以後の操作で undefined behavior
 * 
 * 対策：
 * - 先に新しいリソース作成、成功後に古いリソース削除
 * - Copy-and-Swap idiom による強い例外安全性
 * - RAII パターンの徹底
 * 
 * 【ミス4：メモリリークの発生】
 * 
 * 間違い例：
 * ```cpp
 * ~Animal() {
 *     // delete brain; を忘れる
 * }
 * ```
 * 
 * 問題：
 * - Brain オブジェクトが削除されない
 * - メモリリークの発生
 * - 長時間実行でのメモリ枯渇
 * 
 * 対策：
 * - デストラクタでの確実なリソース解放
 * - スマートポインタの活用検討
 * - メモリリーク検出ツールによる確認
 */