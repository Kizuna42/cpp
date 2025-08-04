/*
 * ====================================================================
 * CPP01 ex04: File Operations - ファイル操作詳細解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - C++におけるファイルI/Oの基礎
 * - ストリームクラスの階層構造理解
 * - ファイルモードとアクセス方法
 * - エラーハンドリングのベストプラクティス
 * - バイナリとテキストファイルの違い
 * 
 * 【重要概念】
 * - iostream ライブラリの構造
 * - RAII によるリソース管理
 * - ファイルの状態管理
 * - 異なるファイル形式への対応
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/*
 * ====================================================================
 * ファイル読み込みの様々な方法
 * ====================================================================
 */

/*
 * 【方法1：行単位読み込み（推奨）】
 * 
 * メリット：
 * - メモリ効率が良い
 * - 大きなファイルでも安全
 * - 改行文字の制御が可能
 * 
 * デメリット：
 * - 若干複雑な実装
 * - 改行文字の管理が必要
 */
std::string readFileLineByLine(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string content;
    std::string line;
    
    while (std::getline(file, line)) {
        content += line;
        if (!file.eof()) {
            content += "\n";
        }
    }
    
    file.close();
    return content;
}

/*
 * 【方法2：全体一括読み込み】
 * 
 * メリット：
 * - シンプルな実装
 * - 高速（一回のI/O操作）
 * - ファイル構造の完全保持
 * 
 * デメリット：
 * - 大きなファイルでメモリ不足の危険
 * - ファイルサイズ事前確認が必要
 */
std::string readFileAtOnce(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    /*
     * ファイルサイズの取得
     */
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    /*
     * メモリ確保と読み込み
     */
    std::string content;
    content.resize(static_cast<size_t>(fileSize));
    
    file.read(&content[0], fileSize);
    file.close();
    
    return content;
}

/*
 * 【方法3：stringstream使用】
 * 
 * メリット：
 * - 非常にシンプル
 * - C++標準ライブラリの活用
 * - 自動的なバッファ管理
 * 
 * デメリット：
 * - 内部でのメモリコピーが発生
 * - 大きなファイルで非効率
 */
std::string readFileWithStringStream(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

/*
 * ====================================================================
 * ファイル書き込みの様々な方法
 * ====================================================================
 */

/*
 * 【方法1：直接書き込み（推奨）】
 */
void writeFileDirectly(const std::string& filename, const std::string& content) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    file << content;
    file.close();
    
    /*
     * 書き込み確認
     */
    if (file.fail()) {
        throw std::runtime_error("Failed to write to file: " + filename);
    }
}

/*
 * 【方法2：バッファリング制御】
 */
void writeFileWithBuffering(const std::string& filename, const std::string& content) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    /*
     * バッファサイズの設定
     */
    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    file.rdbuf()->pubsetbuf(buffer, bufferSize);
    
    file << content;
    file.flush();  // 明示的なフラッシュ
    file.close();
}

/*
 * 【方法3：追記モード】
 */
void appendToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename.c_str(), std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for append: " + filename);
    }
    
    file << content;
    file.close();
}

/*
 * ====================================================================
 * ファイル存在性と権限の確認
 * ====================================================================
 */

/*
 * 【ファイル存在確認】
 */
bool fileExists(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
}

/*
 * 【読み込み可能性確認】
 */
bool isFileReadable(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.is_open() && file.good();
}

/*
 * 【書き込み可能性確認】
 */
bool isFileWritable(const std::string& filename) {
    /*
     * 既存ファイルの場合：追記モードで確認
     */
    std::ofstream file(filename.c_str(), std::ios::app);
    bool writable = file.is_open();
    file.close();
    return writable;
}

/*
 * ====================================================================
 * エラーハンドリングの実践
 * ====================================================================
 */

/*
 * 【詳細なエラー判定】
 */
enum FileError {
    FILE_SUCCESS = 0,
    FILE_NOT_FOUND,
    FILE_PERMISSION_DENIED,
    FILE_ALREADY_EXISTS,
    FILE_DISK_FULL,
    FILE_IO_ERROR,
    FILE_UNKNOWN_ERROR
};

/*
 * 【エラー状態の詳細判定】
 */
FileError getFileError(const std::ifstream& file, const std::string& filename) {
    if (file.is_open() && file.good()) {
        return FILE_SUCCESS;
    }
    
    if (file.fail()) {
        /*
         * 具体的なエラー原因の推定
         * 注：完璧な判定はOSによって異なる
         */
        if (!fileExists(filename)) {
            return FILE_NOT_FOUND;
        } else {
            return FILE_PERMISSION_DENIED;
        }
    }
    
    if (file.bad()) {
        return FILE_IO_ERROR;
    }
    
    return FILE_UNKNOWN_ERROR;
}

/*
 * 【エラーメッセージの生成】
 */
std::string getErrorMessage(FileError error, const std::string& filename) {
    switch (error) {
        case FILE_SUCCESS:
            return "Success";
        case FILE_NOT_FOUND:
            return "File not found: " + filename;
        case FILE_PERMISSION_DENIED:
            return "Permission denied: " + filename;
        case FILE_ALREADY_EXISTS:
            return "File already exists: " + filename;
        case FILE_DISK_FULL:
            return "Disk full while writing: " + filename;
        case FILE_IO_ERROR:
            return "I/O error occurred: " + filename;
        default:
            return "Unknown error: " + filename;
    }
}

/*
 * ====================================================================
 * 安全なファイル操作クラス
 * ====================================================================
 */

/*
 * 【RAII パターンのファイルハンドラ】
 */
class SafeFileReader {
private:
    std::ifstream file_;
    std::string filename_;
    
public:
    explicit SafeFileReader(const std::string& filename) 
        : filename_(filename) {
        file_.open(filename.c_str());
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }
    
    ~SafeFileReader() {
        if (file_.is_open()) {
            file_.close();
        }
    }
    
    std::string readAll() {
        if (!file_.is_open()) {
            throw std::runtime_error("File is not open: " + filename_);
        }
        
        std::stringstream buffer;
        buffer << file_.rdbuf();
        return buffer.str();
    }
    
    bool readLine(std::string& line) {
        return static_cast<bool>(std::getline(file_, line));
    }
    
    bool isOpen() const {
        return file_.is_open();
    }
    
    bool isEOF() const {
        return file_.eof();
    }
};

/*
 * 【安全なファイル書き込みクラス】
 */
class SafeFileWriter {
private:
    std::ofstream file_;
    std::string filename_;
    
public:
    explicit SafeFileWriter(const std::string& filename) 
        : filename_(filename) {
        file_.open(filename.c_str());
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot create file: " + filename);
        }
    }
    
    ~SafeFileWriter() {
        if (file_.is_open()) {
            file_.close();
        }
    }
    
    void write(const std::string& content) {
        if (!file_.is_open()) {
            throw std::runtime_error("File is not open: " + filename_);
        }
        
        file_ << content;
        if (file_.fail()) {
            throw std::runtime_error("Failed to write to file: " + filename_);
        }
    }
    
    void writeLine(const std::string& line) {
        write(line + "\n");
    }
    
    void flush() {
        if (file_.is_open()) {
            file_.flush();
        }
    }
};

/*
 * ====================================================================
 * 使用例とテストケース
 * ====================================================================
 */

void demonstrateFileOperations() {
    try {
        /*
         * 【基本的な読み書き】
         */
        std::string testContent = "Hello, World!\nThis is a test file.\n";
        std::string testFile = "test_demo.txt";
        
        // 書き込み
        writeFileDirectly(testFile, testContent);
        std::cout << "File written successfully." << std::endl;
        
        // 読み込み
        std::string readContent = readFileLineByLine(testFile);
        std::cout << "File content:\n" << readContent << std::endl;
        
        // 内容確認
        if (readContent == testContent) {
            std::cout << "Read/Write test passed." << std::endl;
        } else {
            std::cout << "Read/Write test failed." << std::endl;
        }
        
        /*
         * 【安全なクラス使用例】
         */
        {
            SafeFileWriter writer("safe_test.txt");
            writer.writeLine("Line 1");
            writer.writeLine("Line 2");
            writer.write("Final content");
        } // デストラクタで自動クローズ
        
        {
            SafeFileReader reader("safe_test.txt");
            std::string line;
            int lineNumber = 1;
            
            while (reader.readLine(line)) {
                std::cout << "Line " << lineNumber << ": " << line << std::endl;
                ++lineNumber;
            }
        } // デストラクタで自動クローズ
        
        /*
         * 【エラーケースのテスト】
         */
        try {
            SafeFileReader invalidReader("nonexistent_file.txt");
        } catch (const std::exception& e) {
            std::cout << "Expected error caught: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*
 * ====================================================================
 * パフォーマンス比較とベンチマーク
 * ====================================================================
 */

#include <ctime>

void performanceComparison(const std::string& filename) {
    const int iterations = 100;
    
    /*
     * 【方法1のベンチマーク】
     */
    clock_t start = clock();
    for (int i = 0; i < iterations; ++i) {
        std::string content = readFileLineByLine(filename);
    }
    clock_t end = clock();
    
    double lineByLineTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Line-by-line reading: " << lineByLineTime << " seconds" << std::endl;
    
    /*
     * 【方法2のベンチマーク】
     */
    start = clock();
    for (int i = 0; i < iterations; ++i) {
        std::string content = readFileAtOnce(filename);
    }
    end = clock();
    
    double atOnceTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "At-once reading: " << atOnceTime << " seconds" << std::endl;
    
    /*
     * 【方法3のベンチマーク】
     */
    start = clock();
    for (int i = 0; i < iterations; ++i) {
        std::string content = readFileWithStringStream(filename);
    }
    end = clock();
    
    double streamTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "StringStream reading: " << streamTime << " seconds" << std::endl;
    
    /*
     * 【結果の比較】
     */
    std::cout << "\nPerformance comparison:" << std::endl;
    std::cout << "Line-by-line: " << lineByLineTime << "s (baseline)" << std::endl;
    std::cout << "At-once: " << atOnceTime << "s (" 
              << (atOnceTime / lineByLineTime) << "x)" << std::endl;
    std::cout << "StringStream: " << streamTime << "s (" 
              << (streamTime / lineByLineTime) << "x)" << std::endl;
}

/*
 * 【main関数での実行例】
 */
int main() {
    std::cout << "=== File Operations Demonstration ===" << std::endl;
    
    demonstrateFileOperations();
    
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    // テスト用ファイルの作成
    std::string largeContent;
    for (int i = 0; i < 1000; ++i) {
        largeContent += "This is line " + std::to_string(i) + " of the test file.\n";
    }
    writeFileDirectly("large_test.txt", largeContent);
    
    performanceComparison("large_test.txt");
    
    return 0;
}

/*
 * ====================================================================
 * 学習ポイントまとめ
 * ====================================================================
 * 
 * 【ファイルI/Oの基本原則】
 * 1. 必ずオープン確認を行う
 * 2. RAII でリソース管理する
 * 3. エラーハンドリングを適切に行う
 * 4. 用途に応じて最適な方法を選択する
 * 
 * 【性能vs安全性のトレードオフ】
 * - 小さなファイル：どの方法でも問題なし
 * - 大きなファイル：行単位読み込みが安全
 * - 高速処理が必要：一括読み込み
 * - メモリ制限がある：ストリーミング処理
 * 
 * 【実用的な選択指針】
 * 1. まず行単位読み込みを試す
 * 2. 性能が問題なら一括読み込み
 * 3. メモリが問題ならストリーミング
 * 4. 複雑な処理なら専用クラス作成
 */