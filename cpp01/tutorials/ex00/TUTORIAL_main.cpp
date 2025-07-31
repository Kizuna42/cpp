/*
 * ====================================================================
 * CPP01 ex00: main関数実装解説版
 * ====================================================================
 * 
 * このmain関数は、スタックとヒープでのメモリ管理の違いを
 * 実際に体験するための包括的なデモンストレーションです。
 * 各セクションの動作を詳しく解説します。
 */

#include "Zombie.hpp"

/*
 * ====================================================================
 * main関数の全体構成解説
 * ====================================================================
 * 
 * この関数の学習目的：
 * 1. newZombie（ヒープ確保）の使用方法
 * 2. randomChump（スタック確保）の使用方法  
 * 3. 直接的なスタック変数作成の比較
 * 4. スコープによる自動削除の観察
 * 5. メモリ管理責任の違いの実体験
 */
int main(void) {
    /*
     * ====================================================================
     * セクション1: ヒープ確保のテスト (newZombie)
     * ====================================================================
     */
    std::cout << "=== Testing heap allocation (newZombie) ===" << std::endl;
    
    /*
     * ヒープにZombieオブジェクトを作成
     * 
     * 何が起こっているのか？
     * 1. newZombie("HeapWalker") が呼ばれる
     * 2. 内部で new Zombie("HeapWalker") が実行される
     * 3. ヒープメモリにZombieオブジェクトが作成される
     * 4. コンストラクタが呼ばれ "Zombie HeapWalker created" が出力される
     * 5. オブジェクトのアドレス（ポインタ）が返される
     * 6. そのポインタが heapZombie 変数に格納される
     */
    Zombie* heapZombie = newZombie("HeapWalker");
    
    /*
     * 【重要】ポインタを使ったメンバ関数呼び出し
     * 
     * 構文の説明：
     * - heapZombie->announce() : ポインタ経由でのメンバ関数呼び出し
     * - (*heapZombie).announce() : 上記と同じ意味（ただし可読性が悪い）
     * 
     * なぜ -> を使うのか？
     * - ポインタが指すオブジェクトのメンバにアクセスする標準的な方法
     * - . 演算子はオブジェクト直接アクセス用
     * - -> 演算子はポインタ経由アクセス用
     */
    heapZombie->announce();
    
    /*
     * 【超重要】手動でのメモリ解放
     * 
     * なぜ delete が必要なのか？
     * 1. newで確保したメモリは自動解放されない
     * 2. プログラマーが責任を持って解放する必要がある
     * 3. 解放しないとメモリリークが発生する
     * 
     * delete の動作：
     * 1. オブジェクトのデストラクタを呼び出す
     * 2. "Zombie HeapWalker destroyed" が出力される
     * 3. ヒープメモリを解放する
     * 4. heapZombie ポインタは無効になる（ダングリングポインタ）
     */
    delete heapZombie;
    
    /*
     * 【安全性のヒント】delete後のポインタ処理
     * 
     * 実際のプロジェクトでは以下を推奨：
     * ```cpp
     * delete heapZombie;
     * heapZombie = nullptr;  // ダングリングポインタを防ぐ
     * ```
     * 
     * ただし、この学習段階では簡略化している
     */
    
    /*
     * ====================================================================
     * セクション2: スタック確保のテスト (randomChump)
     * ====================================================================
     */
    std::cout << "\n=== Testing stack allocation (randomChump) ===" << std::endl;
    
    /*
     * randomChump関数の呼び出し
     * 
     * 何が起こっているのか？
     * 1. randomChump("StackShambler") が呼ばれる
     * 2. 関数内でスタックにZombieオブジェクトが作成される
     * 3. コンストラクタが呼ばれ "Zombie StackShambler created" が出力される
     * 4. announce() が呼ばれ "StackShambler: BraiiiiiiinnnzzzZ..." が出力される
     * 5. 関数終了時にデストラクタが自動で呼ばれる
     * 6. "Zombie StackShambler destroyed" が出力される
     * 
     * 【重要】プログラマーがすること：
     * - 関数を呼ぶだけ
     * - delete の必要なし
     * - メモリ管理の心配なし
     */
    randomChump("StackShambler");
    
    /*
     * この時点で StackShambler は既に削除されている！
     * randomChump関数から戻ってきた時点で、
     * 関数内で作成されたZombieオブジェクトは自動削除済み
     */
    
    /*
     * ====================================================================
     * セクション3: スコープによる自動削除のデモンストレーション
     * ====================================================================
     */
    std::cout << "\n=== Additional stack vs heap demonstration ===" << std::endl;
    std::cout << "Creating stack zombie..." << std::endl;
    
    /*
     * スコープブロック { } の開始
     * 
     * なぜブロックを作るのか？
     * - スコープによる自動削除を明確に観察するため
     * - オブジェクトの生存期間を意図的に制限するため
     * - RAII原則の動作を視覚的に確認するため
     */
    {
        /*
         * ブロック内でのスタック変数作成
         * 
         * Zombie stackZombie("LocalUndead");
         * 
         * randomChumpとの違い：
         * - randomChump: 関数内で作成・使用・削除
         * - この例: main関数内のブロックで作成・使用・削除
         * 
         * しかし本質は同じ：
         * - スタック変数
         * - 自動的な生存期間管理
         * - スコープアウト時の自動削除
         */
        Zombie stackZombie("LocalUndead");
        stackZombie.announce();
        
        /*
         * この時点で stackZombie は生きている
         * announce() の実行により
         * "LocalUndead: BraiiiiiiinnnzzzZ..." が出力される
         */
        
    } // ← この } でスコープ終了、stackZombie が自動削除される
    
    /*
     * スコープ終了時の自動削除について
     * 
     * } に到達した瞬間に起こること：
     * 1. stackZombie のデストラクタが自動的に呼ばれる
     * 2. "Zombie LocalUndead destroyed" が出力される
     * 3. スタックメモリが自動的に解放される
     * 4. この行以降、stackZombie は存在しない
     */
    std::cout << "Stack zombie automatically destroyed when leaving scope\n" << std::endl;
    
    /*
     * ====================================================================
     * セクション4: ヒープ確保の再デモンストレーション
     * ====================================================================
     */
    std::cout << "Creating heap zombie..." << std::endl;
    
    /*
     * 再度ヒープにZombieを作成
     * 
     * なぜもう一度ヒープ確保をテストするのか？
     * - スタック変数との対比を明確にするため
     * - 手動削除の重要性を再強調するため
     * - メモリ管理の責任を意識づけるため
     */
    Zombie* anotherHeapZombie = newZombie("PersistentGhoul");
    anotherHeapZombie->announce();
    
    /*
     * 重要な観察ポイント：
     * - 上記のスコープブロック終了後もこのZombieは生き続ける
     * - スタック変数（stackZombie）は自動削除されたが
     * - ヒープ変数（anotherHeapZombie）は削除されていない
     * - つまり、PersistentGhoul は LocalUndead より長生きしている
     */
    
    std::cout << "Heap zombie must be manually deleted..." << std::endl;
    
    /*
     * 【必須】手動でのメモリ解放
     * 
     * この delete を忘れるとどうなるか？
     * - メモリリークが発生
     * - PersistentGhoul のデストラクタが呼ばれない
     * - "destroyed" メッセージが出力されない
     * - メモリが無駄に消費され続ける
     */
    delete anotherHeapZombie;
    
    /*
     * ====================================================================
     * プログラム終了
     * ====================================================================
     */
    return 0;
    
    /*
     * main関数の終了時に何が起こるか？
     * 
     * 1. return文が実行される
     * 2. main関数のスタックフレームが破棄される
     * 3. プログラムが正常終了する
     * 4. この時点で全てのZombieオブジェクトは削除済みのはず
     * 
     * 【確認方法】
     * プログラム実行時のログを確認：
     * - "created" と "destroyed" の数が一致していれば正常
     * - 不一致の場合はメモリリークがある可能性
     */
}

/*
 * ====================================================================
 * 実行時の期待される出力解説
 * ====================================================================
 * 
 * 正常実行時の出力順序：
 * 
 * 1. "=== Testing heap allocation (newZombie) ==="
 * 2. "Zombie HeapWalker created"           ← heapZombie作成
 * 3. "HeapWalker: BraiiiiiiinnnzzzZ..."    ← announce実行  
 * 4. "Zombie HeapWalker destroyed"         ← delete実行
 * 
 * 5. "=== Testing stack allocation (randomChump) ==="
 * 6. "Zombie StackShambler created"        ← randomChump内で作成
 * 7. "StackShambler: BraiiiiiiinnnzzzZ..." ← randomChump内でannounce
 * 8. "Zombie StackShambler destroyed"      ← randomChump終了時に自動削除
 * 
 * 9. "=== Additional stack vs heap demonstration ==="
 * 10. "Creating stack zombie..."
 * 11. "Zombie LocalUndead created"         ← ブロック内で作成
 * 12. "LocalUndead: BraiiiiiiinnnzzzZ..."  ← announce実行
 * 13. "Zombie LocalUndead destroyed"       ← ブロック終了時に自動削除
 * 14. "Stack zombie automatically destroyed when leaving scope"
 * 
 * 15. "Creating heap zombie..."
 * 16. "Zombie PersistentGhoul created"     ← anotherHeapZombie作成
 * 17. "PersistentGhoul: BraiiiiiiinnnzzzZ..." ← announce実行
 * 18. "Heap zombie must be manually deleted..."
 * 19. "Zombie PersistentGhoul destroyed"   ← delete実行
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * □ ヒープとスタック確保の使い分けを理解している
 * □ -> 演算子と . 演算子の違いを理解している  
 * □ スコープによる自動削除のタイミングを理解している
 * □ delete の重要性とタイミングを理解している
 * □ メモリリークが発生する条件を理解している
 * 
 * 【実習課題】
 * 1. delete文をコメントアウトしてメモリリークを体験する
 * 2. 複数のZombieを作成して削除順序を観察する
 * 3. デバッガーでスタックとヒープの状態を観察する
 * 4. valgrindでメモリリーク検出を実行する
 */

/*
 * ====================================================================
 * よくある間違いと対策
 * ====================================================================
 * 
 * 【間違い1】delete忘れ
 * ```cpp
 * Zombie* z = newZombie("Test");
 * // delete z; ← これを忘れる
 * ```
 * 対策：newと対になるdeleteを必ず書く習慣をつける
 * 
 * 【間違い2】スタック変数をdeleteしようとする
 * ```cpp
 * Zombie z("Test");
 * delete &z; ← エラー！スタック変数はdelete不要
 * ```
 * 対策：スタック変数かヒープ変数かを意識する
 * 
 * 【間違い3】delete後のポインタ使用
 * ```cpp
 * delete zombie;
 * zombie->announce(); ← エラー！削除済みオブジェクトへのアクセス
 * ```
 * 対策：delete後はポインタを使用しない、nullptrを代入する
 */