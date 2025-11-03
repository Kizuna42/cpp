/*
 * ====================================================================
 * CPP01 ex01: Moar brainz! - main関数解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - zombieHorde関数の正しい使用方法
 * - 動的配列の生存期間管理
 * - エラーハンドリングの実践
 * - メモリリーク検出の手法
 * - 配列アクセスパターンの理解
 * 
 * 【重要概念】
 * - 動的配列とポインタの関係
 * - new[] と delete[] の対応
 * - NULLポインタチェックの重要性
 * - エッジケーステストの手法
 */

#include "Zombie.hpp"

/*
 * ====================================================================
 * main関数解説
 * ====================================================================
 */
int main(void) {
    /*
     * 【main関数の役割】
     * 
     * このプログラムでの main の責任：
     * 1. zombieHorde関数のテスト実行
     * 2. 作成された配列の正しい使用
     * 3. メモリの適切な解放 
     * 4. エラーケースの動作確認
     * 5. プログラムの正常終了
     * 
     * 【学習のポイント】
     * - 動的メモリ管理の責任が main にある
     * - エラー処理をしっかり行う
     * - テストケースを網羅的に実行
     */
    
    /*
     * ====================================================================
     * セクション1: 基本的なホード作成とテスト
     * ====================================================================
     */
    std::cout << "=== Creating zombie horde ===" << std::endl;
    
    /*
     * 【ホードサイズの決定】
     * 
     * int hordeSize = 5;
     * 
     * なぜ変数に保存するのか？
     * 1. 可読性: 5 という数字の意味が明確
     * 2. 保守性: 後で変更しやすい
     * 3. 再利用: ループなどで同じ値を使用
     * 4. デバッグ: 異なるサイズでのテストが容易
     * 
     * サイズ選択の考慮点：
     * - 小さすぎる（1-2）: 配列の動作が見えにくい
     * - 大きすぎる（100+）: ログが大量になり見づらい
     * - 適度（5-10）: 動作確認に最適
     */
    int hordeSize = 5;
    
    /*
     * 【zombieHorde関数の呼び出し】
     * 
     * Zombie* horde = zombieHorde(hordeSize, "HordeMember");
     * 
     * 何が起こるのか（内部処理）：
     * 1. new Zombie[5] で5個のZombieオブジェクトを作成
     * 2. 各オブジェクトでデフォルトコンストラクタが呼ばれる
     * 3. "Zombie Unknown created" が5回出力される
     * 4. setName("HordeMember") が5回実行される
     * 5. 配列の先頭ポインタが horde に代入される
     * 
     * 戻り値の型：
     * - Zombie*: 配列の先頭要素へのポインタ
     * - horde[0], horde[1], ..., horde[4] でアクセス可能
     * - NULLの可能性もある（エラー時）
     */
    Zombie* horde = zombieHorde(hordeSize, "HordeMember");
    
    /*
     * ====================================================================
     * エラーチェック: NULLポインタの確認
     * ====================================================================
     */
    if (!horde) {
        /*
         * 【NULLチェックの重要性】
         * 
         * なぜこのチェックが必要なのか？
         * 
         * 安全性：
         * - NULLポインタにアクセスするとクラッシュ
         * - horde[0] のアクセスで未定義動作が発生
         * - プログラムが異常終了する可能性
         * 
         * エラー処理：
         * - zombieHorde が失敗した場合の対応
         * - 適切なエラーメッセージの表示
         * - プログラムの安全な終了
         * 
         * デバッグ：
         * - 問題の早期発見
         * - エラー原因の特定の手助け
         */
        std::cout << "Failed to create horde" << std::endl;
        return 1;  // エラー終了（0以外の値で終了）
        
        /*
         * return 1 の意味：
         * - 0: 正常終了
         * - 1: 一般的なエラー
         * - シェルやスクリプトがエラーを検知可能
         * - システム全体での エラー伝播
         */
    }
    
    /*
     * ====================================================================
     * セクション2: 作成されたホードの動作確認
     * ====================================================================
     */
    std::cout << "\n=== Horde announcement ===" << std::endl;
    
    /*
     * 【配列要素への順次アクセス】
     * 
     * for (int i = 0; i < hordeSize; i++)
     * 
     * ループ設計の重要ポイント：
     * 
     * 1. 開始値: i = 0
     *    - 配列のインデックスは0から開始
     *    - C++の標準的なパターン
     * 
     * 2. 終了条件: i < hordeSize  
     *    - hordeSize = 5 なら i は 0,1,2,3,4
     *    - i <= hordeSize は範囲外アクセス（危険）
     *    - 正確な配列サイズの管理が重要
     * 
     * 3. 増分: i++
     *    - 全要素を順次処理
     *    - 処理漏れや重複を防ぐ
     */
    for (int i = 0; i < hordeSize; i++) {
        /*
         * 【配列アクセスの詳細解説】
         * 
         * horde[i] の内部動作：
         * - horde: Zombie* 型のポインタ（配列の先頭）
         * - [i]: i番目の要素にアクセス
         * - horde[i]: *(horde + i) と同等
         * - Zombie オブジェクトそのものを返す（参照として）
         * 
         * メモリレイアウト：
         * ```
         * horde → [Zombie0][Zombie1][Zombie2][Zombie3][Zombie4]
         *          ↑       ↑       ↑       ↑       ↑
         *       horde[0] horde[1] horde[2] horde[3] horde[4]
         * ```
         */
        std::cout << "Zombie #" << i << ": ";
        horde[i].announce();
        
        /*
         * 期待される出力：
         * "Zombie #0: HordeMember: BraiiiiiiinnnzzzZ..."
         * "Zombie #1: HordeMember: BraiiiiiiinnnzzzZ..."
         * "Zombie #2: HordeMember: BraiiiiiiinnnzzzZ..."
         * "Zombie #3: HordeMember: BraiiiiiiinnnzzzZ..."
         * "Zombie #4: HordeMember: BraiiiiiiinnnzzzZ..."
         * 
         * 【重要な観察点】
         * - 各要素が独立して動作している
         * - 全て同じ名前だが、別々のオブジェクト
         * - 各オブジェクトが自分の announce() を実行
         */
    }
    
    /*
     * ====================================================================
     * セクション3: エッジケースのテスト
     * ====================================================================
     */
    std::cout << "\n=== Testing edge cases ===" << std::endl;
    
    /*
     * 【エッジケーステストの重要性】
     * 
     * なぜエッジケースをテストするのか？
     * 
     * 1. 堅牢性の確認
     *    - 異常入力に対する動作確認
     *    - プログラムがクラッシュしないことを確認
     * 
     * 2. 仕様の理解
     *    - 正常範囲と異常範囲の境界を明確化
     *    - エラーハンドリングの動作を確認
     * 
     * 3. デバッグの準備
     *    - 問題が起きやすいケースを事前に特定
     *    - エラー処理の正しさを検証
     */
    
    /*
     * 【テストケース1: 空のホード（N=0）】
     */
    std::cout << "Testing empty horde (N=0):" << std::endl;
    Zombie* emptyHorde = zombieHorde(0, "EmptyTest");
    
    /*
     * 期待される動作：
     * 1. zombieHorde内でエラーチェック（N <= 0）
     * 2. "Error: Invalid horde size" メッセージ出力
     * 3. NULL ポインタの返却
     * 4. オブジェクト作成なし（"created"メッセージなし）
     */
    
    if (!emptyHorde) {
        std::cout << "Correctly handled empty horde case" << std::endl;
        /*
         * 正常なエラー処理を確認：
         * - NULLが正しく返された
         * - プログラムがクラッシュしていない
         * - エラーが適切に処理された
         */
    }
    
    /*
     * 【テストケース2: 負のホードサイズ（N=-1）】
     */
    std::cout << "\nTesting negative horde (N=-1):" << std::endl;
    Zombie* negativeHorde = zombieHorde(-1, "NegativeTest");
    
    /*
     * 期待される動作：
     * - 空のホードと同じエラー処理
     * - N <= 0 の条件でキャッチされる
     * - NULL ポインタの返却
     */
    
    if (!negativeHorde) {
        std::cout << "Correctly handled negative horde case" << std::endl;
    }
    
    /*
     * 【テストケース3: 単体ホード（N=1）】
     */
    std::cout << "\nTesting single zombie horde (N=1):" << std::endl;
    Zombie* singleHorde = zombieHorde(1, "Loner");
    
    /*
     * 期待される動作：
     * 1. new Zombie[1] で1個のオブジェクト作成
     * 2. "Zombie Unknown created" が1回出力
     * 3. setName("Loner") で名前変更
     * 4. 正常なポインタの返却
     */
    
    if (singleHorde) {
        /*
         * 単一要素の配列アクセス：
         * - singleHorde[0] で唯一の要素にアクセス
         * - 配列でも単一でもアクセス方法は同じ
         * - ただし delete[] が必要（配列として確保したため）
         */
        singleHorde[0].announce();
        
        /*
         * 期待される出力：
         * "Loner: BraiiiiiiinnnzzzZ..."
         */
        
        /*
         * 【重要】単一要素でも delete[] を使用
         * 
         * なぜ delete singleHorde ではダメなのか？
         * - new[] で確保したメモリは delete[] で解放
         * - new で確保したメモリは delete で解放
         * - 混在すると未定義動作（危険）
         * 
         * 覚え方：
         * - new Zombie[1] → delete[] 必須
         * - new Zombie() → delete 必須
         */
        delete[] singleHorde;
        
        /*
         * 期待される解放ログ：
         * "Zombie Loner destroyed"
         */
    }
    
    /*
     * ====================================================================
     * セクション4: メインホードの解放
     * ====================================================================
     */
    std::cout << "\n=== Destroying horde ===" << std::endl;
    
    /*
     * 【配列の解放】
     * delete[] horde;
     * 
     * 内部で起こること：
     * 1. 各配列要素のデストラクタが呼ばれる
     * 2. "Zombie HordeMember destroyed" が5回出力される
     * 3. 配列全体のメモリが解放される
     * 4. horde ポインタは無効になる（ダングリングポインタ）
     * 
     * 解放順序（実装依存）：
     * - 通常は逆順（horde[4] → horde[0]）
     * - または正順（horde[0] → horde[4]）
     * - 順序は実装に依存するが全要素で確実に実行
     */
    delete[] horde;
    
    /*
     * 【重要】解放後のポインタの扱い
     * 
     * delete[] 実行後：
     * - horde は無効なポインタ（ダングリングポインタ）
     * - horde[i] へのアクセスは未定義動作
     * - horde = NULL; で明示的にNULLにすることも可能
     * 
     * 安全な実装パターン：
     * ```cpp
     * delete[] horde;
     * horde = NULL;  // ダングリングポインタを防ぐ
     * ```
     * 
     * ただし、main関数の最後なので今回は省略
     */
    
    /*
     * ====================================================================
     * プログラムの正常終了
     * ====================================================================
     */
    return 0;
    
    /*
     * return 0 の意味：
     * - プログラムが正常に終了したことを示す
     * - オペレーティングシステムに成功を報告
     * - シェルスクリプト等での後続処理に影響
     * 
     * 【期待される完全な出力例】
     * 
     * === Creating zombie horde ===
     * Zombie Unknown created      ← horde[0] デフォルトコンストラクタ
     * Zombie Unknown created      ← horde[1] デフォルトコンストラクタ
     * Zombie Unknown created      ← horde[2] デフォルトコンストラクタ
     * Zombie Unknown created      ← horde[3] デフォルトコンストラクタ
     * Zombie Unknown created      ← horde[4] デフォルトコンストラクタ
     * 
     * === Horde announcement ===
     * Zombie #0: HordeMember: BraiiiiiiinnnzzzZ...
     * Zombie #1: HordeMember: BraiiiiiiinnnzzzZ...
     * Zombie #2: HordeMember: BraiiiiiiinnnzzzZ...
     * Zombie #3: HordeMember: BraiiiiiiinnnzzzZ...
     * Zombie #4: HordeMember: BraiiiiiiinnnzzzZ...
     * 
     * === Testing edge cases ===
     * Testing empty horde (N=0):
     * Error: Invalid horde size
     * Correctly handled empty horde case
     * 
     * Testing negative horde (N=-1):
     * Error: Invalid horde size
     * Correctly handled negative horde case
     * 
     * Testing single zombie horde (N=1):
     * Zombie Unknown created      ← singleHorde[0] デフォルトコンストラクタ
     * Loner: BraiiiiiiinnnzzzZ...
     * Zombie Loner destroyed      ← singleHorde[0] デストラクタ
     * 
     * === Destroying horde ===
     * Zombie HordeMember destroyed ← horde[?] デストラクタ（順序は実装依存）
     * Zombie HordeMember destroyed ← horde[?] デストラクタ
     * Zombie HordeMember destroyed ← horde[?] デストラクタ
     * Zombie HordeMember destroyed ← horde[?] デストラクタ
     * Zombie HordeMember destroyed ← horde[?] デストラクタ
     */
}

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このmain関数を理解したか確認：
 * 
 * □ zombieHorde()の戻り値をNULLチェックしている
 * □ 配列のサイズを正確に管理している（hordeSize変数）
 * □ 配列アクセスが範囲内である（i < hordeSize）
 * □ new[]で作成した配列をdelete[]で解放している
 * □ エッジケース（N=0, N=-1, N=1）をテストしている
 * □ エラー時に適切な終了コード（1）を返している
 * □ 正常時に成功コード（0）を返している
 * 
 * 【実習課題】
 * 1. hordeSize を変更して動作確認
 * 2. delete[] を忘れてメモリリークを体験
 * 3. 範囲外アクセス（i <= hordeSize）を試してみる
 * 4. エラーケースのNULLチェックを外して実行
 * 5. より多くのエッジケースを追加
 */

/*
 * ====================================================================
 * よくある間違いと対策
 * ====================================================================
 * 
 * 【間違い1】NULLチェックの忘れ
 * ```cpp
 * Zombie* horde = zombieHorde(0, "Test");
 * horde[0].announce();  // クラッシュ！
 * ```
 * 対策：必ずNULLチェックを実装
 * 
 * 【間違い2】配列サイズの管理ミス
 * ```cpp
 * for (int i = 0; i <= hordeSize; i++) {  // 範囲外アクセス！
 *     horde[i].announce();
 * }
 * ```
 * 対策：i < hordeSize の条件を正確に
 * 
 * 【間違い3】delete/delete[]の混同
 * ```cpp
 * Zombie* horde = zombieHorde(5, "Test");
 * delete horde;  // 危険！未定義動作
 * ```
 * 対策：new[]にはdelete[]を使用
 * 
 * 【間違い4】二重解放
 * ```cpp
 * delete[] horde;
 * delete[] horde;  // 二重解放！未定義動作
 * ```
 * 対策：解放後はhorde = NULLで無効化
 * 
 * 【間違い5】解放忘れ
 * ```cpp
 * Zombie* horde = zombieHorde(5, "Test");
 * // delete[] horde; を忘れる
 * return 0;  // メモリリーク！
 * ```
 * 対策：valgrindなどでメモリリーク検出
 */

/*
 * ====================================================================
 * 次のステップ
 * ====================================================================
 * 
 * この実装を完全に理解したら：
 * 
 * 1. ex02: HI THIS IS BRAIN
 *    - ポインタと参照の違いを学習
 *    - メモリアドレスの理解を深化
 * 
 * 2. ex03: Unnecessary violence  
 *    - より複雑なクラス設計
 *    - オブジェクト間の関係性
 * 
 * 3. 発展学習:
 *    - std::vector による動的配列（STL使用可能時）
 *    - スマートポインタによる自動メモリ管理（C++11以降）
 *    - RAII パターンのより深い理解
 */