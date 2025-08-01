/*
 * ====================================================================
 * CPP01 ex02: HI THIS IS BRAIN - ポインタ vs 参照 徹底比較版
 * ====================================================================
 * 
 * 【学習目標】
 * - ポインタと参照の直接的な比較
 * - 同じ操作での異なる書き方と動作
 * - 使い分けの基準と判断方法
 * - 実践的な選択指針
 * 
 * 【重要概念】
 * - 同じ目的でも異なるアプローチ
 * - 安全性 vs 柔軟性のトレードオフ
 * - コードの可読性と保守性
 * - パフォーマンスへの影響
 */

#include <string>
#include <iostream>

/*
 * ====================================================================
 * 直接比較デモンストレーション関数
 * ====================================================================
 */
void directComparison() {
    std::cout << "=== Direct Pointer vs Reference Comparison ===" << std::endl;
    
    /*
     * ====================================================================
     * 共通の元データ
     * ====================================================================
     */
    std::string brain = "HI THIS IS BRAIN";
    std::cout << "Original variable: \"" << brain << "\" at " << &brain << std::endl;
    
    /*
     * ====================================================================
     * 宣言と初期化の比較
     * ====================================================================
     */
    std::cout << "\n--- Declaration and Initialization ---" << std::endl;
    
    /*
     * ポインタの宣言・初期化
     */
    std::string* stringPTR = &brain;
    std::cout << "Pointer declaration:   std::string* stringPTR = &brain;" << std::endl;
    std::cout << "Pointer holds address: " << stringPTR << std::endl;
    std::cout << "Pointer's own address: " << &stringPTR << std::endl;
    
    /*
     * 参照の宣言・初期化
     */
    std::string& stringREF = brain;
    std::cout << "Reference declaration: std::string& stringREF = brain;" << std::endl;
    std::cout << "Reference address:     " << &stringREF << std::endl;
    std::cout << "Same as original?      " << (&stringREF == &brain ? "Yes" : "No") << std::endl;
    
    /*
     * 【比較ポイント1】宣言の違い
     * 
     * ポインタ：
     * - std::string* ptr = &variable;
     * - アドレス演算子(&)が必要
     * - NULL初期化も可能
     * - 初期化を後回しにできる
     * 
     * 参照：
     * - std::string& ref = variable;
     * - 変数を直接指定
     * - 宣言と同時に必ず初期化
     * - 後から初期化は不可
     */
    
    /*
     * ====================================================================
     * 値の読み取り比較
     * ====================================================================
     */
    std::cout << "\n--- Value Reading ---" << std::endl;
    
    std::cout << "Original variable:     \"" << brain << "\"" << std::endl;
    std::cout << "Via pointer (*ptr):    \"" << *stringPTR << "\"" << std::endl;
    std::cout << "Via reference (ref):   \"" << stringREF << "\"" << std::endl;
    
    /*
     * 【比較ポイント2】アクセス方法の違い
     * 
     * ポインタ：
     * - 間接参照演算子(*)が必要
     * - *ptr で値にアクセス
     * - 一段階の間接アクセス
     * 
     * 参照：
     * - 直接アクセス
     * - ref で値にアクセス
     * - 変数と同じ感覚
     */
    
    /*
     * ====================================================================
     * 値の変更比較
     * ====================================================================
     */
    std::cout << "\n--- Value Modification ---" << std::endl;
    
    std::cout << "Before modification: \"" << brain << "\"" << std::endl;
    
    /*
     * ポインタ経由での変更
     */
    *stringPTR = "Modified by pointer";
    std::cout << "After pointer modification:" << std::endl;
    std::cout << "  brain:     \"" << brain << "\"" << std::endl;
    std::cout << "  *stringPTR: \"" << *stringPTR << "\"" << std::endl;
    std::cout << "  stringREF: \"" << stringREF << "\"" << std::endl;
    
    /*
     * 参照経由での変更
     */
    stringREF = "Modified by reference";
    std::cout << "After reference modification:" << std::endl;
    std::cout << "  brain:     \"" << brain << "\"" << std::endl;
    std::cout << "  *stringPTR: \"" << *stringPTR << "\"" << std::endl;
    std::cout << "  stringREF: \"" << stringREF << "\"" << std::endl;
    
    /*
     * 【比較ポイント3】変更方法の違い
     * 
     * ポインタ：
     * - *ptr = new_value;
     * - 間接参照演算子が必要
     * 
     * 参照：
     * - ref = new_value;
     * - 通常の代入と同じ書き方
     */
    
    /*
     * ====================================================================
     * 再代入の比較
     * ====================================================================
     */
    std::cout << "\n--- Reassignment Comparison ---" << std::endl;
    
    std::string anotherBrain = "ANOTHER BRAIN MESSAGE";
    std::cout << "Created another variable: \"" << anotherBrain << "\" at " << &anotherBrain << std::endl;
    
    /*
     * ポインタの再代入（可能）
     */
    std::cout << "\nBefore pointer reassignment:" << std::endl;
    std::cout << "  stringPTR points to: " << stringPTR << " (value: \"" << *stringPTR << "\")" << std::endl;
    
    stringPTR = &anotherBrain;  // ポインタの再代入
    
    std::cout << "After stringPTR = &anotherBrain:" << std::endl;
    std::cout << "  stringPTR points to: " << stringPTR << " (value: \"" << *stringPTR << "\")" << std::endl;
    std::cout << "  Original brain: \"" << brain << "\" (unchanged)" << std::endl;
    
    /*
     * 参照の「再代入」（実際は値の代入）
     */
    std::cout << "\nReference 'reassignment' attempt:" << std::endl;
    std::cout << "  Before: stringREF address = " << &stringREF << ", value = \"" << stringREF << "\"" << std::endl;
    
    stringREF = anotherBrain;  // これは値の代入、参照の再代入ではない
    
    std::cout << "  After stringREF = anotherBrain:" << std::endl;
    std::cout << "  stringREF address = " << &stringREF << " (same as before)" << std::endl;
    std::cout << "  stringREF value = \"" << stringREF << "\"" << std::endl;
    std::cout << "  brain value = \"" << brain << "\" (changed too)" << std::endl;
    std::cout << "  anotherBrain = \"" << anotherBrain << "\" (unchanged)" << std::endl;
    
    /*
     * 【比較ポイント4】再代入の可否
     * 
     * ポインタ：
     * - 別のオブジェクトを指すように変更可能
     * - ptr = &other_variable;
     * - 柔軟性が高い
     * 
     * 参照：
     * - 常に同じオブジェクトを参照
     * - ref = other_variable; は値のコピー
     * - 安全性が高い（意図しない参照先変更を防ぐ）
     */
    
    /*
     * ====================================================================
     * NULLの扱い比較
     * ====================================================================
     */
    std::cout << "\n--- NULL Handling ---" << std::endl;
    
    /*
     * ポインタのNULL処理
     */
    std::string* nullablePtr = NULL;
    std::cout << "NULL pointer created: " << nullablePtr << std::endl;
    
    if (nullablePtr != NULL) {
        std::cout << "Pointer is valid: \"" << *nullablePtr << "\"" << std::endl;
    } else {
        std::cout << "Pointer is NULL - safe check prevented crash" << std::endl;
    }
    
    /*
     * 参照のNULL不可
     */
    std::cout << "References cannot be NULL:" << std::endl;
    std::cout << "  std::string& ref = brain; // Must be initialized" << std::endl;
    std::cout << "  std::string& nullRef;     // Compilation error" << std::endl;
    
    /*
     * 【比較ポイント5】NULL安全性
     * 
     * ポインタ：
     * - NULLの可能性がある
     * - 使用前にNULLチェックが必要
     * - より多くの防御的プログラミングが必要
     * 
     * 参照：
     * - NULLになることがない
     * - 常に有効なオブジェクトを参照
     * - NULLチェック不要（安全）
     */
}

/*
 * ====================================================================
 * 実用的な使い分け例
 * ====================================================================
 */
void practicalUseCases() {
    std::cout << "\n=== Practical Use Case Examples ===" << std::endl;
    
    /*
     * ====================================================================
     * ケース1: 関数引数での使い分け
     * ====================================================================
     */
    std::cout << "\n--- Function Parameter Use Cases ---" << std::endl;
    
    /*
     * ポインタを使う関数（オプショナルパラメータ）
     */
    auto processOptionalString = [](std::string* str) {
        if (str != NULL) {
            std::cout << "Processing: \"" << *str << "\"" << std::endl;
            *str = "Processed by pointer function";
        } else {
            std::cout << "NULL pointer - no processing" << std::endl;
        }
    };
    
    /*
     * 参照を使う関数（必須パラメータ）
     */
    auto processRequiredString = [](std::string& str) {
        std::cout << "Processing: \"" << str << "\"" << std::endl;
        str = "Processed by reference function";
        // NULLチェック不要 - 常に有効なオブジェクト
    };
    
    std::string testStr = "Test string";
    
    std::cout << "Original: \"" << testStr << "\"" << std::endl;
    
    // ポインタ版関数の呼び出し
    processOptionalString(&testStr);
    std::cout << "After pointer function: \"" << testStr << "\"" << std::endl;
    
    // 参照版関数の呼び出し
    processRequiredString(testStr);
    std::cout << "After reference function: \"" << testStr << "\"" << std::endl;
    
    // ポインタ版はNULLも受け付ける
    processOptionalString(NULL);
    
    /*
     * ====================================================================
     * ケース2: 戻り値での使い分け
     * ====================================================================
     */
    std::cout << "\n--- Return Value Use Cases ---" << std::endl;
    
    /*
     * ポインタを返す関数（失敗の可能性がある場合）
     */
    static std::string globalStr = "Global string";
    
    auto findString = [](bool success) -> std::string* {
        if (success) {
            return &globalStr;
        } else {
            return NULL;  // 失敗を示す
        }
    };
    
    /*
     * 参照を返す関数（常に成功する場合）
     */
    auto getGlobalString = []() -> std::string& {
        return globalStr;  // 常に有効なオブジェクトを返す
    };
    
    // ポインタ版の使用
    std::string* foundPtr = findString(true);
    if (foundPtr != NULL) {
        std::cout << "Found string: \"" << *foundPtr << "\"" << std::endl;
    }
    
    foundPtr = findString(false);
    if (foundPtr == NULL) {
        std::cout << "String not found (NULL returned)" << std::endl;
    }
    
    // 参照版の使用
    std::string& foundRef = getGlobalString();
    std::cout << "Global string reference: \"" << foundRef << "\"" << std::endl;
    
    /*
     * ====================================================================
     * ケース3: コンテナアクセスでの使い分け
     * ====================================================================
     */
    std::cout << "\n--- Container Access Use Cases ---" << std::endl;
    
    // 配列的なアクセス
    std::string stringArray[3] = {"First", "Second", "Third"};
    
    /*
     * ポインタを使った配列アクセス
     */
    std::string* arrayPtr = stringArray;
    std::cout << "Pointer array access:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  [" << i << "]: \"" << *(arrayPtr + i) << "\"" << std::endl;
    }
    
    /*
     * 参照を使った個別要素アクセス
     */
    std::string& firstElement = stringArray[0];
    std::cout << "Reference to first element: \"" << firstElement << "\"" << std::endl;
    
    firstElement = "Modified first";
    std::cout << "After modification: \"" << stringArray[0] << "\"" << std::endl;
}

/*
 * ====================================================================
 * パフォーマンス比較
 * ====================================================================
 */
void performanceComparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    /*
     * メモリ使用量の比較
     */
    std::string original = "Performance test string";
    std::string* ptr = &original;
    std::string& ref = original;
    
    std::cout << "Memory usage comparison:" << std::endl;
    std::cout << "  sizeof(std::string):    " << sizeof(std::string) << " bytes" << std::endl;
    std::cout << "  sizeof(std::string*):   " << sizeof(std::string*) << " bytes" << std::endl;
    std::cout << "  sizeof(std::string&):   " << sizeof(std::string&) << " bytes" << std::endl;
    
    std::cout << "\nAddress comparison:" << std::endl;
    std::cout << "  original address:  " << &original << std::endl;
    std::cout << "  pointer value:     " << ptr << std::endl;
    std::cout << "  pointer address:   " << &ptr << std::endl;
    std::cout << "  reference address: " << &ref << std::endl;
    
    /*
     * 【パフォーマンス考察】
     * 
     * メモリ使用量：
     * - 参照：追加のメモリ使用なし（コンパイラ最適化）
     * - ポインタ：ポインタサイズ分の追加メモリ（通常8バイト）
     * 
     * アクセス速度：
     * - 参照：直接アクセス（最適化時はオーバーヘッドなし）
     * - ポインタ：間接参照（わずかなオーバーヘッド）
     * 
     * 実際の性能差：
     * - 最適化ON時：ほぼ同等の性能
     * - 最適化OFF時：参照がわずかに高速
     * - 実用上の差：無視できるレベル
     */
}

/*
 * ====================================================================
 * main関数
 * ====================================================================
 */
int main(void) {
    std::cout << "/*" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " * CPP01 ex02: Pointer vs Reference Comprehensive Comparison" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " */" << std::endl;
    std::cout << std::endl;
    
    directComparison();
    practicalUseCases();
    performanceComparison();
    
    return 0;
}

/*
 * ====================================================================
 * 決定フローチャート: ポインタ vs 参照
 * ====================================================================
 * 
 * 以下の質問に順番に答えて、適切な選択をしてください：
 * 
 * 1. NULLになる可能性はありますか？
 *    YES → ポインタを使用
 *    NO  → 次の質問へ
 * 
 * 2. 再代入（別のオブジェクトを指す）が必要ですか？
 *    YES → ポインタを使用
 *    NO  → 次の質問へ
 * 
 * 3. ポインタ演算（配列アクセス等）が必要ですか？
 *    YES → ポインタを使用
 *    NO  → 次の質問へ
 * 
 * 4. 動的メモリ管理が関わりますか？
 *    YES → ポインタを使用
 *    NO  → 次の質問へ
 * 
 * 5. 単純なエイリアス（別名）が欲しいだけですか？
 *    YES → 参照を使用
 *    NO  → コンテキストに応じて判断
 * 
 * 【一般的な推奨順序】
 * 1. まず参照を検討（安全性重視）
 * 2. 参照で不十分ならポインタ（柔軟性重視）
 * 3. 一貫性を保つ（同じプロジェクト内で統一）
 * 4. チームの規約に従う
 */

/*
 * ====================================================================
 * 実世界での使用例
 * ====================================================================
 * 
 * 【参照を使う場面】
 * - 関数引数（大きなオブジェクトのコピー回避）
 * - operator overloading（演算子のオーバーロード）
 * - STLアルゴリズムの関数オブジェクト
 * - range-based for loop（C++11以降）
 * - getter/setter functions
 * 
 * 【ポインタを使う場面】
 * - 動的メモリ確保（new/delete）
 * - データ構造の実装（リンクリスト、ツリー）
 * - C言語との互換性が必要な場合
 * - 関数ポインタ
 * - optional parameters（C++17のstd::optional以前）
 * 
 * 【どちらでも良い場面】
 * - 関数の戻り値（設計方針による）
 * - 単純な値の受け渡し
 * - ローカル変数のエイリアス
 */

/*
 * ====================================================================
 * よくある誤解と正しい理解
 * ====================================================================
 * 
 * 【誤解1】「参照はポインタの糖衣構文」
 * 正解：参照は独立した概念。コンパイラレベルでは異なる扱い
 * 
 * 【誤解2】「参照の方が常に高速」
 * 正解：最適化により性能差はほぼなし。可読性・安全性で選ぶ
 * 
 * 【誤解3】「ポインタは危険だから使わない方が良い」
 * 正解：適切に使えば強力なツール。場面に応じて使い分ける
 * 
 * 【誤解4】「参照は変更できない」
 * 正解：参照先の値は変更可能。変更できないのは参照先オブジェクト
 * 
 * 【誤解5】「参照はメモリを消費しない」
 * 正解：実装依存。多くの場合最適化されるが、絶対ではない
 */