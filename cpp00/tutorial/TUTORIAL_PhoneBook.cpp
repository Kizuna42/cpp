// ===============================================
// PhoneBook.cpp - 電話帳クラス実装（完全解説版）
// ===============================================

#include "TUTORIAL_PhoneBook.hpp"
#include <iostream>
#include <iomanip>  // std::setw用

/*
 * コンストラクタ - 初期化リストを使用
 *
 * 記法: PhoneBook() : contactCount(0), nextIndex(0)
 * - コロン(:)の後に初期化リストを記述
 * - メンバー変数を効率的に初期化
 * - 代入ではなく初期化（コンストラクタ呼び出し）
 */
PhoneBook::PhoneBook() : contactCount(0), nextIndex(0) {
    // 配列contacts[8]は自動的にContactのデフォルトコンストラクタで初期化される
}

PhoneBook::~PhoneBook() {
    // 特別な処理は不要（自動的にメンバーのデストラクタが呼ばれる）
}

/*
 * addContact() - 連絡先の追加
 *
 * 循環バッファの実装:
 * 1. nextIndexの位置に新しい連絡先を保存
 * 2. nextIndexを次の位置に移動（8になったら0に戻る）
 * 3. 連絡先数をカウント（最大8まで）
 */
void PhoneBook::addContact(const Contact& contact) {
    // 指定された位置に連絡先をコピー代入
    contacts[nextIndex] = contact;
    
    // 次のインデックスを計算（0～7の循環）
    // % 演算子: 余りを計算（8で割った余り = 0～7）
    nextIndex = (nextIndex + 1) % 8;
    
    // 連絡先数を増加（最大8まで）
    if (contactCount < 8)
        contactCount++;
}

/*
 * ヘルパー関数 - 文字列の切り詰め
 * 
 * この関数はファイルスコープ（このファイル内でのみ使用可能）
 * 10文字を超える文字列を9文字+ドットに変換
 */
std::string truncateString(const std::string& str) {
    if (str.length() > 10) {
        // substr(開始位置, 長さ): 部分文字列を取得
        return str.substr(0, 9) + ".";
    }
    return str;  // 10文字以下はそのまま返す
}

/*
 * displayContacts() - 連絡先一覧の表示
 *
 * 学習ポイント:
 * 1. iomanipライブラリの使用
 * 2. 表形式の出力
 * 3. 文字列の切り詰め処理
 */
void PhoneBook::displayContacts() const {
    // テーブルヘッダーの表示
    // std::setw(10): 次の出力を10文字幅で右揃え
    std::cout << std::setw(10) << "Index" << "|";
    std::cout << std::setw(10) << "First Name" << "|";
    std::cout << std::setw(10) << "Last Name" << "|";
    std::cout << std::setw(10) << "Nickname" << std::endl;
    
    // 各連絡先をループ表示
    for (int i = 0; i < contactCount; i++) {
        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].getFirstName()) << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].getLastName()) << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].getNickname()) << std::endl;
    }
}

/*
 * displayContact() - 特定連絡先の詳細表示
 * 
 * 学習ポイント:
 * 1. 範囲チェック（エラーハンドリング）
 * 2. 早期リターン（early return）パターン
 * 3. const参照の使用
 */
void PhoneBook::displayContact(int index) const {
    // 範囲チェック: 無効なインデックスの処理
    if (index < 0 || index >= contactCount) {
        std::cout << "Invalid index" << std::endl;
        return;  // 早期リターン（これ以上の処理をしない）
    }
    
    // const参照で連絡先を取得（コピーを避けて効率的）
    const Contact& contact = contacts[index];
    
    // 詳細情報を表示
    std::cout << "First Name: " << contact.getFirstName() << std::endl;
    std::cout << "Last Name: " << contact.getLastName() << std::endl;
    std::cout << "Nickname: " << contact.getNickname() << std::endl;
    std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}

/*
 * getContactCount() - 連絡先数の取得
 * 
 * シンプルなゲッター関数
 * const関数（メンバー変数を変更しない）
 */
int PhoneBook::getContactCount() const {
    return contactCount;
}

/*
 * このクラスの重要な学習ポイント:
 * 
 * 1. カプセル化:
 *    - データ（配列）を隠蔽し、関数経由でアクセス
 *    - 不正な操作を防ぐ
 * 
 * 2. メモリ管理:
 *    - 動的割り当てを使わない（new/delete不要）
 *    - 自動的なコンストラクタ/デストラクタ呼び出し
 * 
 * 3. エラーハンドリング:
 *    - 範囲チェック
 *    - 無効な操作に対する適切な応答
 * 
 * 4. 効率性:
 *    - 参照渡しでコピーを避ける
 *    - const使用で意図を明確化
 */