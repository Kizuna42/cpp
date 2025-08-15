/*
 * ====================================================================
 * CPP04 ex00: WrongAnimal - 非仮想基底クラス比較解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - 仮想関数なしの基底クラス設計理解
 * - 静的バインディングの動作メカニズム
 * - virtualありとなしの具体的な違い理解
 * - 多態性が働かない場合の問題点体験
 * - 正しい設計の重要性を対比学習で理解
 * 
 * 【重要概念】
 * - 静的バインディング（Static Binding）の限界
 * - コンパイル時関数解決の問題点
 * - スライシング問題の実際の発生
 * - 非仮想デストラクタの危険性
 * - 設計判断が実行時動作に与える影響
 */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

/*
 * ====================================================================
 * WrongAnimal クラス設計思想（意図的な問題実装）
 * ====================================================================
 * 
 * 【このクラスの存在意義】
 * 
 * 教育的対比目的：
 * - Animalクラスとの比較による学習促進
 * - virtualなしの場合の問題点を実際に体験
 * - 正しい設計の重要性を身をもって理解
 * 
 * 実際のプロジェクトでの教訓：
 * - legacy codeで見つかる古い設計パターン
 * - virtualを後から追加する際の困難さ
 * - 初期設計の重要性の実感
 * 
 * 【Animalクラスとの意図的な違い】
 * 
 * 共通点（基本構造）：
 * - 同じメンバ変数（type）
 * - 同じ基本機能（getType, makeSound）
 * - 同じOrthodox Canonical Form
 * 
 * 重要な相違点：
 * - makeSound() に virtual がない
 * - デストラクタに virtual がない
 * - 多態性が期待通りに働かない
 * 
 * 【予想される問題】
 * 
 * 1. 静的バインディング：
 *    - WrongAnimal* ptr = new WrongCat();
 *    - ptr->makeSound(); // WrongAnimal::makeSound() が呼ばれる
 * 
 * 2. デストラクタ問題：
 *    - delete ptr; // WrongAnimal::~WrongAnimal() のみ実行
 *    - WrongCat のデストラクタが呼ばれない
 * 
 * 3. スライシング問題：
 *    - WrongCat cat;
 *    - WrongAnimal animal = cat; // 派生クラス部分が失われる
 */
class WrongAnimal {
protected:
    /*
     * ====================================================================
     * 基底クラスメンバ変数（Animalと同一）
     * ====================================================================
     */
    
    /*
     * 【動物種類識別子】
     * std::string type;
     * 
     * Animalクラスと同じ設計：
     * - protectedアクセス修飾子
     * - 派生クラスからの直接アクセス許可
     * - getType()での値返却用
     * 
     * 比較学習のポイント：
     * - メンバ変数レベルでは問題なし
     * - 問題は関数の仮想性の有無にある
     * - データ構造とインターフェース設計は別問題
     */
    std::string type;

public:
    /*
     * ====================================================================
     * Orthodox Canonical Form（非仮想版）
     * ====================================================================
     */
    
    /*
     * 【デフォルトコンストラクタ】
     * WrongAnimal();
     * 
     * 基本的な初期化処理：
     * - type = "WrongAnimal" の設定
     * - デバッグ出力による動作確認
     * - 派生クラスからの呼び出し対応
     * 
     * Animalとの違い：
     * - 名前以外は基本的に同じ実装
     * - virtualの有無は実行時動作で判明
     */
    WrongAnimal();
    
    /*
     * 【コピーコンストラクタ】
     * WrongAnimal(const WrongAnimal& other);
     * 
     * 標準的なコピー処理：
     * - typeメンバの値コピー
     * - 独立したオブジェクト作成
     * - スライシング問題の発生源（重要）
     * 
     * スライシング問題の例：
     * ```cpp
     * WrongCat cat("Kitty");
     * WrongAnimal animal(cat);  // WrongCat部分が失われる
     * animal.makeSound();       // WrongAnimal::makeSound() 実行
     * ```
     */
    WrongAnimal(const WrongAnimal& other);
    
    /*
     * 【代入演算子】
     * WrongAnimal& operator=(const WrongAnimal& other);
     * 
     * 標準的な代入処理：
     * - 自己代入チェック
     * - typeメンバの代入
     * - *thisの返却
     * 
     * スライシング代入の例：
     * ```cpp
     * WrongCat cat("Kitty");
     * WrongAnimal animal;
     * animal = cat;  // WrongCat情報が失われる
     * ```
     */
    WrongAnimal& operator=(const WrongAnimal& other);
    
    /*
     * 【非仮想デストラクタ】
     * ~WrongAnimal();
     * 
     * ⚠️  virtual がない重要な問題点：
     * 
     * 多態性での削除問題：
     * ```cpp
     * WrongAnimal* animal = new WrongCat("Kitty");
     * delete animal;  // ❌ WrongAnimal::~WrongAnimal() のみ実行
     * // WrongCat::~WrongCat() が呼ばれない！
     * ```
     * 
     * 正しい実装（参考）：
     * ```cpp
     * virtual ~WrongAnimal();  // これなら安全
     * ```
     * 
     * 結果的な問題：
     * - メモリリークの可能性
     * - リソースリークの危険性
     * - 予期しない実行時エラー
     */
    ~WrongAnimal();
    
    /*
     * ====================================================================
     * 非仮想関数インターフェース
     * ====================================================================
     */
    
    /*
     * 【非仮想関数：makeSound】
     * void makeSound() const;
     * 
     * ⚠️  virtual がない最重要問題点：
     * 
     * 静的バインディングの結果：
     * ```cpp
     * WrongAnimal* animal = new WrongCat("Kitty");
     * animal->makeSound();  // ❌ WrongAnimal::makeSound() が実行される
     * // WrongCat::makeSound() ではない！
     * ```
     * 
     * なぜこうなるか：
     * - virtualがないため、コンパイル時に関数が決定
     * - ポインタの型（WrongAnimal*）で関数選択
     * - 実際のオブジェクト型（WrongCat）は無視
     * 
     * 正しい実装（参考）：
     * ```cpp
     * virtual void makeSound() const;  // これなら動的バインディング
     * ```
     * 
     * 学習のポイント：
     * - vtable が作成されない
     * - 実行時の型情報が活用されない
     * - 多態性の恩恵を受けられない
     */
    void makeSound() const;
    
    /*
     * 【型情報取得関数】
     * std::string getType() const;
     * 
     * 非仮想関数（問題なし）：
     * - 単純なメンバ変数返却
     * - 通常はvirtualにする必要なし
     * - Animalクラスとの実装一致
     * 
     * この関数での学習ポイント：
     * - 全ての関数をvirtualにする必要はない
     * - 適切な判断による使い分けが重要
     * - データアクセサは通常non-virtual
     */
    std::string getType() const;
};

#endif

/*
 * ====================================================================
 * 静的バインディングの詳細メカニズム
 * ====================================================================
 * 
 * 【vtable が作成されない理由】
 * 
 * virtualなし の場合：
 * ```
 * WrongAnimal オブジェクト:
 * +------------------+
 * | type (string)    |  ← vtableポインタなし
 * +------------------+
 * ```
 * 
 * virtualあり の場合（参考）：
 * ```
 * Animal オブジェクト:
 * +------------------+
 * | vtable ptr       |  ← vtableへのポインタ
 * | type (string)    |
 * +------------------+
 * ```
 * 
 * 【関数呼び出しの解決方法】
 * 
 * 静的バインディング（WrongAnimal）：
 * ```cpp
 * WrongAnimal* animal = new WrongCat();
 * animal->makeSound();
 * 
 * // コンパイル時決定：
 * // animal の型は WrongAnimal* 
 * // → WrongAnimal::makeSound() 呼び出し
 * ```
 * 
 * 動的バインディング（Animal）：
 * ```cpp
 * Animal* animal = new Cat();
 * animal->makeSound();
 * 
 * // 実行時決定：
 * // vtable を参照
 * // → 実際のオブジェクト型（Cat）の関数呼び出し
 * // → Cat::makeSound() 呼び出し
 * ```
 */

/*
 * ====================================================================
 * 具体的な問題例とその影響
 * ====================================================================
 * 
 * 【問題例1：期待と異なる関数実行】
 * 
 * コード例：
 * ```cpp
 * WrongAnimal* animals[] = {
 *     new WrongAnimal(),
 *     new WrongCat("Kitty"),
 *     new WrongCat("Fluffy")
 * };
 * 
 * for (int i = 0; i < 3; i++) {
 *     animals[i]->makeSound();
 * }
 * ```
 * 
 * 実際の出力：
 * ```
 * Some generic wrong animal sound!
 * Some generic wrong animal sound!  ← WrongCatのはずなのに...
 * Some generic wrong animal sound!  ← WrongCatのはずなのに...
 * ```
 * 
 * 期待していた出力：
 * ```
 * Some generic wrong animal sound!
 * Wrong Meow! Wrong Meow!
 * Wrong Meow! Wrong Meow!
 * ```
 * 
 * 【問題例2：デストラクタの不完全実行】
 * 
 * コード例：
 * ```cpp
 * WrongAnimal* animal = new WrongCat("Kitty");
 * delete animal;
 * ```
 * 
 * 実際の実行順序：
 * ```
 * WrongAnimal destructor called     ← これだけ
 * WrongAnimal entity destroyed
 * ```
 * 
 * 期待していた実行順序：
 * ```
 * WrongCat destructor called
 * WrongCat Kitty is going to sleep!
 * WrongAnimal destructor called
 * WrongAnimal entity destroyed
 * ```
 * 
 * 【問題例3：スライシング問題】
 * 
 * コード例：
 * ```cpp
 * WrongCat cat("Kitty");
 * WrongAnimal animal = cat;  // スライシング発生
 * animal.makeSound();
 * ```
 * 
 * 実際の動作：
 * - cat オブジェクトから WrongAnimal 部分のみコピー
 * - WrongCat 固有の情報は失われる
 * - animal.makeSound() は WrongAnimal::makeSound() を実行
 */

/*
 * ====================================================================
 * Animal vs WrongAnimal の比較表
 * ====================================================================
 * 
 * | 項目 | Animal | WrongAnimal | 結果 |
 * |------|--------|-------------|------|
 * | makeSound() | virtual | 非virtual | 多態性の有無 |
 * | デストラクタ | virtual | 非virtual | 安全な削除の可否 |
 * | vtable | あり | なし | 実行時型情報の有無 |
 * | バインディング | 動的 | 静的 | 関数解決タイミング |
 * | メモリオーバーヘッド | +8bytes | 0bytes | vtableポインタ分 |
 * | 実行速度 | わずかに遅い | 高速 | 間接呼び出しの有無 |
 * | 拡張性 | 高い | 低い | 派生クラス追加の容易さ |
 * | 安全性 | 高い | 低い | 実行時エラーの可能性 |
 * 
 * 【学習のまとめ】
 * 
 * WrongAnimal の意図的な問題：
 * - 高速だが柔軟性がない
 * - メモリ効率は良いが安全性に問題
 * - 初期実装は簡単だが後の拡張が困難
 * 
 * Animal の利点：
 * - わずかなオーバーヘッドで大きな柔軟性
 * - 安全で拡張可能な設計
 * - オブジェクト指向の恩恵を最大限活用
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * このヘッダーで理解すべき項目：
 * 
 * □ virtualなしの基底クラス設計の問題点
 * □ 静的バインディングと動的バインディングの違い
 * □ vtableの有無による実行時動作の変化
 * □ 非仮想デストラクタの危険性
 * □ スライシング問題の具体的発生場面
 * □ コンパイル時関数解決の限界
 * □ 多態性が働かない場合の動作
 * □ 設計判断が実行時に与える影響
 * □ パフォーマンスとデザインのトレードオフ
 * □ legacy code での問題パターン認識
 * 
 * 【実習課題】
 * 1. WrongCat実装とAnimal/Catとの比較実験
 * 2. デストラクタ問題の実際の確認
 * 3. 大量のオブジェクトでのパフォーマンス測定
 * 4. 既存のWrongAnimalをAnimalに変換する手順検討
 * 5. virtual追加時の影響範囲の調査
 */

/*
 * ====================================================================
 * よくある誤解と対策
 * ====================================================================
 * 
 * 【誤解1：「virtualは常に遅い」】
 * 
 * 実際：
 * - 現代のCPUでは間接呼び出しのペナルティは最小限
 * - 設計の柔軟性の価値の方が大きい
 * - プロファイリング結果に基づいた判断が重要
 * 
 * 【誤解2：「後からvirtualを追加すれば良い」】
 * 
 * 実際：
 * - ABIの変更により既存バイナリとの互換性破綻
 * - 大規模コードベースでの変更コストが膨大
 * - 初期設計での適切な判断が重要
 * 
 * 【誤解3：「WrongAnimalの方が常に高速」】
 * 
 * 実際：
 * - 関数呼び出し回数が少ない場合は差は微小
 * - vtableキャッシュヒット率が高い場合はほぼ同等
 * - 設計の明確性による開発効率向上の方が重要
 * 
 * 【対策】
 * 
 * 1. プロファイリングによる実測
 * 2. 設計時の十分な検討
 * 3. 教育目的以外ではvirtualを基本とする
 * 4. パフォーマンス最適化は測定後に実施
 */

/*
 * ====================================================================
 * 実世界での応用と教訓
 * ====================================================================
 * 
 * 【Legacy Systemでの実例】
 * 
 * よく見つかるパターン：
 * ```cpp
 * class BaseClass {  // 古いコード
 * public:
 *     void process();  // virtualなし
 *     ~BaseClass();    // virtualなし
 * };
 * 
 * class DerivedClass : public BaseClass {
 * public:
 *     void process();  // オーバーライドのつもり
 *     ~DerivedClass(); // リソース管理が必要
 * };
 * ```
 * 
 * 発生する問題：
 * - BaseClass* でのDerivedClassの操作が期待通りに動かない
 * - メモリリークやリソースリークが発生
 * - バグの発見が困難（実行時の予期しない動作）
 * 
 * 【リファクタリング戦略】
 * 
 * 段階的アプローチ：
 * 1. インターフェース分析と影響範囲調査
 * 2. テストカバレッジの拡充
 * 3. virtual追加による機能修正
 * 4. 段階的デプロイとモニタリング
 * 
 * 【設計原則】
 * 
 * 継承を使う場合の基本原則：
 * 1. 基底クラスのデストラクタは virtual にする
 * 2. オーバーライドされる可能性がある関数は virtual にする
 * 3. パフォーマンス最適化は測定に基づいて実施
 * 4. 教育目的の意図的な悪い例以外は避ける
 */