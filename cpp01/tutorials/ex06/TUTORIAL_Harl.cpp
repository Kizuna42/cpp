/*
 * ====================================================================
 * CPP01 ex06: harlFilter - Switch文フィルタリング実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - switch文のfall-through機能実装
 * - 文字列からenum値への変換実装
 * - ログレベルフィルタリングシステム
 * - 階層的ログ出力の実現
 * - 無効入力のエラーハンドリング
 * 
 * 【重要概念】
 * - switch文による効率的な分岐処理
 * - fall-throughによる連続実行制御
 * - enum値を使った数値比較
 * - 文字列解析とマッピング処理
 * - ログレベルの実用的な運用
 */

#include "Harl.hpp"

/*
 * ====================================================================
 * コンストラクタ・デストラクタの実装（ex05と同じ）
 * ====================================================================
 */

/*
 * 【デフォルトコンストラクタ】
 * 
 * ex05と同じ実装：
 * - オブジェクト作成の通知
 * - デバッグ情報の出力
 * - ライフサイクル追跡
 */
Harl::Harl(void) {
    std::cout << "Harl filter instance created" << std::endl;
}

/*
 * 【デストラクタ】
 * 
 * ex05と同じ実装：
 * - オブジェクト破棄の通知  
 * - リソース解放（不要）
 * - デバッグ情報の出力
 */
Harl::~Harl(void) {
    std::cout << "Harl filter instance destroyed" << std::endl;
}

/*
 * ====================================================================
 * private メンバ関数の実装（ex05と同じ）
 * ====================================================================
 */

/*
 * 【DEBUG レベル実装】
 * 
 * 内容はex05と同じ：
 * - [DEBUG] プレフィックス
 * - 最も詳細なログ情報
 * - 開発時の追跡情報
 */
void Harl::debug(void) {
    std::cout << "[DEBUG] I love having extra bacon for my "
              << "7XL-double-cheese-triple-pickle-special-ketchup burger. "
              << "I really do!" << std::endl;
}

/*
 * 【INFO レベル実装】
 * 
 * 内容はex05と同じ：
 * - [INFO] プレフィックス
 * - 一般的な情報メッセージ
 * - ユーザー向けの通知
 */
void Harl::info(void) {
    std::cout << "[INFO] I cannot believe adding extra bacon costs more money. "
              << "You didn't put enough bacon in my burger! "
              << "If you did, I wouldn't be asking for more!" << std::endl;
}

/*
 * 【WARNING レベル実装】
 * 
 * 内容はex05と同じ：
 * - [WARNING] プレフィックス
 * - 警告レベルのメッセージ
 * - 注意が必要な状況
 */
void Harl::warning(void) {
    std::cout << "[WARNING] I think I deserve to have some extra bacon for free. "
              << "I've been coming for years whereas you started "
              << "working here since last month." << std::endl;
}

/*
 * 【ERROR レベル実装】
 * 
 * 内容はex05と同じ：
 * - [ERROR] プレフィックス
 * - 最高重要度のエラー
 * - 緊急対応が必要
 */
void Harl::error(void) {
    std::cout << "[ERROR] This is unacceptable! I want to speak to the manager now." 
              << std::endl;
}

/*
 * ====================================================================
 * 補助メソッド：文字列→レベル変換
 * ====================================================================
 */

/*
 * 【文字列からenum値への変換】
 * LogLevel Harl::stringToLevel(const std::string& level)
 * 
 * 目的：
 * - 文字列レベルをenum値に変換
 * - switch文で使用可能な数値を生成
 * - 無効な入力の検出と処理
 * 
 * 実装手法：
 * - if-else チェーンによる文字列比較
 * - 完全一致による判定
 * - 大文字小文字の区別
 * 
 * 戻り値：
 * - 有効な場合：対応するenum値
 * - 無効な場合：INVALID_LEVEL
 */
LogLevel Harl::stringToLevel(const std::string& level) {
    /*
     * 【文字列比較による変換】
     * 
     * if-else チェーンの利点：
     * - 理解しやすい実装
     * - デバッグが容易
     * - C++98で確実に動作
     * 
     * 他の実装方法（参考）：
     * - std::map<std::string, LogLevel> (C++98でも可能）
     * - ハッシュテーブル（より高速）
     * - 配列とループ（ex05スタイル）
     */
    if (level == "DEBUG") {
        return DEBUG_LEVEL;
    } else if (level == "INFO") {
        return INFO_LEVEL;
    } else if (level == "WARNING") {
        return WARNING_LEVEL;
    } else if (level == "ERROR") {
        return ERROR_LEVEL;
    } else {
        /*
         * 【無効レベルの処理】
         * 
         * INVALID_LEVEL の返却：
         * - 呼び出し元でのエラー処理を可能に
         * - switch文での default case へ誘導
         * - 例外を使わないエラーハンドリング
         */
        return INVALID_LEVEL;
    }
}

/*
 * ====================================================================
 * メイン機能：complainFilter メソッドの実装
 * ====================================================================
 */

/*
 * 【ログレベルフィルタリングシステム】
 * void Harl::complainFilter(std::string level)
 * 
 * ex05との根本的違い：
 * 
 * ex05 (complain):
 * - 指定されたレベルのみ実行
 * - メンバ関数ポインタで動的選択
 * - 1つのメッセージ出力
 * 
 * ex06 (complainFilter):
 * - 指定レベル以上をすべて実行
 * - switch文のfall-throughで階層実行
 * - 複数メッセージの連続出力
 * 
 * 核心技術：
 * - switch文のfall-through動作
 * - 階層的ログ出力システム
 * - レベルベースフィルタリング
 */
void Harl::complainFilter(std::string level) {
    /*
     * 【レベル変換処理】
     * 
     * stringToLevel() による変換：
     * 1. 文字列レベルをenum値に変換
     * 2. switch文で使用可能な数値を取得
     * 3. 無効入力の検出
     */
    LogLevel logLevel = stringToLevel(level);
    
    /*
     * 【switch文によるフィルタリング実装】
     * 
     * switch (logLevel) の動作原理：
     * 
     * 通常のswitch（break有り）：
     * - 該当するcaseのみ実行
     * - breakで即座に終了
     * 
     * fall-through switch（breakなし）：
     * - 該当するcaseから下のすべてを実行
     * - 階層的な処理に最適
     * 
     * 実行例（WARNING指定時）：
     * 1. WARNING_LEVEL case から開始
     * 2. warning() を実行
     * 3. breakがないので次へ継続
     * 4. ERROR_LEVEL case も実行
     * 5. error() を実行
     * 6. breakで終了
     * 
     * 結果：WARNING と ERROR の両方が出力される
     */
    switch (logLevel) {
        /*
         * 【DEBUG_LEVEL case】
         * 
         * レベル 0（最低レベル）：
         * - すべてのログが出力される
         * - 開発時のフルデバッグモード
         * - 最も詳細な情報取得
         */
        case DEBUG_LEVEL:
            debug();
            /*
             * fall-through（意図的なbreakなし）
             * 次のINFO_LEVELケースも実行される
             */
            
        /*
         * 【INFO_LEVEL case】
         * 
         * レベル 1：
         * - INFO, WARNING, ERROR が出力
         * - 一般的な運用時のログレベル
         * - DEBUGを除く重要な情報
         */
        case INFO_LEVEL:
            info();
            /*
             * fall-through
             * 次のWARNING_LEVELケースも実行される
             */
            
        /*
         * 【WARNING_LEVEL case】
         * 
         * レベル 2：
         * - WARNING, ERROR が出力
         * - 本番環境での一般的なレベル
         * - 問題の可能性がある状況のみ
         */
        case WARNING_LEVEL:
            warning();
            /*
             * fall-through
             * 次のERROR_LEVELケースも実行される
             */
            
        /*
         * 【ERROR_LEVEL case】
         * 
         * レベル 3（最高レベル）：
         * - ERROR のみ出力
         * - 重大な問題のみを記録
         * - 最小限のログ出力
         */
        case ERROR_LEVEL:
            error();
            /*
             * ここでbreakを配置
             * switch文から抜け出す
             */
            break;
            
        /*
         * 【default case】
         * 
         * 無効なレベルの処理：
         * - INVALID_LEVEL または想定外の値
         * - エラーメッセージの表示
         * - システムの堅牢性確保
         */
        default:
            /*
             * 【特別なメッセージ表示】
             * 
             * 課題仕様による特別な処理：
             * - 無効レベル時の専用メッセージ
             * - ユーモアのあるエラー表示
             * - Harlキャラクターの一貫性維持
             */
            std::cout << "[ Probably complaining about insignificant problems ]" 
                      << std::endl;
            break;
    }
}

/*
 * ====================================================================
 * 実装の詳細解説と動作例
 * ====================================================================
 * 
 * 【動作例1：DEBUG レベル指定】
 * 
 * 入力：harl.complainFilter("DEBUG");
 * 
 * 実行フロー：
 * 1. stringToLevel("DEBUG") → DEBUG_LEVEL (0)
 * 2. switch (DEBUG_LEVEL) → case DEBUG_LEVEL:
 * 3. debug() 実行 → "[DEBUG] I love having extra bacon..."
 * 4. fall-through → case INFO_LEVEL:
 * 5. info() 実行 → "[INFO] I cannot believe adding..."
 * 6. fall-through → case WARNING_LEVEL:
 * 7. warning() 実行 → "[WARNING] I think I deserve..."
 * 8. fall-through → case ERROR_LEVEL:
 * 9. error() 実行 → "[ERROR] This is unacceptable!"
 * 10. break → switch終了
 * 
 * 出力：4つのメッセージすべてが表示
 * 
 * 【動作例2：WARNING レベル指定】
 * 
 * 入力：harl.complainFilter("WARNING");
 * 
 * 実行フロー：
 * 1. stringToLevel("WARNING") → WARNING_LEVEL (2)
 * 2. switch (WARNING_LEVEL) → case WARNING_LEVEL:
 * 3. debug(), info() はスキップされる
 * 4. warning() 実行 → "[WARNING] I think I deserve..."
 * 5. fall-through → case ERROR_LEVEL:
 * 6. error() 実行 → "[ERROR] This is unacceptable!"
 * 7. break → switch終了
 * 
 * 出力：WARNING と ERROR の2つのメッセージ
 * 
 * 【動作例3：無効レベル指定】
 * 
 * 入力：harl.complainFilter("INVALID");
 * 
 * 実行フロー：
 * 1. stringToLevel("INVALID") → INVALID_LEVEL (4)
 * 2. switch (INVALID_LEVEL) → default:
 * 3. 特別メッセージ出力
 * 4. break → switch終了
 * 
 * 出力："[ Probably complaining about insignificant problems ]"
 */

/*
 * ====================================================================
 * fall-through機能の詳細理解
 * ====================================================================
 * 
 * 【なぜfall-throughが適切なのか？】
 * 
 * ログレベルの性質：
 * - 階層構造を持つ（DEBUG < INFO < WARNING < ERROR）
 * - 高いレベルは低いレベルを含む概念
 * - フィルタリングでは「以上」の概念が重要
 * 
 * 従来の実装方法との比較：
 * 
 * 【方法1：if文による実装】
 * ```cpp
 * void complainFilter(std::string level) {
 *     LogLevel logLevel = stringToLevel(level);
 *     if (logLevel <= DEBUG_LEVEL) debug();
 *     if (logLevel <= INFO_LEVEL) info();
 *     if (logLevel <= WARNING_LEVEL) warning();
 *     if (logLevel <= ERROR_LEVEL) error();
 * }
 * ```
 * 
 * 【方法2：for文による実装】
 * ```cpp
 * void complainFilter(std::string level) {
 *     LogLevel logLevel = stringToLevel(level);
 *     void (Harl::*functions[])(void) = {&Harl::debug, &Harl::info, 
 *                                         &Harl::warning, &Harl::error};
 *     for (int i = logLevel; i <= ERROR_LEVEL; i++) {
 *         (this->*functions[i])();
 *     }
 * }
 * ```
 * 
 * 【switch + fall-throughの利点】
 * 
 * 1. 意図の明確性
 *    - 各レベルでの開始点が明確
 *    - 階層構造が視覚的に理解しやすい
 * 
 * 2. 効率性
 *    - 条件判定が1回のみ
 *    - 不要な比較処理なし
 * 
 * 3. 拡張性
 *    - 新しいレベル追加が容易
 *    - case追加のみで対応可能
 * 
 * 4. 可読性
 *    - 各レベルでの処理が明確
 *    - デバッグが容易
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ switch文の基本構文理解
 * □ fall-through動作の理解と実装
 * □ enum値を使った数値比較
 * □ 文字列からenum値への変換実装
 * □ 階層的ログ出力システムの実現
 * □ default caseでのエラーハンドリング
 * □ break文の適切な配置
 * □ 意図的なbreak省略（fall-through）
 * □ レベルフィルタリングの実用的応用
 * □ ex05との実装手法比較理解
 * 
 * 【実習課題】
 * 1. 新しいログレベル（FATAL）をシステムに追加
 * 2. 逆順出力（高レベルから低レベル）の実装
 * 3. レベル範囲指定（開始〜終了）の対応
 * 4. 出力先指定（コンソール/ファイル）の実装
 * 5. タイムスタンプ付きログの追加
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：意図しないfall-through】
 * 
 * 間違い例：
 * ```cpp
 * switch (level) {
 *     case DEBUG_LEVEL:
 *         debug();
 *         // breakを忘れる → 意図しない継続実行
 *     case INFO_LEVEL:
 *         info();
 *         break;
 * }
 * ```
 * 
 * 対策：
 * - fall-throughの意図を明確にコメント
 * - 各caseでの動作を文書化
 * - コードレビューでの確認
 * 
 * 【ミス2：enum値の順序間違い】
 * 
 * 間違い例：
 * ```cpp
 * enum LogLevel {
 *     ERROR_LEVEL = 0,    // 順序が逆
 *     WARNING_LEVEL = 1,
 *     INFO_LEVEL = 2,
 *     DEBUG_LEVEL = 3
 * };
 * ```
 * 
 * 影響：フィルタリング動作が逆になる
 * 対策：レベルの重要度順序を明確に定義
 * 
 * 【ミス3：default caseの処理不備】
 * 
 * 間違い例：
 * ```cpp
 * switch (level) {
 *     // cases...
 *     default:
 *         // 何も処理しない → 無言でエラー
 * }
 * ```
 * 
 * 対策：
 * - 必ずdefault caseを実装
 * - 適切なエラーメッセージ出力
 * - ログやデバッグ情報の記録
 * 
 * 【ミス4：文字列比較の大文字小文字】
 * 
 * 問題：
 * - "debug" と "DEBUG" が別扱い
 * - ユーザビリティの低下
 * 
 * 改良案：
 * ```cpp
 * std::string upperLevel = level;
 * std::transform(upperLevel.begin(), upperLevel.end(), 
 *                upperLevel.begin(), ::toupper);
 * if (upperLevel == "DEBUG") {
 *     return DEBUG_LEVEL;
 * }
 * ```
 */

/*
 * ====================================================================
 * 発展的な改良提案
 * ====================================================================
 * 
 * 【改良1：設定ファイル対応】
 * ```cpp
 * class ConfigurableHarl {
 * private:
 *     LogLevel defaultLevel;
 *     
 * public:
 *     void loadConfig(const std::string& configFile) {
 *         // 設定ファイルからレベルを読み込み
 *     }
 * };
 * ```
 * 
 * 【改良2：出力カスタマイズ】
 * ```cpp
 * class CustomHarl {
 * private:
 *     std::map<LogLevel, std::string> customMessages;
 *     
 * public:
 *     void setCustomMessage(LogLevel level, const std::string& msg) {
 *         customMessages[level] = msg;
 *     }
 * };
 * ```
 * 
 * 【改良3：ログ出力制御】
 * ```cpp
 * class ControlledHarl {
 * private:
 *     bool enabledLevels[4];
 *     
 * public:
 *     void enableLevel(LogLevel level, bool enable) {
 *         enabledLevels[level] = enable;
 *     }
 *     
 *     void complainFilter(std::string level) {
 *         LogLevel logLevel = stringToLevel(level);
 *         switch (logLevel) {
 *             case DEBUG_LEVEL:
 *                 if (enabledLevels[DEBUG_LEVEL]) debug();
 *                 // fall-through
 *             case INFO_LEVEL:
 *                 if (enabledLevels[INFO_LEVEL]) info();
 *                 // fall-through
 *             // ...
 *         }
 *     }
 * };
 * ```
 * 
 * 【改良4：パフォーマンス最適化】
 * ```cpp
 * class OptimizedHarl {
 * private:
 *     static const std::map<std::string, LogLevel> levelMap;
 *     
 * public:
 *     LogLevel stringToLevel(const std::string& level) {
 *         std::map<std::string, LogLevel>::const_iterator it = 
 *             levelMap.find(level);
 *         return (it != levelMap.end()) ? it->second : INVALID_LEVEL;
 *     }
 * };
 * 
 * const std::map<std::string, LogLevel> OptimizedHarl::levelMap = {
 *     {"DEBUG", DEBUG_LEVEL},
 *     {"INFO", INFO_LEVEL},
 *     {"WARNING", WARNING_LEVEL},
 *     {"ERROR", ERROR_LEVEL}
 * };
 * ```
 */