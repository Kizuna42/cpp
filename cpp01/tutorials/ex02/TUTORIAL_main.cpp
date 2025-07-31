/*
 * ====================================================================
 * CPP01 ex02: HI THIS IS BRAIN - ポインタと参照の本質理解
 * ====================================================================
 * 
 * この演習は、ポインタと参照の根本的な違いを体験的に理解するための
 * シンプルながら重要な実装です。メモリアドレスの概念を視覚化します。
 */

#include <string>
#include <iostream>

/*
 * ====================================================================
 * main関数 - ポインタと参照の完全比較デモ
 * ====================================================================
 */
int main(void) {
    /*
     * ====================================================================
     * 基本変数とポインタ・参照の作成
     * ====================================================================
     */
    
    /*
     * 元となる文字列変数の作成
     * 
     * std::string brain = "HI THIS IS BRAIN";
     * 
     * 何が起こっているのか？
     * 1. スタック上にstd::stringオブジェクトが作成される
     * 2. 変数名 "brain" でそのオブジェクトにアクセス可能
     * 3. 内部で文字列データ "HI THIS IS BRAIN" が保存される
     * 4. brain変数は特定のメモリアドレスを持つ
     */
    std::string brain = "HI THIS IS BRAIN";
    
    /*
     * ポインタの作成と初期化
     * 
     * std::string* stringPTR = &brain;
     * 
     * 詳細解説：
     * - std::string*: std::stringオブジェクトを指すポインタ型
     * - stringPTR: ポインタ変数の名前
     * - &brain: brain変数のアドレスを取得（アドレス演算子）
     * - =: ポインタにアドレスを代入
     * 
     * 結果：stringPTRはbrainと同じメモリ位置を指す
     */
    std::string* stringPTR = &brain;
    
    /*
     * 参照の作成と初期化
     * 
     * std::string& stringREF = brain;
     * 
     * 詳細解説：
     * - std::string&: std::stringオブジェクトへの参照型
     * - stringREF: 参照変数の名前
     * - = brain: brain変数への参照を作成
     * 
     * 重要な違い：
     * - ポインタ: &brain（アドレスを代入）
     * - 参照: brain（オブジェクト自体を参照）
     * 
     * 結果：stringREFはbrainの別名（エイリアス）となる
     */
    std::string& stringREF = brain;
    
    /*
     * ====================================================================
     * メモリアドレスの表示と比較
     * ====================================================================
     */
    std::cout << "=== Memory addresses ===" << std::endl;
    
    /*
     * brain変数のアドレス表示
     * 
     * &brain: アドレス演算子でbrain変数のメモリアドレスを取得
     * 
     * 出力例: 0x7ffeefbff5c8 (実際のアドレスは実行毎に変わる)
     */
    std::cout << "Address of brain variable: " << &brain << std::endl;
    
    /*
     * ポインタが保持するアドレス表示
     * 
     * stringPTR: ポインタ変数の値（＝指している先のアドレス）
     * 
     * 重要：&brainと同じアドレスが表示されるはず
     */
    std::cout << "Address held by stringPTR: " << stringPTR << std::endl;
    
    /*
     * 参照のアドレス表示
     * 
     * &stringREF: 参照のアドレス（実際はbrainのアドレス）
     * 
     * 重要：&brainと同じアドレスが表示されるはず
     * 参照は別名なので、アドレスも同じになる
     */
    std::cout << "Address held by stringREF: " << &stringREF << std::endl;
    
    /*
     * 【学習ポイント】3つのアドレスが全て同じであることを確認
     * - &brain == stringPTR == &stringREF
     * - これが「同じメモリ位置を指している」証拠
     */
    
    /*
     * ====================================================================
     * 値の表示と間接参照の比較
     * ====================================================================
     */
    std::cout << "\n=== Values ===" << std::endl;
    
    /*
     * 直接アクセス: brain変数の値
     * 
     * brain: 変数に直接アクセス
     * 出力: "HI THIS IS BRAIN"
     */
    std::cout << "Value of brain variable:   " << brain << std::endl;
    
    /*
     * ポインタ経由アクセス: 間接参照
     * 
     * *stringPTR: ポインタの間接参照演算子
     * - stringPTR: ポインタが指すアドレス
     * - *stringPTR: そのアドレスにあるオブジェクトの値
     * 
     * 出力: "HI THIS IS BRAIN" (brainと同じ値)
     */
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    
    /*
     * 参照経由アクセス: 透明なアクセス
     * 
     * stringREF: 参照は自動的に元のオブジェクトにアクセス
     * - 特別な演算子不要
     * - brainと全く同じように使える
     * 
     * 出力: "HI THIS IS BRAIN" (brainと同じ値)
     */
    std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;
    
    /*
     * ====================================================================
     * 実践的なポインタ vs 参照のデモンストレーション
     * ====================================================================
     */
    std::cout << "\n=== Demonstration: Pointer vs Reference ===" << std::endl;
    
    std::cout << "Original string: \"" << brain << "\"" << std::endl;
    
    /*
     * ポインタ経由での値変更
     * 
     * *stringPTR = "Modified via pointer";
     * 
     * 何が起こるのか？
     * 1. stringPTRが指すメモリ位置（brainの場所）にアクセス
     * 2. そこにある文字列オブジェクトの値を変更
     * 3. brain, stringREFからも同じ変更が見える
     * 
     * 重要：元のオブジェクト（brain）が変更される
     */
    *stringPTR = "Modified via pointer";
    std::cout << "After modification via pointer: \"" << brain << "\"" << std::endl;
    std::cout << "stringREF now shows: \"" << stringREF << "\"" << std::endl;
    
    /*
     * 参照経由での値変更
     * 
     * stringREF = "Modified via reference";
     * 
     * 何が起こるのか？
     * 1. stringREFは透明にbrainにアクセス
     * 2. brain変数の値を直接変更
     * 3. ポインタ経由でも同じ変更が見える
     * 
     * 重要：これも元のオブジェクト（brain）が変更される
     */
    stringREF = "Modified via reference";
    std::cout << "After modification via reference: \"" << brain << "\"" << std::endl;
    std::cout << "stringPTR now points to: \"" << *stringPTR << "\"" << std::endl;
    
    /*
     * ====================================================================
     * ポインタと参照の重要な違いの解説
     * ====================================================================
     */
    std::cout << "\n=== Key Differences ===" << std::endl;
    
    /*
     * 1. 再代入の可否
     * 
     * ポインタ：
     * std::string other = "Another string";
     * stringPTR = &other;  // 可能：別のオブジェクトを指すよう変更
     * 
     * 参照：
     * std::string& stringREF2 = other;  // 不可能：既に初期化済み
     * stringREF = other;                // これは値の代入（参照先変更ではない）
     */
    std::cout << "1. Pointer can be reassigned, reference cannot" << std::endl;
    
    /*
     * 2. NULL値の可否
     * 
     * ポインタ：
     * std::string* ptr = NULL;     // 可能：何も指さないポインタ
     * std::string* ptr2 = nullptr; // C++11以降
     * 
     * 参照：
     * std::string& ref;            // 不可能：初期化が必須
     * std::string& ref = NULL;     // 不可能：NULLは参照できない
     */
    std::cout << "2. Pointer can be NULL, reference must be initialized" << std::endl;
    
    /*
     * 3. ポインタ演算の可否
     * 
     * ポインタ：
     * stringPTR + 1;               // 可能：次のメモリ位置
     * stringPTR++;                 // 可能：ポインタを進める
     * 
     * 参照：
     * stringREF + 1;               // 不可能：参照には演算子がない
     * stringREF++;                 // 不可能：参照自体は変更不可
     */
    std::cout << "3. Pointer arithmetic possible, not with references" << std::endl;
    
    /*
     * 4. 同じメモリ位置へのアクセス
     * 
     * 適切に設定されていれば：
     * - &brain == stringPTR == &stringREF
     * - brain == *stringPTR == stringREF
     * 
     * すべて同じオブジェクトにアクセスしている
     */
    std::cout << "4. Both access the same memory location when properly set" << std::endl;
    
    return 0;
}

/*
 * ====================================================================
 * 学習のポイントと応用
 * ====================================================================
 * 
 * 【このプログラムから学ぶべきこと】
 * 
 * 1. アドレスの概念
 *    - 全ての変数はメモリ上の特定の位置に存在する
 *    - &演算子でアドレスを取得できる
 *    - ポインタはアドレスを格納する変数
 * 
 * 2. 間接参照の概念
 *    - *演算子でポインタが指すオブジェクトにアクセス
 *    - 参照は自動的な間接参照（透明）
 * 
 * 3. 同一性の理解
 *    - 異なる方法で同じオブジェクトにアクセス可能
 *    - 一つを変更すると全てに反映される
 * 
 * 【実用的な応用】
 * 
 * 1. 関数パラメータでの使い分け
 *    - 値を変更したい場合：ポインタまたは参照
 *    - NULLの可能性がある場合：ポインタ
 *    - 常に有効な値がある場合：参照
 * 
 * 2. 設計での判断基準
 *    - シンプルさ重視：参照
 *    - 柔軟性重視：ポインタ
 *    - 配列操作：ポインタ（演算が必要）
 * 
 * 【よくある誤解】
 * 
 * 1. 「参照はポインタより安全」
 *    → 正解：用途によって適切さが変わる
 * 
 * 2. 「ポインタは危険」
 *    → 正解：適切に使用すれば安全で強力
 * 
 * 3. 「参照は別のオブジェクト」
 *    → 正解：参照は既存オブジェクトの別名
 */

/*
 * ====================================================================
 * 実行時の期待される出力
 * ====================================================================
 * 
 * === Memory addresses ===
 * Address of brain variable: 0x7ffeefbff5c8
 * Address held by stringPTR: 0x7ffeefbff5c8
 * Address held by stringREF: 0x7ffeefbff5c8
 * 
 * === Values ===
 * Value of brain variable:   HI THIS IS BRAIN
 * Value pointed to by stringPTR: HI THIS IS BRAIN
 * Value pointed to by stringREF: HI THIS IS BRAIN
 * 
 * === Demonstration: Pointer vs Reference ===
 * Original string: "HI THIS IS BRAIN"
 * After modification via pointer: "Modified via pointer"
 * stringREF now shows: "Modified via pointer"
 * After modification via reference: "Modified via reference"
 * stringPTR now points to: "Modified via reference"
 * 
 * === Key Differences ===
 * 1. Pointer can be reassigned, reference cannot
 * 2. Pointer can be NULL, reference must be initialized
 * 3. Pointer arithmetic possible, not with references
 * 4. Both access the same memory location when properly set
 * 
 * 【重要な観察ポイント】
 * - 3つのアドレスが全て同じ値
 * - 一つを変更すると他も変更される
 * - 参照とポインタの使用感の違い
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * □ &演算子でアドレスを取得できる
 * □ *演算子でポインタの間接参照ができる
 * □ 参照は元のオブジェクトの別名であることを理解
 * □ ポインタと参照の4つの主な違いを説明できる
 * □ いつポインタを、いつ参照を使うべきか判断できる
 * 
 * 【実習課題】
 * 1. 複数の変数で同様の実験をしてみる
 * 2. int型やfloat型でも同じ実験をしてみる
 * 3. 配列とポインタの関係を調べてみる
 * 4. 関数の引数でポインタと参照を使い分けてみる
 */