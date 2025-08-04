/*
 * ====================================================================
 * CPP03 ex01: ScavTrap - 継承（Inheritance）の基礎解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - public継承の構文と意味の理解
 * - 基底クラスと派生クラスの関係性
 * - コンストラクタチェーンの実装
 * - 仮想関数の基礎（virtual function）
 * - 継承によるコードの再利用性向上
 * 
 * 【重要概念】
 * - is-a関係（ScavTrap is a ClapTrap）
 * - メンバ関数のオーバーライド
 * - 基底クラスコンストラクタの呼び出し
 * - protected アクセス修飾子の活用
 * - 多態性（Polymorphism）の導入
 */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>
#include <iostream>

/*
 * ====================================================================
 * ScavTrap クラス設計解説
 * ====================================================================
 * 
 * 【継承の基本構文】
 * class ScavTrap : public ClapTrap
 * 
 * 構文の詳細：
 * - class ScavTrap: 派生クラス（子クラス）
 * - : public: 継承指定子
 * - ClapTrap: 基底クラス（親クラス）
 * 
 * 【public継承の意味】
 * 
 * public継承：
 * - 基底クラスのpublicメンバ → 派生クラスでもpublic
 * - 基底クラスのprotectedメンバ → 派生クラスでもprotected
 * - 基底クラスのprivateメンバ → 派生クラスからアクセス不可
 * 
 * is-a関係の確立：
 * - ScavTrap is a ClapTrap（ScavTrapはClapTrapの一種）
 * - ClapTrapができることはScavTrapでも可能
 * - ScavTrapは追加の機能を持つ
 * 
 * 【継承の利点】
 * 
 * 1. コードの再利用性
 *    - ClapTrapの機能をそのまま継承
 *    - 重複するコードの削減
 * 
 * 2. 拡張性
 *    - 新しい機能の追加が容易
 *    - 既存コードへの影響最小化
 * 
 * 3. 多態性の実現
 *    - 同じインターフェースで異なる動作
 *    - 仮想関数による動的バインディング
 */
class ScavTrap : public ClapTrap {
public:
    /*
     * ====================================================================
     * コンストラクタ・デストラクタ
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * ScavTrap();
     * 
     * 継承でのコンストラクタの特徴：
     * 
     * 呼び出し順序：
     * 1. 基底クラス（ClapTrap）のコンストラクタ
     * 2. 派生クラス（ScavTrap）のコンストラクタ
     * 
     * 初期化の流れ：
     * - ClapTrapの初期化（基本的な戦闘ユニット）
     * - ScavTrapの追加初期化（門番としての特性）
     * 
     * デフォルト値の設定：
     * - name: "DefaultScav"
     * - hitPoints: 100（ClapTrapより強化）
     * - energyPoints: 50（ClapTrapより強化）
     * - attackDamage: 20（ClapTrapより強化）
     */
    ScavTrap();
    
    /*
     * 【パラメータ付きコンストラクタ】
     * ScavTrap(const std::string& name);
     * 
     * 名前指定でのScavTrap作成：
     * 
     * 基底クラスコンストラクタの呼び出し：
     * - ClapTrap(name, 100, 50, 20) を呼び出し
     * - ScavTrap用のパラメータで初期化
     * 
     * 実装パターン：
     * ```cpp
     * ScavTrap::ScavTrap(const std::string& name) 
     *     : ClapTrap(name, 100, 50, 20) {
     *     // ScavTrap固有の初期化
     * }
     * ```
     * 
     * 学習ポイント：
     * - メンバ初期化リストでの基底クラス呼び出し
     * - 基底クラスのコンストラクタ選択
     * - 派生クラス固有の初期化処理
     */
    ScavTrap(const std::string& name);
    
    /*
     * 【コピーコンストラクタ】
     * ScavTrap(const ScavTrap& other);
     * 
     * 継承でのコピーコンストラクタ：
     * 
     * 呼び出し順序：
     * 1. 基底クラスのコピーコンストラクタ
     * 2. 派生クラスのコピーコンストラクタ
     * 
     * 実装パターン：
     * ```cpp
     * ScavTrap::ScavTrap(const ScavTrap& other) 
     *     : ClapTrap(other) {
     *     // ScavTrap固有のコピー処理
     * }
     * ```
     * 
     * 重要な点：
     * - ClapTrap(other)で基底部分をコピー
     * - 追加メンバがあれば個別にコピー
     * - スライシング問題の理解
     */
    ScavTrap(const ScavTrap& other);
    
    /*
     * 【代入演算子】  
     * ScavTrap& operator=(const ScavTrap& other);
     * 
     * 継承での代入演算子：
     * 
     * 実装パターン：
     * ```cpp
     * ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
     *     if (this != &other) {
     *         ClapTrap::operator=(other);  // 基底部分の代入
     *         // ScavTrap固有の代入処理
     *     }
     *     return *this;
     * }
     * ```
     * 
     * 注意点：
     * - 自己代入チェック
     * - 基底クラスの代入演算子呼び出し
     * - 例外安全性の確保
     */
    ScavTrap& operator=(const ScavTrap& other);
    
    /*
     * 【デストラクタ】
     * ~ScavTrap();
     * 
     * 継承でのデストラクタの特徴：
     * 
     * 呼び出し順序（コンストラクタの逆）：
     * 1. 派生クラス（ScavTrap）のデストラクタ
     * 2. 基底クラス（ClapTrap）のデストラクタ
     * 
     * virtual指定の重要性：
     * - 多態性を使用する場合は必須
     * - 基底クラスポインタ経由の削除で正しいデストラクタ呼び出し
     * - メモリリークの防止
     * 
     * 実装例：
     * ```cpp
     * ScavTrap::~ScavTrap() {
     *     std::cout << "ScavTrap destructor called" << std::endl;
     *     // ScavTrap固有のクリーンアップ
     *     // ClapTrapのデストラクタは自動的に呼ばれる
     * }
     * ```
     */
    ~ScavTrap();
    
    /*
     * ====================================================================
     * オーバーライド関数
     * ====================================================================
     */
    
    /*
     * 【attack関数のオーバーライド】
     * void attack(const std::string& target);
     * 
     * ClapTrap::attack()との違い：
     * 
     * ClapTrap版：
     * - 一般的な攻撃メッセージ
     * - "ClapTrap <name> attacks <target>"
     * 
     * ScavTrap版：
     * - ScavTrap専用の攻撃メッセージ
     * - "ScavTrap <name> attacks <target>"
     * - より威圧的で門番らしい表現
     * 
     * オーバーライドの実装：
     * ```cpp
     * void ScavTrap::attack(const std::string& target) {
     *     if (energyPoints > 0 && hitPoints > 0) {
     *         std::cout << "ScavTrap " << name << " fiercely attacks " 
     *                   << target << ", causing " << attackDamage 
     *                   << " points of damage!" << std::endl;
     *         energyPoints--;
     *     } else {
     *         std::cout << "ScavTrap " << name << " cannot attack!" 
     *                   << std::endl;
     *     }
     * }
     * ```
     * 
     * 学習ポイント：
     * - 同じシグネチャでの関数の再定義
     * - 基底クラス版の隠蔽（hiding）
     * - virtual指定による動的バインディング
     * - protectedメンバへのアクセス
     */
    void attack(const std::string& target);
    
    /*
     * ====================================================================
     * ScavTrap固有の機能
     * ====================================================================
     */
    
    /*
     * 【Gate keeper mode機能】
     * void guardGate();
     * 
     * ScavTrap専用の特殊能力：
     * 
     * 機能の詳細：
     * - 門番モードの切り替え
     * - エネルギーポイントの消費
     * - 状態変更の通知
     * 
     * 実装例：
     * ```cpp
     * void ScavTrap::guardGate() {
     *     if (hitPoints > 0) {
     *         std::cout << "ScavTrap " << name 
     *                   << " is now in Gate keeper mode!" << std::endl;
     *         // 門番状態の設定や効果の適用
     *     } else {
     *         std::cout << "ScavTrap " << name 
     *                   << " cannot guard the gate (no hit points)!" 
     *                   << std::endl;
     *     }
     * }
     * ```
     * 
     * 設計の特徴：
     * - ScavTrapでのみ利用可能
     * - ClapTrapには存在しない機能
     * - 継承による機能拡張の例
     * - ゲーム性を高める特殊能力
     */
    void guardGate();
};

#endif

/*
 * ====================================================================
 * 継承の詳細理解
 * ====================================================================
 * 
 * 【メモリレイアウト】
 * 
 * ScavTrapオブジェクトのメモリ構造：
 * ```
 * +------------------+
 * | ClapTrap部分     |
 * | - name           |
 * | - hitPoints      |
 * | - energyPoints   |
 * | - attackDamage   |
 * +------------------+
 * | ScavTrap部分     |
 * | (追加メンバ)     |
 * +------------------+
 * ```
 * 
 * 【アクセス権限】
 * 
 * ScavTrapからのアクセス：
 * - public: attack(), takeDamage(), beRepaired() → アクセス可能
 * - protected: name, hitPoints, energyPoints, attackDamage → アクセス可能
 * - private: (存在しない) → アクセス不可
 * 
 * 【仮想関数テーブル（vtable）】
 * 
 * ClapTrapが仮想関数を持つ場合：
 * ```
 * ClapTrap vtable:
 * +------------------+
 * | attack()         | → ClapTrap::attack()
 * | takeDamage()     | → ClapTrap::takeDamage()
 * | beRepaired()     | → ClapTrap::beRepaired()
 * +------------------+
 * 
 * ScavTrap vtable:
 * +------------------+
 * | attack()         | → ScavTrap::attack()  (オーバーライド)
 * | takeDamage()     | → ClapTrap::takeDamage() (継承)
 * | beRepaired()     | → ClapTrap::beRepaired() (継承)
 * | guardGate()      | → ScavTrap::guardGate() (新規)
 * +------------------+
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ public継承の構文と意味
 * □ is-a関係の概念理解
 * □ 基底クラスと派生クラスの関係
 * □ コンストラクタチェーンの仕組み
 * □ オーバーライドによる機能の再定義
 * □ protectedアクセス修飾子の役割
 * □ 継承によるコードの再利用
 * □ Orthodox Canonical Formの継承版実装
 * □ 仮想関数の基礎概念
 * □ メモリレイアウトの理解
 * 
 * 【実習課題】
 * 1. ScavTrapに新しい能力の追加
 * 2. 複数の派生クラス作成（FragTrap等）
 * 3. 多重継承の実験
 * 4. virtual指定による動的バインディング確認
 * 5. スライシング問題の体験と対策
 */

/*
 * ====================================================================
 * よくある継承のミスと対策
 * ====================================================================
 * 
 * 【ミス1：基底クラスコンストラクタの呼び忘れ】
 * 
 * 間違い例：
 * ```cpp
 * ScavTrap::ScavTrap(const std::string& name) {
 *     // ClapTrapのコンストラクタが呼ばれない
 *     // デフォルトコンストラクタが自動で呼ばれる
 * }
 * ```
 * 
 * 正解：
 * ```cpp
 * ScavTrap::ScavTrap(const std::string& name) 
 *     : ClapTrap(name, 100, 50, 20) {
 *     // 明示的に適切なコンストラクタを呼び出し
 * }
 * ```
 * 
 * 【ミス2：デストラクタの仮想化忘れ】
 * 
 * 問題：
 * - 基底クラスポインタ経由の削除で問題発生
 * - 派生クラスのデストラクタが呼ばれない
 * - メモリリークやリソースリークの原因
 * 
 * 対策：
 * ```cpp
 * class ClapTrap {
 * public:
 *     virtual ~ClapTrap();  // 仮想デストラクタ
 * };
 * ```
 * 
 * 【ミス3：アクセス権限の誤解】
 * 
 * 間違い：
 * - privateメンバへの直接アクセス試行
 * - protected の意味を理解していない
 * 
 * 理解すべき点：
 * - private: 同じクラス内でのみアクセス可能
 * - protected: 同じクラス＋派生クラスでアクセス可能
 * - public: どこからでもアクセス可能
 * 
 * 【ミス4：スライシング問題】
 * 
 * 問題コード：
 * ```cpp
 * ScavTrap scav("Guard");
 * ClapTrap clap = scav;  // スライシング発生
 * // scavのScavTrap部分が失われる
 * ```
 * 
 * 対策：
 * - ポインタや参照を使用
 * - 仮想関数による多態性活用
 * - コピー時の注意深い設計
 */

/*
 * ====================================================================
 * 実用的な継承設計パターン
 * ====================================================================
 * 
 * 【パターン1：Template Method Pattern】
 * ```cpp
 * class ClapTrap {
 * public:
 *     void performAction() {  // テンプレートメソッド
 *         prepare();
 *         doAction();  // 派生クラスで実装
 *         cleanup();
 *     }
 * 
 * protected:
 *     virtual void doAction() = 0;  // 純粋仮想関数
 *     void prepare() { /* 共通処理 */ }
 *     void cleanup() { /* 共通処理 */ }
 * };
 * 
 * class ScavTrap : public ClapTrap {
 * protected:
 *     void doAction() override {
 *         // ScavTrap固有の処理
 *     }
 * };
 * ```
 * 
 * 【パターン2：Strategy Pattern with Inheritance】
 * ```cpp
 * class AttackStrategy {
 * public:
 *     virtual ~AttackStrategy() {}
 *     virtual void attack(const std::string& target) = 0;
 * };
 * 
 * class GuardAttack : public AttackStrategy {
 * public:
 *     void attack(const std::string& target) override {
 *         // 門番らしい攻撃
 *     }
 * };
 * 
 * class ScavTrap : public ClapTrap {
 * private:
 *     AttackStrategy* strategy;
 * 
 * public:
 *     void setAttackStrategy(AttackStrategy* newStrategy) {
 *         strategy = newStrategy;
 *     }
 * };
 * ```
 * 
 * 【パターン3：Factory Method with Inheritance】
 * ```cpp
 * class TrapFactory {
 * public:
 *     virtual ~TrapFactory() {}
 *     virtual ClapTrap* createTrap(const std::string& name) = 0;
 * };
 * 
 * class ScavTrapFactory : public TrapFactory {
 * public:
 *     ClapTrap* createTrap(const std::string& name) override {
 *         return new ScavTrap(name);
 *     }
 * };
 * ```
 */

/*
 * ====================================================================
 * C++98での継承制限と対策
 * ====================================================================
 * 
 * 【制限1：override キーワードなし】
 * 
 * C++11以降：
 * ```cpp
 * void attack(const std::string& target) override;  // エラー検出
 * ```
 * 
 * C++98対策：
 * ```cpp
 * // コメントで意図を明示
 * void attack(const std::string& target); // Override ClapTrap::attack()
 * ```
 * 
 * 【制限2：final キーワードなし】
 * 
 * C++11以降：
 * ```cpp
 * class ScavTrap final : public ClapTrap {};  // 継承禁止
 * ```
 * 
 * C++98対策：
 * ```cpp
 * // プライベートコンストラクタによる継承防止
 * class ScavTrap : public ClapTrap {
 * private:
 *     ScavTrap();  // 継承を困難にする
 * };
 * ```
 * 
 * 【制限3：deleted function なし】
 * 
 * C++11以降：
 * ```cpp
 * ScavTrap(const ScavTrap&) = delete;  // コピー禁止
 * ```
 * 
 * C++98対策：
 * ```cpp
 * private:
 *     ScavTrap(const ScavTrap&);  // 宣言のみ、実装なし
 *     ScavTrap& operator=(const ScavTrap&);
 * ```
 */