/*
 * ====================================================================
 * CPP04 ex01: 深いコピーとリソース管理 - Brain実装解説版
 * ====================================================================
 * 
 * この実装では、深いコピーの実際のコード実装を学習します。
 * - 配列の要素ごとコピー
 * - 境界チェックの実装
 * - 効率的なループ処理
 * - デバッグ支援機能
 */

#include "Brain.hpp"

/*
 * ====================================================================
 * デフォルトコンストラクタ - 配列の初期化
 * ====================================================================
 * 
 * Brain::Brain(void) {
 *     std::cout << "Brain constructor called" << std::endl;
 *     for (int i = 0; i < IDEA_COUNT; i++) {
 *         this->ideas[i] = "Empty idea";
 *     }
 * }
 * 
 * 【配列初期化の戦略】
 * 
 * なぜループで初期化？
 * C++98では配列の一括初期化が限定的
 * 
 * 【代替初期化方法】
 * 
 * 方法1: 初期化リスト（C++11以降）
 * std::string ideas[3] = {"idea1", "idea2", "idea3"};
 * → 100個では非現実的
 * 
 * 方法2: memset使用
 * memset(ideas, 0, sizeof(ideas));
 * → std::string には不適切（オブジェクトが破壊される）
 * 
 * 方法3: std::fill使用（STL）
 * std::fill(ideas, ideas + IDEA_COUNT, "Empty idea");
 * → CPP04では STL 制限により使用不可
 * 
 * 方法4: ループ初期化（採用）
 * → 最も確実で理解しやすい
 */
Brain::Brain(void) {
    /*
     * デバッグ出力
     * 
     * オブジェクトの生成を可視化
     * - Animal の作成時に Brain も作成されることを確認
     * - メモリリークの検出支援
     * - 初期化順序の確認
     */
    std::cout << "Brain constructor called" << std::endl;
    
    /*
     * 配列の全要素初期化
     * 
     * for (int i = 0; i < IDEA_COUNT; i++) {
     *     this->ideas[i] = "Empty idea";
     * }
     * 
     * 【ループの詳細分析】
     * 
     * 初期化: int i = 0
     * - ループカウンターの初期値
     * - 配列の最初のインデックス
     * 
     * 条件: i < IDEA_COUNT
     * - 境界チェック
     * - IDEA_COUNT = 100 なので、0～99 をループ
     * 
     * 更新: i++
     * - 次のインデックスに進む
     * - 後置インクリメント（前置でも可）
     * 
     * 【this-> の使用意図】
     * 技術的には不要だが明示性のため使用
     * - メンバ変数であることを明確化
     * - ローカル変数との区別
     * - コーディングスタイルの一貫性
     * 
     * 【初期値選択の理由】
     * "Empty idea" を選択:
     * - 初期化済みであることが明確
     * - デバッグ時に識別しやすい
     * - 空文字列 "" より意味がある
     * - nullptr や未初期化状態を避ける
     */
    for (int i = 0; i < IDEA_COUNT; i++) {
        this->ideas[i] = "Empty idea";
    }
}

/*
 * ====================================================================
 * コピーコンストラクタ - 深いコピーの実装パターン
 * ====================================================================
 * 
 * Brain::Brain(const Brain& other) {
 *     std::cout << "Brain copy constructor called" << std::endl;
 *     *this = other;
 * }
 * 
 * 【代入演算子再利用パターン】
 * 
 * 利点:
 * 1. DRY原則（Don't Repeat Yourself）
 * 2. コピーロジックの一元化
 * 3. 保守性の向上
 * 4. バグの一元管理
 * 
 * 欠点:
 * 1. わずかなパフォーマンスオーバーヘッド
 * 2. 自己代入チェックの無駄実行
 * 3. 初期化リストが使用不可
 * 
 * 【代替実装パターン】
 * 
 * 直接実装版:
 * Brain::Brain(const Brain& other) {
 *     std::cout << "Brain copy constructor called" << std::endl;
 *     for (int i = 0; i < IDEA_COUNT; i++) {
 *         this->ideas[i] = other.ideas[i];
 *     }
 * }
 * 
 * より効率的だが、コードが重複する
 * 
 * 【実行フロー】
 * 1. コピーコンストラクタが呼ばれる
 * 2. デバッグメッセージ出力
 * 3. *this = other; で代入演算子呼び出し
 * 4. 代入演算子内でデバッグメッセージ出力
 * 5. 配列のコピー実行
 * 
 * 結果として2つのデバッグメッセージが出力される
 */
Brain::Brain(const Brain& other) {
    /*
     * コピーコンストラクタのデバッグ出力
     * 
     * 代入演算子とは異なるメッセージで区別
     * どちらが呼ばれたかを明確に識別可能
     */
    std::cout << "Brain copy constructor called" << std::endl;
    
    /*
     * 代入演算子を利用したコピー処理
     * 
     * *this = other;
     * 
     * この1行で以下が実行される:
     * 1. operator=(const Brain& other) の呼び出し
     * 2. 自己代入チェック（必ず false）
     * 3. 配列の全要素コピー
     * 4. *this の返却（ここでは使用されない）
     * 
     * 【なぜ自己代入チェックが false？】
     * コピーコンストラクタでは this と &other は
     * 常に異なるオブジェクト（新規作成中 vs 既存）
     */
    *this = other;
}

/*
 * ====================================================================
 * 代入演算子 - 深いコピーの核心実装
 * ====================================================================
 * 
 * Brain& Brain::operator=(const Brain& other) {
 *     std::cout << "Brain assignment operator called" << std::endl;
 *     if (this != &other) {
 *         for (int i = 0; i < IDEA_COUNT; i++) {
 *             this->ideas[i] = other.ideas[i];
 *         }
 *     }
 *     return *this;
 * }
 * 
 * 【深いコピーの実装詳細】
 * 
 * この実装が「深いコピー」である理由:
 * 各配列要素を個別にコピーしている
 * 
 * std::string のコピー動作:
 * ideas[i] = other.ideas[i]; で std::string の
 * operator= が呼ばれ、文字列内容がコピーされる
 * 
 * 【浅いコピーとの比較】
 * 
 * 浅いコピー（仮想例）:
 * memcpy(this, &other, sizeof(Brain));
 * → 危険：std::string の内部状態が破壊される
 * 
 * 正しい深いコピー（現在の実装）:
 * 各要素の operator= を使用
 * → 安全：各 std::string が適切にコピーされる
 */
Brain& Brain::operator=(const Brain& other) {
    /*
     * 代入演算子のデバッグ出力
     * 
     * コピーコンストラクタとは異なるメッセージ
     * どちらの経路でコピーが実行されたかを識別
     */
    std::cout << "Brain assignment operator called" << std::endl;
    
    /*
     * 自己代入チェック
     * 
     * if (this != &other) {
     * 
     * 【なぜ必要？】
     * 
     * 自己代入の例:
     * Brain brain;
     * brain = brain;  // この場合 this == &other
     * 
     * チェックなしで実行すると:
     * 1. パフォーマンスの無駄（同じ内容を再コピー）
     * 2. 将来の拡張で問題（動的メモリ使用時など）
     * 
     * 【動的メモリでの危険性（参考）】
     * delete[] ideas;  // 自分のデータを削除
     * ideas = new std::string[IDEA_COUNT];
     * for (...) ideas[i] = other.ideas[i];  // 削除済みデータにアクセス！
     * 
     * 現在の実装では問題ないが、一貫性のため実装
     */
    if (this != &other) {
        /*
         * 配列の要素ごとコピー
         * 
         * for (int i = 0; i < IDEA_COUNT; i++) {
         *     this->ideas[i] = other.ideas[i];
         * }
         * 
         * 【ループの効率性分析】
         * 
         * IDEA_COUNT = 100 なので 100回のループ
         * 各ループで std::string の operator= が実行
         * 
         * 【std::string::operator= の動作】
         * 1. 既存の文字列メモリ確認
         * 2. 必要に応じてメモリ再確保
         * 3. 文字列内容のコピー
         * 4. 適切な終端処理
         * 
         * 【最適化の可能性】
         * 
         * 現在: ideas[i] = other.ideas[i];
         * 代替: ideas[i].assign(other.ideas[i]);
         * → 同じ動作、可読性で現在の方法を選択
         * 
         * 【並列化の可能性（参考）】
         * C++11以降なら std::for_each + parallel execution
         * しかし、CPP04 では使用不可
         */
        for (int i = 0; i < IDEA_COUNT; i++) {
            this->ideas[i] = other.ideas[i];
        }
    }
    
    /*
     * 自身への参照を返す
     * 
     * return *this;
     * 
     * 【連鎖代入の実現】
     * brain1 = brain2 = brain3;
     * 
     * 実行順序:
     * 1. brain2 = brain3  → brain2& を返す
     * 2. brain1 = brain2  → 返された brain2 を使用
     * 
     * 【参照返しの重要性】
     * 値返し（Brain）では不効率
     * 参照返し（Brain&）で効率的
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタ - リソースの自動管理
 * ====================================================================
 * 
 * Brain::~Brain(void) {
 *     std::cout << "Brain destructor called" << std::endl;
 * }
 * 
 * 【現在の実装での処理】
 * 
 * 特別なクリーンアップは不要:
 * - std::string 配列は自動的に破棄される
 * - 各 std::string の destructor が自動実行
 * - スタック上のオブジェクトなので自動管理
 * 
 * 【デバッグ出力の価値】
 * 
 * 1. オブジェクトの生存期間確認
 * 2. メモリリークの検出
 * 3. デストラクタ呼び出し順序の確認
 * 4. Animal との関係性の理解
 * 
 * 【動的メモリ版での実装（参考）】
 * 
 * class DynamicBrain {
 *     std::string* ideas;
 * public:
 *     ~DynamicBrain() {
 *         delete[] ideas;  // 明示的な削除が必要
 *         std::cout << "DynamicBrain destructor called" << std::endl;
 *     }
 * };
 */
Brain::~Brain(void) {
    /*
     * デバッグ出力でデストラクタ呼び出しを可視化
     * 
     * Animal のデストラクタと組み合わせて見ることで、
     * 構築・破棄の順序を理解できる
     * 
     * 期待される出力順序例:
     * "Animal constructor called"
     * "Brain constructor called" 
     * ... (使用)
     * "Animal destructor called"
     * "Brain destructor called"
     */
    std::cout << "Brain destructor called" << std::endl;
}

/*
 * ====================================================================
 * setIdea() - 安全な要素設定
 * ====================================================================
 * 
 * void Brain::setIdea(int index, const std::string& idea) {
 *     if (index >= 0 && index < IDEA_COUNT) {
 *         this->ideas[index] = idea;
 *     }
 * }
 * 
 * 【境界チェックの実装】
 * 
 * 条件: index >= 0 && index < IDEA_COUNT
 * 
 * index >= 0:
 * - 負のインデックスを拒否
 * - C++ では負のインデックスは未定義動作
 * 
 * index < IDEA_COUNT:
 * - 配列サイズを超えたアクセスを拒否
 * - バッファオーバーフローを防止
 * 
 * 【エラーハンドリングの選択肢】
 * 
 * 現在の実装: 無視
 * - 簡潔で理解しやすい
 * - 学習段階に適している
 * 
 * 代替案1: 例外処理
 * if (index < 0 || index >= IDEA_COUNT) {
 *     throw std::out_of_range("Invalid index");
 * }
 * 
 * 代替案2: エラーメッセージ
 * if (index < 0 || index >= IDEA_COUNT) {
 *     std::cerr << "Invalid index: " << index << std::endl;
 *     return;
 * }
 * 
 * 代替案3: bool戻り値
 * bool setIdea(int index, const std::string& idea) {
 *     if (index >= 0 && index < IDEA_COUNT) {
 *         this->ideas[index] = idea;
 *         return true;
 *     }
 *     return false;
 * }
 */
void Brain::setIdea(int index, const std::string& idea) {
    /*
     * 境界チェック付きの要素設定
     * 
     * 安全性を重視した実装
     * 無効なインデックスは静かに無視
     */
    if (index >= 0 && index < IDEA_COUNT) {
        /*
         * 有効なインデックスの場合のみ設定
         * 
         * this->ideas[index] = idea;
         * 
         * std::string の代入演算子が呼ばれる:
         * - 既存文字列の適切な削除
         * - 新しい文字列内容のコピー
         * - メモリ管理の自動処理
         */
        this->ideas[index] = idea;
    }
    /*
     * else節がない = 無効なインデックスは無視
     * 
     * 実用アプリケーションでは、より明確な
     * エラーハンドリングが必要になる場合が多い
     */
}

/*
 * ====================================================================
 * getIdea() - 安全な要素取得
 * ====================================================================
 * 
 * std::string Brain::getIdea(int index) const {
 *     if (index >= 0 && index < IDEA_COUNT) {
 *         return this->ideas[index];
 *     }
 *     return "Invalid index";
 * }
 * 
 * 【const correctness の実践】
 * 
 * const修飾:
 * - このメソッドはオブジェクトの状態を変更しない
 * - const Brain オブジェクトからも呼び出し可能
 * - コンパイラによる最適化の手がかり
 * 
 * const Brain brain;
 * std::string idea = brain.getIdea(0);  // OK
 * 
 * 【戻り値設計の考慮】
 * 
 * 値返し vs 参照返し:
 * 
 * 現在: std::string (値返し)
 * 利点: 安全（元データへの影響なし）
 * 欠点: コピーコスト
 * 
 * 代替: const std::string& (参照返し)
 * 利点: 効率的
 * 欠点: エラー時の処理が複雑
 * 
 * 学習段階では安全性を重視して値返しを採用
 */
std::string Brain::getIdea(int index) const {
    /*
     * 境界チェック付きの要素取得
     */
    if (index >= 0 && index < IDEA_COUNT) {
        /*
         * 有効なインデックスの場合、要素を返す
         * 
         * return this->ideas[index];
         * 
         * std::string のコピーコンストラクタが呼ばれる:
         * - 新しい std::string オブジェクトが作成
         * - 元の文字列内容がコピーされる
         * - 呼び出し元で自由に変更可能
         */
        return this->ideas[index];
    }
    
    /*
     * 無効なインデックスの場合、エラーメッセージを返す
     * 
     * return "Invalid index";
     * 
     * 【エラー処理の工夫】
     * 固定メッセージを返すことで:
     * - 呼び出し元でエラーかどうかを判定可能
     * - プログラムのクラッシュを回避
     * - デバッグ時の問題特定が容易
     * 
     * 【より高度なエラー処理】
     * std::optional (C++17) や std::pair<bool, std::string>
     * を使用してエラー状態をより明確に表現することも可能
     */
    return "Invalid index";
}

/*
 * ====================================================================
 * printIdeas() - デバッグ支援機能
 * ====================================================================
 * 
 * void Brain::printIdeas(int count) const {
 *     if (count > IDEA_COUNT) count = IDEA_COUNT;
 *     for (int i = 0; i < count; i++) {
 *         std::cout << "  Idea " << i << ": " << this->ideas[i] << std::endl;
 *     }
 * }
 * 
 * 【デフォルト引数の活用】
 * 
 * ヘッダーで: printIdeas(int count = 5)
 * - count 省略時は 5個表示
 * - 明示指定で任意の個数表示可能
 * 
 * 使用例:
 * brain.printIdeas();     // 最初の5個
 * brain.printIdeas(10);   // 最初の10個
 * brain.printIdeas(100);  // 全て
 */
void Brain::printIdeas(int count) const {
    /*
     * 上限チェック
     * 
     * if (count > IDEA_COUNT) count = IDEA_COUNT;
     * 
     * 配列サイズを超えた要求の場合、
     * 自動的に最大値に制限
     * 
     * 例：printIdeas(1000) → 実際は100個表示
     */
    if (count > IDEA_COUNT) count = IDEA_COUNT;
    
    /*
     * 指定された個数だけ表示
     * 
     * for (int i = 0; i < count; i++) {
     *     std::cout << "  Idea " << i << ": " << this->ideas[i] << std::endl;
     * }
     * 
     * 【出力フォーマットの工夫】
     * 
     * "  Idea 0: Empty idea"
     * "  Idea 1: Empty idea"
     * ...
     * 
     * - インデント（"  "）で階層表現
     * - インデックス番号で位置を明確化
     * - コロン区切りで見やすさ向上
     * - std::endl で確実な改行とフラッシュ
     * 
     * 【デバッグでの活用】
     * - オブジェクトの内部状態確認
     * - テスト時の期待値検証
     * - デモンストレーション用表示
     */
    for (int i = 0; i < count; i++) {
        std::cout << "  Idea " << i << ": " << this->ideas[i] << std::endl;
    }
}

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このファイルから学ぶべきこと】
 * 
 * 1. 深いコピーの実装技法
 *    - 配列要素の個別コピー
 *    - 代入演算子の再利用パターン
 *    - 自己代入チェックの重要性
 * 
 * 2. 配列の安全な操作
 *    - 境界チェックの実装
 *    - インデックス検証の手法
 *    - エラーハンドリングの選択肢
 * 
 * 3. const correctness の実践
 *    - const メソッドの適切な使用
 *    - const 参照パラメータ
 *    - 読み取り専用操作の保証
 * 
 * 4. デバッグ支援機能
 *    - 状態可視化メソッド
 *    - 開発効率向上のツール
 *    - ユーザビリティの配慮
 * 
 * 【次のステップ】
 * - Animal クラスでの Brain 使用例
 * - ポリモーフィズムとの組み合わせ
 * - より複雑なリソース管理への応用
 */

/*
 * ====================================================================
 * よくある質問と回答
 * ====================================================================
 * 
 * Q: なぜ std::vector を使わないのか？
 * A: CPP04 では STL コンテナの使用が制限されているため。
 *    実用開発では std::vector が推奨される。
 * 
 * Q: 配列のサイズを動的に変更できないのか？
 * A: 固定配列では不可能。動的配列や std::vector なら可能。
 *    ただし、メモリ管理が複雑になる。
 * 
 * Q: printIdeas() でなぜ全要素を表示しないのか？
 * A: 100個の表示は通常不要で見づらい。
 *    デフォルトで適度な数に制限している。
 * 
 * Q: エラー時に例外を投げないのはなぜ？
 * A: 学習段階でのシンプルさを重視。
 *    実用アプリケーションでは例外処理も検討すべき。
 */

/*
 * ====================================================================
 * パフォーマンス分析
 * ====================================================================
 * 
 * 【現在の実装のパフォーマンス特性】
 * 
 * メモリ使用量:
 * - Brain 1個あたり: 100 × sizeof(std::string)
 * - 概算: 100 × 32 bytes = 3.2KB (処理系依存)
 * 
 * コピー時間:
 * - O(n) where n = IDEA_COUNT = 100
 * - 各文字列の長さにも依存
 * - 現実的な範囲では高速
 * 
 * 【最適化の可能性】
 * 
 * 1. 移動セマンティクス (C++11以降)
 * Brain(Brain&& other) noexcept {
 *     std::swap(ideas, other.ideas);
 * }
 * 
 * 2. Copy-on-Write (COW)
 * 複数オブジェクトで同じデータを共有
 * 変更時のみ実際にコピー
 * 
 * 3. 小文字列最適化 (SSO)
 * std::string の内部最適化を活用
 * 短い文字列はヒープを使わない
 * 
 * しかし、学習段階では理解しやすさを優先
 */

/*
 * ====================================================================
 * 実用的な拡張案
 * ====================================================================
 * 
 * 【機能拡張案】
 * 
 * 1. 検索機能
 * int findIdea(const std::string& searchTerm) const;
 * bool hasIdea(const std::string& idea) const;
 * 
 * 2. 統計機能
 * int getUsedSlots() const;  // "Empty idea" でない数
 * int getEmptySlots() const;
 * 
 * 3. 永続化機能
 * bool saveToFile(const std::string& filename) const;
 * bool loadFromFile(const std::string& filename);
 * 
 * 4. ランダムアクセス
 * std::string getRandomIdea() const;
 * void shuffleIdeas();
 * 
 * 【設計改善案】
 * 
 * 1. イテレータサポート
 * class const_iterator { ... };
 * const_iterator begin() const;
 * const_iterator end() const;
 * 
 * 2. 容量管理
 * void reserve(int newSize);
 * void shrinkToFit();
 * 
 * 3. 比較機能
 * bool operator==(const Brain& other) const;
 * bool operator!=(const Brain& other) const;
 * 
 * これらの機能は実用アプリケーションでよく求められる
 */