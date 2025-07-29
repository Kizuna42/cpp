// ===============================================
// Contact.hpp - 連絡先クラス定義（完全解説版）
// ===============================================

#ifndef CONTACT_HPP
#define CONTACT_HPP

/*
 * ヘッダーガード: 
 * 同じヘッダーファイルが複数回インクルードされることを防ぐ
 * #ifndef CONTACT_HPP ～ #endif で囲む
 */

#include <string>

/*
 * クラス (class) - C++のオブジェクト指向プログラミングの基本
 *
 * クラスとは:
 * - データ（メンバー変数）と処理（メンバー関数）をまとめたもの
 * - 「設計図」のようなもの
 * - この設計図から「オブジェクト」を作成する
 */
class Contact {

/*
 * private: 
 * - クラス内部でのみアクセス可能
 * - 外部から直接変更できない = データの保護
 * - カプセル化の重要な概念
 */
private:
    // メンバー変数（データ）
    std::string firstName;     // 名前
    std::string lastName;      // 姓
    std::string nickname;      // ニックネーム
    std::string phoneNumber;   // 電話番号
    std::string darkestSecret; // 最も暗い秘密

/*
 * public:
 * - どこからでもアクセス可能
 * - インターフェース（外部とのやり取り）を定義
 */
public:
    // コンストラクタ: オブジェクト作成時に呼ばれる
    Contact();
    
    // デストラクタ: オブジェクト破棄時に呼ばれる
    ~Contact();
    
    // セッター（設定用メンバー関数）
    // const std::string& : 参照渡し（コピーを避けて効率的）
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setNickname(const std::string& nickname);
    void setPhoneNumber(const std::string& phoneNumber);
    void setDarkestSecret(const std::string& darkestSecret);
    
    // ゲッター（取得用メンバー関数）
    // const: この関数内でメンバー変数を変更しないことを保証
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;
    
    // ユーティリティ関数
    bool isEmpty() const;  // 空の連絡先かどうか判定
};

/*
 * カプセル化の利点:
 * 1. データの保護: 外部から直接変更されない
 * 2. 検証可能: セッターで入力値をチェックできる  
 * 3. 変更の容易さ: 内部実装を変更しても外部に影響しない
 * 
 * 使用例:
 * Contact contact;                    // オブジェクト作成
 * contact.setFirstName("田中");       // セッターでデータ設定
 * std::string name = contact.getFirstName();  // ゲッターでデータ取得
 */

#endif