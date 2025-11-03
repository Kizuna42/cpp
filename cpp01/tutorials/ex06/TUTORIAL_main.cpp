/*
 * ====================================================================
 * CPP01 ex06: harlFilter - main関数とコマンドライン処理解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - コマンドライン引数の処理と検証
 * - 実用的なログフィルタリングシステムの使用
 * - switch文によるプログラム制御の実践
 * - エラーハンドリングとユーザビリティ
 * - レベルベースフィルタリングの体験
 * 
 * 【重要概念】
 * - argc/argv によるコマンドライン解析
 * - 引数検証とエラーメッセージ
 * - オブジェクト指向設計の実践的活用
 * - ログシステムの実用的な運用
 * - プログラムの終了コード管理
 */

#include "Harl.hpp"

/*
 * ====================================================================
 * main関数の実装と解説
 * ====================================================================
 */

/*
 * 【プログラムの目的】
 * 
 * harlFilter プログラム：
 * - コマンドライン引数でログレベルを指定
 * - 指定レベル以上のすべてのメッセージを出力
 * - switch文のfall-through機能を活用
 * - 実用的なログフィルタリングシステムのデモ
 * 
 * 使用方法：
 * ./harlFilter <level>
 * 
 * 有効なレベル：
 * - DEBUG: すべてのレベルを出力
 * - INFO: INFO, WARNING, ERROR を出力
 * - WARNING: WARNING, ERROR を出力
 * - ERROR: ERROR のみ出力
 * - その他: 特別なメッセージを出力
 */
int main(int argc, char* argv[]) {
    /*
     * 【プログラムの動作概要】
     * 
     * 処理フロー：
     * 1. コマンドライン引数の検証
     * 2. Harlオブジェクトの作成
     * 3. ログレベルフィルタリングの実行
     * 4. 結果の出力と終了
     * 
     * ex05との違い：
     * - ex05: 個別レベルの実行
     * - ex06: 階層的フィルタリング実行
     */
    
    /*
     * ====================================================================
     * コマンドライン引数の検証
     * ====================================================================
     */
    
    /*
     * 【引数数の確認】
     * 
     * argc != 2 の場合のエラー：
     * - argc[0]: プログラム名（自動設定）
     * - argc[1]: ログレベル（ユーザー指定）
     * 
     * 合計2個の引数が必要
     * 
     * エラー時の動作：
     * - 使用方法の表示
     * - エラー終了コード（1）で終了
     * - ユーザーへの適切なフィードバック
     */
    if (argc != 2) {
        /*
         * 【使用方法の表示】
         * 
         * ユーザビリティの考慮：
         * - 明確な使用方法の提示
         * - 有効なレベル一覧の表示
         * - エラーメッセージの親切さ
         */
        std::cout << "Usage: " << argv[0] << " <level>" << std::endl;
        std::cout << "Valid levels: DEBUG, INFO, WARNING, ERROR" << std::endl;
        
        /*
         * 【エラー終了】
         * 
         * return 1 の意味：
         * - 異常終了を示す終了コード
         * - シェルスクリプトでのエラー検出可能
         * - 標準的なエラーハンドリング
         */
        return 1;
    }
    
    /*
     * 【引数の取得】
     * 
     * char* から std::string への変換：
     * - C言語スタイル文字列からC++文字列オブジェクト
     * - より安全で豊富な文字列操作
     * - std::string のメソッド活用
     */
    std::string level = argv[1];
    
    /*
     * ====================================================================
     * Harl オブジェクトの作成と使用
     * ====================================================================
     */
    
    /*
     * 【Harl インスタンスの作成】
     * 
     * Harl harl;
     * 
     * 内部で起こること：
     * 1. Harl のデフォルトコンストラクタ呼び出し
     * 2. "Harl filter instance created" の出力
     * 3. オブジェクトの初期化完了
     * 
     * RAII パターン：
     * - コンストラクタでリソース取得
     * - デストラクタで自動解放
     * - 例外安全性の確保
     */
    Harl harl;
    
    /*
     * 【プログラムの開始通知】
     * 
     * ユーザーへの情報提供：
     * - プログラムの開始確認
     * - 指定されたレベルの表示
     * - 実行状況の透明性
     */
    std::cout << std::endl;
    std::cout << "=== Harl Filter System ===" << std::endl;
    std::cout << "Filtering with level: " << level << std::endl;
    std::cout << "Output (showing " << level << " and above):" << std::endl;
    std::cout << std::endl;
    
    /*
     * ====================================================================
     * フィルタリング処理の実行
     * ====================================================================
     */
    
    /*
     * 【complainFilter メソッドの呼び出し】
     * 
     * harl.complainFilter(level);
     * 
     * 内部処理フロー：
     * 1. stringToLevel() で文字列→enum変換
     * 2. switch文による分岐処理
     * 3. fall-throughによる階層的実行
     * 4. 指定レベル以上のメッセージ出力
     * 
     * 実行例（"WARNING" 指定時）：
     * - WARNING メッセージ出力
     * - ERROR メッセージ出力
     * - DEBUG, INFO はスキップ
     */
    harl.complainFilter(level);
    
    /*
     * ====================================================================
     * プログラム終了処理
     * ====================================================================
     */
    
    /*
     * 【処理完了の通知】
     * 
     * ユーザーへのフィードバック：
     * - フィルタリング処理の完了確認
     * - プログラムの正常終了通知
     * - 視覚的な区切り提供
     */
    std::cout << std::endl;
    std::cout << "=== Filtering Complete ===" << std::endl;
    
    /*
     * 【正常終了】
     * 
     * return 0 の意味：
     * - 正常終了を示す終了コード
     * - システムへの成功通知
     * - シェルスクリプトでの成功判定
     * 
     * オブジェクトの自動破棄：
     * 1. main関数終了時にharlオブジェクトのデストラクタ呼び出し
     * 2. "Harl filter instance destroyed" の出力
     * 3. RAII による自動リソース管理
     */
    return 0;
}

/*
 * ====================================================================
 * 期待される実行例と出力
 * ====================================================================
 * 
 * 【実行例1：DEBUG レベル指定】
 * 
 * コマンド：./harlFilter DEBUG
 * 
 * 期待される出力：
 * ```
 * Harl filter instance created
 * 
 * === Harl Filter System ===
 * Filtering with level: DEBUG
 * Output (showing DEBUG and above):
 * 
 * [DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!
 * [INFO] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!
 * [WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.
 * [ERROR] This is unacceptable! I want to speak to the manager now.
 * 
 * === Filtering Complete ===
 * Harl filter instance destroyed
 * ```
 * 
 * 【実行例2：WARNING レベル指定】
 * 
 * コマンド：./harlFilter WARNING
 * 
 * 期待される出力：
 * ```
 * Harl filter instance created
 * 
 * === Harl Filter System ===
 * Filtering with level: WARNING
 * Output (showing WARNING and above):
 * 
 * [WARNING] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.
 * [ERROR] This is unacceptable! I want to speak to the manager now.
 * 
 * === Filtering Complete ===
 * Harl filter instance destroyed
 * ```
 * 
 * 【実行例3：ERROR レベル指定】
 * 
 * コマンド：./harlFilter ERROR
 * 
 * 期待される出力：
 * ```
 * Harl filter instance created
 * 
 * === Harl Filter System ===
 * Filtering with level: ERROR
 * Output (showing ERROR and above):
 * 
 * [ERROR] This is unacceptable! I want to speak to the manager now.
 * 
 * === Filtering Complete ===
 * Harl filter instance destroyed
 * ```
 * 
 * 【実行例4：無効レベル指定】
 * 
 * コマンド：./harlFilter INVALID
 * 
 * 期待される出力：
 * ```
 * Harl filter instance created
 * 
 * === Harl Filter System ===
 * Filtering with level: INVALID
 * Output (showing INVALID and above):
 * 
 * [ Probably complaining about insignificant problems ]
 * 
 * === Filtering Complete ===
 * Harl filter instance destroyed
 * ```
 * 
 * 【実行例5：引数不足エラー】
 * 
 * コマンド：./harlFilter
 * 
 * 期待される出力：
 * ```
 * Usage: ./harlFilter <level>
 * Valid levels: DEBUG, INFO, WARNING, ERROR
 * ```
 * 
 * 終了コード：1（エラー）
 */

/*
 * ====================================================================
 * 実用的な使用シナリオ
 * ====================================================================
 * 
 * 【開発時のデバッグ】
 * ```bash
 * # 全ての情報を確認したい場合
 * ./harlFilter DEBUG
 * 
 * # 重要な情報のみ確認したい場合
 * ./harlFilter INFO
 * ```
 * 
 * 【本番環境での運用】
 * ```bash
 * # 警告以上のみ記録したい場合
 * ./harlFilter WARNING > warnings.log
 * 
 * # エラーのみ記録したい場合
 * ./harlFilter ERROR > errors.log
 * ```
 * 
 * 【シェルスクリプトでの活用】
 * ```bash
 * #!/bin/bash
 * for level in DEBUG INFO WARNING ERROR; do
 *     echo "=== Testing $level ==="
 *     ./harlFilter $level
 *     echo
 * done
 * ```
 * 
 * 【システム統合例】
 * ```bash
 * # 設定ファイルからレベルを読み込み
 * LEVEL=$(cat /etc/harl/level.conf)
 * ./harlFilter $LEVEL
 * 
 * # 終了コードによる分岐
 * if ./harlFilter $LEVEL; then
 *     echo "Filtering completed successfully"
 * else
 *     echo "Error in filtering process"
 * fi
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この main 関数で確認すべき項目：
 * 
 * □ argc/argv によるコマンドライン引数処理
 * □ 引数数の検証とエラーメッセージ
 * □ char* から std::string への変換
 * □ オブジェクトの作成と使用
 * □ メソッド呼び出しと結果の確認
 * □ プログラムの終了コード管理
 * □ ユーザビリティを考慮したメッセージ出力
 * □ RAII によるオブジェクト自動管理
 * □ エラーハンドリングの実装
 * □ switch文フィルタリングシステムの実用的活用
 * 
 * 【実習課題】
 * 1. 複数レベル指定の対応（例：DEBUG,WARNING）
 * 2. ヘルプオプション（-h, --help）の追加
 * 3. 出力ファイル指定オプションの実装
 * 4. 設定ファイル読み込み機能の追加
 * 5. レベル番号（0-3）での指定対応
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：引数検証の不備】
 * 
 * 間違い例：
 * ```cpp
 * // 引数数チェックなし
 * std::string level = argv[1];  // セグメンテーション違反の可能性
 * ```
 * 
 * 正解：
 * ```cpp
 * if (argc != 2) {
 *     // エラー処理
 *     return 1;
 * }
 * std::string level = argv[1];  // 安全
 * ```
 * 
 * 【ミス2：エラーメッセージの不親切さ】
 * 
 * 間違い例：
 * ```cpp
 * if (argc != 2) {
 *     std::cout << "Error" << std::endl;  // 不親切
 *     return 1;
 * }
 * ```
 * 
 * 改良：
 * ```cpp
 * if (argc != 2) {
 *     std::cout << "Usage: " << argv[0] << " <level>" << std::endl;
 *     std::cout << "Valid levels: DEBUG, INFO, WARNING, ERROR" << std::endl;
 *     return 1;
 * }
 * ```
 * 
 * 【ミス3：終了コードの不適切な使用】
 * 
 * 間違い例：
 * ```cpp
 * return -1;  // 負の値は避ける
 * exit(999);  // 大きすぎる値
 * ```
 * 
 * 推奨：
 * ```cpp
 * return 0;  // 正常終了
 * return 1;  // 一般的なエラー
 * return 2;  // 特定のエラータイプ（必要に応じて）
 * ```
 * 
 * 【ミス4：出力フォーマットの不統一】
 * 
 * 問題：
 * - メッセージの書式がバラバラ
 * - 視覚的な区切りがない
 * - ユーザー体験の低下
 * 
 * 改善：
 * - 一貫したフォーマット使用
 * - 視覚的な区切り線追加
 * - 階層的な情報表示
 */

/*
 * ====================================================================
 * 発展的な改良提案
 * ====================================================================
 * 
 * 【改良1：コマンドラインオプション対応】
 * ```cpp
 * #include <getopt.h>  // GNU getopt
 * 
 * int main(int argc, char* argv[]) {
 *     std::string level = "INFO";  // デフォルト
 *     std::string outputFile = "";
 *     bool showHelp = false;
 *     
 *     int opt;
 *     while ((opt = getopt(argc, argv, "l:o:h")) != -1) {
 *         switch (opt) {
 *             case 'l':
 *                 level = optarg;
 *                 break;
 *             case 'o':
 *                 outputFile = optarg;
 *                 break;
 *             case 'h':
 *                 showHelp = true;
 *                 break;
 *         }
 *     }
 * }
 * ```
 * 
 * 【改良2：設定ファイル対応】
 * ```cpp
 * class ConfigReader {
 * public:
 *     static std::string readLevel(const std::string& configFile) {
 *         std::ifstream file(configFile.c_str());
 *         std::string line;
 *         while (std::getline(file, line)) {
 *             if (line.find("level=") == 0) {
 *                 return line.substr(6);  // "level=" の後
 *             }
 *         }
 *         return "INFO";  // デフォルト
 *     }
 * };
 * 
 * int main(int argc, char* argv[]) {
 *     std::string level;
 *     if (argc == 2) {
 *         level = argv[1];
 *     } else {
 *         level = ConfigReader::readLevel("/etc/harl.conf");
 *     }
 * }
 * ```
 * 
 * 【改良3：出力カスタマイズ】
 * ```cpp
 * class OutputManager {
 * private:
 *     std::ostream* output;
 *     
 * public:
 *     OutputManager(const std::string& filename = "") {
 *         if (filename.empty()) {
 *             output = &std::cout;
 *         } else {
 *             output = new std::ofstream(filename.c_str());
 *         }
 *     }
 *     
 *     ~OutputManager() {
 *         if (output != &std::cout) {
 *             delete output;
 *         }
 *     }
 *     
 *     std::ostream& getStream() { return *output; }
 * };
 * ```
 * 
 * 【改良4：インタラクティブモード】
 * ```cpp
 * void interactiveMode() {
 *     Harl harl;
 *     std::string input;
 *     
 *     std::cout << "Interactive Harl Filter" << std::endl;
 *     std::cout << "Enter level (DEBUG/INFO/WARNING/ERROR) or 'quit':" << std::endl;
 *     
 *     while (true) {
 *         std::cout << "> ";
 *         std::getline(std::cin, input);
 *         
 *         if (input == "quit" || input == "exit") {
 *             break;
 *         }
 *         
 *         harl.complainFilter(input);
 *         std::cout << std::endl;
 *     }
 * }
 * 
 * int main(int argc, char* argv[]) {
 *     if (argc == 1) {
 *         interactiveMode();
 *     } else {
 *         // 通常のコマンドライン処理
 *     }
 * }
 * ```
 */

/*
 * ====================================================================
 * ex05とex06の比較まとめ
 * ====================================================================
 * 
 * 【機能比較】
 * 
 * ex05 (complain):
 * - 個別レベル実行
 * - メンバ関数ポインタ使用
 * - 1つのメッセージ出力
 * - 動的関数選択の学習
 * 
 * ex06 (complainFilter):
 * - フィルタリング実行
 * - switch文のfall-through使用
 * - 複数メッセージ出力
 * - レベル階層システム学習
 * 
 * 【技術的な学習ポイント】
 * 
 * ex05で学ぶもの：
 * - メンバ関数ポインタの構文
 * - 動的な関数呼び出し
 * - 配列を使った関数マッピング
 * - オブジェクト指向の基礎
 * 
 * ex06で学ぶもの：
 * - switch文の高度な使用法
 * - fall-through機能の活用
 * - レベルベースシステム設計
 * - 実用的なフィルタリング
 * 
 * 【実用性】
 * 
 * ex05のアプローチ：
 * - 特定のログレベルが必要な場合
 * - デバッグ時の個別確認
 * - 動的な関数選択が必要
 * 
 * ex06のアプローチ：
 * - 包括的なログ確認が必要
 * - 本番環境でのフィルタリング
 * - レベル階層に基づく運用
 * 
 * どちらも実際のプログラミングで有用な技術であり、
 * 用途に応じて適切な手法を選択することが重要。
 */