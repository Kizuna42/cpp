// ===============================================
// main.cpp - メインプログラム（完全解説版）
// ===============================================

#include "TUTORIAL_PhoneBook.hpp"
#include "TUTORIAL_Contact.hpp"
#include <iostream>
#include <string>

/*
 * ヘルパー関数群
 *
 * これらの関数はmain()の前に定義する必要がある
 * または、関数宣言をmain()の前に書いて、実装を後に書くことも可能
 */

/*
 * getInput() - ユーザー入力の取得
 *
 * 学習ポイント:
 * 1. 関数の引数と戻り値
 * 2. std::getline()の使用
 * 3. 入力と出力の基本
 */
std::string getInput(const std::string& prompt) {
    std::string input;

    // プロンプトを表示
    std::cout << prompt;

    // 1行全体を読み取り（スペースを含む）
    // std::cin >> input では最初のスペースまでしか読まない
    // std::getline()を使うことで1行全体を取得
    std::getline(std::cin, input);
    return input;
}

/*
 * isValidInput() - 入力検証
 *
 * 学習ポイント:
 * 1. bool型の戻り値
 * 2. 文字列の空チェック
 * 3. 関数の単一責任原則
 */
bool isValidInput(const std::string& input) {
    // .empty(): std::stringのメンバー関数
    // !: 論理否定演算子（trueをfalseに、falseをtrueに）
    return !input.empty();
}

/*
 * stringToInt() - 文字列を整数に変換（C++98準拠）
 * 
 * 学習ポイント:
 * 1. C++98では std::stoi が使えない
 * 2. 手動での文字列→整数変換
 * 3. エラーハンドリング（無効文字の検出）
 * 4. ASCII文字コードの理解
 */
int stringToInt(const std::string& str) {
    int result = 0;
    
    // 文字列の各文字をチェック
    for (size_t i = 0; i < str.length(); i++) {
        // 数字以外の文字があるかチェック
        // '0'～'9' のASCIIコード範囲外なら無効
        if (str[i] < '0' || str[i] > '9')
            return -1;  // エラーを示す値
        
        // 数字文字を整数値に変換
        // '0'のASCIIコードを引くことで数値を得る
        // 例: '5' - '0' = 5
        result = result * 10 + (str[i] - '0');
    }
    
    return result;
}

/*
 * createContact() - 連絡先作成の対話処理
 * 
 * 学習ポイント:
 * 1. do-while ループ
 * 2. オブジェクトの作成と操作
 * 3. ユーザーインターフェースの設計
 * 4. 入力検証ループ
 */
Contact createContact() {
    Contact contact;  // 新しい連絡先オブジェクトを作成
    std::string input;
    
    // 各フィールドの入力（空文字列は受け付けない）
    
    // do-while: 最低1回は実行し、条件がtrueの間は繰り返す
    do {
        input = getInput("Enter first name: ");
    } while (!isValidInput(input));  // 有効な入力があるまで繰り返し
    contact.setFirstName(input);
    
    do {
        input = getInput("Enter last name: ");
    } while (!isValidInput(input));
    contact.setLastName(input);
    
    do {
        input = getInput("Enter nickname: ");
    } while (!isValidInput(input));
    contact.setNickname(input);
    
    do {
        input = getInput("Enter phone number: ");
    } while (!isValidInput(input));
    contact.setPhoneNumber(input);
    
    do {
        input = getInput("Enter darkest secret: ");
    } while (!isValidInput(input));
    contact.setDarkestSecret(input);
    
    return contact;  // 完成した連絡先オブジェクトを返す
}

/*
 * main() - メイン関数
 * 
 * 学習ポイント:
 * 1. メインループ（Read-Eval-Print Loop: REPL）
 * 2. if-else if-else の制御構造
 * 3. 文字列比較
 * 4. オブジェクト指向プログラミングの実践
 */
int main() {
    PhoneBook phoneBook;  // 電話帳オブジェクトを作成
    std::string command;
    
    // ウェルカムメッセージ
    std::cout << "Welcome to the PhoneBook!" << std::endl;
    std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
    
    // メインループ - プログラムの中心処理
    while (true) {  // 無限ループ（EXITで終了）
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        
        // コマンドの処理
        if (command == "ADD") {
            /*
             * ADD コマンド処理
             * 1. 新しい連絡先を作成
             * 2. 電話帳に追加
             * 3. 成功メッセージ表示
             */
            Contact newContact = createContact();
            phoneBook.addContact(newContact);
            std::cout << "Contact added successfully!" << std::endl;
        }
        else if (command == "SEARCH") {
            /*
             * SEARCH コマンド処理
             * 1. 連絡先の有無をチェック
             * 2. 一覧表示
             * 3. インデックス入力受付
             * 4. 詳細表示
             */
            
            // 連絡先が0件の場合の処理
            if (phoneBook.getContactCount() == 0) {
                std::cout << "No contacts available." << std::endl;
                continue;  // ループの先頭に戻る
            }
            
            // 連絡先一覧を表示
            phoneBook.displayContacts();
            
            // インデックス入力
            std::string indexStr;
            std::cout << "Enter index of contact to display: ";
            std::getline(std::cin, indexStr);
            
            // 文字列を整数に変換
            int index = stringToInt(indexStr);
            if (index == -1) {
                // 変換に失敗（無効な文字が含まれる）
                std::cout << "Invalid index" << std::endl;
            } else {
                // 有効な数値なので詳細表示を試行
                phoneBook.displayContact(index);
            }
        }
        else if (command == "EXIT") {
            /*
             * EXIT コマンド処理
             * プログラムを終了
             */
            std::cout << "Goodbye!" << std::endl;
            break;  // whileループから抜ける
        }
        else {
            /*
             * 無効なコマンドの処理
             * エラーメッセージを表示してループを継続
             */
            std::cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << std::endl;
        }
    }
    
    return 0;  // プログラム正常終了
    
    /*
     * ここでローカル変数（phoneBook, command等）のデストラクタが
     * 自動的に呼ばれ、メモリが解放される
     */
}

/*
 * このプログラム全体で学ぶ重要概念:
 * 
 * 1. オブジェクト指向設計:
 *    - クラスの協調（PhoneBookとContact）
 *    - カプセル化によるデータ保護
 *    - 責任の分離
 * 
 * 2. メモリ管理:
 *    - 自動変数（スタック上）の使用
 *    - 動的割り当て（new/delete）の回避
 *    - RAIIパターン（Resource Acquisition Is Initialization）
 * 
 * 3. エラーハンドリング:
 *    - 入力検証
 *    - 範囲チェック
 *    - 無効な操作への対応
 * 
 * 4. ユーザーインターフェース:
 *    - 対話的プログラム設計
 *    - 適切なメッセージ表示
 *    - ユーザビリティの考慮
 * 
 * 5. C++98 準拠:
 *    - 古い標準での制約
 *    - 手動実装の必要性
 *    - 移植性の考慮
 */