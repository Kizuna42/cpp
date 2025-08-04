/*
 * ====================================================================
 * CPP01 ex06: harlFilter - Switch文とログフィルタリング解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - switch文による条件分岐の実装
 * - 文字列レベルから数値レベルへの変換
 * - ログレベルフィルタリングシステム
 * - fall-through機能を活用したログ階層表示
 * - enum型による定数管理
 * 
 * 【重要概念】
 * - switch文のfall-through動作
 * - ログレベルの階層的構造
 * - 文字列解析と数値変換
 * - レベル比較による出力制御
 * - コマンドライン引数の活用
 */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>
#include <iostream>

/*
 * ====================================================================
 * ログレベル定数の定義
 * ====================================================================
 * 
 * 【enum によるレベル定義】
 * 
 * なぜ enum を使用するのか？
 * - 型安全性の確保
 * - 意味のある名前付け
 * - コンパイル時定数
 * - 順序関係の表現
 * 
 * 値の設計：
 * - DEBUG = 0: 最低レベル（最も詳細）
 * - INFO = 1: 情報レベル
 * - WARNING = 2: 警告レベル
 * - ERROR = 3: 最高レベル（最も重要）
 * - INVALID = 4: 無効レベル（エラー処理用）
 */
enum LogLevel {
    DEBUG_LEVEL = 0,
    INFO_LEVEL = 1,
    WARNING_LEVEL = 2,
    ERROR_LEVEL = 3,
    INVALID_LEVEL = 4
};

/*
 * ====================================================================
 * Harl クラス設計（ex05からの発展）
 * ====================================================================
 * 
 * 【ex05との違い】
 * 
 * ex05: 個別のログレベル実行
 * - 指定されたレベルのみ出力
 * - メンバ関数ポインタによる動的呼び出し
 * 
 * ex06: フィルタリングシステム
 * - 指定レベル以上のすべてを出力
 * - switch文による階層的出力
 * - fall-through機能の活用
 * 
 * 【設計コンセプト】
 * 
 * ログレベルフィルタリング：
 * - ユーザーが最小レベルを指定
 * - そのレベル以上のすべてを出力
 * - 重要度の高い情報は常に表示
 * 
 * 実用的な応用：
 * - デバッグ時：DEBUG以上すべて表示
 * - 本番環境：WARNING以上のみ表示
 * - トラブル調査：INFO以上で詳細把握
 */
class Harl {
private:
    /*
     * ====================================================================
     * private メンバ関数群（ex05と同じ）
     * ====================================================================
     */
    
    /*
     * 【各ログレベル関数】
     * 
     * ex05と同じ実装：
     * - debug(): [DEBUG] メッセージ出力
     * - info(): [INFO] メッセージ出力
     * - warning(): [WARNING] メッセージ出力
     * - error(): [ERROR] メッセージ出力
     * 
     * 実装は変更なし、使用方法が変化
     */
    void debug(void);
    void info(void);
    void warning(void);
    void error(void);

public:
    /*
     * ====================================================================
     * public インターフェース
     * ====================================================================
     */
    
    /*
     * 【コンストラクタ・デストラクタ】
     * 
     * ex05と同じ実装：
     * - リソース管理
     * - デバッグ出力
     * - オブジェクトライフサイクル追跡
     */
    Harl(void);
    ~Harl(void);
    
    /*
     * 【メイン機能：complainFilter メソッド】
     * void complainFilter(std::string level);
     * 
     * ex05の complain() との違い：
     * 
     * complain():
     * - 指定されたレベルのみ実行
     * - メンバ関数ポインタ使用
     * - 1つのメッセージのみ出力
     * 
     * complainFilter():
     * - 指定レベル以上をすべて実行
     * - switch文のfall-through使用
     * - 複数メッセージの階層出力
     * 
     * 引数：
     * - level: "DEBUG", "INFO", "WARNING", "ERROR" のいずれか
     * - 無効な場合は特別なメッセージ表示
     * 
     * 動作例：
     * - "WARNING" 指定時：WARNING と ERROR を出力
     * - "DEBUG" 指定時：DEBUG, INFO, WARNING, ERROR をすべて出力
     * - "ERROR" 指定時：ERROR のみ出力
     * 
     * コア技術：
     * - switch文によるレベル判定
     * - fall-through（break文なし）による連続実行
     * - 文字列からenum値への変換
     */
    void complainFilter(std::string level);
    
    /*
     * 【補助メソッド：文字列→レベル変換】
     * LogLevel stringToLevel(const std::string& level);
     * 
     * 目的：
     * - 文字列レベルをenum値に変換
     * - switch文で使用可能な数値を生成
     * - 無効な文字列の検出
     * 
     * 引数：
     * - level: レベル文字列（"DEBUG"等）
     * 
     * 戻り値：
     * - 対応するenum値
     * - 無効な場合はINVALID_LEVEL
     * 
     * 実装方法：
     * - 文字列比較による判定
     * - if-else チェーンまたはマップ使用
     * - 大文字小文字の区別
     * 
     * 使用例：
     * ```cpp
     * LogLevel level = stringToLevel("DEBUG");
     * switch (level) {
     *     case DEBUG_LEVEL:
     *         // DEBUG処理
     *         // fall-through（breakなし）
     *     case INFO_LEVEL:
     *         // INFO処理
     *         // fall-through
     *     // ...
     * }
     * ```
     */
    LogLevel stringToLevel(const std::string& level);
};

#endif

/*
 * ====================================================================
 * switch文のfall-through解説
 * ====================================================================
 * 
 * 【fall-throughとは】
 * 
 * 通常のswitch文：
 * ```cpp
 * switch (value) {
 *     case 1:
 *         doSomething1();
 *         break;  // ここで終了
 *     case 2:
 *         doSomething2();
 *         break;  // ここで終了
 * }
 * ```
 * 
 * fall-through使用：
 * ```cpp
 * switch (value) {
 *     case 1:
 *         doSomething1();
 *         // breakなし → 次のcaseも実行
 *     case 2:
 *         doSomething2();
 *         // breakなし → 次のcaseも実行
 *     case 3:
 *         doSomething3();
 *         break;  // ここで終了
 * }
 * ```
 * 
 * 【harlFilterでの活用】
 * 
 * DEBUG指定時（level = 0）：
 * ```cpp
 * switch (DEBUG_LEVEL) {  // 0
 *     case DEBUG_LEVEL:    // 0 → 実行
 *         debug();
 *         // fall-through
 *     case INFO_LEVEL:     // 1 → 実行
 *         info();
 *         // fall-through
 *     case WARNING_LEVEL:  // 2 → 実行
 *         warning();
 *         // fall-through
 *     case ERROR_LEVEL:    // 3 → 実行
 *         error();
 *         break;
 * }
 * ```
 * 
 * WARNING指定時（level = 2）：
 * ```cpp
 * switch (WARNING_LEVEL) {  // 2
 *     case DEBUG_LEVEL:     // 0 → スキップ
 *     case INFO_LEVEL:      // 1 → スキップ
 *     case WARNING_LEVEL:   // 2 → 実行開始点
 *         warning();
 *         // fall-through
 *     case ERROR_LEVEL:     // 3 → 実行
 *         error();
 *         break;
 * }
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ enum型による定数定義の方法
 * □ ログレベルの階層構造理解
 * □ switch文のfall-through動作
 * □ 文字列からenum値への変換手法
 * □ レベルフィルタリングの概念
 * □ ex05とex06の設計思想の違い
 * □ コマンドライン引数との連携
 * □ 実用的なログシステムの構造
 * 
 * 【実習課題】
 * 1. 新しいログレベル（FATAL）の追加
 * 2. レベル数値での直接指定対応
 * 3. 逆順出力（高レベルから低レベル）
 * 4. ログ出力の無効化機能
 * 5. 複数レベル指定の対応
 */

/*
 * ====================================================================
 * よくある設計の疑問と回答
 * ====================================================================
 * 
 * 【Q1】なぜex05とex06で別々のクラスにしないのか？
 * 
 * A1：
 * - 同じ基本機能（debug, info, warning, error）を共有
 * - 42課題の仕様でクラス名が指定されている
 * - 実際のプロジェクトでは用途別にクラス分離も有効
 * 
 * 【Q2】enumの値を明示的に指定する理由は？
 * 
 * A2：
 * - 順序関係の明確化
 * - 将来の仕様変更への対応
 * - 数値の意味を文書化
 * - デバッグ時の理解容易性
 * 
 * 【Q3】文字列比較とenum変換、どちらが効率的？
 * 
 * A3：
 * - 文字列比較：理解しやすいが低速
 * - enum変換：高速だが変換コストがある
 * - この規模では性能差は無視できる
 * - 可読性とメンテナンス性を重視
 * 
 * 【Q4】fall-throughは危険な機能では？
 * 
 * A4：
 * - 適切に使用すれば強力な機能
 * - コメントによる意図の明示が重要
 * - このケースでは階層出力に最適
 * - 誤用を防ぐためのコードレビューが必要
 */

/*
 * ====================================================================
 * 発展的な設計アイデア
 * ====================================================================
 * 
 * 【アイデア1：設定可能なフィルタ】
 * ```cpp
 * class ConfigurableHarl {
 * private:
 *     LogLevel minLevel;
 *     bool enabledLevels[4];
 * 
 * public:
 *     void setMinLevel(LogLevel level) { minLevel = level; }
 *     void enableLevel(LogLevel level, bool enable) { 
 *         enabledLevels[level] = enable; 
 *     }
 * };
 * ```
 * 
 * 【アイデア2：出力先の選択】
 * ```cpp
 * class FlexibleHarl {
 * private:
 *     std::ostream* debugOut;
 *     std::ostream* infoOut;
 *     std::ostream* warningOut;
 *     std::ostream* errorOut;
 * 
 * public:
 *     void setOutputStream(LogLevel level, std::ostream* stream);
 * };
 * ```
 * 
 * 【アイデア3：タイムスタンプ付きログ】
 * ```cpp
 * class TimestampedHarl {
 * private:
 *     std::string getCurrentTime();
 * 
 * public:
 *     void debug() {
 *         std::cout << "[" << getCurrentTime() << "] [DEBUG] ...";
 *     }
 * };
 * ```
 * 
 * 【アイデア4：マルチスレッド対応】
 * ```cpp
 * #include <mutex>
 * 
 * class ThreadSafeHarl {
 * private:
 *     mutable std::mutex logMutex;
 * 
 * public:
 *     void complainFilter(std::string level) {
 *         std::lock_guard<std::mutex> lock(logMutex);
 *         // thread-safe logging
 *     }
 * };
 * ```
 */