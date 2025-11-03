// ===============================================
// Contact.cpp - 連絡先クラス実装（完全解説版）
// ===============================================

#include "TUTORIAL_Contact.hpp"

/*
 * コンストラクタ - オブジェクト作成時に自動実行
 *
 * 記法: クラス名::関数名
 * :: はスコープ解決演算子（この関数がContactクラスのものであることを示す）
 */
Contact::Contact() {
    // デフォルトコンストラクタ
    // std::stringは自動的に空文字列""で初期化される
    // 明示的に何かする必要があれば、ここに書く
}

/*
 * デストラクタ - オブジェクト破棄時に自動実行
 *
 * 記法: ~クラス名()
 * リソースの解放（動的メモリ、ファイルクローズ等）に使用
 * この例ではstd::stringが自動的に解放されるので特に何もしない
 */
Contact::~Contact() {
    // 特別な処理は不要
}

/*
 * セッター関数群 - データの設定
 * 
 * const std::string& firstName:
 * - const: 関数内で引数を変更しない
 * - &: 参照渡し（値のコピーを避けて効率的）
 * 
 * this->firstName:
 * - this: 現在のオブジェクトへのポインタ
 * - ->: ポインタ経由でのメンバーアクセス
 * - 引数名とメンバー変数名が同じ場合の区別に使用
 */
void Contact::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void Contact::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void Contact::setNickname(const std::string& nickname) {
    this->nickname = nickname;
}

void Contact::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Contact::setDarkestSecret(const std::string& darkestSecret) {
    this->darkestSecret = darkestSecret;
}

/*
 * ゲッター関数群 - データの取得
 * 
 * 戻り値の型: std::string
 * 関数末尾のconst: この関数はメンバー変数を変更しないことを保証
 * return this->firstName: メンバー変数の値を返す
 */
std::string Contact::getFirstName() const {
    return this->firstName;
}

std::string Contact::getLastName() const {
    return this->lastName;
}

std::string Contact::getNickname() const {
    return this->nickname;
}

std::string Contact::getPhoneNumber() const {
    return this->phoneNumber;
}

std::string Contact::getDarkestSecret() const {
    return this->darkestSecret;
}

/*
 * isEmpty() - 連絡先が空かどうかの判定
 * 
 * 論理演算子:
 * ||: OR演算子（どれか1つでもtrueならtrue）
 * .empty(): std::stringのメンバー関数（文字列が空ならtrue）
 * 
 * この関数の意味:
 * 「どれか1つでも空のフィールドがあれば、この連絡先は空（不完全）」
 */
bool Contact::isEmpty() const {
    return firstName.empty() || lastName.empty() || nickname.empty() || 
           phoneNumber.empty() || darkestSecret.empty();
}

/*
 * 使用例:
 *
 * Contact contact;                           // オブジェクト作成（コンストラクタ呼び出し）
 * contact.setFirstName("田中");             // セッターでデータ設定
 * 
 * if (contact.isEmpty()) {                   // 空チェック
 *     std::cout << "データが不完全です" << std::endl;
 * }
 * 
 * std::string name = contact.getFirstName(); // ゲッターでデータ取得
 * std::cout << "名前: " << name << std::endl;
 * 
 * // オブジェクトがスコープから外れると自動的にデストラクタが呼ばれる
 */