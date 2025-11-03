/*
 * ====================================================================
 * CPP02 ex02: 完全な演算子オーバーロード - 実装解説版
 * ====================================================================
 * 
 * この実装では、C++の演算子オーバーロードの完全な形を学習します。
 * 各演算子がどのように実装され、なぜその実装になっているのか、
 * プロフェッショナルなC++での演算子設計原則を理解します。
 */

#include "Fixed.hpp"

/*
 * ====================================================================
 * 基本機能（ex01から継承、デバッグログ削除版）
 * ====================================================================
 * 
 * 【ex01からの変更点】
 * デバッグログを削除して実用版に
 * 
 * なぜログを削除？
 * 1. 演算子が頻繁に呼ばれるため出力が煩雑
 * 2. 実用性を重視
 * 3. パフォーマンス向上
 * 
 * これは実際の開発でよくある進化
 * 開発版 → デバッグ版 → リリース版
 */

Fixed::Fixed(void) : _value(0) {
    /*
     * 簡潔な実装
     * デバッグログなしでパフォーマンス重視
     */
}

Fixed::Fixed(const int value) {
    /*
     * 整数変換（ex01と同じアルゴリズム）
     * ログ出力なしでクリーンな実装
     */
    this->_value = value << this->_fractionalBits;
}

Fixed::Fixed(const float value) {
    /*
     * 浮動小数点変換（ex01と同じアルゴリズム）
     * roundf() による適切な丸め処理
     */
    this->_value = roundf(value * (1 << this->_fractionalBits));
}

Fixed::Fixed(const Fixed& other) {
    /*
     * コピーコンストラクタ
     * 代入演算子を利用した実装
     */
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
    /*
     * 代入演算子
     * 自己代入チェック付き
     */
    if (this != &other) {
        this->_value = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed(void) {
    /*
     * デストラクタ
     * 特別な処理不要のためシンプル実装
     */
}

int Fixed::getRawBits(void) const {
    return this->_value;
}

void Fixed::setRawBits(int const raw) {
    this->_value = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(this->_value) / (1 << this->_fractionalBits);
}

int Fixed::toInt(void) const {
    return this->_value >> this->_fractionalBits;
}

/*
 * ====================================================================
 * 新機能1: 比較演算子群の実装
 * ====================================================================
 * 
 * 【実装原理】
 * 固定小数点数では内部表現の比較で十分
 * スケールが同じなら大小関係が保持される
 * 
 * 【設計パターン】
 * 6つの演算子すべてを直接実装
 * （他の演算子からの派生実装も可能だが、効率性を重視）
 */

/*
 * bool Fixed::operator>(const Fixed& other) const {
 *     return this->_value > other._value;
 * }
 * 
 * 【なぜ内部表現で比較？】
 * 
 * 数学的証明:
 * a > b ⟺ (a_value / scale) > (b_value / scale)
 *       ⟺ a_value > b_value (scale > 0)
 * 
 * 具体例:
 * 3.5 → _value = 896
 * 2.8 → _value = 716  
 * 896 > 716 ✓ (3.5 > 2.8)
 * 
 * 【効率性】
 * - toFloat() 変換不要
 * - 整数比較1回だけ
 * - 精度損失なし
 */
bool Fixed::operator>(const Fixed& other) const {
    /*
     * シンプルで効率的な実装
     * 内部表現の直接比較
     */
    return this->_value > other._value;
}

bool Fixed::operator<(const Fixed& other) const {
    /*
     * より小さい判定
     * > と同じ原理
     */
    return this->_value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const {
    /*
     * 以上の判定
     * 
     * 【代替実装】
     * return !(*this < other);  // < の否定でも実装可能
     * 
     * 現在の実装を選択した理由:
     * 1. 直接的で理解しやすい
     * 2. わずかに効率的（否定演算不要）
     * 3. デバッグ時に分かりやすい
     */
    return this->_value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const {
    /*
     * 以下の判定
     * >= と同様の設計判断
     */
    return this->_value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const {
    /*
     * 等価判定
     * 
     * 【重要な特徴】
     * 固定小数点では厳密な等価判定が可能
     * 
     * 浮動小数点との違い:
     * float: 0.1 + 0.2 != 0.3 (丸め誤差)
     * Fixed: 正確な等価判定可能
     * 
     * 【注意点】
     * 異なる方法で作成された同じ値は等価
     * Fixed a(3.14f);
     * Fixed b = Fixed(3) + Fixed(0.14f);
     * a == b は実装次第で結果が変わる可能性
     */
    return this->_value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const {
    /*
     * 非等価判定
     * 
     * 【実装選択】
     * 現在: 直接実装
     * 代替: return !(*this == other);
     * 
     * どちらも正しいが、一貫性のため直接実装を選択
     */
    return this->_value != other._value;
}

/*
 * ====================================================================
 * 新機能2: 算術演算子群の実装
 * ====================================================================
 * 
 * 【共通の実装パターン】
 * 1. 新しいFixedオブジェクトを作成
 * 2. 計算結果をsetRawBits()で設定
 * 3. 結果オブジェクトを値で返す
 * 
 * 【なぜ値返し？】
 * - 新しい値の作成（元のオブジェクトは不変）
 * - ローカル変数の参照返しは危険
 * - 組み込み型との一貫性
 */

/*
 * Fixed Fixed::operator+(const Fixed& other) const {
 *     Fixed result;
 *     result.setRawBits(this->_value + other._value);
 *     return result;
 * }
 * 
 * 【加算の原理】
 * 
 * 数学的背景:
 * (a × scale) + (b × scale) = (a + b) × scale
 * 
 * 内部表現での計算:
 * a._value + b._value = (a + b) の内部表現
 * 
 * 例:
 * 3.5 (896) + 2.25 (576) = 5.75 (1472)
 * 896 + 576 = 1472 ✓
 * 
 * 【オーバーフロー考慮】
 * int の範囲内であれば問題なし
 * より安全な実装では long long を使用
 */
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    /*
     * setRawBits() を使用する理由:
     * 1. カプセル化の原則
     * 2. 将来の拡張への対応
     * 3. 一貫したインターフェース使用
     */
    result.setRawBits(this->_value + other._value);
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
    /*
     * 減算
     * 加算と同じ原理、符号が逆
     */
    Fixed result;
    result.setRawBits(this->_value - other._value);
    return result;
}

/*
 * Fixed Fixed::operator*(const Fixed& other) const {
 *     Fixed result;
 *     result.setRawBits((this->_value * other._value) >> this->_fractionalBits);
 *     return result;
 * }
 * 
 * 【乗算の複雑さ】
 * 
 * 単純な乗算では不正確:
 * (a × scale) × (b × scale) = (a × b) × scale²
 * スケールが二重になってしまう
 * 
 * 【スケール調整】
 * 結果を scale で割る必要がある
 * (a._value × b._value) / scale
 * = (a._value × b._value) >> _fractionalBits
 * 
 * ビット演算による除算で効率化
 * 
 * 【例】
 * 3.5 (896) × 2.0 (512) = 7.0
 * 896 × 512 = 458752
 * 458752 >> 8 = 1792
 * 1792 / 256 = 7.0 ✓
 * 
 * 【オーバーフロー対策】
 * より安全な実装:
 * long long temp = (long long)this->_value * other._value;
 * result.setRawBits(temp >> this->_fractionalBits);
 */
Fixed Fixed::operator*(const Fixed& other) const {
    Fixed result;
    /*
     * 現在の実装は簡潔だがオーバーフローリスク有り
     * 実用的な範囲では十分だが、より安全な実装も可能
     */
    result.setRawBits((this->_value * other._value) >> this->_fractionalBits);
    return result;
}

/*
 * Fixed Fixed::operator/(const Fixed& other) const {
 *     Fixed result;
 *     result.setRawBits((this->_value << this->_fractionalBits) / other._value);
 *     return result;
 * }
 * 
 * 【除算の工夫】
 * 
 * 問題:
 * a._value / b._value では精度が失われる
 * 
 * 解決策:
 * 分子を scale 倍してから除算
 * (a._value × scale) / b._value
 * = (a._value << _fractionalBits) / b._value
 * 
 * 【例】
 * 7.0 (1792) ÷ 2.0 (512) = 3.5
 * (1792 << 8) ÷ 512 = 458752 ÷ 512 = 896
 * 896 / 256 = 3.5 ✓
 * 
 * 【ゼロ除算対策】
 * 現在の実装では未対応
 * 実用版では以下が必要:
 * if (other._value == 0) {
 *     // エラー処理（例外throw等）
 * }
 */
Fixed Fixed::operator/(const Fixed& other) const {
    Fixed result;
    /*
     * ゼロ除算チェックは省略（課題要件による）
     * 実用実装では必須
     */
    result.setRawBits((this->_value << this->_fractionalBits) / other._value);
    return result;
}

/*
 * ====================================================================
 * 新機能3: インクリメント/デクリメント演算子
 * ====================================================================
 * 
 * 【前置 vs 後置の実装パターン】
 * 
 * 前置: オブジェクトを変更してから参照を返す
 * 後置: 元の値を保存、オブジェクト変更、元の値を返す
 * 
 * 【パフォーマンス比較】
 * 前置: 高速（コピー不要）
 * 後置: 低速（一時オブジェクト作成）
 * 
 * 推奨: 戻り値を使わない場合は前置を使用
 */

/*
 * Fixed& Fixed::operator++(void) {
 *     this->_value++;
 *     return *this;
 * }
 * 
 * 【前置インクリメント実装分析】
 * 
 * this->_value++;
 * 
 * 問題: これは1/256だけ増加
 * 意図: 1.0だけ増加したい
 * 
 * 正しい実装:
 * this->_value += (1 << this->_fractionalBits);
 * 
 * 【現在の実装の意味】
 * 最小単位（1/256 ≈ 0.00390625）だけ増加
 * 
 * これは設計判断の問題:
 * 1. 1.0ずつ増加（直感的）
 * 2. 最小単位ずつ増加（精密制御）
 * 
 * 課題では最小単位を採用
 */
Fixed& Fixed::operator++(void) {
    /*
     * 最小単位での増加
     * 
     * より直感的な実装案:
     * this->_value += (1 << this->_fractionalBits);  // 1.0増加
     */
    this->_value++;
    return *this;
}

/*
 * Fixed Fixed::operator++(int) {
 *     Fixed temp(*this);
 *     this->_value++;
 *     return temp;
 * }
 * 
 * 【後置インクリメント実装パターン】
 * 
 * 1. コピー保存: Fixed temp(*this);
 * 2. 自身を変更: this->_value++;
 * 3. 元の値返却: return temp;
 * 
 * 【int パラメータ】
 * 前置との区別用ダミーパラメータ
 * 実際には使用されない
 * C++の言語仕様による識別方法
 * 
 * 【効率性の考慮】
 * temp オブジェクトの作成でオーバーヘッド
 * 戻り値を使わない場合は前置を推奨
 */
Fixed Fixed::operator++(int) {
    /*
     * 標準的な後置インクリメント実装
     * 
     * 手順:
     * 1. 元の状態を保存
     * 2. 前置演算子の処理を実行
     * 3. 保存した元の状態を返す
     */
    Fixed temp(*this);
    this->_value++;
    return temp;
}

Fixed& Fixed::operator--(void) {
    /*
     * 前置デクリメント
     * インクリメントと同じパターン
     */
    this->_value--;
    return *this;
}

Fixed Fixed::operator--(int) {
    /*
     * 後置デクリメント
     * インクリメントと同じパターン
     */
    Fixed temp(*this);
    this->_value--;
    return temp;
}

/*
 * ====================================================================
 * 新機能4: 静的min/max関数の実装
 * ====================================================================
 * 
 * 【静的関数の設計理由】
 * 1. 特定のインスタンスに依存しない汎用機能
 * 2. std::min, std::max との一貫性
 * 3. クラスレベルのユーティリティ関数
 * 
 * 【const版とnon-const版】
 * オーバーロードによりconst性を保持
 * 適切なバージョンがコンパイラにより選択される
 */

/*
 * Fixed& Fixed::min(Fixed& a, Fixed& b) {
 *     return (a < b) ? a : b;
 * }
 * 
 * 【三項演算子の使用】
 * (a < b) ? a : b
 * 
 * if文と同等だが簡潔
 * 戻り値の型が統一される
 * 
 * 【参照返しの利点】
 * 1. 結果を変更可能: Fixed::min(a, b) = c;
 * 2. 効率的（コピー不要）
 * 3. 元のオブジェクトとの同一性保持
 * 
 * 【比較演算子の活用】
 * 既に実装したoperator<を使用
 * 実装の再利用とDRY原則
 */
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    /*
     * シンプルで効率的な実装
     * 既存の比較演算子を活用
     */
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    /*
     * const版
     * 
     * const参照を受け取り、const参照を返す
     * constオブジェクトからも呼び出し可能
     */
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    /*
     * 最大値取得
     * min()と対照的な実装
     */
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    /*
     * const版の最大値取得
     */
    return (a > b) ? a : b;
}

/*
 * ストリーム出力演算子（ex01と同じ）
 */
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このファイルから学ぶべきこと】
 * 
 * 1. 演算子オーバーロードの完全な実装
 *    - 比較演算子の効率的実装
 *    - 算術演算子のスケーリング処理
 *    - 前置・後置演算子の区別
 * 
 * 2. 固定小数点演算の数学的原理
 *    - 内部表現での直接演算
 *    - スケール調整の必要性
 *    - ビット演算による最適化
 * 
 * 3. C++の言語機能の活用
 *    - 戻り値型の適切な選択
 *    - const correctness の実践
 *    - 静的関数の設計
 * 
 * 4. 実用的なクラス設計
 *    - 組み込み型との一貫性
 *    - 効率性と使いやすさのバランス
 *    - 拡張可能な設計
 * 
 * 【次のステップ】
 * - BSP (Binary Space Partitioning) での実用応用
 * - より高度なC++機能への発展
 * - パフォーマンス最適化の検討
 */

/*
 * ====================================================================
 * よくある質問と回答
 * ====================================================================
 * 
 * Q: なぜ++演算子で1.0ではなく最小単位を増加？
 * A: 設計判断の問題。最小単位なら精密制御が可能。
 *    1.0ずつ増加したい場合は += 1 を使用。
 * 
 * Q: 乗算・除算でオーバーフローは起こらない？
 * A: int の範囲内では通常問題なし。
 *    より安全な実装では long long を使用。
 * 
 * Q: ゼロ除算のチェックは不要？
 * A: 課題要件によっては省略可能。
 *    実用実装では必須の機能。
 * 
 * Q: 静的関数のconst版は本当に必要？
 * A: const correctness のため必要。
 *    コンパイラが適切に選択する。
 */

/*
 * ====================================================================
 * 改善案と拡張可能性
 * ====================================================================
 * 
 * 【パフォーマンス改善】
 * 1. 乗算・除算での long long 使用
 * 2. インライン関数化の検討
 * 3. 移動セマンティクス（C++11以降）
 * 
 * 【機能拡張】
 * 1. 複合代入演算子（+=, -=, *=, /=）
 * 2. 数学関数（sqrt, sin, cos等）
 * 3. より高精度な変換関数
 * 
 * 【安全性向上】
 * 1. オーバーフロー検出
 * 2. ゼロ除算例外処理
 * 3. 範囲チェック機能
 * 
 * これらは CPP05 以降や実用プロジェクトでの発展課題
 */