/*
 * ====================================================================
 * CPP01 ex02: HI THIS IS BRAIN - 参照詳細解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 参照の基本概念と使用方法
 * - 参照とポインタの根本的な違い
 * - 参照の初期化と生存期間
 * - 参照の制約と利点
 * - 参照使用時の注意点
 * 
 * 【重要概念】
 * - 参照は「別名（エイリアス）」
 * - 初期化時に必ず実体を指定
 * - 再代入不可（一度決めたら変更不可）
 * - NULL参照は存在しない
 */

#include <string>
#include <iostream>

/*
 * ====================================================================
 * 参照デモンストレーション関数
 * ====================================================================
 */
void demonstrateReferences() {
    std::cout << "=== Reference Demonstration ===" << std::endl;
    
    /*
     * ====================================================================
     * 基本的な参照の作成と使用
     * ====================================================================
     */
    
    /*
     * 【ステップ1】元となる変数の作成
     */
    std::string brain = "HI THIS IS BRAIN";
    std::cout << "Original variable 'brain': \"" << brain << "\"" << std::endl;
    std::cout << "Address of 'brain': " << &brain << std::endl;
    
    /*
     * 【ステップ2】参照の宣言と初期化
     * 
     * std::string& stringREF = brain;
     * 
     * 構文分解：
     * - std::string&: 参照の型（std::stringへの参照）
     * - stringREF: 参照の名前（実際は brain の別名）
     * - = brain: 初期化（brain を参照するように設定）
     * 
     * 【重要】参照の初期化について
     * - 宣言と同時に必ず初期化が必要
     * - std::string& ref; だけではコンパイルエラー
     * - 初期化後は再代入不可（常に同じオブジェクトを参照）
     */
    std::string& stringREF = brain;
    
    /*
     * 【参照の特徴確認】
     * 参照は元の変数と完全に同じメモリアドレスを持つ
     */
    std::cout << "\nReference 'stringREF' created:" << std::endl;
    std::cout << "Address of stringREF: " << &stringREF << std::endl;
    std::cout << "Address of brain:     " << &brain << std::endl;
    std::cout << "Are they the same?    " << (&stringREF == &brain ? "Yes" : "No") << std::endl;
    
    /*
     * 【重要な概念】参照は別名（エイリアス）
     * 
     * - stringREF と brain は同じメモリ位置を指す
     * - stringREF は brain の完全な別名
     * - メモリ上では区別がつかない
     * - 新しいメモリ領域は確保されない
     * 
     * メモリレイアウト：
     * ```
     * アドレス     | 内容                | アクセス方法
     * 0x7fff1234   | "HI THIS IS BRAIN" | brain または stringREF
     * ```
     */
    
    /*
     * ====================================================================
     * 参照を通じた値の読み取り
     * ====================================================================
     */
    
    /*
     * 【ステップ3】参照による値の読み取り
     * 
     * 参照の読み取りは直接的：
     * - ポインタのような間接参照演算子（*）は不要
     * - 変数名と同じ感覚で使用可能
     * - より自然で読みやすいコード
     */
    std::cout << "\nReading value through reference:" << std::endl;
    std::cout << "Value of stringREF: \"" << stringREF << "\"" << std::endl;
    
    /*
     * 【検証】参照と元の変数の内容比較
     */
    std::cout << "\nVerification:" << std::endl;
    std::cout << "brain == stringREF: " << (brain == stringREF ? "true" : "false") << std::endl;
    std::cout << "Same object?        " << (&brain == &stringREF ? "true" : "false") << std::endl;
    
    /*
     * ====================================================================
     * 参照を通じた値の変更
     * ====================================================================
     */
    
    /*
     * 【ステップ4】参照による値の変更
     * 
     * stringREF = "新しい値";
     * 
     * 何が起こるのか：
     * 1. stringREF は brain の別名なので、brain の内容が変更される
     * 2. 代入演算子が呼ばれ、文字列の内容が置き換えられる
     * 3. 参照自体は変更されない（常に同じオブジェクトを参照）
     */
    std::cout << "\n=== Modifying value through reference ===" << std::endl;
    std::cout << "Before: brain = \"" << brain << "\"" << std::endl;
    
    stringREF = "Modified via reference";
    
    std::cout << "After stringREF = \"Modified via reference\":" << std::endl;
    std::cout << "brain = \"" << brain << "\"" << std::endl;
    std::cout << "stringREF = \"" << stringREF << "\"" << std::endl;
    
    /*
     * 【重要】参照の変更 vs 参照先の変更
     * 
     * stringREF = "Modified via reference"; は：
     * - 参照自体を変更するのではない
     * - 参照が指すオブジェクト（brain）の内容を変更
     * - 参照は常に同じオブジェクトを指し続ける
     */
    
    /*
     * ====================================================================
     * 参照の制約: 再代入不可
     * ====================================================================
     */
    
    /*
     * 【ステップ5】参照の再代入が不可能であることの確認
     * 
     * 参照の重要な制約：
     * - 初期化後は別のオブジェクトを参照できない
     * - ポインタのような柔軟性はない
     * - 安全性と引き換えに制約がある
     */
    std::cout << "\n=== Reference reassignment impossibility ===" << std::endl;
    
    std::string anotherString = "Another brain message";
    std::cout << "Created another string: \"" << anotherString << "\"" << std::endl;
    std::cout << "Address of anotherString: " << &anotherString << std::endl;
    
    /*
     * 【重要】参照の「再代入」を試してみる
     * 
     * stringREF = anotherString;
     * 
     * これは参照の再代入ではなく、参照先オブジェクトの値の変更：
     * - stringREF が anotherString を参照するようになるのではない
     * - brain の内容が anotherString の内容で置き換えられる
     * - stringREF は依然として brain を参照している
     */
    std::cout << "\nBefore 'reassignment':" << std::endl;
    std::cout << "stringREF address: " << &stringREF << std::endl;
    std::cout << "brain address:     " << &brain << std::endl;
    
    stringREF = anotherString;  // これは代入、再参照ではない
    
    std::cout << "\nAfter stringREF = anotherString:" << std::endl;
    std::cout << "stringREF address: " << &stringREF << std::endl;
    std::cout << "brain address:     " << &brain << std::endl;
    std::cout << "brain value:       \"" << brain << "\"" << std::endl;
    std::cout << "stringREF value:   \"" << stringREF << "\"" << std::endl;
    std::cout << "anotherString:     \"" << anotherString << "\" (unchanged)" << std::endl;
    
    /*
     * 【観察結果】
     * - stringREF のアドレスは変わらない（brain と同じまま）
     * - brain の内容が anotherString の内容で置き換えられた
     * - anotherString 自体は変更されていない
     * - これは参照の再代入ではなく、値のコピー
     */
    
    /*
     * ====================================================================
     * 参照の生存期間と安全性
     * ====================================================================
     */
    
    /*
     * 【ステップ6】参照の生存期間について
     * 
     * 参照の安全性：
     * - NULL参照は存在しない（コンパイル時に保証）
     * - 必ず有効なオブジェクトを参照
     * - 参照先オブジェクトの生存期間を意識する必要
     */
    std::cout << "\n=== Reference lifetime and safety ===" << std::endl;
    
    /*
     * 安全な参照の例
     */
    {
        std::string localVar = "Local variable";
        std::string& localREF = localVar;
        
        std::cout << "Inside scope - localREF: \"" << localREF << "\"" << std::endl;
        
        /*
         * ここでlocalREFは安全に使用可能
         * localVarが存在している限り、localREFも有効
         */
    }
    /*
     * スコープ外では localREF は無効
     * ただし、参照自体がスコープ外なので問題にならない
     */
    
    /*
     * 【危険な例】ダングリング参照（コメントアウト）
     * 
     * ```cpp
     * std::string& getDanglingReference() {
     *     std::string temp = "Temporary";
     *     return temp;  // 危険！tempはスコープ外で破棄される
     * }
     * ```
     * 
     * このような関数から返される参照は危険：
     * - 参照先オブジェクトが既に破棄されている
     * - アクセスすると未定義動作
     * - コンパイラが警告を出すことが多い
     */
    
    /*
     * ====================================================================
     * 参照の初期化バリエーション
     * ====================================================================
     */
    
    /*
     * 【ステップ7】様々な初期化パターン
     */
    std::cout << "\n=== Reference initialization patterns ===" << std::endl;
    
    /*
     * パターン1: 通常の変数への参照
     */
    std::string normalVar = "Normal variable";
    std::string& normalREF = normalVar;
    std::cout << "Normal reference: \"" << normalREF << "\"" << std::endl;
    
    /*
     * パターン2: const参照（読み取り専用）
     */
    const std::string& constREF = normalVar;
    std::cout << "Const reference: \"" << constREF << "\"" << std::endl;
    // constREF = "Cannot modify"; // コンパイルエラー
    
    /*
     * パターン3: const変数への参照
     */
    const std::string constVar = "Constant variable";
    const std::string& constVarREF = constVar;
    std::cout << "Reference to const: \"" << constVarREF << "\"" << std::endl;
    
    /*
     * パターン4: 一時オブジェクトへのconst参照
     * （C++の特殊な機能：一時オブジェクトの生存期間延長）
     */
    const std::string& tempREF = std::string("Temporary object");
    std::cout << "Reference to temporary: \"" << tempREF << "\"" << std::endl;
    /*
     * 注意：非constの参照は一時オブジェクトを参照できない
     * std::string& invalidREF = std::string("Temp"); // コンパイルエラー
     */
}

/*
 * ====================================================================
 * main関数
 * ====================================================================
 */
int main(void) {
    /*
     * このファイルは教育目的の参照デモンストレーション
     * 実際のex02では、より簡潔なmain.cppを使用
     */
    
    std::cout << "/*" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " * CPP01 ex02: Reference Comprehensive Tutorial" << std::endl;
    std::cout << " * ====================================================================" << std::endl;
    std::cout << " */" << std::endl;
    std::cout << std::endl;
    
    demonstrateReferences();
    
    return 0;
}

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * 参照について理解すべき項目：
 * 
 * □ 参照は元の変数の別名（エイリアス）である
 * □ 宣言時に必ず初期化が必要
 * □ 再代入不可（常に同じオブジェクトを参照）
 * □ NULL参照は存在しない
 * □ 参照と元の変数は同じメモリアドレス
 * □ 間接参照演算子（*）は不要
 * □ const参照の概念と使用場面
 * □ 参照先オブジェクトの生存期間の重要性
 * 
 * 【実習課題】
 * 1. 異なる型の参照（int&, char&）で同様の操作を試す
 * 2. const参照の制約を確認（書き込み禁止）
 * 3. 参照の初期化忘れでコンパイルエラーを体験
 * 4. スコープと参照の生存期間の関係を確認
 */

/*
 * ====================================================================
 * よくある間違いと対策
 * ====================================================================
 * 
 * 【間違い1】参照の初期化忘れ
 * ```cpp
 * std::string& ref;          // コンパイルエラー
 * ```
 * 対策：宣言と同時に必ず初期化
 * 
 * 【間違い2】参照の再代入と値の代入の混同
 * ```cpp
 * std::string& ref = var1;
 * ref = var2;                // 参照の再代入ではなく、値の代入
 * ```
 * 理解：参照は常に同じオブジェクトを参照、値のみが変更される
 * 
 * 【間違い3】ダングリング参照
 * ```cpp
 * std::string& getRef() {
 *     std::string temp = "temp";
 *     return temp;           // 危険！
 * }
 * ```
 * 対策：参照先オブジェクトの生存期間を意識
 * 
 * 【間違い4】一時オブジェクトへの非const参照
 * ```cpp
 * std::string& ref = std::string("temp"); // コンパイルエラー
 * ```
 * 対策：一時オブジェクトにはconst参照を使用
 */

/*
 * ====================================================================
 * 参照の利点と使用場面
 * ====================================================================
 * 
 * 【利点】
 * 1. 安全性：NULL参照が存在しない
 * 2. 簡潔性：間接参照演算子（*）が不要
 * 3. 効率性：大きなオブジェクトのコピーを避けられる
 * 4. 可読性：変数と同じ感覚で使用可能
 * 5. 初期化強制：宣言時に必ず有効なオブジェクトを指定
 * 
 * 【主要な使用場面】
 * 1. 関数の引数（大きなオブジェクトの受け渡し）
 * 2. 関数の戻り値（チェーン呼び出し）
 * 3. for文でのコンテナ要素アクセス
 * 4. エイリアス（長い名前の短縮）
 * 5. オペレータオーバーロード
 * 
 * 【制約】
 * 1. 再代入不可（柔軟性が低い）
 * 2. NULL値を取れない
 * 3. 配列として使用不可
 * 4. ポインタ演算不可
 * 5. 初期化が必須
 */

/*
 * ====================================================================
 * 参照 vs ポインタ 使い分けガイド
 * ====================================================================
 * 
 * 【参照を使うべき場面】
 * - 単純なエイリアスが欲しい場合
 * - 関数引数でオブジェクトを変更したい場合
 * - NULLになることがない場合
 * - 再代入の必要がない場合
 * - コードの可読性を重視する場合
 * 
 * 【ポインタを使うべき場面】
 * - 動的メモリ管理が必要な場合
 * - NULLの可能性がある場合
 * - 再代入が必要な場合
 * - ポインタ演算が必要な場合
 * - データ構造（リンクリスト等）の実装
 * 
 * 【一般的な推奨】
 * 1. まず参照を検討
 * 2. 参照で不十分ならポインタ
 * 3. 安全性を優先
 * 4. コードの意図を明確に
 */