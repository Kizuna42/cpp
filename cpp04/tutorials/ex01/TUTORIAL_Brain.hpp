/*
 * ====================================================================
 * CPP04 ex01: 深いコピーとリソース管理 - Brainクラスヘッダー解説版
 * ====================================================================
 * 
 * この演習では、C++で最も重要な概念の一つ「深いコピー」を学習します。
 * 
 * 【学習目標】
 * - 浅いコピー vs 深いコピーの違い
 * - 配列を含むクラスの正しいコピー実装
 * - Orthodox Canonical Form の実用的応用
 * - メモリ安全性の確保
 * 
 * Brainクラスはこれらの概念を学ぶ理想的な例です。
 */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

/*
 * ====================================================================
 * 深いコピーが必要な理由
 * ====================================================================
 * 
 * 【問題の背景】
 * 
 * デフォルトのコピー動作（浅いコピー）:
 * - メンバ変数をそのままコピー
 * - ポインタの場合、アドレスのみコピー
 * - 配列の場合、各要素を個別にコピー（実は深いコピー）
 * 
 * 【Brainクラスでの状況】
 * ideas[100] という配列を持つ
 * → デフォルトコピーでも配列の各要素はコピーされる
 * → しかし、明示的な実装で学習価値を高める
 * 
 * 【将来の拡張性】
 * ideas が std::string* になった場合:
 * → 浅いコピーではポインタのみコピー
 * → 深いコピーの実装が必須になる
 */

/*
 * ====================================================================
 * Brain クラス - 思考を管理するクラス
 * ====================================================================
 * 
 * 【設計コンセプト】
 * Animal（動物）が持つ「脳」を表現
 * 100個のアイデア（思考）を保持
 * 
 * 【なぜ100個？】
 * 1. 配列操作の学習に適したサイズ
 * 2. メモリ管理の重要性を実感できる量
 * 3. ループ処理の実装練習
 * 
 * 【実用的な応用例】
 * - ゲームのNPCの行動パターン
 * - AI システムの記憶機構
 * - データベースのレコード管理
 */
class Brain {
private:
    /*
     * static const int IDEA_COUNT = 100;
     * 
     * 【定数定義の設計原則】
     * 
     * なぜ static const？
     * - static: 全てのBrainインスタンスで共有
     * - const: 実行中に変更不可
     * - int: 配列サイズとして使用可能
     * 
     * なぜマジックナンバーを避ける？
     * - 保守性: 値を変更する場合、1箇所だけ修正
     * - 可読性: IDEA_COUNT という名前で意図が明確
     * - エラー防止: typo による間違った値の使用を防ぐ
     * 
     * 【代替実装】
     * C++11以降なら constexpr も使用可能:
     * static constexpr int IDEA_COUNT = 100;
     * 
     * しかし C++98 では static const が標準
     */
    static const int IDEA_COUNT = 100;
    
    /*
     * std::string ideas[IDEA_COUNT];
     * 
     * 【配列 vs 動的配列 vs コンテナ】
     * 
     * 現在の実装: 固定サイズ配列
     * 利点:
     * - シンプルな実装
     * - スタック上に確保
     * - 自動的なメモリ管理
     * 
     * 欠点:
     * - サイズ変更不可
     * - 大きなオブジェクトサイズ
     * 
     * 【代替案1: 動的配列】
     * std::string* ideas;
     * 
     * 利点: 実行時サイズ決定可能
     * 欠点: 手動メモリ管理が必要
     * 
     * 【代替案2: コンテナ使用】
     * std::vector<std::string> ideas;
     * 
     * 利点: 自動メモリ管理 + 可変サイズ
     * 欠点: CPP04では STL 使用制限
     * 
     * 【学習価値】
     * 固定配列での実装により:
     * - 配列コピーの仕組み理解
     * - メモリレイアウトの理解
     * - インデックス管理の重要性理解
     */
    std::string ideas[IDEA_COUNT];

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form - 深いコピーの実装
     * ====================================================================
     * 
     * 配列を含むクラスでは OCF の正しい実装が重要
     * 特にコピーコンストラクタと代入演算子
     */
    
    /*
     * Brain(void);
     * 
     * デフォルトコンストラクタ
     * 
     * 【初期化戦略】
     * 全ての ideas を "Empty idea" で初期化
     * 
     * なぜ初期化が必要？
     * - 未初期化状態の回避
     * - 予測可能な動作の保証
     * - デバッグ時の分かりやすさ
     * 
     * 【初期化方法の選択肢】
     * 1. "Empty idea" (採用)
     * 2. "" (空文字列)
     * 3. 個別の初期値
     * 4. ランダムな内容
     * 
     * "Empty idea" を選択した理由:
     * - 初期化済みであることが明確
     * - デバッグ時に識別しやすい
     * - 意味のある文字列
     */
    Brain(void);
    
    /*
     * Brain(const Brain& other);
     * 
     * コピーコンストラクタ - 深いコピーの実装
     * 
     * 【深いコピーの要件】
     * 配列の各要素を個別にコピー
     * 
     * 実装方針:
     * for (int i = 0; i < IDEA_COUNT; i++) {
     *     this->ideas[i] = other.ideas[i];
     * }
     * 
     * 【なぜ代入演算子を再利用？】
     * *this = other;
     * 
     * 利点:
     * - コードの重複排除 (DRY原則)
     * - 保守性の向上
     * - バグの一元管理
     * 
     * 欠点:
     * - わずかなパフォーマンスオーバーヘッド
     * - 自己代入チェックの無駄実行
     * 
     * 【実装パターンの比較】
     * パターン1: 代入演算子使用 (採用)
     * パターン2: 直接実装
     * 
     * 学習段階では分かりやすさを重視してパターン1を採用
     */
    Brain(const Brain& other);
    
    /*
     * Brain& operator=(const Brain& other);
     * 
     * 代入演算子 - 深いコピーの核心
     * 
     * 【配列の代入処理】
     * 配列全体を一度にコピーすることはできない
     * 各要素を個別にコピーする必要がある
     * 
     * 【自己代入の重要性】
     * brain1 = brain1; のような場合の処理
     * 
     * 配列の場合は問題が起きにくいが、
     * 動的メモリの場合は致命的エラーの原因
     * 一貫したチェックの実装が重要
     * 
     * 【戻り値の設計】
     * Brain& を返すことで連鎖代入を可能にする
     * brain1 = brain2 = brain3;
     */
    Brain& operator=(const Brain& other);
    
    /*
     * ~Brain(void);
     * 
     * デストラクタ
     * 
     * 【現在の実装】
     * 特別なクリーンアップ処理は不要
     * std::string の配列は自動的に破棄される
     * 
     * 【デバッグ出力の価値】
     * オブジェクトの生存期間を可視化
     * メモリリークの検出支援
     * 
     * 【将来の拡張】
     * 動的メモリ使用時は delete[] が必要
     * ファイルハンドル等があれば close() が必要
     */
    ~Brain(void);
    
    /*
     * ====================================================================
     * パブリックインターフェース - 安全なアクセス方法
     * ====================================================================
     */
    
    /*
     * void setIdea(int index, const std::string& idea);
     * 
     * 【安全なセッター】
     * 
     * インデックス境界チェック:
     * if (index >= 0 && index < IDEA_COUNT)
     * 
     * なぜ境界チェックが重要？
     * - バッファオーバーフロー防止
     * - セキュリティ脆弱性の回避
     * - プログラムクラッシュの防止
     * 
     * 【パラメータ設計】
     * const std::string& idea:
     * - const: 関数内でパラメータを変更しない
     * - &: 参照渡しで効率化（コピー回避）
     * 
     * 【エラーハンドリング】
     * 現在: 無効なインデックスは無視
     * 代替案:
     * - 例外を投げる
     * - エラーフラグを返す
     * - std::cerr でエラーメッセージ
     * 
     * 学習段階では簡潔性を重視
     */
    void setIdea(int index, const std::string& idea);
    
    /*
     * std::string getIdea(int index) const;
     * 
     * 【安全なゲッター】
     * 
     * const修飾:
     * - オブジェクトの状態を変更しない
     * - const Brain からも呼び出し可能
     * 
     * 【戻り値の設計判断】
     * std::string を値で返す理由:
     * - 呼び出し元が自由に変更可能
     * - 元の配列要素への影響なし
     * - 安全性を重視
     * 
     * 代替案: const std::string& を返す
     * 利点: 効率的（コピー不要）
     * 欠点: 呼び出し元で変更リスク
     * 
     * 【エラーハンドリング】
     * 無効なインデックスに対して "Invalid index" を返す
     * 呼び出し元でエラーかどうかを判断可能
     */
    std::string getIdea(int index) const;
    
    /*
     * void printIdeas(int count = 5) const;
     * 
     * 【デバッグ支援メソッド】
     * 
     * デフォルト引数:
     * count = 5 により、引数省略時は最初の5個を表示
     * 
     * 【使用場面】
     * - 開発中のデバッグ
     * - テスト時の状態確認
     * - デモンストレーション
     * 
     * 【実装の工夫】
     * count の上限チェック:
     * if (count > IDEA_COUNT) count = IDEA_COUNT;
     * 
     * これにより、無効な範囲のアクセスを防ぐ
     * 
     * 【出力フォーマット】
     * "  Idea 0: Empty idea"
     * "  Idea 1: Empty idea"
     * ...
     * 
     * インデックスを表示することで、
     * どの位置にどんなアイデアがあるかを明確化
     */
    void printIdeas(int count = 5) const;  // Print first 'count' ideas
};

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このヘッダーから学ぶべきこと】
 * 
 * 1. 深いコピーの必要性
 *    - 配列やポインタを含むクラスでの重要性
 *    - デフォルトコピーの限界
 *    - 明示的実装の価値
 * 
 * 2. 配列の安全な管理
 *    - 境界チェックの重要性
 *    - const correctness の実践
 *    - エラーハンドリングの考慮
 * 
 * 3. OCF の実用的応用
 *    - 配列を含むクラスでの実装
 *    - コード再利用の技法
 *    - 保守性とパフォーマンスのバランス
 * 
 * 4. インターフェース設計
 *    - 安全なアクセス方法の提供
 *    - デバッグ支援機能の実装
 *    - 使いやすさと安全性の両立
 * 
 * 【次のステップ】
 * - TUTORIAL_Brain.cpp で実装詳細を学習
 * - Animal クラスでの Brain 使用例を確認
 * - 動的メモリ版の実装を検討
 */

#endif

/*
 * ====================================================================
 * 深いコピー vs 浅いコピーの比較
 * ====================================================================
 * 
 * 【浅いコピー（デフォルト動作）】
 * 
 * struct SimpleData {
 *     int value;
 *     char* ptr;
 * };
 * 
 * SimpleData a, b;
 * a.value = 10;
 * a.ptr = new char[100];
 * b = a;  // 浅いコピー
 * 
 * 結果:
 * - b.value = 10 (正しくコピー)
 * - b.ptr = a.ptr (同じアドレス！)
 * 
 * 問題:
 * delete[] a.ptr; の後、b.ptr は無効
 * 
 * 【深いコピー（明示的実装）】
 * 
 * class SafeData {
 *     int value;
 *     char* ptr;
 * public:
 *     SafeData& operator=(const SafeData& other) {
 *         if (this != &other) {
 *             delete[] ptr;  // 既存データ削除
 *             ptr = new char[100];  // 新しい領域確保
 *             memcpy(ptr, other.ptr, 100);  // データコピー
 *             value = other.value;
 *         }
 *         return *this;
 *     }
 * };
 * 
 * 結果: 各オブジェクトが独立したデータを持つ
 * 
 * 【Brainクラスでの状況】
 * std::string 配列の場合、各 std::string は
 * 内部で動的メモリを管理するため、
 * 配列要素のコピーでも深いコピーが実現される
 */

/*
 * ====================================================================
 * メモリ安全性の考慮
 * ====================================================================
 * 
 * 【現在の実装の安全性】
 * 
 * 利点:
 * - スタック上の配列使用
 * - 自動的なメモリ管理
 * - バッファオーバーフロー対策
 * 
 * 潜在的リスク:
 * - 大きなスタック使用量
 * - 固定サイズの制限
 * 
 * 【より安全な動的メモリ版】
 * 
 * class SafeBrain {
 *     std::string* ideas;
 *     int size;
 * 
 * public:
 *     SafeBrain(int count) : size(count), ideas(new std::string[count]) {}
 *     
 *     ~SafeBrain() {
 *         delete[] ideas;
 *     }
 *     
 *     SafeBrain(const SafeBrain& other) : size(other.size) {
 *         ideas = new std::string[size];
 *         for (int i = 0; i < size; i++) {
 *             ideas[i] = other.ideas[i];
 *         }
 *     }
 *     
 *     SafeBrain& operator=(const SafeBrain& other) {
 *         if (this != &other) {
 *             delete[] ideas;
 *             size = other.size;
 *             ideas = new std::string[size];
 *             for (int i = 0; i < size; i++) {
 *                 ideas[i] = other.ideas[i];
 *             }
 *         }
 *         return *this;
 *     }
 * };
 * 
 * この実装では深いコピーの重要性がより明確になる
 */

/*
 * ====================================================================
 * 実用的な応用例
 * ====================================================================
 * 
 * 【ゲーム開発での応用】
 * 
 * class NPCBrain {
 *     std::string behaviors[50];
 *     std::string memories[100];
 *     
 * public:
 *     void addMemory(const std::string& event);
 *     std::string decideBehavior(const std::string& situation);
 *     NPCBrain clone() const;  // 深いコピーでNPC複製
 * };
 * 
 * 【データベース設計での応用】
 * 
 * class Record {
 *     std::string fields[20];
 *     
 * public:
 *     Record backup() const;  // 深いコピーでバックアップ
 *     void restore(const Record& backup);
 *     bool isModified(const Record& original) const;
 * };
 * 
 * 【AI システムでの応用】
 * 
 * class KnowledgeBase {
 *     std::string facts[1000];
 *     
 * public:
 *     KnowledgeBase learn(const KnowledgeBase& other) const;
 *     void merge(const KnowledgeBase& other);
 *     KnowledgeBase subspecialize(const std::string& domain) const;
 * };
 * 
 * これらの例では、深いコピーによる独立したデータ管理が重要
 */