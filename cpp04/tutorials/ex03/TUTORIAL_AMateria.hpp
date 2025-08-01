/*
 * ====================================================================
 * CPP04 ex03: 抽象基底クラスとクローンパターン - AMateriaヘッダー解説版
 * ====================================================================
 * 
 * この演習では、抽象基底クラスの設計を学習します。
 * 
 * 【学習目標】
 * - 抽象基底クラス vs インターフェースの違い
 * - クローンパターン（Prototype Pattern）の実装
 * - 仮想関数と純粋仮想関数の使い分け
 * - 共通機能の適切な抽象化
 * 
 * AMateriaは「魔法の石」を表現する抽象基底クラスです。
 * 具象クラス（Ice, Cure等）の共通基盤を提供します。
 */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include <string>

/*
 * class ICharacter;  // Forward declaration
 * 
 * 【相互参照の解決】
 * 
 * AMateria::use(ICharacter& target) で ICharacter を使用
 * ICharacter::equip(AMateria* m) で AMateria を使用
 * 
 * どちらも相手の完全な定義が必要だが、
 * 両方のヘッダーを相互インクルードすると循環参照
 * 
 * 【解決策】
 * 前方宣言により、ポインタや参照での使用を可能にする
 * 実装ファイル（.cpp）で実際のインクルードを行う
 */
class ICharacter;  // Forward declaration

/*
 * ====================================================================
 * AMateria 抽象基底クラス - 部分的実装を提供
 * ====================================================================
 * 
 * 【抽象基底クラスの特徴】
 * 
 * 1. 純粋仮想関数を含む（インスタンス化不可）
 * 2. 具象メソッドとデータメンバも持つ
 * 3. 派生クラスの共通機能を実装
 * 4. 部分的な実装を提供
 * 
 * 【インターフェース（ICharacter）との違い】
 * 
 * インターフェース:
 * - 純粋仮想関数のみ
 * - データメンバなし
 * - 契約の定義
 * 
 * 抽象基底クラス:
 * - 混在（具象 + 純粋仮想）
 * - データメンバあり
 * - 共通実装の提供
 * 
 * 【設計の意図】
 * すべての Materia が持つ共通属性（type）と
 * 共通動作（getType）を実装
 * 
 * 個別の動作（clone, use）は派生クラスで実装
 */
class AMateria {
protected:
    /*
     * std::string type;
     * 
     * 【protectedアクセス指定子】
     * 
     * private でも public でもなく protected:
     * - 派生クラスからアクセス可能
     * - 外部からは直接アクセス不可
     * - カプセル化を維持しつつ継承で利用
     * 
     * 【なぜ protected？】
     * 
     * private の場合:
     * 派生クラスからアクセス不可
     * → getType() 経由でのみアクセス
     * → オーバーヘッドが発生
     * 
     * public の場合:
     * 外部から直接変更可能
     * → カプセル化の破綻
     * → 予期しない動作の原因
     * 
     * protected の場合:
     * 継承階層内でのみアクセス可能
     * → 適切なカプセル化
     * → 効率的なアクセス
     * 
     * 【設計原則】
     * 「派生クラスは基底クラスの内部実装にアクセスできるが、
     *  外部クライアントはアクセスできない」
     * 
     * 【type の役割】
     * - Materia の種類を識別（"ice", "cure" 等）
     * - 実行時型情報（RTTI）の代替
     * - デバッグ時の識別子
     * - ゲームロジックでの判定材料
     */
    std::string type;

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form - 抽象基底クラス版
     * ====================================================================
     * 
     * 抽象基底クラスでも OCF は必要
     * ただし、実装に特別な配慮が必要
     */
    
    /*
     * AMateria(void);
     * 
     * デフォルトコンストラクタ
     * 
     * 【抽象クラスのコンストラクタ】
     * - 直接インスタンス化はできない
     * - 派生クラスのコンストラクタから呼び出される
     * - 共通の初期化処理を実行
     * 
     * 【初期化戦略】
     * type を空文字列で初期化？
     * type を "unknown" で初期化？
     * 
     * 実装では空文字列を選択
     * 派生クラスで適切な値を設定することを前提
     */
    AMateria(void);
    
    /*
     * AMateria(const std::string& type);
     * 
     * 型指定コンストラクタ
     * 
     * 【派生クラスからの利用】
     * class Ice : public AMateria {
     * public:
     *     Ice() : AMateria("ice") {}
     * };
     * 
     * 基底クラスのコンストラクタを明示的に呼び出し
     * 適切な type 値を設定
     * 
     * 【const std::string& の利点】
     * - 文字列リテラルから効率的に初期化
     * - 不要なコピーを回避
     * - 一時オブジェクトからも初期化可能
     */
    AMateria(const std::string& type);
    
    /*
     * AMateria(const AMateria& other);
     * 
     * コピーコンストラクタ
     * 
     * 【抽象クラスのコピー】
     * 
     * 直接的な使用例:
     * AMateria obj1, obj2;  // エラー：抽象クラス
     * 
     * 間接的な使用例:
     * Ice ice1;
     * Ice ice2(ice1);  // Ice のコピーコンストラクタから呼び出される
     * 
     * 【実装の重要性】
     * 派生クラスのコピーコンストラクタで
     * 基底クラス部分のコピーが必要
     * 
     * 【スライシング問題への注意】
     * AMateria& ref = ice;
     * AMateria copy = ref;  // スライシング発生（コンパイルエラー）
     */
    AMateria(const AMateria& other);
    
    /*
     * AMateria& operator=(const AMateria& other);
     * 
     * 代入演算子
     * 
     * 【ポリモーフィックな代入の課題】
     * 
     * 問題のあるコード:
     * Ice ice;
     * Cure cure;
     * AMateria& ref1 = ice;
     * AMateria& ref2 = cure;
     * ref1 = ref2;  // Ice に Cure を代入？
     * 
     * この実装では type のみコピー
     * 実際の Materia の種類は変わらない
     * 
     * 【設計判断】
     * 完全なポリモーフィック代入は複雑
     * 基本的な属性（type）のコピーのみ実装
     * より複雑な代入が必要な場合は clone() を使用
     */
    AMateria& operator=(const AMateria& other);
    
    /*
     * virtual ~AMateria(void);
     * 
     * 仮想デストラクタ
     * 
     * 【必須の理由】
     * AMateria* ptr = new Ice();
     * delete ptr;  // Ice のデストラクタが正しく呼ばれる必要
     * 
     * virtual がないと:
     * AMateria のデストラクタのみ実行
     * → Ice の固有リソースがリークする可能性
     * 
     * virtual があると:
     * 実際のオブジェクト型（Ice）のデストラクタが実行
     * → 適切なクリーンアップが保証される
     * 
     * 【抽象クラスでの実装】
     * 純粋仮想デストラクタも可能だが複雑
     * 通常の仮想デストラクタで十分
     */
    virtual ~AMateria(void);
    
    /*
     * ====================================================================
     * 具象メソッド - 共通機能の実装
     * ====================================================================
     */
    
    /*
     * const std::string& getType(void) const;
     * 
     * 【共通機能の実装】
     * 
     * すべての Materia で同じ動作:
     * - type メンバの値を返す
     * - 実装が共通なので基底クラスで提供
     * 
     * 【const correctness】
     * - const メソッド: オブジェクトを変更しない
     * - const 戻り値: 呼び出し元での変更を防止
     * - 参照返し: 効率的（コピー回避）
     * 
     * 【virtual にしない理由】
     * - 派生クラスでの動作変更が不要
     * - 実装が完全に共通
     * - 仮想関数のオーバーヘッド回避
     * 
     * ただし、virtual にしても問題はない
     * 設計方針の問題
     */
    const std::string& getType(void) const;
    
    /*
     * ====================================================================
     * 純粋仮想関数 - 派生クラスでの実装が必要
     * ====================================================================
     */
    
    /*
     * virtual AMateria* clone(void) const = 0;
     * 
     * 【クローンパターン（Prototype Pattern）】
     * 
     * 目的:
     * 既存のオブジェクトをコピーして新しいインスタンスを作成
     * 
     * 使用場面:
     * AMateria* original = new Ice();
     * AMateria* copy = original->clone();  // Ice の新しいインスタンス
     * 
     * 【なぜ純粋仮想関数？】
     * 
     * 各 Materia で異なる実装が必要:
     * 
     * class Ice : public AMateria {
     * public:
     *     AMateria* clone() const override {
     *         return new Ice(*this);  // Ice のコピーを作成
     *     }
     * };
     * 
     * class Cure : public AMateria {
     * public:
     *     AMateria* clone() const override {
     *         return new Cure(*this);  // Cure のコピーを作成
     *     }
     * };
     * 
     * 【戻り値型の設計】
     * AMateria* を返す理由:
     * - ポリモーフィズムを維持
     * - 呼び出し元が具体型を知る必要なし
     * - 統一的な扱いが可能
     * 
     * 【メモリ管理の責任】
     * clone() は new でオブジェクトを作成
     * 呼び出し元が delete の責任を持つ
     * 
     * 【const correctness】
     * const メソッド:
     * - 元のオブジェクトを変更しない
     * - const オブジェクトからも呼び出し可能
     * - コピー操作の本質に合致
     */
    virtual AMateria* clone(void) const = 0;  // Pure virtual function
    
    /*
     * virtual void use(ICharacter& target) = 0;
     * 
     * 【使用効果の抽象インターフェース】
     * 
     * 目的:
     * Materia を使用した時の効果を実装
     * 
     * 各 Materia で異なる効果:
     * - Ice: 攻撃魔法
     * - Cure: 回復魔法
     * - Fire: 炎属性攻撃
     * - etc.
     * 
     * 【パラメータ設計】
     * ICharacter& target:
     * - 参照渡しで non-null を保証
     * - 対象キャラクターへの効果適用
     * - 自分自身も対象にできる（回復等）
     * 
     * 【実装例】
     * class Ice : public AMateria {
     * public:
     *     void use(ICharacter& target) override {
     *         std::cout << "* shoots an ice bolt at " 
     *                   << target.getName() << " *" << std::endl;
     *         target.takeDamage(10);  // 仮想的なダメージ
     *     }
     * };
     * 
     * class Cure : public AMateria {
     * public:
     *     void use(ICharacter& target) override {
     *         std::cout << "* heals " << target.getName() 
     *                   << "'s wounds *" << std::endl;
     *         target.heal(15);  // 仮想的な回復
     *     }
     * };
     * 
     * 【Strategy Pattern との関係】
     * 各 Materia の use() は異なる戦略（アルゴリズム）を実装
     * 実行時に適切な戦略が選択される
     */
    virtual void use(ICharacter& target) = 0;  // Pure virtual function
};

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このヘッダーから学ぶべきこと】
 * 
 * 1. 抽象基底クラスの設計
 *    - 共通機能の実装提供
 *    - 個別機能の抽象インターフェース
 *    - protected メンバの適切な使用
 * 
 * 2. クローンパターンの実装
 *    - 仮想コピーコンストラクタの代替
 *    - ポリモーフィックなオブジェクト複製
 *    - メモリ管理の責任分担
 * 
 * 3. 仮想関数の使い分け
 *    - 純粋仮想関数：必須実装
 *    - 通常仮想関数：オーバーライド可能
 *    - 非仮想関数：共通実装
 * 
 * 4. インターフェースとの相互作用
 *    - 前方宣言による循環参照回避
 *    - 抽象度の異なるクラス間の協調
 *    - 責任の適切な分割
 * 
 * 【次のステップ】
 * - 具体的な Materia クラス（Ice, Cure）の実装
 * - Character クラスでの Materia 管理
 * - 実用的なゲームシステムの構築
 */

#endif

/*
 * ====================================================================
 * デザインパターンとの関係
 * ====================================================================
 * 
 * 【Prototype Pattern（プロトタイプパターン）】
 * clone() メソッドで実現
 * 
 * 利点:
 * - 具体クラスを知らずにオブジェクト複製
 * - 実行時の型に基づいた適切な複製
 * - ファクトリパターンの代替
 * 
 * 【Strategy Pattern（戦略パターン）】  
 * use() メソッドで実現
 * 
 * 各 Materia が異なる使用戦略を持つ
 * キャラクターは戦略の実行のみ担当
 * 
 * 【Template Method Pattern の回避】
 * 
 * 代替設計：
 * class AMateria {
 *     void use(ICharacter& target) {  // 非純粋仮想
 *         prepareUse();               // フック
 *         applyEffect(target);        // 純粋仮想
 *         finishUse();                // フック
 *     }
 * protected:
 *     virtual void prepareUse() {}
 *     virtual void applyEffect(ICharacter& target) = 0;
 *     virtual void finishUse() {}
 * };
 * 
 * 現在の設計の方がシンプルで理解しやすい
 */

/*
 * ====================================================================
 * 実用的な拡張例
 * ====================================================================
 * 
 * 【より豊富な Materia システム】
 * 
 * class AMateria {
 * protected:
 *     std::string type;
 *     int level;           // Materia のレベル
 *     int durability;      // 耐久度
 *     int manaCost;        // 消費マナ
 * 
 * public:
 *     // 基本情報
 *     virtual int getLevel() const { return level; }
 *     virtual int getDurability() const { return durability; }
 *     virtual int getManaCost() const { return manaCost; }
 *     
 *     // 状態管理
 *     virtual void levelUp();
 *     virtual bool canUse(const ICharacter& user) const;
 *     virtual void onUse();  // 使用時の耐久度減少等
 *     
 *     // 特殊効果
 *     virtual bool hasPassiveEffect() const { return false; }
 *     virtual void applyPassiveEffect(ICharacter& owner) const {}
 *     
 *     // 組み合わせ効果
 *     virtual std::vector<std::string> getCompatibleTypes() const;
 *     virtual AMateria* combine(const AMateria& other) const;
 * };
 * 
 * 【属性システム】
 * 
 * enum class Element { FIRE, ICE, EARTH, AIR, LIGHT, DARK };
 * enum class MateriaRarity { COMMON, RARE, EPIC, LEGENDARY };
 * 
 * class AMateria {
 * protected:
 *     Element element;
 *     MateriaRarity rarity;
 *     std::vector<std::string> requirements;  // 装備条件
 * 
 * public:
 *     virtual Element getElement() const { return element; }
 *     virtual MateriaRarity getRarity() const { return rarity; }
 *     virtual bool meetsRequirements(const ICharacter& character) const;
 *     
 *     // 属性相性
 *     virtual float getEffectivenessAgainst(Element targetElement) const;
 *     virtual bool isWeakAgainst(Element attackerElement) const;
 * };
 * 
 * 【効果システム】
 * 
 * class Effect {
 * public:
 *     virtual void apply(ICharacter& target) = 0;
 *     virtual void remove(ICharacter& target) = 0;
 *     virtual bool isExpired() const = 0;
 * };
 * 
 * class AMateria {
 * public:
 *     virtual std::vector<std::unique_ptr<Effect>> createEffects() const = 0;
 *     virtual void use(ICharacter& target) override {
 *         auto effects = createEffects();
 *         for (auto& effect : effects) {
 *             effect->apply(target);
 *         }
 *     }
 * };
 * 
 * これらの拡張により、より複雑で興味深い
 * ゲームシステムを構築できる
 */

/*
 * ====================================================================
 * パフォーマンス考慮事項
 * ====================================================================
 * 
 * 【仮想関数のオーバーヘッド】
 * 
 * 仮想関数テーブル（vtable）による間接呼び出し
 * - 1回の追加メモリアクセス
 * - 分岐予測の困難さ
 * - インライン化の阻害
 * 
 * 【clone() のメモリ管理】
 * 
 * 頻繁な new/delete はパフォーマンス問題
 * 
 * 改善案:
 * 1. オブジェクトプール使用
 * 2. スマートポインタ使用
 * 3. 値セマンティクス採用
 * 
 * 【type 文字列の最適化】
 * 
 * 文字列比較は相対的に重い処理
 * 
 * 改善案:
 * enum class MateriaType { ICE, CURE, FIRE, ... };
 * 整数比較で高速化
 * 
 * しかし、学習段階では理解しやすさを優先
 * 実用システムではパフォーマンス最適化を検討
 */