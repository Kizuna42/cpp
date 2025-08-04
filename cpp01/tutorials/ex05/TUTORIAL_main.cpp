/*
 * ====================================================================
 * CPP01 ex05: Harl - メンバ関数ポインタ実践解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - Harl クラスの実用的な使用方法
 * - メンバ関数ポインタの動作確認
 * - 様々なログレベルでのテスト
 * - 無効な入力に対するエラーハンドリング
 * - 関数ポインタシステムの理解
 * 
 * 【重要概念】
 * - 動的な関数呼び出しの実際
 * - 文字列による関数選択の仕組み
 * - ログシステムの階層的設計
 * - エラーケースの適切な処理
 */

#include "Harl.hpp"

/*
 * ====================================================================
 * main関数解説
 * ====================================================================
 */
int main(void) {
    /*
     * 【プログラムの目的】
     * 
     * Harl クラスのメンバ関数ポインタシステムをテスト：
     * 1. 各ログレベルの正常動作確認
     * 2. 無効なレベル指定時の動作確認
     * 3. メンバ関数ポインタの動作原理確認
     * 4. ログシステムとしての実用性評価
     * 
     * 【学習のポイント】
     * - オブジェクト作成と使用方法
     * - 文字列指定による関数呼び出し
     * - エラーケースでの動作確認
     * - ログレベルの階層的な意味理解
     */
    
    /*
     * ====================================================================
     * セクション1: Harl オブジェクトの作成
     * ====================================================================
     */
    
    /*
     * 【Harl インスタンスの作成】
     * 
     * Harl harl;
     * 
     * 内部で起こること：
     * 1. Harl のデフォルトコンストラクタが呼ばれる
     * 2. 初期化処理が実行される（ログ出力等）
     * 3. メンバ関数ポインタ配列は complain() 内で動的に作成
     */
    Harl harl;
    
    std::cout << "=== Harl Complaint System Test ===" << std::endl;
    std::cout << "Testing all log levels with member function pointers" << std::endl;
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * セクション2: 各ログレベルのテスト
     * ====================================================================
     */
    
    /*
     * 【DEBUG レベルのテスト】
     * 
     * harl.complain("DEBUG");
     * 
     * 内部処理フロー：
     * 1. complain("DEBUG") メソッド呼び出し
     * 2. メンバ関数ポインタ配列の作成
     * 3. "DEBUG" 文字列の検索
     * 4. 対応する &Harl::debug の呼び出し
     * 5. (this->*functions[0])() による間接呼び出し
     * 6. debug() メソッドの実行
     */
    std::cout << "=== DEBUG Level ===" << std::endl;
    harl.complain("DEBUG");
    std::cout << std::endl;
    
    /*
     * 期待される出力例：
     * "[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
     * 
     * 【メンバ関数ポインタの動作】
     * 
     * 配列内での対応：
     * functions[0] = &Harl::debug
     * levels[0] = "DEBUG"
     * 
     * 呼び出し：
     * (this->*functions[0])() → this->debug()
     */
    
    /*
     * 【INFO レベルのテスト】
     * 
     * 一般的な情報レベルのログ出力確認
     */
    std::cout << "=== INFO Level ===" << std::endl;
    harl.complain("INFO");
    std::cout << std::endl;
    
    /*
     * 期待される出力例：
     * "[INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"
     * 
     * 【配列インデックスの対応】
     * functions[1] = &Harl::info
     * levels[1] = "INFO"
     */
    
    /*
     * 【WARNING レベルのテスト】
     * 
     * 警告レベルのログ出力確認
     */
    std::cout << "=== WARNING Level ===" << std::endl;
    harl.complain("WARNING");
    std::cout << std::endl;
    
    /*
     * 期待される出力例：
     * "[WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month."
     * 
     * 【メンバ関数ポインタ配列での対応】
     * functions[2] = &Harl::warning
     * levels[2] = "WARNING"
     */
    
    /*
     * 【ERROR レベルのテスト】
     * 
     * 最高重要度レベルのログ出力確認
     */
    std::cout << "=== ERROR Level ===" << std::endl;
    harl.complain("ERROR");
    std::cout << std::endl;
    
    /*
     * 期待される出力例：
     * "[ERROR] This is unacceptable! I want to speak to the manager now."
     * 
     * 【最後の配列要素】
     * functions[3] = &Harl::error
     * levels[3] = "ERROR"
     */
    
    /*
     * ====================================================================
     * セクション3: エラーケースのテスト
     * ====================================================================
     */
    
    std::cout << "=== Error Cases Testing ===" << std::endl;
    
    /*
     * 【無効なレベル名のテスト】
     * 
     * harl.complain("INVALID");
     * 
     * 内部処理：
     * 1. 配列内で "INVALID" を検索
     * 2. 全ての levels[i] と比較
     * 3. 一致するものが見つからない
     * 4. ループ終了後、エラーメッセージ出力
     */
    std::cout << "Testing invalid level:" << std::endl;
    harl.complain("INVALID");
    std::cout << std::endl;
    
    /*
     * 期待される出力：
     * "Invalid level: INVALID" または類似のエラーメッセージ
     */
    
    /*
     * 【大文字小文字の区別テスト】
     * 
     * 通常、ログレベルは大文字で統一されているため、
     * 小文字での指定は無効として扱われる
     */
    std::cout << "Testing case sensitivity:" << std::endl;
    harl.complain("debug");  // 小文字での指定
    std::cout << std::endl;
    
    /*
     * 【空文字列のテスト】
     */
    std::cout << "Testing empty string:" << std::endl;
    harl.complain("");
    std::cout << std::endl;
    
    /*
     * 【部分一致のテスト】
     */
    std::cout << "Testing partial match:" << std::endl;
    harl.complain("DEBU");  // "DEBUG" の部分文字列
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * セクション4: 連続実行のテスト
     * ====================================================================
     */
    
    std::cout << "=== Continuous Execution Test ===" << std::endl;
    
    /*
     * 【複数回の連続呼び出し】
     * 
     * 同じオブジェクトで複数のレベルを連続実行：
     * - メンバ関数ポインタ配列は毎回再作成される
     * - オブジェクトの状態は保持される
     * - 関数呼び出しの独立性を確認
     */
    std::string levels[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    
    std::cout << "Executing all levels in reverse order:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "Level " << (i + 1) << ": ";
        harl.complain(levels[i]);
    }
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * セクション5: パフォーマンステスト
     * ====================================================================
     */
    
    std::cout << "=== Performance Test ===" << std::endl;
    
    /*
     * 【大量呼び出しテスト】
     * 
     * メンバ関数ポインタシステムの性能確認：
     * - 毎回の配列作成コスト
     * - 線形検索の性能
     * - 関数呼び出しオーバーヘッド
     */
    const int iterations = 1000;
    
    std::cout << "Performing " << iterations << " DEBUG calls..." << std::endl;
    
    /*
     * 簡易的な時間測定（デモ用）
     * 実際の測定には <ctime> や <chrono> を使用
     */
    for (int i = 0; i < iterations; i++) {
        harl.complain("DEBUG");
        if (i % 100 == 0) {
            std::cout << "." << std::flush;
        }
    }
    std::cout << " Done!" << std::endl;
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * セクション6: 異なるオブジェクトでのテスト
     * ====================================================================
     */
    
    std::cout << "=== Multiple Objects Test ===" << std::endl;
    
    /*
     * 【複数のHarlオブジェクト】
     * 
     * 異なるインスタンスでの独立性確認：
     * - 各オブジェクトが独立してメソッドを実行
     * - thisポインタが正しく使用される
     * - メンバ関数ポインタが適切に動作
     */
    Harl harl1, harl2, harl3;
    
    std::cout << "Three different Harl objects complaining:" << std::endl;
    
    std::cout << "Harl 1: ";
    harl1.complain("DEBUG");
    
    std::cout << "Harl 2: ";
    harl2.complain("INFO");
    
    std::cout << "Harl 3: ";
    harl3.complain("ERROR");
    
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * プログラム終了
     * ====================================================================
     */
    
    std::cout << "=== Test Completed ===" << std::endl;
    std::cout << "All Harl objects will be destroyed now." << std::endl;
    
    return 0;
    
    /*
     * 【オブジェクトの自動破棄】
     * 
     * return 文の実行後：
     * 1. harl3, harl2, harl1, harl の順でデストラクタ呼び出し
     * 2. 各デストラクタでログ出力（実装に依存）
     * 3. RAII による自動リソース管理
     * 4. プログラム正常終了（戻り値 0）
     */
}

/*
 * ====================================================================
 * 期待される出力例
 * ====================================================================
 * 
 * プログラム実行時の予想出力：
 * 
 * Harl instance created
 * === Harl Complaint System Test ===
 * Testing all log levels with member function pointers
 * 
 * === DEBUG Level ===
 * [DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!
 * 
 * === INFO Level ===
 * [INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
 * 
 * === WARNING Level ===
 * [WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.
 * 
 * === ERROR Level ===
 * [ERROR] This is unacceptable! I want to speak to the manager now.
 * 
 * === Error Cases Testing ===
 * Testing invalid level:
 * Invalid level: INVALID
 * 
 * Testing case sensitivity:
 * Invalid level: debug
 * 
 * Testing empty string:
 * Invalid level: 
 * 
 * Testing partial match:
 * Invalid level: DEBU
 * 
 * === Continuous Execution Test ===
 * Executing all levels in reverse order:
 * Level 1: [ERROR] This is unacceptable! I want to speak to the manager now.
 * Level 2: [WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.
 * Level 3: [INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
 * Level 4: [DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!
 * 
 * === Performance Test ===
 * Performing 1000 DEBUG calls...
 * .......... Done!
 * 
 * === Multiple Objects Test ===
 * Harl instance created
 * Harl instance created
 * Harl instance created
 * Three different Harl objects complaining:
 * Harl 1: [DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!
 * Harl 2: [INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
 * Harl 3: [ERROR] This is unacceptable! I want to speak to the manager now.
 * 
 * === Test Completed ===
 * All Harl objects will be destroyed now.
 * Harl instance destroyed
 * Harl instance destroyed
 * Harl instance destroyed
 * Harl instance destroyed
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この main 関数で確認すべき項目：
 * 
 * □ Harl オブジェクトの作成と使用
 * □ 各ログレベルの正常動作
 * □ メンバ関数ポインタによる動的呼び出し
 * □ 無効な入力に対するエラーハンドリング
 * □ 大文字小文字の区別
 * □ 連続実行での動作確認
 * □ 複数オブジェクトでの独立性
 * □ パフォーマンス特性の理解
 * □ RAII によるオブジェクト管理
 * 
 * 【実習課題】
 * 1. 新しいログレベル（FATAL）の追加
 * 2. 大文字小文字を無視する改良版実装
 * 3. ログレベルの数値化と比較機能
 * 4. ファイル出力機能の追加
 * 5. タイムスタンプ付きログの実装
 */

/*
 * ====================================================================
 * よくある実行時の問題と対策
 * ====================================================================
 * 
 * 【問題1】期待されるメッセージが出力されない
 * 
 * 原因：
 * - Harl.cpp の実装が不完全
 * - メンバ関数ポインタの配列初期化ミス
 * - 文字列比較の問題
 * 
 * 対策：
 * - 各 private メンバ関数の実装確認
 * - complain() メソッドの配列初期化確認
 * - デバッグ出力で関数が呼ばれているか確認
 * 
 * 【問題2】無効なレベルでクラッシュ
 * 
 * 原因：
 * - エラーハンドリングの不備
 * - 配列外アクセス
 * - NULL ポインタ呼び出し
 * 
 * 対策：
 * - レベル検索ループの境界チェック
 * - 無効レベル時の適切な処理実装
 * - 防御的プログラミングの実践
 * 
 * 【問題3】メンバ関数ポインタのコンパイルエラー
 * 
 * 原因：
 * - 構文ミス（void (Harl::*)(void) の書き方）
 * - 関数アドレス取得ミス（&Harl::debug）
 * - 呼び出し構文ミス（(this->*ptr)()）
 * 
 * 対策：
 * - 構文の正確な理解と実装
 * - コンパイラエラーメッセージの詳細確認
 * - 段階的な実装とテスト
 * 
 * 【問題4】パフォーマンスの問題
 * 
 * 原因：
 * - 毎回の配列作成オーバーヘッド
 * - 線形検索の非効率性
 * - 不必要なオブジェクト作成
 * 
 * 対策：
 * - static 配列の使用検討
 * - より効率的な検索アルゴリズム
 * - プロファイリングによる最適化
 */

/*
 * ====================================================================
 * 発展的な改良提案
 * ====================================================================
 * 
 * 【改良1：設定可能なログレベル】
 * ```cpp
 * class ConfigurableHarl {
 * private:
 *     LogLevel minLevel;
 * 
 * public:
 *     void setMinLevel(LogLevel level) { minLevel = level; }
 * 
 *     void complain(std::string level) {
 *         LogLevel currentLevel = stringToLevel(level);
 *         if (currentLevel >= minLevel) {
 *             // 通常の処理実行
 *         }
 *     }
 * };
 * ```
 * 
 * 【改良2：ログファイル出力】
 * ```cpp
 * class FileHarl : public Harl {
 * private:
 *     std::ofstream logFile;
 * 
 * public:
 *     FileHarl(const std::string& filename) : logFile(filename) {}
 * 
 *     void complain(std::string level) override {
 *         // コンソール出力
 *         Harl::complain(level);
 *         
 *         // ファイル出力
 *         logFile << "[" << getCurrentTime() << "] " 
 *                 << level << ": " << getMessage(level) << std::endl;
 *     }
 * };
 * ```
 * 
 * 【改良3：マルチスレッド対応】
 * ```cpp
 * #include <mutex>
 * 
 * class ThreadSafeHarl {
 * private:
 *     mutable std::mutex logMutex;
 * 
 * public:
 *     void complain(std::string level) {
 *         std::lock_guard<std::mutex> lock(logMutex);
 *         // 通常の処理（スレッドセーフ）
 *     }
 * };
 * ```
 * 
 * 【改良4：構造化ログ】
 * ```cpp
 * struct LogEntry {
 *     std::string timestamp;
 *     std::string level;
 *     std::string message;
 *     std::string source;
 * };
 * 
 * class StructuredHarl {
 * public:
 *     void complain(std::string level, const std::string& source = "") {
 *         LogEntry entry;
 *         entry.timestamp = getCurrentTime();
 *         entry.level = level;
 *         entry.message = getMessage(level);
 *         entry.source = source;
 *         
 *         outputLogEntry(entry);
 *     }
 * };
 * ```
 */