/*
 * ====================================================================
 * CPP01 ex00: newZombie 関数実装解説版
 * ====================================================================
 * 
 * この関数はヒープメモリ管理の基礎を学ぶための重要な実装です。
 * なぜこのような実装になっているのかを詳しく解説します。
 */

#include "Zombie.hpp"

/*
 * ====================================================================
 * newZombie関数実装解説
 * ====================================================================
 */
Zombie* newZombie(std::string name) {
    /*
     * 関数の役割：ヒープにZombieオブジェクトを作成して返す
     * 
     * 【設計意図】
     * なぜこの関数が必要なのか？
     * 
     * 1. 関数スコープを超えてオブジェクトを使用したい
     *    - この関数を呼んだ後も、作成されたZombieを使い続けたい
     *    - スタック変数では関数終了時に自動削除されてしまう
     * 
     * 2. 動的メモリ確保の学習
     *    - new 演算子の使用方法
     *    - ヒープメモリの概念理解
     *    - メモリ管理の責任について
     * 
     * 3. ファクトリーパターンの基礎
     *    - オブジェクト作成処理の抽象化
     *    - 使用者は作成の詳細を知る必要がない
     */
    
    /*
     * メモリ確保とオブジェクト作成： new Zombie(name)
     * 
     * 何が起こっているのか？
     * 1. ヒープメモリ上にZombieオブジェクト分のメモリを確保
     * 2. 確保されたメモリ上でZombie(name)コンストラクタを実行
     * 3. 作成されたオブジェクトのアドレス（ポインタ）を返す
     * 
     * なぜ引数付きコンストラクタを使うのか？
     * - 作成と同時に名前を設定したい
     * - より効率的で安全な初期化
     * - setName()を後から呼ぶ必要がない
     */
    return new Zombie(name);
    
    /*
     * 【重要】メモリ管理の責任
     * 
     * この関数の呼び出し元が負う責任：
     * 1. 返されたポインタを適切に保存する
     * 2. 使用後に必ず delete を呼び出す
     * 3. delete 後はポインタを使用しない
     * 
     * 正しい使用例：
     * ```cpp
     * Zombie* zombie = newZombie("Alice");
     * zombie->announce();
     * delete zombie;    // 必須！
     * zombie = nullptr; // 安全のため
     * ```
     * 
     * 間違った使用例：
     * ```cpp
     * newZombie("Bob")->announce(); // ポインタを保存していない
     * // この場合、delete できないのでメモリリーク発生
     * ```
     */
}

/*
 * ====================================================================
 * 設計の深い理解
 * ====================================================================
 * 
 * 【なぜこのシンプルな実装なのか？】
 * 
 * 1. 責任の分離
 *    - この関数：オブジェクトの作成のみ
 *    - 呼び出し元：オブジェクトの使用と削除
 *    - 各々の責任が明確
 * 
 * 2. 拡張性の考慮
 *    - 将来的に作成処理が複雑になっても、インターフェースは変わらない
 *    - ログ出力、エラーハンドリングなどを追加可能
 * 
 * 3. 学習段階での簡潔性
 *    - new の基本的な使用方法を理解する
 *    - 複雑な処理で本質を見失わない
 * 
 * 【実際のプロジェクトでの改良案】
 * 
 * エラーハンドリングの追加：
 * ```cpp
 * Zombie* newZombie(std::string name) {
 *     if (name.empty()) {
 *         std::cerr << "Error: Empty name" << std::endl;
 *         return nullptr;
 *     }
 *     
 *     try {
 *         return new Zombie(name);
 *     } catch (std::bad_alloc& e) {
 *         std::cerr << "Memory allocation failed" << std::endl;
 *         return nullptr;
 *     }
 * }
 * ```
 * 
 * しかし、学習段階では上記の複雑さは必要ない。
 */

/*
 * ====================================================================
 * よくある質問と回答
 * ====================================================================
 * 
 * Q: なぜ関数名が "newZombie" なのか？
 * A: - "new" は動的メモリ確保を示唆
 *    - 42スクールの課題仕様
 *    - ファクトリーパターンの命名慣習
 * 
 * Q: なぜ値渡しで std::string を受け取るのか？
 * A: - C++98時代の標準的な方法
 *    - コピーが発生するが安全
 *    - 現代のC++では const std::string& が推奨される場合もある
 * 
 * Q: new が失敗したらどうなるのか？
 * A: - std::bad_alloc 例外が投げられる
 *    - プログラムが終了する（例外処理しない場合）
 *    - 実際のプロジェクトでは例外処理が必要
 * 
 * Q: なぜ Zombie& ではなく Zombie* を返すのか？
 * A: - 参照は初期化後に変更できない
 *    - ポインタは nullptr で「作成失敗」を表現可能
 *    - delete の対象にはポインタが必要
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * □ new 演算子の動作を説明できる
 * □ ヒープとスタックの違いを理解している
 * □ なぜこの関数がポインタを返すのか説明できる
 * □ メモリリークが発生する条件を理解している
 * □ 正しい delete の使用方法を知っている
 * 
 * 【実習課題】
 * 1. この関数を使ってZombieを作成し、announceを呼び、削除してみる
 * 2. 意図的に delete を忘れてメモリリークを体験してみる
 * 3. nullptr チェックを追加した版を実装してみる
 */

/*
 * ====================================================================
 * 次のステップ
 * ====================================================================
 * 
 * この実装を理解したら次は：
 * 1. randomChump.cpp でスタック変数との比較
 * 2. main.cpp で実際の使用例を学習
 * 3. メモリリーク検出ツールの使用方法
 * 4. valgrind や AddressSanitizer での検証
 */