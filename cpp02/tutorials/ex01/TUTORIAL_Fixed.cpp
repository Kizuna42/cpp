/*
 * ====================================================================
 * CPP02 ex01: 型変換コンストラクタ - Fixed クラス実装解説版
 * ====================================================================
 * 
 * この実装では、実用的な固定小数点クラスの核心機能を学びます。
 * - 効率的な型変換アルゴリズム
 * - ビット演算による高速計算
 * - ストリーム出力の実装
 * - 精度と性能のバランス
 */

#include "Fixed.hpp"

/*
 * ====================================================================
 * デフォルトコンストラクタ（ex00と同じ）
 * ====================================================================
 */
Fixed::Fixed(void) : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

/*
 * ====================================================================
 * 新機能1: 整数変換コンストラクタ
 * ====================================================================
 * 
 * Fixed::Fixed(const int value) {
 *     std::cout << "Int constructor called" << std::endl;
 *     this->_value = value << this->_fractionalBits;
 * }
 * 
 * 【変換アルゴリズムの詳細解析】
 * 
 * value << this->_fractionalBits
 * 
 * 数学的意味:
 * - 内部表現 = 実際の値 × 2^fractionalBits
 * - 例: value = 42, fractionalBits = 8
 * - 内部表現 = 42 × 2^8 = 42 × 256 = 10752
 * 
 * ビット表現での理解:
 * 42 (decimal) = 00101010 (binary)
 * 42 << 8      = 0010101000000000 (binary) = 10752 (decimal)
 * 
 * 【なぜ左シフトを使うのか？】
 * 
 * 1. 効率性:
 *    左シフト: CPUの1命令で実行
 *    乗算: 複数命令が必要
 * 
 * 2. 精度:
 *    ビット演算は精密
 *    浮動小数点乗算では誤差が入る可能性
 * 
 * 3. 可読性:
 *    固定小数点の概念が明確
 * 
 * 【代替実装との比較】
 * 
 * // 方法1: ビット演算（採用）
 * this->_value = value << this->_fractionalBits;
 * 
 * // 方法2: 乗算
 * this->_value = value * (1 << this->_fractionalBits);
 * 
 * // 方法3: pow関数
 * this->_value = value * static_cast<int>(std::pow(2, this->_fractionalBits));
 * 
 * 採用理由: 方法1が最も効率的かつ明確
 */
Fixed::Fixed(const int value) {
    /*
     * デバッグログの価値
     * 
     * "Int constructor called"
     * - どの型からの変換が起こったかを明確化
     * - 意図しない暗黙的変換の検出に有用
     * - パフォーマンス分析での呼び出し頻度確認
     */
    std::cout << "Int constructor called" << std::endl;
    
    /*
     * 変換処理の詳細
     * 
     * this->_value = value << this->_fractionalBits;
     * 
     * 実行例:
     * - value = 5
     * - _fractionalBits = 8
     * - _value = 5 << 8 = 5 * 256 = 1280
     * 
     * 検証:
     * 1280 / 256 = 5.0 ✓
     * 
     * 境界値テスト:
     * - value = 0: _value = 0 (0.0を表現)
     * - value = -1: _value = -256 (-1.0を表現)
     * - value = 127: _value = 32512 (127.0を表現)
     * 
     * オーバーフロー考慮:
     * int の最大値は約21億
     * 左シフト8bit: 約800万まで安全
     * 実用的な範囲では十分
     */
    this->_value = value << this->_fractionalBits;
}

/*
 * ====================================================================
 * 新機能2: 浮動小数点変換コンストラクタ
 * ====================================================================
 * 
 * Fixed::Fixed(const float value) {
 *     std::cout << "Float constructor called" << std::endl;
 *     this->_value = roundf(value * (1 << this->_fractionalBits));
 * }
 * 
 * 【なぜこの変換が複雑なのか？】
 * 
 * 浮動小数点 → 固定小数点の課題:
 * 1. 精度の違い: float は約7桁、fixed は設定による
 * 2. 表現方法の違い: 指数表現 vs 固定スケール
 * 3. 丸め誤差: 変換時の精度損失
 * 
 * 【変換アルゴリズムの段階的解析】
 * 
 * ステップ1: スケーリング
 * value * (1 << this->_fractionalBits)
 * 
 * なぜ (1 << _fractionalBits) なのか？
 * - 2^8 = 256 を効率的に計算
 * - 1 << 8 = 256
 * - ビット演算による高速化
 * 
 * ステップ2: 丸め処理
 * roundf(scaled_value)
 * 
 * なぜ roundf() が必要？
 * - 浮動小数点の小数部を適切に処理
 * - 3.7 → 4, 3.3 → 3 (四捨五入)
 * - truncate（切り捨て）では不正確
 * 
 * 【具体例での検証】
 * 
 * 例1: value = 3.14f
 * - スケーリング: 3.14 * 256 = 803.84
 * - 丸め: roundf(803.84) = 804
 * - 検証: 804 / 256 = 3.140625 ≈ 3.14 ✓
 * 
 * 例2: value = -2.5f
 * - スケーリング: -2.5 * 256 = -640.0
 * - 丸め: roundf(-640.0) = -640
 * - 検証: -640 / 256 = -2.5 ✓
 * 
 * 【精度分析】
 * 
 * _fractionalBits = 8 の場合:
 * - 最小単位: 1/256 ≈ 0.00390625
 * - 表現できない例: 0.001 → 0 (精度不足)
 * - 十分な例: 0.01 → 0.0078125 (近似)
 */
Fixed::Fixed(const float value) {
    /*
     * 型別のデバッグログ
     * 
     * Int と Float で異なるメッセージ
     * - デバッグ時にどちらが呼ばれたか明確
     * - 暗黙的変換の追跡が容易
     */
    std::cout << "Float constructor called" << std::endl;
    
    /*
     * 変換処理の実装
     * 
     * this->_value = roundf(value * (1 << this->_fractionalBits));
     * 
     * 【代替実装との比較】
     * 
     * // 現在の実装（推奨）
     * this->_value = roundf(value * (1 << this->_fractionalBits));
     * 
     * // 代替1: static_cast で切り捨て
     * this->_value = static_cast<int>(value * (1 << this->_fractionalBits));
     * 問題: 3.9 → 3 (本来は4になるべき)
     * 
     * // 代替2: floor/ceil の手動実装
     * float scaled = value * (1 << this->_fractionalBits);
     * this->_value = (scaled >= 0) ? static_cast<int>(scaled + 0.5) : static_cast<int>(scaled - 0.5);
     * 冗長だが同じ結果
     * 
     * 【roundf() の詳細仕様】
     * - IEEE 754 準拠の四捨五入
     * - .5 の場合は偶数への丸め（banker's rounding）
     * - 例: 2.5 → 2, 3.5 → 4
     */
    this->_value = roundf(value * (1 << this->_fractionalBits));
}

/*
 * ====================================================================
 * OCF要素（ex00と基本的に同じ）
 * ====================================================================
 */
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_value = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

/*
 * ====================================================================
 * アクセサメソッド（ex00から変更）
 * ====================================================================
 */

/*
 * int Fixed::getRawBits(void) const {
 *     return this->_value;
 * }
 * 
 * 【ex00からの変更点】
 * 
 * ex00版:
 * std::cout << "getRawBits member function called" << std::endl;
 * return this->_value;
 * 
 * ex01版:
 * return this->_value;  // ログ出力なし
 * 
 * 【なぜログを削除？】
 * 1. toFloat(), 代入演算子から頻繁に呼ばれる
 * 2. 出力が煩雑になる
 * 3. 実用性を重視した設計変更
 * 
 * これは実際の開発でよくある進化パターン
 * デバッグ → 実用 → 最適化
 */
int Fixed::getRawBits(void) const {
    /*
     * シンプルな実装
     * 
     * ログ出力なしでパフォーマンス向上
     * 頻度の高いメソッドでは重要な判断
     */
    return this->_value;
}

void Fixed::setRawBits(int const raw) {
    this->_value = raw;
}

/*
 * ====================================================================
 * 新機能3: 型変換メソッド - toFloat()
 * ====================================================================
 * 
 * float Fixed::toFloat(void) const {
 *     return static_cast<float>(this->_value) / (1 << this->_fractionalBits);
 * }
 * 
 * 【逆変換アルゴリズム】
 * 
 * 数学的表現:
 * 実際の値 = 内部表現 / 2^fractionalBits
 * 
 * 【static_cast の重要性】
 * 
 * なぜ static_cast<float> が必要？
 * 
 * // ❌ 間違い: 整数除算になる
 * return this->_value / (1 << this->_fractionalBits);
 * 
 * // ✅ 正しい: 浮動小数点除算
 * return static_cast<float>(this->_value) / (1 << this->_fractionalBits);
 * 
 * 例で確認:
 * _value = 804, _fractionalBits = 8
 * 
 * 整数除算: 804 / 256 = 3 (小数部切り捨て)
 * 浮動小数点除算: 804.0f / 256.0f = 3.140625f
 * 
 * 【精度の考慮】
 * 
 * float の精度限界:
 * - 仮数部: 23bit ≈ 7桁の精度
 * - Fixed の内部: 32bit int
 * - 変換で精度損失の可能性
 * 
 * 実用上の問題:
 * _fractionalBits = 8 なら十分な精度
 * より高精度が必要なら double を検討
 */
float Fixed::toFloat(void) const {
    /*
     * 型変換の詳細
     * 
     * static_cast<float>(this->_value)
     * - int から float への明示的変換
     * - コンパイラ警告の抑制
     * - 変換意図の明確化
     * 
     * (1 << this->_fractionalBits)
     * - 2^8 = 256 の効率的計算
     * - 除数として使用
     * 
     * 全体の効果:
     * 固定小数点の内部表現を実際の浮動小数点値に復元
     */
    return static_cast<float>(this->_value) / (1 << this->_fractionalBits);
}

/*
 * ====================================================================
 * 新機能4: 型変換メソッド - toInt()
 * ====================================================================
 * 
 * int Fixed::toInt(void) const {
 *     return this->_value >> this->_fractionalBits;
 * }
 * 
 * 【整数部抽出アルゴリズム】
 * 
 * 右シフトによる整数部の取得:
 * _value >> _fractionalBits
 * 
 * 数学的意味:
 * 整数部 = 内部表現 / 2^fractionalBits (小数部切り捨て)
 * 
 * 【ビット演算での理解】
 * 
 * 例: _value = 804, _fractionalBits = 8
 * 
 * 804 (decimal) = 001100100100 (12bit表現)
 * 804 >> 8      = 0011 (上位4bit) = 3 (decimal)
 * 
 * 小数部は自動的に切り捨て
 * 
 * 【負数での動作】
 * 
 * C++の右シフトは算術シフト（符号拡張）
 * 
 * 例: _value = -256 (-1.0を表現)
 * -256 >> 8 = -1 ✓
 * 
 * 2の補数表現で正しく動作
 * 
 * 【代替実装との比較】
 * 
 * // 方法1: 右シフト（採用）
 * return this->_value >> this->_fractionalBits;
 * 
 * // 方法2: 除算
 * return this->_value / (1 << this->_fractionalBits);
 * 
 * // 方法3: 浮動小数点経由
 * return static_cast<int>(this->toFloat());
 * 
 * 採用理由:
 * 1. 最も効率的（1CPU命令）
 * 2. 精密（丸め誤差なし）
 * 3. 概念的に明確（ビットの移動）
 */
int Fixed::toInt(void) const {
    /*
     * シンプルで効率的な実装
     * 
     * 右シフトで小数部を切り落とす
     * - 符号付き整数で正しく動作
     * - 浮動小数点演算より高速
     * - メモリ効率も良い
     */
    return this->_value >> this->_fractionalBits;
}

/*
 * ====================================================================
 * 新機能5: ストリーム出力演算子のオーバーロード
 * ====================================================================
 * 
 * std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
 *     out << fixed.toFloat();
 *     return out;
 * }
 * 
 * 【なぜフリー関数なのか？】
 * 
 * メンバ関数での実装を試すと:
 * 
 * class Fixed {
 *     std::ostream& operator<<(std::ostream& out) const;  // ❌ 不可能
 * };
 * 
 * 使用法: fixed << std::cout;  // ❌ 不自然
 * 
 * フリー関数なら:
 * std::cout << fixed;  // ✅ 自然
 * 
 * 【パラメータ設計の詳細】
 * 
 * std::ostream& out:
 * - cout, cerr, ofstream等に対応
 * - 参照渡しで効率化
 * - 戻り値で連鎖可能
 * 
 * const Fixed& fixed:
 * - 出力でオブジェクト変更なし
 * - 参照渡しでコピー回避
 * - 一時オブジェクトからも呼び出し可能
 * 
 * 【戻り値の設計】
 * 
 * std::ostream& を返す理由:
 * 連鎖出力を可能にする
 * 
 * std::cout << f1 << " and " << f2;
 *           ↑         ↑
 *        戻り値      再利用
 * 
 * 【実装方針の選択】
 * 
 * // 方法1: toFloat()使用（採用）
 * out << fixed.toFloat();
 * 
 * // 方法2: 直接計算
 * out << static_cast<float>(fixed.getRawBits()) / 256.0f;
 * 
 * // 方法3: 整数と小数部を分離
 * int intPart = fixed.toInt();
 * float fracPart = fixed.toFloat() - intPart;
 * out << intPart << "." << fracPart;
 * 
 * 採用理由:
 * 1. 既存メソッドの再利用
 * 2. 実装の一貫性
 * 3. 保守性の向上
 */
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    /*
     * シンプルで効果的な実装
     * 
     * fixed.toFloat() を使用:
     * - メソッドの再利用でDRY原則
     * - 変換ロジックの一元化
     * - 将来の変更に対する堅牢性
     * 
     * 出力形式:
     * 浮動小数点表現で人間に読みやすい
     * 例: 3.14159, -2.5, 0
     */
    out << fixed.toFloat();
    
    /*
     * ストリーム連鎖のための戻り値
     * 
     * return out;
     * 
     * これにより以下が可能:
     * std::cout << "Value: " << fixed << " units" << std::endl;
     * 
     * 実行順序:
     * 1. std::cout << "Value: "  → std::cout& 返却
     * 2. std::cout << fixed      → std::cout& 返却  
     * 3. std::cout << " units"   → std::cout& 返却
     * 4. std::cout << std::endl  → std::cout& 返却
     */
    return out;
}

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このファイルから学ぶべきこと】
 * 
 * 1. 効率的なビット演算
 *    - 左シフト（<<）による高速乗算
 *    - 右シフト（>>）による高速除算
 *    - 浮動小数点演算の回避
 * 
 * 2. 精度と性能のバランス
 *    - roundf() による適切な丸め
 *    - static_cast による明示的変換
 *    - デバッグログの取捨選択
 * 
 * 3. 演算子オーバーロードの実践
 *    - メンバ vs フリー関数の選択基準
 *    - 参照返しによる連鎖操作
 *    - const correctness の徹底
 * 
 * 4. 実用的なクラス設計
 *    - 自然な使用感の実現
 *    - 既存メソッドの効果的な再利用
 *    - 拡張可能な設計
 * 
 * 【次のステップ】
 * - TUTORIAL_main.cpp での実用例確認
 * - ex02 での完全な算術演算子実装
 * - BSP応用での実際の用途理解
 */

/*
 * ====================================================================
 * よくある質問と回答
 * ====================================================================
 * 
 * Q: なぜ int から float への変換で精度が落ちない？
 * A: int は32bit、float の仮数部は23bit。
 *    固定小数点の精度範囲内では問題なし。
 * 
 * Q: 負数の右シフトは大丈夫？
 * A: C++では算術シフト（符号拡張）が保証されており、
 *    2の補数表現で正しく動作する。
 * 
 * Q: roundf() を使わないとどうなる？
 * A: static_cast<int>() は切り捨てのため、
 *    3.9 → 3 となり、本来の4にならない。
 * 
 * Q: ストリーム演算子をメンバにできない理由は？
 * A: 左オペランドが std::ostream であり、
 *    固有クラスのメンバ関数では実現不可能。
 */

/*
 * ====================================================================
 * 実装品質チェックリスト
 * ====================================================================
 * 
 * □ 型変換コンストラクタが適切に実装されている
 * □ ビット演算が正しく使用されている
 * □ 丸め処理が適切に行われている
 * □ const correctness が徹底されている
 * □ ストリーム出力が自然に動作する
 * □ パフォーマンスが最適化されている
 * □ 負数でも正しく動作する
 * □ 精度損失が最小限に抑えられている
 */