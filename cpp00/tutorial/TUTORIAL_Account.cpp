// ===============================================
// Account.cpp - アカウントクラス実装（完全解説版）
// ===============================================

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

/*
 * 静的メンバー変数の初期化
 * 
 * 重要な学習ポイント:
 * 1. 静的メンバーはクラス定義の外で初期化する必要がある
 * 2. 全てのオブジェクトで共有される
 * 3. プログラム開始時に初期化される
 * 4. スコープ解決演算子(::)を使用
 */
int Account::_nbAccounts = 0;          // アカウント総数
int Account::_totalAmount = 0;         // 総残高
int Account::_totalNbDeposits = 0;     // 総預金回数
int Account::_totalNbWithdrawals = 0;  // 総出金回数

/*
 * コンストラクタ - 初期化リストの使用
 * 
 * 学習ポイント:
 * 1. 初期化リストの効率性
 * 2. 静的変数とインスタンス変数の使い分け
 * 3. 実行順序の理解
 */
Account::Account(int initial_deposit) 
    : _accountIndex(_nbAccounts),    // インデックスは現在の総数
      _amount(initial_deposit),      // 初期残高
      _nbDeposits(0),               // 預金回数は0から
      _nbWithdrawals(0)             // 出金回数は0から
{
    /*
     * コンストラクタ本体
     * 初期化リスト実行後に実行される
     */
    
    // 静的変数の更新（全アカウント共通データ）
    _nbAccounts++;                    // 総アカウント数を増加
    _totalAmount += initial_deposit;  // 総残高に追加
    
    // ログ出力
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";amount:" << _amount 
              << ";created" << std::endl;
}

/*
 * デストラクタ
 * 
 * 学習ポイント:
 * 1. オブジェクト破棄時の処理
 * 2. リソースクリーンアップ
 * 3. ログの一貫性
 */
Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";amount:" << _amount 
              << ";closed" << std::endl;
}

/*
 * 静的メンバー関数群
 * 
 * 学習ポイント:
 * 1. static関数はオブジェクトなしで呼び出し可能
 * 2. インスタンスメンバーにはアクセスできない
 * 3. クラス全体の情報を提供
 */

int Account::getNbAccounts(void) {
    return _nbAccounts;
}

int Account::getTotalAmount(void) {
    return _totalAmount;
}

int Account::getNbDeposits(void) {
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
    return _totalNbWithdrawals;
}

/*
 * displayAccountsInfos() - 全アカウント情報の表示
 * 
 * 静的関数の典型的な使用例
 */
void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts 
              << ";total:" << _totalAmount 
              << ";deposits:" << _totalNbDeposits 
              << ";withdrawals:" << _totalNbWithdrawals 
              << std::endl;
}

/*
 * makeDeposit() - 預金処理
 * 
 * 学習ポイント:
 * 1. 取引前の状態保存
 * 2. インスタンス変数と静的変数の同期更新
 * 3. ログの詳細記録
 */
void Account::makeDeposit(int deposit) {
    int p_amount = _amount;  // 前の残高を保存（ログ用）
    
    // 残高と回数の更新
    _amount += deposit;
    _nbDeposits++;
    
    // 静的変数の更新（全体の統計）
    _totalAmount += deposit;
    _totalNbDeposits++;
    
    // ログ出力
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";p_amount:" << p_amount 
              << ";deposit:" << deposit 
              << ";amount:" << _amount 
              << ";nb_deposits:" << _nbDeposits 
              << std::endl;
}

/*
 * makeWithdrawal() - 出金処理
 * 
 * 学習ポイント:
 * 1. 事前条件チェック（残高不足）
 * 2. 成功/失敗の分岐処理
 * 3. bool戻り値による結果通知
 */
bool Account::makeWithdrawal(int withdrawal) {
    int p_amount = _amount;  // 前の残高を保存
    
    // 残高不足チェック
    if (withdrawal > _amount) {
        _displayTimestamp();
        std::cout << "index:" << _accountIndex 
                  << ";p_amount:" << p_amount 
                  << ";withdrawal:refused" 
                  << std::endl;
        return false;  // 失敗を示す
    }
    
    // 出金処理（残高が十分な場合）
    _amount -= withdrawal;
    _nbWithdrawals++;
    
    // 静的変数の更新
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;
    
    // 成功ログ
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";p_amount:" << p_amount 
              << ";withdrawal:" << withdrawal 
              << ";amount:" << _amount 
              << ";nb_withdrawals:" << _nbWithdrawals 
              << std::endl;
    
    return true;  // 成功を示す
}

/*
 * checkAmount() - 残高照会
 * 
 * シンプルなゲッター関数
 * const関数（メンバー変数を変更しない）
 */
int Account::checkAmount(void) const {
    return _amount;
}

/*
 * displayStatus() - アカウント状態表示
 * 
 * 個別アカウントの詳細情報
 */
void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";amount:" << _amount 
              << ";deposits:" << _nbDeposits 
              << ";withdrawals:" << _nbWithdrawals 
              << std::endl;
}

/*
 * _displayTimestamp() - タイムスタンプ表示
 * 
 * 学習ポイント:
 * 1. C言語スタイルの時刻処理
 * 2. フォーマット指定
 * 3. ゼロパディング
 * 4. 静的プライベート関数
 */
void Account::_displayTimestamp(void) {
    /*
     * 現在時刻の取得
     * 
     * time_t: 時刻を表す型（通常はlong）
     * time(0): 現在のUnixタイムスタンプを取得
     * localtime(): タイムスタンプを構造体に変換
     */
    time_t now = time(0);
    tm *ltm = localtime(&now);

    /*
     * フォーマット指定による出力
     * 
     * std::setfill('0'): 埋め文字を'0'に設定
     * std::setw(2): 出力幅を2文字に設定
     * 1900 + ltm->tm_year: 1900年からの経過年数
     * 1 + ltm->tm_mon: 0-11月を1-12月に変換
     */
    std::cout << "[" << 1900 + ltm->tm_year
              << std::setfill('0') << std::setw(2) << 1 + ltm->tm_mon
              << std::setfill('0') << std::setw(2) << ltm->tm_mday
              << "_"
              << std::setfill('0') << std::setw(2) << ltm->tm_hour
              << std::setfill('0') << std::setw(2) << ltm->tm_min
              << std::setfill('0') << std::setw(2) << ltm->tm_sec
              << "] ";
}

/*
 * この演習の重要な学習ポイント:
 * 
 * 1. 静的メンバーの理解:
 *    - クラス全体で共有されるデータ
 *    - オブジェクト間の協調
 *    - 初期化の仕組み
 * 
 * 2. ログシステムの設計:
 *    - 一貫したフォーマット
 *    - 時系列データの記録
 *    - デバッグ情報の提供
 * 
 * 3. エラーハンドリング:
 *    - 事前条件チェック
 *    - 戻り値による状態通知
 *    - 失敗時の適切な処理
 * 
 * 4. データ整合性:
 *    - インスタンス変数と静的変数の同期
 *    - 取引の原子性
 *    - 状態の一貫性維持
 * 
 * 5. リバースエンジニアリング:
 *    - ログファイルからの仕様推測
 *    - 実装の逆算
 *    - テスト駆動開発的アプローチ
 */