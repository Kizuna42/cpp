/*
 * ====================================================================
 * CPP02 ex02: 完全な演算子オーバーロード - ヘッダー解説版
 * ====================================================================
 * 
 * この演習でFixedクラスが完成形になります。
 * - 6つの比較演算子（>, <, >=, <=, ==, !=）
 * - 4つの算術演算子（+, -, *, /）
 * - 4つのインクリメント/デクリメント演算子（++, --の前置・後置）
 * - 静的なmin/max関数（const版とnon-const版）
 * 
 * これにより、組み込み型と同等の使いやすさを実現します。
 */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

/*
 * ====================================================================
 * Fixed クラス - 完全機能版固定小数点数
 * ====================================================================
 * 
 * 【設計目標】
 * C++の組み込み型（int, float）と同じように使える
 * 
 * 使用例:
 * Fixed a(10.5f);
 * Fixed b(20.3f);
 * if (a < b) {                    // 比較演算子
 *     Fixed c = a + b;            // 算術演算子
 *     ++c;                        // インクリメント
 *     std::cout << c << std::endl; // ストリーム出力
 * }
 * Fixed d = Fixed::max(a, b);     // 静的関数
 */
class Fixed {
private:
    /*
     * プライベートメンバ（ex00, ex01と同じ）
     * インターフェースのみ拡張、内部実装は変更なし
     */
    int _value;
    static const int _fractionalBits = 8;

public:
    /*
     * ====================================================================
     * 基本機能（ex01から継承）
     * ====================================================================
     */
    Fixed(void);
    Fixed(const int value);
    Fixed(const float value);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed(void);
    
    int getRawBits(void) const;
    void setRawBits(int const raw);
    
    float toFloat(void) const;
    int toInt(void) const;
    
    /*
     * ====================================================================
     * 新機能1: 比較演算子群
     * ====================================================================
     * 
     * 6つの比較演算子をすべて実装
     * 
     * 【なぜ6つすべて必要？】
     * C++98では自動生成されない
     * （C++20からは <=> でまとめて生成可能）
     * 
     * 【実装戦略】
     * 基本演算子（< と ==）を実装
     * 他の演算子はこれらを組み合わせて実装
     * - a > b  ≡ b < a
     * - a >= b ≡ !(a < b)
     * - a <= b ≡ !(b < a)
     * - a != b ≡ !(a == b)
     */
    
    /*
     * bool operator>(const Fixed& other) const;
     * 
     * より大きい判定
     * 
     * 【実装原理】
     * 内部表現同士の比較
     * this->_value > other._value
     * 
     * 【なぜこれで正しいのか？】
     * 固定小数点表現の性質:
     * - スケールが同じなら大小関係保持
     * - 例: 3.5 → 896, 2.5 → 640
     * - 896 > 640 ✓
     */
    bool operator>(const Fixed& other) const;
    
    /*
     * bool operator<(const Fixed& other) const;
     * 
     * より小さい判定
     * 基本的な比較演算子の一つ
     */
    bool operator<(const Fixed& other) const;
    
    /*
     * bool operator>=(const Fixed& other) const;
     * bool operator<=(const Fixed& other) const;
     * 
     * 以上、以下の判定
     * 
     * 【実装方針】
     * - >= : !(< other)
     * - <= : !( other < *this)
     * 
     * 論理的関係を利用した効率的実装
     */
    bool operator>=(const Fixed& other) const;
    bool operator<=(const Fixed& other) const;
    
    /*
     * bool operator==(const Fixed& other) const;
     * 
     * 等価判定
     * 
     * 【注意点】
     * 浮動小数点との比較ではepsilon判定が必要
     * 固定小数点では厳密な等価判定が可能
     * this->_value == other._value
     */
    bool operator==(const Fixed& other) const;
    
    /*
     * bool operator!=(const Fixed& other) const;
     * 
     * 非等価判定
     * !(this == other) で実装
     */
    bool operator!=(const Fixed& other) const;
    
    /*
     * ====================================================================
     * 新機能2: 算術演算子群
     * ====================================================================
     * 
     * 4つの基本算術演算子
     * 
     * 【戻り値の設計判断】
     * Fixed operator+(const Fixed& other) const;
     * 
     * なぜ値返し（Fixed）なのか？
     * - a + b は新しい値を作成
     * - 元のオブジェクトは変更しない
     * - 組み込み型と同じ動作
     * 
     * なぜ参照返し（Fixed&）ではダメなのか？
     * - ローカル変数への参照は危険
     * - 一時オブジェクトの寿命問題
     */
    
    /*
     * Fixed operator+(const Fixed& other) const;
     * 
     * 加算演算子
     * 
     * 【実装原理】
     * 内部表現同士を加算
     * result._value = this->_value + other._value
     * 
     * 【なぜこれで正しいのか？】
     * 固定小数点の加算:
     * (a * 2^n) + (b * 2^n) = (a + b) * 2^n
     * 
     * 例: 3.5 + 2.25
     * 3.5 → 896, 2.25 → 576
     * 896 + 576 = 1472
     * 1472 / 256 = 5.75 ✓
     */
    Fixed operator+(const Fixed& other) const;
    
    /*
     * Fixed operator-(const Fixed& other) const;
     * 
     * 減算演算子
     * 加算と同様の原理
     */
    Fixed operator-(const Fixed& other) const;
    
    /*
     * Fixed operator*(const Fixed& other) const;
     * 
     * 乗算演算子
     * 
     * 【実装の複雑さ】
     * 単純な内部表現の乗算では不正確
     * 
     * 間違い: result._value = this->_value * other._value
     * 理由: スケールが二重になる
     * 
     * 正しい実装:
     * long long temp = (long long)this->_value * other._value;
     * result._value = temp >> _fractionalBits;
     * 
     * 【なぜlong longが必要？】
     * int * int でオーバーフローの可能性
     * より大きな型で計算してからスケール調整
     */
    Fixed operator*(const Fixed& other) const;
    
    /*
     * Fixed operator/(const Fixed& other) const;
     * 
     * 除算演算子
     * 
     * 【実装の工夫】
     * スケール調整が必要
     * 
     * 実装例:
     * long long temp = ((long long)this->_value << _fractionalBits);
     * result._value = temp / other._value;
     * 
     * 【ゼロ除算の考慮】
     * other._value == 0 のチェックが必要
     * 例外処理またはエラー値の返却
     */
    Fixed operator/(const Fixed& other) const;
    
    /*
     * ====================================================================
     * 新機能3: インクリメント/デクリメント演算子
     * ====================================================================
     * 
     * 前置と後置の区別が重要
     * 
     * 【前置 vs 後置の区別方法】
     * Fixed& operator++();     // 前置: ++a
     * Fixed operator++(int);   // 後置: a++
     * 
     * int パラメータは識別用のダミー
     * 実際には使用されない
     */
    
    /*
     * Fixed& operator++(void);  // 前置インクリメント
     * 
     * 【動作】
     * オブジェクト自身を変更してから返す
     * ++a の結果は変更後の a
     * 
     * 【実装】
     * _value += (1 << _fractionalBits);  // 1.0を加算
     * return *this;
     * 
     * 【戻り値が参照の理由】
     * - 効率性（コピー不要）
     * - 連鎖操作可能: ++(++a)
     * - 組み込み型との一貫性
     */
    Fixed& operator++(void);        // pre-increment
    
    /*
     * Fixed operator++(int);  // 後置インクリメント
     * 
     * 【動作】
     * 元の値を返してからオブジェクトを変更
     * a++ の結果は変更前の a
     * 
     * 【実装パターン】
     * Fixed temp(*this);  // 元の値を保存
     * ++(*this);          // 前置演算子を利用
     * return temp;        // 元の値を返す
     * 
     * 【戻り値が値の理由】
     * 元の状態のコピーを返すため
     * 参照だと変更後の値になってしまう
     */
    Fixed operator++(int);          // post-increment
    
    /*
     * デクリメント演算子も同様の設計
     */
    Fixed& operator--(void);        // pre-decrement
    Fixed operator--(int);          // post-decrement
    
    /*
     * ====================================================================
     * 新機能4: 静的min/max関数
     * ====================================================================
     * 
     * std::min, std::max と同様の機能
     * 
     * 【なぜ静的関数？】
     * - クラスレベルの汎用関数
     * - 特定のインスタンスに依存しない
     * - 使用法: Fixed::min(a, b)
     * 
     * 【const版とnon-const版】
     * 
     * static Fixed& min(Fixed& a, Fixed& b);
     * static const Fixed& min(const Fixed& a, const Fixed& b);
     * 
     * なぜ両方必要？
     * - constオブジェクトからも呼び出し可能
     * - 戻り値のconst性を保持
     * - コンパイラの適切なオーバーロード解決
     */
    
    /*
     * static Fixed& min(Fixed& a, Fixed& b);
     * 
     * 【実装】
     * return (a < b) ? a : b;
     * 
     * 【戻り値が参照の理由】
     * - 結果を変更可能にする
     * - Fixed::min(a, b) = c; のような使用が可能
     * - 効率性（コピー回避）
     */
    static Fixed& min(Fixed& a, Fixed& b);
    
    /*
     * static const Fixed& min(const Fixed& a, const Fixed& b);
     * 
     * const版
     * constオブジェクトから呼び出し可能
     * 戻り値もconst参照
     */
    static const Fixed& min(const Fixed& a, const Fixed& b);
    
    /*
     * max関数も同様の設計
     */
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
};

/*
 * ストリーム出力演算子（ex01から継承）
 */
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このヘッダーから学ぶべきこと】
 * 
 * 1. 完全な演算子オーバーロード
 *    - 比較演算子の相互関係
 *    - 算術演算子のスケーリング問題
 *    - 前置・後置演算子の区別
 * 
 * 2. const correctness の徹底
 *    - const版とnon-const版の使い分け
 *    - メソッドのconst修飾
 *    - 戻り値のconst性
 * 
 * 3. 効率性と使いやすさのバランス
 *    - 参照返し vs 値返し
 *    - 基本演算子からの派生実装
 *    - 静的関数の活用
 * 
 * 4. 組み込み型との一貫性
 *    - 動作の予測可能性
 *    - 自然な使用感
 *    - 標準ライブラリとの統合性
 * 
 * 【次のステップ】
 * - TUTORIAL_Fixed.cpp で実装詳細を学習
 * - ex03 でBSP応用を通じた実用例確認
 * - より高度なC++機能への発展
 */

#endif

/*
 * ====================================================================
 * 演算子オーバーロードの設計原則
 * ====================================================================
 * 
 * 【基本原則】
 * 1. 直感的な動作: 組み込み型と同じ感覚
 * 2. 効率性: 不要なコピーの回避
 * 3. 安全性: const correctness の徹底
 * 4. 一貫性: 相互関係の維持
 * 
 * 【実装優先順位】
 * 1. 基本演算子（<, ==, +, *）を先に実装
 * 2. 派生演算子（>, !=, -, /）をそれらから実装
 * 3. 複合演算子（++, --）を基本演算子を使って実装
 * 
 * 【よくある間違い】
 * - 算術演算子でのスケーリング忘れ
 * - 前置・後置の戻り値型混同
 * - const版とnon-const版の実装忘れ
 * - オーバーフロー対策の不備
 */

/*
 * ====================================================================
 * 使用例プレビュー
 * ====================================================================
 * 
 * このヘッダーで可能になる自然な使用法:
 * 
 * Fixed a(10.5f);
 * Fixed b(20.3f);
 * 
 * // 比較演算
 * if (a < b) {
 *     std::cout << "a is smaller" << std::endl;
 * }
 * 
 * // 算術演算
 * Fixed c = a + b;      // 30.8
 * Fixed d = a * b;      // 213.15
 * 
 * // インクリメント
 * ++c;                  // c = 31.8
 * Fixed e = d++;        // e = 213.15, d = 214.15
 * 
 * // 静的関数
 * Fixed largest = Fixed::max(a, b);  // 20.3
 * 
 * // ストリーム出力
 * std::cout << "Result: " << largest << std::endl;
 * 
 * 組み込み型と区別がつかないレベルの使いやすさ！
 */