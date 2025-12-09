// ===============================================
// PhoneBook.hpp - 電話帳クラス定義（完全解説版）
// ===============================================

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "TUTORIAL_Contact.hpp"  // Contactクラスを使用するため

/*
 * PhoneBookクラス - 複数の連絡先を管理する
 *
 * このクラスで学ぶ重要概念:
 * 1. 配列によるデータ管理
 * 2. 循環バッファ（Ring Buffer）
 * 3. クラスの協調（PhoneBookがContactを使用）
 */
class PhoneBook {

private:
    /*
     * メンバー変数
     *
     * Contact contacts[8]:
     * - 固定サイズの配列（動的メモリ割り当てなし）
     * - 8個のContactオブジェクトを格納
     * - C++では配列の境界チェックは自動的に行われない（注意が必要）
     */
    Contact contacts[8];  // 連絡先の配列
    int contactCount;     // 現在保存されている連絡先数（0～8）
    int nextIndex;        // 次に上書きするインデックス（循環バッファ用）

public:
    // コンストラクタとデストラクタ
    PhoneBook();
    ~PhoneBook();
    
    /*
     * パブリック関数（外部インターフェース）
     * 
     * const Contact& contact:
     * - 参照渡し（効率的）
     * - const（関数内で引数を変更しない）
     */
    void addContact(const Contact& contact);    // 連絡先追加
    void displayContacts() const;               // 連絡先一覧表示
    void displayContact(int index) const;       // 特定連絡先の詳細表示
    int getContactCount() const;                // 連絡先数取得
};

/*
 * 設計のポイント:
 * 
 * 1. データ隠蔽:
 *    - contacts配列はprivate → 外部から直接アクセス不可
 *    - 制御された方法（関数経由）でのみアクセス可能
 * 
 * 2. 循環バッファ:
 *    - 8個を超えると古いものから上書き
 *    - nextIndexで次の位置を管理
 *
 * 3. エラー安全性:
 *    - インデックスの範囲チェック
 *    - 無効な操作に対する適切な処理
 */

#endif