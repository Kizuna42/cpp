/*
 * ====================================================================
 * CPP04 ex03: インターフェースとポリモーフィズム - ICharacterヘッダー解説版
 * ====================================================================
 * 
 * この演習では、C++における「インターフェース」設計を学習します。
 * 
 * 【学習目標】
 * - 純粋仮想関数によるインターフェース定義
 * - 抽象基底クラスの設計原則
 * - ポリモーフィズムの実用的応用
 * - 依存性逆転の原則 (DIP) の実践
 * 
 * ICharacterは「キャラクター」の振る舞いを定義する
 * 純粋なインターフェースクラスです。
 */

#ifndef ICHARACTER_HPP
#define ICHARACTER_HPP

#include <string>

/*
 * class AMateria;  // Forward declaration
 * 
 * 【前方宣言の重要性】
 * 
 * なぜ前方宣言が必要？
 * 1. ヘッダーファイルの循環参照回避
 * 2. コンパイル時間の短縮
 * 3. 依存関係の最小化
 * 
 * 【循環参照の問題】
 * ICharacter.hpp が AMateria.hpp をインクルード
 * AMateria.hpp が ICharacter.hpp をインクルード
 * → 無限ループでコンパイルエラー
 * 
 * 【前方宣言で解決】
 * ポインタや参照でのみ使用する場合、
 * 完全な型定義は不要
 * 
 * 使用可能: AMateria* m, AMateria& ref
 * 使用不可: AMateria obj, sizeof(AMateria)
 */
class AMateria;  // Forward declaration

/*
 * ====================================================================
 * ICharacter インターフェース - 純粋抽象基底クラス
 * ====================================================================
 * 
 * 【インターフェース設計の原則】
 * 
 * 1. 純粋仮想関数のみ定義
 * 2. 実装は派生クラスに委譲
 * 3. 共通の振る舞いを抽象化
 * 4. 具体的な実装に依存しない
 * 
 * 【命名規則】
 * ICharacter の "I" は Interface を表す
 * - Microsoft の命名規則から
 * - Java の命名規則でも一般的
 * - C++ では必須ではないが、明示的で分かりやすい
 * 
 * 【設計意図】
 * あらゆる「キャラクター」が持つべき
 * 最小限の機能セットを定義
 * 
 * - 名前の取得
 * - 装備の管理
 * - アイテムの使用
 * 
 * 具体的なキャラクター（戦士、魔法使い等）は
 * このインターフェースを実装
 */
class ICharacter {
public:
    /*
     * ====================================================================
     * 仮想デストラクタ - ポリモーフィズムの基本要件
     * ====================================================================
     * 
     * virtual ~ICharacter(void) {}
     * 
     * 【なぜ仮想デストラクタが必要？】
     * 
     * ポリモーフィズムでの使用例:
     * ICharacter* character = new ConcreteCharacter();
     * delete character;  // どのデストラクタが呼ばれる？
     * 
     * 非仮想デストラクタの場合:
     * ICharacter のデストラクタのみ呼ばれる
     * → ConcreteCharacter のクリーンアップが実行されない
     * → メモリリークやリソースリークの原因
     * 
     * 仮想デストラクタの場合:
     * 実際のオブジェクト型（ConcreteCharacter）の
     * デストラクタが正しく呼ばれる
     * → 適切なクリーンアップが実行される
     * 
     * 【インライン実装】
     * virtual ~ICharacter(void) {}
     * 
     * 空の実装をヘッダーに記述:
     * - インターフェースなので特別な処理は不要
     * - 派生クラスで必要に応じてオーバーライド
     * - コンパイラによるインライン展開の可能性
     * 
     * 【C++の重要原則】
     * 「基底クラスのデストラクタは必ず virtual にする」
     * ポリモーフィズムを使用する場合の鉄則
     */
    virtual ~ICharacter(void) {}
    
    /*
     * ====================================================================
     * 純粋仮想関数群 - インターフェースの定義
     * ====================================================================
     * 
     * = 0 の意味:
     * - 純粋仮想関数 (Pure Virtual Function)
     * - このクラスでは実装を提供しない
     * - 派生クラスで必ず実装が必要
     * - このクラスはインスタンス化不可能（抽象クラス）
     */
    
    /*
     * virtual const std::string& getName(void) const = 0;
     * 
     * 【名前取得インターフェース】
     * 
     * 戻り値型: const std::string&
     * - 参照返しで効率化
     * - const で変更を防止
     * - 文字列のコピーを避ける
     * 
     * const 修飾:
     * - このメソッドはオブジェクトを変更しない
     * - const ICharacter からも呼び出し可能
     * - 読み取り専用操作であることを明示
     * 
     * 【設計判断】
     * なぜ名前の変更メソッド（setName）がない？
     * - キャラクターの名前は通常不変
     * - コンストラクタで設定し、以後変更しない
     * - より安全で予測可能な設計
     * 
     * 【使用例】
     * void printCharacterInfo(const ICharacter& character) {
     *     std::cout << "Character: " << character.getName() << std::endl;
     * }
     */
    virtual const std::string& getName(void) const = 0;
    
    /*
     * virtual void equip(AMateria* m) = 0;
     * 
     * 【装備インターフェース】
     * 
     * パラメータ: AMateria* m
     * - ポインタ渡しで所有権の移転を表現
     * - nullptr チェックが実装側で必要
     * - 動的多態性を活用
     * 
     * 【所有権の設計】
     * このメソッド呼び出し後:
     * - キャラクターが AMateria の所有権を取得
     * - 呼び出し元は delete してはいけない
     * - キャラクターが責任を持って管理
     * 
     * 【実装側での考慮事項】
     * - インベントリの空きスロット確認
     * - 既存装備との重複チェック
     * - 装備失敗時の処理（nullptr設定等）
     * 
     * 【インターフェースレベルでの抽象化】
     * - 具体的な装備制限は実装クラスに依存
     * - 4個制限、10個制限等は派生クラスで決定
     * - 柔軟な実装を可能にする設計
     */
    virtual void equip(AMateria* m) = 0;
    
    /*
     * virtual void unequip(int idx) = 0;
     * 
     * 【装備解除インターフェース】
     * 
     * パラメータ: int idx
     * - インデックス指定での装備解除
     * - 0-based インデックスを想定
     * - 無効なインデックスの処理は実装側で決定
     * 
     * 【重要な設計決定】
     * unequip は delete しない！
     * - AMateria* を無効化するだけ
     * - メモリ解放は別途管理が必要
     * - メモリリーク防止は実装側の責任
     * 
     * 【なぜ delete しないのか？】
     * 1. 装備を他のキャラクターに渡す可能性
     * 2. 一時的な装備解除の可能性
     * 3. 装備の再利用の可能性
     * 4. 所有権管理の複雑さ回避
     * 
     * 【実装例での処理フロー】
     * void ConcreteCharacter::unequip(int idx) {
     *     if (idx >= 0 && idx < 4 && inventory[idx]) {
     *         // どこかに保存（例：地面に落とす）
     *         droppedItems.push_back(inventory[idx]);
     *         inventory[idx] = nullptr;  // スロットを空にする
     *     }
     * }
     */
    virtual void unequip(int idx) = 0;
    
    /*
     * virtual void use(int idx, ICharacter& target) = 0;
     * 
     * 【アイテム使用インターフェース】
     * 
     * パラメータ1: int idx
     * - 使用するアイテムのスロット番号
     * - 装備済みアイテムからの選択
     * 
     * パラメータ2: ICharacter& target
     * - 使用対象のキャラクター
     * - 参照渡しで non-null を保証
     * - 自分自身も対象にできる（回復魔法等）
     * 
     * 【インターフェースの抽象度】
     * - 具体的な効果は AMateria::use に委譲
     * - キャラクターは「使用の実行」を担当
     * - アイテムは「効果の実装」を担当
     * - 責任の明確な分離
     * 
     * 【使用例】
     * character1.use(0, character2);  // スロット0のアイテムをcharacter2に使用
     * character1.use(1, character1);  // スロット1のアイテムを自分に使用
     * 
     * 【エラーハンドリング（実装側）】
     * - 無効なインデックス
     * - 空のスロット
     * - 使用不可能なアイテム
     * これらの処理は実装クラスで決定
     */
    virtual void use(int idx, ICharacter& target) = 0;
};

/*
 * ====================================================================
 * 学習のポイント
 * ====================================================================
 * 
 * 【このヘッダーから学ぶべきこと】
 * 
 * 1. インターフェース設計の原則
 *    - 純粋仮想関数による抽象化
 *    - 最小限の機能セットの定義
 *    - 実装の詳細を隠蔽
 * 
 * 2. ポリモーフィズムの基盤
 *    - 仮想デストラクタの重要性
 *    - 動的束縛の実現
 *    - 型安全性の確保
 * 
 * 3. 依存関係の管理
 *    - 前方宣言の効果的使用
 *    - 循環参照の回避
 *    - コンパイル時間の最適化
 * 
 * 4. 所有権とリソース管理
 *    - ポインタによる所有権移転
 *    - メモリ管理の責任分担
 *    - リソースリークの防止
 * 
 * 【次のステップ】
 * - TUTORIAL_AMateria.hpp でのMateria抽象クラス学習
 * - 具体的な実装クラスの設計
 * - ポリモーフィズムの実用例確認
 */

#endif

/*
 * ====================================================================
 * インターフェース vs 抽象クラス
 * ====================================================================
 * 
 * 【純粋インターフェース（ICharacter）】
 * - すべてのメソッドが純粋仮想関数
 * - データメンバを持たない（原則）
 * - 振る舞いのみを定義
 * - 多重継承に適している
 * 
 * 【抽象クラス（AMateria）】
 * - 一部のメソッドが純粋仮想関数
 * - 具象メソッドとデータメンバを持つ
 * - 共通実装を提供
 * - 単一継承が一般的
 * 
 * 【C++でのインターフェース実現】
 * 言語レベルでの interface キーワードなし（Java/C#と異なる）
 * 純粋仮想関数のみのクラスで代用
 * 
 * 【設計での使い分け】
 * インターフェース: 契約の定義
 * 抽象クラス: 部分的な実装提供
 * 
 * ICharacter: 「キャラクターとは何ができる存在か」
 * AMateria: 「マテリアの共通属性と個別実装」
 */

/*
 * ====================================================================
 * SOLID原則との関係
 * ====================================================================
 * 
 * 【依存性逆転の原則 (DIP)】
 * - 高レベルモジュールは低レベルモジュールに依存すべきでない
 * - 両方とも抽象に依存すべき
 * 
 * 適用例:
 * class Game {
 *     void battle(ICharacter& attacker, ICharacter& defender) {
 *         // 具体的なキャラクタークラスに依存しない
 *         attacker.use(0, defender);
 *     }
 * };
 * 
 * 【インターフェース分離の原則 (ISP)】
 * - クライアントは不要なインターフェースに依存すべきでない
 * 
 * ICharacter は最小限の機能のみ定義
 * 戦闘専用、魔法専用等の機能は別インターフェースで定義
 * 
 * 【開閉原則 (OCP)】
 * - 拡張に対して開き、修正に対して閉じる
 * 
 * 新しいキャラクタータイプを追加:
 * ICharacter を実装するだけ
 * 既存コードの修正不要
 */

/*
 * ====================================================================
 * 実用的な拡張例
 * ====================================================================
 * 
 * 【より詳細なインターフェース】
 * 
 * class ICharacter {
 * public:
 *     // 基本情報
 *     virtual const std::string& getName() const = 0;
 *     virtual int getLevel() const = 0;
 *     virtual int getHP() const = 0;
 *     virtual int getMP() const = 0;
 *     
 *     // 装備管理
 *     virtual void equip(AMateria* m) = 0;
 *     virtual void unequip(int idx) = 0;
 *     virtual AMateria* getEquipped(int idx) const = 0;
 *     
 *     // 行動
 *     virtual void use(int idx, ICharacter& target) = 0;
 *     virtual void attack(ICharacter& target) = 0;
 *     virtual void defend() = 0;
 *     
 *     // 状態変更
 *     virtual void takeDamage(int amount) = 0;
 *     virtual void heal(int amount) = 0;
 *     virtual bool isAlive() const = 0;
 * };
 * 
 * 【特化インターフェース】
 * 
 * class ICombatant : public ICharacter {
 * public:
 *     virtual void attack(ICharacter& target) = 0;
 *     virtual void defend() = 0;
 *     virtual int getAttackPower() const = 0;
 *     virtual int getDefensePower() const = 0;
 * };
 * 
 * class IMagicUser : public ICharacter {
 * public:
 *     virtual void castSpell(int spellId, ICharacter& target) = 0;
 *     virtual int getMagicPower() const = 0;
 *     virtual bool canCastSpell(int spellId) const = 0;
 * };
 * 
 * 【複数インターフェースの実装】
 * 
 * class Wizard : public ICombatant, public IMagicUser {
 *     // 戦闘とマジック両方の機能を実装
 * };
 * 
 * このような設計により、柔軟で拡張可能な
 * ゲームシステムを構築できる
 */