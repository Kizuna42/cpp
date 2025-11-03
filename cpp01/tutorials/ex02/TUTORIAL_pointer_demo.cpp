/*
 * ====================================================================
 * CPP01 ex02: HI THIS IS BRAIN - ポインタ詳細解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - ポインタの基本概念と使用方法
 * - メモリアドレスとポインタの関係
 * - ポインタ演算と間接参照
 * - ポインタの再代入と NULL ポインタ
 * - ポインタ使用時の注意点
 * 
 * 【重要概念】
 * - ポインタは「アドレスを格納する変数」
 * - 間接参照（*演算子）でアクセス
 * - ポインタ自体も変数（再代入可能）
 * - NULL チェックの重要性
 */

#include <string>
#include <iostream>

/*
 * ====================================================================
 * ポインタデモンストレーション関数
 * ====================================================================
 */
void demonstratePointers() {
    std::cout << "=== Pointer Demonstration ===" << std::endl;
    
    /*
     * ====================================================================
     * 基本的なポインタの作成と使用
     * ====================================================================
     */
    
    /*
     * 【ステップ1】元となる変数の作成
     */
    std::string brain = "HI THIS IS BRAIN";
    std::cout << "Original variable 'brain': \"" << brain << "\"" << std::endl;
    std::cout << "Address of 'brain': " << &brain << std::endl;
    
    /*
     * 【ステップ2】ポインタの宣言と初期化
     * 
     * std::string* stringPTR = &brain;
     * 
     * 構文分解：
     * - std::string*: ポインタの型（std::stringを指すポインタ）
     * - stringPTR: ポインタ変数の名前
     * - &brain: brain変数のアドレスを取得
     * - =: 代入演算子（ポインタにアドレスを格納）
     * 
     * 【重要】ポインタの型について
     * - int* → int型変数を指すポインタ
     * - std::string* → std::string型変数を指すポインタ
     * - char* → char型変数を指すポインタ
     * - void* → 任意の型を指すポインタ（型情報なし）
     */
    std::string* stringPTR = &brain;
    
    std::cout << "\nPointer 'stringPTR' created:" << std::endl;
    std::cout << "Value of stringPTR (address it holds): " << stringPTR << std::endl;
    std::cout << "Address of stringPTR itself: " << &stringPTR << std::endl;
    
    /*
     * 【重要な概念】ポインタ変数自体もメモリを占有
     * 
     * - brain: std::stringオブジェクトが格納されているアドレス
     * - stringPTR: brainのアドレスが格納されているアドレス
     * - &stringPTR: stringPTR自体のアドレス
     * 
     * メモリレイアウト例：
     * ```
     * アドレス     | 内容
     * 0x7fff1234   | "HI THIS IS BRAIN"  ← brain の内容
     * 0x7fff5678   | 0x7fff1234          ← stringPTR の内容（brainのアドレス）
     * ```
     */
    
    /*
     * ====================================================================
     * 間接参照（Dereference）演算子の使用
     * ====================================================================
     */
    
    /*
     * 【ステップ3】間接参照によるアクセス
     * 
     * *stringPTR: ポインタが指すメモリ位置の内容にアクセス
     * 
     * 演算子の意味：
     * - stringPTR: ポインタが保持するアドレス値
     * - *stringPTR: そのアドレスに格納されている実際の値
     */
    std::cout << "\nDereferencing pointer:" << std::endl;
    std::cout << "Value pointed to by stringPTR: \"" << *stringPTR << "\"" << std::endl;
    
    /*
     * 【検証】ポインタ経由のアクセスと直接アクセスの比較
     */
    std::cout << "\nVerification:" << std::endl;
    std::cout << "brain == *stringPTR: " << (brain == *stringPTR ? "true" : "false") << std::endl;
    std::cout << "&brain == stringPTR: " << (&brain == stringPTR ? "true" : "false") << std::endl;
    
    /*
     * ====================================================================
     * ポインタ経由での値の変更
     * ====================================================================
     */
    
    /*
     * 【ステップ4】間接参照による値の変更
     * 
     * *stringPTR = "新しい値";
     * 
     * 何が起こるのか：
     * 1. stringPTRが指すメモリ位置（brainの場所）を特定
     * 2. そのメモリ位置の内容を新しい値で置き換え
     * 3. brain変数も同じメモリ位置なので値が変更される
     */
    std::cout << "\n=== Modifying value through pointer ===" << std::endl;
    std::cout << "Before: brain = \"" << brain << "\"" << std::endl;
    
    *stringPTR = "Modified via pointer";
    
    std::cout << "After *stringPTR = \"Modified via pointer\":" << std::endl;
    std::cout << "brain = \"" << brain << "\"" << std::endl;
    std::cout << "*stringPTR = \"" << *stringPTR << "\"" << std::endl;
    
    /*
     * 【重要】同じメモリ位置を参照
     * - brain と *stringPTR は同じメモリ位置を指している
     * - どちらを変更しても、もう一方も変更される
     * - これがポインタの威力であり、危険性でもある
     */
    
    /*
     * ====================================================================
     * ポインタの再代入
     * ====================================================================
     */
    
    /*
     * 【ステップ5】別の変数を指すようにポインタを変更
     * 
     * ポインタの重要な特徴：再代入可能
     * - 参照とは異なり、ポインタは別の変数を指すように変更できる
     * - これにより柔軟なメモリアクセスが可能
     */
    std::cout << "\n=== Pointer reassignment ===" << std::endl;
    
    std::string anotherString = "Another brain message";
    std::cout << "Created another string: \"" << anotherString << "\"" << std::endl;
    std::cout << "Address of anotherString: " << &anotherString << std::endl;
    
    /*
     * ポインタを別の変数に向ける
     */
    stringPTR = &anotherString;
    
    std::cout << "\nAfter stringPTR = &anotherString:" << std::endl;
    std::cout << "stringPTR now points to: " << stringPTR << std::endl;
    std::cout << "*stringPTR = \"" << *stringPTR << "\"" << std::endl;
    std::cout << "Original brain is still: \"" << brain << "\"" << std::endl;
    
    /*
     * 【重要な観察】
     * - stringPTRは今や anotherString を指している
     * - brain は影響を受けない（もう stringPTR でアクセスできない）
     * - ポインタの柔軟性を示している
     */
    
    /*
     * ====================================================================
     * NULLポインタの概念
     * ====================================================================
     */
    
    /*
     * 【ステップ6】NULLポインタの作成と危険性
     * 
     * ポインタの特殊な値：NULL（またはnullptr）
     * - 何も指していない状態を表す
     * - 無効なアドレス（通常は0）
     * - アクセスすると未定義動作（クラッシュ）
     */
    std::cout << "\n=== NULL pointer demonstration ===" << std::endl;
    
    std::string* nullPTR = NULL;  // C++98ではNULL、C++11以降はnullptrが推奨
    
    std::cout << "NULL pointer created:" << std::endl;
    std::cout << "Value of nullPTR: " << nullPTR << std::endl;
    
    /*
     * 【安全なNULLチェック】
     * 
     * ポインタ使用前の必須チェック
     * - NULLポインタへの間接参照は危険
     * - プログラムクラッシュの原因
     * - 防御的プログラミングの基本
     */
    if (nullPTR != NULL) {
        std::cout << "Safe to access: " << *nullPTR << std::endl;
    } else {
        std::cout << "NULL pointer - cannot dereference safely" << std::endl;
    }
    
    /*
     * 【危険な例】コメントアウトされた危険なコード
     * 
     * // std::cout << *nullPTR << std::endl;  // 危険！クラッシュの原因
     * 
     * このコードを実行すると：
     * - セグメンテーション違反（Segmentation fault）
     * - プログラムの異常終了
     * - デバッグが困難なバグの原因
     */
    
    /*
     * ====================================================================
     * ポインタ演算の基礎
     * ====================================================================
     */
    
    /*
     * 【ステップ7】ポインタ演算の例
     * 
     * ポインタは算術演算が可能（配列でよく使用）
     * - ポインタ + 整数: 指定した要素数分アドレスを進める
     * - ポインタ - 整数: 指定した要素数分アドレスを戻す
     * - 2つのポインタの差: 要素数の差を返す
     */
    std::cout << "\n=== Pointer arithmetic example ===" << std::endl;
    
    /*
     * 文字列での簡単なポインタ演算例
     * （注意：std::stringではなく、C文字列での例）
     */
    const char* cString = "HELLO";
    const char* charPTR = cString;
    
    std::cout << "C-string: \"" << cString << "\"" << std::endl;
    std::cout << "charPTR points to: '" << *charPTR << "'" << std::endl;
    
    charPTR++;  // 次の文字を指す
    std::cout << "After charPTR++: '" << *charPTR << "'" << std::endl;
    
    charPTR += 2;  // 2文字進む
    std::cout << "After charPTR += 2: '" << *charPTR << "'" << std::endl;
    
    /*
     * 【注意】std::stringでのポインタ演算
     * - std::stringオブジェクト自体でのポインタ演算は推奨されない
     * - std::string::data()やc_str()で内部データへのポインタを取得可能
     * - ただし学習段階では直接的なポインタ演算は避ける
     */
}

/*
 * ====================================================================
 * main関数
 * ====================================================================
 */
int main(void) {
    /*
     * このファイルは教育目的のポインタデモンストレーション
     * 実際のex02では、より簡潔なmain.cppを使用
     */
    
    std::cout << "/*" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " * CPP01 ex02: Pointer Comprehensive Tutorial" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " */" << std::endl;
    std::cout << std::endl;
    
    demonstratePointers();
    
    return 0;
}

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * ポインタについて理解すべき項目：
 * 
 * □ ポインタはアドレスを格納する変数である
 * □ *演算子で間接参照（値にアクセス）
 * □ &演算子でアドレス取得
 * □ ポインタは再代入可能
 * □ NULLポインタの概念と危険性
 * □ ポインタ自体もメモリを占有する
 * □ ポインタ演算の基本概念
 * □ ポインタ使用前のNULLチェックの重要性
 * 
 * 【実習課題】
 * 1. 異なる型のポインタ（int*, char*）で同様の操作を試す
 * 2. 意図的にNULLポインタにアクセスしてクラッシュを体験
 * 3. ポインタの再代入を複数回行い、値の変化を観察
 * 4. ポインタのサイズ（sizeof）を確認
 */

/*
 * ====================================================================
 * よくある間違いと対策
 * ====================================================================
 * 
 * 【間違い1】初期化されていないポインタの使用
 * ```cpp
 * std::string* ptr;          // 未初期化
 * std::cout << *ptr;         // 危険！
 * ```
 * 対策：宣言時に必ず初期化するか、NULLで初期化
 * 
 * 【間違い2】NULLチェックの忘れ
 * ```cpp
 * std::string* ptr = getNullablePointer();
 * std::cout << *ptr;         // ptrがNULLの可能性
 * ```
 * 対策：使用前に必ずNULLチェック
 * 
 * 【間違い3】ダングリングポインタ
 * ```cpp
 * std::string* ptr;
 * {
 *     std::string temp = "test";
 *     ptr = &temp;           // tempのスコープ外でptrが無効に
 * }
 * std::cout << *ptr;         // 危険！
 * ```
 * 対策：ポインタが指すオブジェクトの生存期間を意識
 * 
 * 【間違い4】ポインタと配列の混同
 * ```cpp
 * std::string* ptr = &someString;
 * ptr[1];                    // 配列アクセスだが単一オブジェクトを指している
 * ```
 * 対策：ポインタが単一オブジェクトか配列かを明確に意識
 */

/*
 * ====================================================================
 * ポインタの利点と使用場面
 * ====================================================================
 * 
 * 【利点】
 * 1. 柔軟性：実行時に指す対象を変更可能
 * 2. 効率性：大きなオブジェクトのコピーを避けられる
 * 3. 動的メモリ：ヒープメモリの管理が可能
 * 4. データ構造：リンクリストや木構造の実装
 * 5. 関数引数：オブジェクトを関数で変更可能
 * 
 * 【主要な使用場面】
 * 1. 動的メモリ確保（new/delete）
 * 2. 関数の引数・戻り値（参照の代替）
 * 3. ポリモーフィズム（基底クラスポインタ）
 * 4. データ構造の実装
 * 5. C言語との互換性
 * 
 * 【注意点】
 * 1. メモリリークの危険性
 * 2. ダングリングポインタ
 * 3. NULL参照によるクラッシュ
 * 4. メモリ破壊の可能性
 * 5. デバッグの難しさ
 */