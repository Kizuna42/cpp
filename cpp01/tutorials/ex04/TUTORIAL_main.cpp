/*
 * ====================================================================
 * CPP01 ex04: Sed is for losers - ファイルI/O文字列置換解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - C++でのファイル入出力操作
 * - std::ifstream, std::ofstream の使用方法
 * - std::string の文字列操作（find, replace）
 * - コマンドライン引数の処理
 * - エラーハンドリングの実践
 * - ファイルの安全な読み書き
 * 
 * 【重要概念】
 * - RAII によるファイル自動管理
 * - 文字列検索・置換アルゴリズム
 * - バイナリ安全な文字列処理
 * - ファイル存在性とアクセス権限の確認
 */

#include <string>
#include <iostream>
#include <fstream>

/*
 * ====================================================================
 * 文字列置換関数の解説
 * ====================================================================
 */
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    /*
     * 【関数の目的】
     * 
     * 文字列内の全ての部分文字列を置換：
     * - str: 置換対象の文字列（コピー渡し）
     * - from: 検索する部分文字列
     * - to: 置換する文字列
     * 
     * 戻り値：置換後の文字列
     * 
     * 【設計判断】
     * 
     * なぜ値渡し（コピー）なのか？
     * 1. 元の文字列を変更せず安全
     * 2. 戻り値として置換結果を返す
     * 3. 呼び出し元のデータ保護
     */
    
    /*
     * 【エラーケース：空文字列の検索】
     * 
     * from.empty() の場合：
     * - 空文字列は無限に見つかってしまう
     * - 無限ループの原因となる
     * - 早期リターンで回避
     */
    if (from.empty()) return str;
    
    /*
     * 【置換アルゴリズムの実装】
     * 
     * 検索開始位置の管理：
     * - start_pos: 検索を開始する位置
     * - 見つかった位置から置換後文字列の長さ分進める
     * - 重複置換やスキップを防ぐ
     */
    size_t start_pos = 0;
    
    /*
     * 【置換ループの詳細】
     * 
     * while ((start_pos = str.find(from, start_pos)) != std::string::npos)
     * 
     * 処理フロー：
     * 1. str.find(from, start_pos) で次の出現位置を検索
     * 2. std::string::npos と比較（見つからない場合の戻り値）
     * 3. 見つかった場合はループ継続、見つからない場合は終了
     */
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        /*
         * 【文字列置換の実行】
         * 
         * str.replace(start_pos, from.length(), to)
         * 
         * パラメータ：
         * - start_pos: 置換開始位置
         * - from.length(): 削除する文字数
         * - to: 挿入する文字列
         * 
         * 動作：
         * 1. start_pos から from.length() 文字を削除
         * 2. その位置に to を挿入
         * 3. 文字列長が変更される可能性
         */
        str.replace(start_pos, from.length(), to);
        
        /*
         * 【次回検索位置の更新】
         * 
         * start_pos += to.length()
         * 
         * なぜ to.length() を加算するのか？
         * 
         * 1. 重複置換の防止
         *    - 置換した部分を再び検索対象にしない
         *    - "aaa" で "aa" → "b" を実行時の安全性
         * 
         * 2. 効率性の向上
         *    - 既に処理済みの部分をスキップ
         *    - 不要な再検索を避ける
         * 
         * 例：
         * - 元文字列: "hello world hello"
         * - from: "hello", to: "hi"
         * - 1回目: "hi world hello" (start_pos = 2)
         * - 2回目: "hi world hi" (start_pos = 11)
         */
        start_pos += to.length();
    }
    
    /*
     * 【置換完了後の戻り値】
     * 
     * 置換されたすべての部分文字列を含む新しい文字列を返す
     */
    return str;
}

/*
 * ====================================================================
 * main関数の解説
 * ====================================================================
 */
int main(int argc, char* argv[]) {
    /*
     * 【プログラムの目的】
     * 
     * UNIXの sed コマンド風のファイル文字列置換ツール：
     * 1. ファイルからテキストを読み込み
     * 2. 指定した文字列を別の文字列に置換
     * 3. 結果を新しいファイルに出力
     * 
     * 使用法：./program <filename> <s1> <s2>
     * - filename: 入力ファイル名
     * - s1: 置換対象文字列
     * - s2: 置換後文字列
     */
    
    /*
     * ====================================================================
     * コマンドライン引数の検証
     * ====================================================================
     */
    
    /*
     * 【引数数の確認】
     * 
     * argc != 4 の場合：
     * - argc[0]: プログラム名
     * - argc[1]: ファイル名
     * - argc[2]: 検索文字列（s1）
     * - argc[3]: 置換文字列（s2）
     * 
     * 合計4個の引数が必要
     */
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;  // エラー終了
    }
    
    /*
     * 【引数の取得と変換】
     * 
     * char* から std::string への変換：
     * - C言語的な文字列からC++の文字列オブジェクトへ
     * - より安全で使いやすい文字列操作のため
     * - std::string の豊富なメソッドを活用
     */
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    
    /*
     * 【検索文字列の妥当性確認】
     * 
     * s1.empty() のチェック：
     * - 空文字列を検索すると無限ループの危険
     * - replaceAll 関数でも同じチェックを実装
     * - 二重の安全対策
     */
    if (s1.empty()) {
        std::cout << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }
    
    /*
     * ====================================================================
     * 入力ファイルの読み込み
     * ====================================================================
     */
    
    /*
     * 【ファイルストリームの作成】
     * 
     * std::ifstream inputFile(filename.c_str())
     * 
     * C++98 での制約：
     * - std::ifstream のコンストラクタは const char* を要求
     * - std::string から c_str() で C文字列を取得
     * - C++11 以降では std::string を直接使用可能
     */
    std::ifstream inputFile(filename.c_str());
    
    /*
     * 【ファイルオープンの確認】
     * 
     * inputFile.is_open() による検証：
     * - ファイルが存在しない場合
     * - アクセス権限がない場合
     * - 他のプロセスが排他ロックしている場合
     * 
     * これらの場合に false を返す
     */
    if (!inputFile.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    /*
     * 【ファイル内容の読み込み】
     * 
     * 行単位読み込みによる内容取得：
     * 
     * 設計判断：
     * - 一行ずつ読み込んで連結
     * - 改行文字の正確な再現
     * - メモリ効率的な処理
     */
    std::string content;
    std::string line;
    
    /*
     * 【行読み込みループ】
     * 
     * while (std::getline(inputFile, line))
     * 
     * std::getline の動作：
     * 1. 改行文字まで読み込み
     * 2. 改行文字は結果に含まれない
     * 3. ファイル終端で false を返す
     */
    while (std::getline(inputFile, line)) {
        content += line;
        
        /*
         * 【改行文字の追加処理】
         * 
         * if (!inputFile.eof())
         * 
         * 最後の行以外に改行文字を追加：
         * - getline は改行文字を除去するため
         * - 元ファイルの改行構造を維持
         * - 最終行の後は改行を追加しない
         * 
         * 重要：この処理により元ファイルの構造を正確に保持
         */
        if (!inputFile.eof()) {
            content += "\n";
        }
    }
    
    /*
     * 【ファイルクローズ】
     * 
     * inputFile.close()
     * 
     * RAII による自動管理：
     * - デストラクタでも自動的にクローズされる
     * - 明示的なクローズは推奨プラクティス
     * - エラー時の早期リソース解放
     */
    inputFile.close();
    
    /*
     * ====================================================================
     * 文字列置換の実行
     * ====================================================================
     */
    
    /*
     * 【置換処理の実行】
     * 
     * replaceAll(content, s1, s2)
     * 
     * 処理内容：
     * - ファイル内容全体から s1 を検索
     * - 見つかった全ての s1 を s2 に置換
     * - 置換結果を新しい文字列として取得
     */
    std::string result = replaceAll(content, s1, s2);
    
    /*
     * ====================================================================
     * 出力ファイルへの書き込み
     * ====================================================================
     */
    
    /*
     * 【出力ファイル名の生成】
     * 
     * filename + ".replace"
     * 
     * 命名規則：
     * - 元ファイル名に .replace 拡張子を追加
     * - 例：test.txt → test.txt.replace
     * - 元ファイルの上書きを防ぐ安全な設計
     */
    std::string outputFilename = filename + ".replace";
    
    /*
     * 【出力ファイルストリームの作成】
     * 
     * std::ofstream outputFile(outputFilename.c_str())
     * 
     * デフォルトモード：
     * - std::ios::out（書き込み専用）
     * - std::ios::trunc（既存内容を削除）
     * - テキストモード（改行文字の自動変換）
     */
    std::ofstream outputFile(outputFilename.c_str());
    
    /*
     * 【出力ファイルオープンの確認】
     * 
     * 失敗する可能性：
     * - ディスク容量不足
     * - 書き込み権限なし
     * - ファイルが他のプロセスで使用中
     * - ディレクトリが存在しない
     */
    if (!outputFile.is_open()) {
        std::cout << "Error: Could not create output file " << outputFilename << std::endl;
        return 1;
    }
    
    /*
     * 【内容の書き込み】
     * 
     * outputFile << result
     * 
     * ストリーム演算子による書き込み：
     * - 文字列全体を一度に出力
     * - 改行文字も含めて正確に出力
     * - バッファリングによる効率的な処理
     */
    outputFile << result;
    
    /*
     * 【出力ファイルクローズ】
     * 
     * outputFile.close()
     * 
     * 明示的クローズの重要性：
     * - バッファ内容の確実な書き込み
     * - ファイルハンドルの早期解放
     * - エラー検出の機会
     */
    outputFile.close();
    
    /*
     * ====================================================================
     * 処理完了の報告
     * ====================================================================
     */
    
    /*
     * 【成功メッセージの表示】
     * 
     * 出力ファイル名を含む成功報告：
     * - ユーザーに結果ファイルの場所を通知
     * - 処理が正常完了したことを確認
     * - 次のアクションへの案内
     */
    std::cout << "File processed successfully. Output: " << outputFilename << std::endl;
    
    return 0;  // 正常終了
}

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【実行例1：正常処理】
 * 
 * コマンド：./sed test.txt "old" "new"
 * 
 * test.txt の内容：
 * ```
 * This is an old file.
 * The old system is old.
 * ```
 * 
 * 実行後の test.txt.replace：
 * ```
 * This is an new file.
 * The new system is new.
 * ```
 * 
 * 出力：
 * "File processed successfully. Output: test.txt.replace"
 * 
 * 【実行例2：エラーケース】
 * 
 * コマンド：./sed nonexistent.txt "old" "new"
 * 出力：
 * "Error: Could not open file nonexistent.txt"
 * 終了コード：1
 * 
 * 【実行例3：引数不足】
 * 
 * コマンド：./sed test.txt "old"
 * 出力：
 * "Usage: ./sed <filename> <s1> <s2>"
 * 終了コード：1
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このプログラムで理解すべき項目：
 * 
 * □ std::ifstream でのファイル読み込み
 * □ std::ofstream でのファイル書き込み
 * □ is_open() によるファイルオープン確認
 * □ std::getline() による行単位読み込み
 * □ std::string の find() と replace() メソッド
 * □ コマンドライン引数の処理（argc, argv）
 * □ エラーハンドリングと終了コード
 * □ RAII によるリソース自動管理
 * □ C++98 での文字列とファイル操作
 * 
 * 【実習課題】
 * 1. 存在しないファイルでのエラー処理確認
 * 2. 空文字列検索でのエラー処理確認
 * 3. 大きなファイルでの性能測定
 * 4. バイナリファイルでの動作確認
 * 5. 複雑な置換パターンのテスト
 */

/*
 * ====================================================================
 * よくある間違いと対策
 * ====================================================================
 * 
 * 【間違い1】ファイルオープンの確認忘れ
 * ```cpp
 * std::ifstream file("test.txt");
 * std::string line;
 * std::getline(file, line);  // ファイルが開けていない可能性
 * ```
 * 対策：必ず is_open() で確認
 * 
 * 【間違い2】改行文字の処理ミス
 * ```cpp
 * while (std::getline(file, line)) {
 *     content += line + "\n";  // 最後に余分な改行
 * }
 * ```
 * 対策：EOF チェックで最終行を判定
 * 
 * 【間違い3】空文字列検索の考慮不足
 * ```cpp
 * str.replace(pos, 0, replacement);  // 無限ループの原因
 * ```
 * 対策：検索文字列の空チェック
 * 
 * 【間違い4】C文字列とC++文字列の混同
 * ```cpp
 * std::ifstream file(filename);  // C++98ではエラー
 * ```
 * 対策：c_str() で変換
 */

/*
 * ====================================================================
 * 発展的な改良案
 * ====================================================================
 * 
 * 【改良1：正規表現対応】
 * ```cpp
 * #include <regex>  // C++11以降
 * std::string regexReplace(const std::string& str, 
 *                         const std::string& pattern,
 *                         const std::string& replacement) {
 *     return std::regex_replace(str, std::regex(pattern), replacement);
 * }
 * ```
 * 
 * 【改良2：大きなファイルの効率的処理】
 * ```cpp
 * void processLargeFile(const std::string& filename) {
 *     std::ifstream input(filename);
 *     std::ofstream output(filename + ".replace");
 *     std::string line;
 *     while (std::getline(input, line)) {
 *         output << replaceAll(line, s1, s2) << "\n";
 *     }
 * }
 * ```
 * 
 * 【改良3：バックアップ機能】
 * ```cpp
 * void createBackup(const std::string& filename) {
 *     std::string backupName = filename + ".backup";
 *     // ファイルコピー処理
 * }
 * ```
 * 
 * 【改良4：エラー処理の強化】
 * ```cpp
 * enum ProcessResult {
 *     SUCCESS,
 *     FILE_NOT_FOUND,
 *     PERMISSION_DENIED,
 *     DISK_FULL,
 *     INVALID_ARGUMENTS
 * };
 * ```
 */

/*
 * ====================================================================
 * パフォーマンス考慮事項
 * ====================================================================
 * 
 * 【文字列置換の効率性】
 * 
 * 現在の実装：O(n * m)
 * - n: 文字列長
 * - m: 置換回数
 * 
 * より効率的なアルゴリズム：
 * - Boyer-Moore 文字列検索
 * - KMP (Knuth-Morris-Pratt) アルゴリズム
 * 
 * 【メモリ使用量】
 * 
 * 現在：ファイル全体をメモリに読み込み
 * - 小〜中サイズファイル向け
 * - シンプルで理解しやすい
 * 
 * 大きなファイル向け改善：
 * - ストリーミング処理
 * - チャンク単位での処理
 * - メモリ使用量の制限
 * 
 * 【I/O効率化】
 * 
 * バッファサイズの調整：
 * ```cpp
 * inputFile.rdbuf()->pubsetbuf(buffer, buffer_size);
 * ```
 * 
 * 一括読み込み：
 * ```cpp
 * inputFile.seekg(0, std::ios::end);
 * size_t fileSize = inputFile.tellg();
 * inputFile.seekg(0, std::ios::beg);
 * content.resize(fileSize);
 * inputFile.read(&content[0], fileSize);
 * ```
 */