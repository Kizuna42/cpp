/*
 * ====================================================================
 * CPP04 ex03: Character - マテリアシステム実装解説版
 * ====================================================================
 * 
 * 【学習目標】
 * - インターフェース実装と具象クラス設計
 * - 配列による動的オブジェクト管理
 * - ポインタ配列とオブジェクト所有権の理解
 * - ゲームシステム設計での実用的なパターン
 * - 複雑な状態管理とリソース制御
 * 
 * 【重要概念】
 * - 固定サイズ配列による効率的管理
 * - null ポインタチェックによる安全性確保
 * - インベントリシステムの実装パターン
 * - オブジェクトの所有権と責任の明確化
 * - ゲームロジックでの実用的なC++活用
 */

#include "Character.hpp"

/*
 * ====================================================================
 * コンストラクタの実装
 * ====================================================================
 */

/*
 * 【パラメータ付きコンストラクタ】
 * Character::Character(const std::string& name)
 * 
 * キャラクター固有の初期化：
 * 
 * 初期化の責任：
 * - キャラクター名の設定
 * - マテリア装備スロットの初期化（全てnull）
 * - インベントリシステムの準備
 * - デバッグ情報の出力
 * 
 * 設計判断：
 * - 4つの固定装備スロット（ゲームバランス考慮）
 * - 初期状態では何も装備していない
 * - 名前による個体識別
 */
Character::Character(const std::string& name) : name(name) {
    /*
     * 【マテリア配列の初期化】
     * 
     * for ループによる null 初期化：
     * - C++98 では配列初期化子が限定的
     * - 明示的なループによる確実な初期化
     * - 全スロットを null 状態に設定
     * - 後の装備処理での前提条件確立
     * 
     * 代替初期化方法（C++11以降）：
     * ```cpp
     * AMateria* materia[4] = {nullptr, nullptr, nullptr, nullptr};
     * ```
     * 
     * C++98 での制限：
     * - nullptr がない（NULL または 0 使用）
     * - 配列初期化子の制限
     * - ループによる明示的初期化が安全
     */
    for (int i = 0; i < 4; i++) {
        materia[i] = NULL;  // C++98 では nullptr の代わりに NULL
    }
    
    /*
     * 【キャラクター作成の記録】
     * 
     * デバッグ出力の意義：
     * - キャラクター作成の確認
     * - 名前設定の確認
     * - 初期状態の記録
     * - システム動作の透明性確保
     */
    std::cout << "Character constructor called" << std::endl;
    std::cout << "Character '" << name << "' has entered the battlefield!" << std::endl;
    std::cout << "Equipment slots initialized (0/4 equipped)" << std::endl;
}

/*
 * 【コピーコンストラクタ】
 * Character::Character(const Character& other) : name(other.name)
 * 
 * キャラクターの複製処理：
 * 
 * 複製の方針：
 * - 名前は同じ（同じキャラクターの複製）
 * - 装備マテリアは独立してコピー
 * - 新しいマテリア実体の作成
 * - 完全に独立したキャラクター生成
 */
Character::Character(const Character& other) : name(other.name) {
    /*
     * 【マテリア装備の深いコピー】
     * 
     * 各スロットでの処理：
     * - NULL チェックによる安全性確保
     * - clone() による新しいマテリア作成
     * - 独立したオブジェクトの所有
     * - 元キャラクターとの分離
     */
    for (int i = 0; i < 4; i++) {
        if (other.materia[i] != NULL) {
            /*
             * 【clone() メソッドの活用】
             * 
             * clone() による複製の利点：
             * - 実際の型に応じた適切なコピー作成
             * - 仮想関数による多態的コピー
             * - Ice/Cure 固有の状態も正確にコピー
             * - メモリ管理の責任移転
             */
            materia[i] = other.materia[i]->clone();
        } else {
            materia[i] = NULL;
        }
    }
    
    /*
     * 【コピー操作の記録】
     * 
     * デバッグ出力での確認：
     * - コピー元キャラクター情報
     * - 装備状況のコピー結果
     * - 新しいキャラクターの独立性確認
     */
    std::cout << "Character copy constructor called" << std::endl;
    std::cout << "Character '" << name << "' has been cloned with independent equipment!" << std::endl;
    
    // 装備状況の確認
    int equippedCount = 0;
    for (int i = 0; i < 4; i++) {
        if (materia[i] != NULL) {
            equippedCount++;
        }
    }
    std::cout << "Cloned character has " << equippedCount << "/4 materia equipped" << std::endl;
}

/*
 * 【代入演算子】
 * Character& Character::operator=(const Character& other)
 * 
 * キャラクター状態の更新：
 * 
 * 代入の複雑性：
 * - 既存装備の適切な削除
 * - 新しい装備の独立コピー
 * - 自己代入安全性の確保
 * - リソース管理の一貫性
 */
Character& Character::operator=(const Character& other) {
    /*
     * 【自己代入チェック】
     * 
     * 安全性確保：
     * - 同一オブジェクトへの代入検出
     * - 自己破壊の防止
     * - 不要な処理の回避
     * - パフォーマンス最適化
     */
    if (this != &other) {
        /*
         * 【既存装備の削除】
         * 
         * 各スロットでの処理：
         * - NULL チェックによる安全な削除
         * - delete による動的メモリ解放
         * - AMateria::~AMateria() の自動実行
         * - メモリリークの防止
         */
        for (int i = 0; i < 4; i++) {
            if (materia[i] != NULL) {
                delete materia[i];
                materia[i] = NULL;  // ダングリングポインタ防止
            }
        }
        
        /*
         * 【新しい装備の設定】
         * 
         * 名前とマテリアの更新：
         * - name の文字列コピー
         * - 各マテリアの clone() による深いコピー
         * - 独立したリソース所有
         * - 完全な状態置換
         */
        name = other.name;
        
        for (int i = 0; i < 4; i++) {
            if (other.materia[i] != NULL) {
                materia[i] = other.materia[i]->clone();
            } else {
                materia[i] = NULL;
            }
        }
        
        /*
         * 【代入操作の記録】
         * 
         * デバッグ出力による確認：
         * - 代入操作の実行通知
         * - 新しい状態の確認
         * - 装備更新の結果表示
         */
        std::cout << "Character assignment operator called" << std::endl;
        std::cout << "Character has been updated to '" << name << "'!" << std::endl;
        
        int equippedCount = 0;
        for (int i = 0; i < 4; i++) {
            if (materia[i] != NULL) {
                equippedCount++;
            }
        }
        std::cout << "Equipment updated: " << equippedCount << "/4 materia equipped" << std::endl;
    } else {
        /*
         * 【自己代入時の処理】
         * 
         * 安全性確保：
         * - 何もしない（効率的）
         * - デバッグ情報のみ出力
         * - 状態の一貫性維持
         */
        std::cout << "Character self-assignment detected - no changes needed" << std::endl;
    }
    
    /*
     * 【*this の返却】
     * 
     * 連鎖代入への対応：
     * - Character& としての返却
     * - 標準的な代入演算子パターン
     * - 一貫したインターフェース提供
     */
    return *this;
}

/*
 * ====================================================================
 * デストラクタの実装
 * ====================================================================
 */

/*
 * 【デストラクタ】
 * Character::~Character()
 * 
 * キャラクターの削除処理：
 * 
 * クリーンアップの責任：
 * - 装備中の全マテリアの削除
 * - 動的メモリの適切な解放
 * - リソースリークの防止
 * - デバッグ情報の出力
 */
Character::~Character() {
    /*
     * 【装備マテリアの全削除】
     * 
     * 各スロットでの削除処理：
     * - NULL チェックによる安全な削除
     * - delete による AMateria 派生クラス削除
     * - 仮想デストラクタによる適切なクリーンアップ
     * - 全リソースの確実な解放
     */
    for (int i = 0; i < 4; i++) {
        if (materia[i] != NULL) {
            delete materia[i];
            // NULL 代入は不要（オブジェクト破棄中のため）
        }
    }
    
    /*
     * 【キャラクター削除の記録】
     * 
     * デバッグ出力による確認：
     * - デストラクタ実行の確認
     * - 全装備の削除確認
     * - リソース解放の完了通知
     * - オブジェクトライフサイクルの終了記録
     */
    std::cout << "Character destructor called" << std::endl;
    std::cout << "Character '" << name << "' is leaving the battlefield..." << std::endl;
    std::cout << "All equipped materia have been safely released" << std::endl;
}

/*
 * ====================================================================
 * ICharacter インターフェース実装
 * ====================================================================
 */

/*
 * 【getName 関数】
 * const std::string& Character::getName() const
 * 
 * キャラクター名の取得：
 * 
 * 実装の特徴：
 * - const 参照による効率的な返却
 * - コピーコストの回避
 * - const correctness の実践
 * - インターフェース契約の遵守
 */
const std::string& Character::getName() const {
    return name;
}

/*
 * 【equip 関数】
 * void Character::equip(AMateria* m)
 * 
 * マテリア装備処理：
 * 
 * 装備ロジック：
 * - 空いているスロットを検索
 * - 最初の空きスロットに装備
 * - 満杯時は装備拒否
 * - NULL ポインタの安全な処理
 */
void Character::equip(AMateria* m) {
    /*
     * 【NULL ポインタチェック】
     * 
     * 安全性確保：
     * - 無効なマテリアの装備防止
     * - セグメンテーション違反の防止
     * - ユーザーへの適切なフィードバック
     * - システムの安定性確保
     */
    if (m == NULL) {
        std::cout << "Cannot equip NULL materia!" << std::endl;
        return;
    }
    
    /*
     * 【空きスロット検索と装備】
     * 
     * 装備プロセス：
     * - 4つのスロットを順次確認
     * - 最初の NULL スロットに装備
     * - 装備成功時は即座に処理終了
     * - 満杯時は最後に拒否メッセージ
     */
    for (int i = 0; i < 4; i++) {
        if (materia[i] == NULL) {
            materia[i] = m;
            std::cout << "Character '" << name << "' equipped " << m->getType() 
                      << " materia in slot " << i << std::endl;
            return;  // 装備完了、処理終了
        }
    }
    
    /*
     * 【装備満杯時の処理】
     * 
     * 満杯時の対応：
     * - 装備拒否の明確な通知
     * - マテリアの所有権は変更されない
     * - 呼び出し元での適切な処理が必要
     * - システムの一貫性維持
     */
    std::cout << "Character '" << name << "' cannot equip more materia (4/4 slots full)" << std::endl;
}

/*
 * 【unequip 関数】
 * void Character::unequip(int idx)
 * 
 * マテリア装備解除処理：
 * 
 * 解除ロジック：
 * - インデックス範囲の検証
 * - 装備状態の確認
 * - ポインタのクリア（削除はしない）
 * - 所有権の放棄
 */
void Character::unequip(int idx) {
    /*
     * 【インデックス範囲チェック】
     * 
     * 安全性確保：
     * - 配列境界外アクセスの防止
     * - 不正なスロット指定の拒否
     * - システムクラッシュの防止
     * - ユーザーエラーの適切な処理
     */
    if (idx < 0 || idx >= 4) {
        std::cout << "Invalid slot index: " << idx << " (valid range: 0-3)" << std::endl;
        return;
    }
    
    /*
     * 【装備状態の確認と解除】
     * 
     * 解除プロセス：
     * - 指定スロットの装備確認
     * - NULL の場合は既に空き
     * - 装備中の場合はポインタクリア
     * - メモリ削除は実行しない（重要）
     */
    if (materia[idx] != NULL) {
        /*
         * 【所有権の放棄】
         * 
         * 重要な設計判断：
         * - delete は実行しない
         * - 呼び出し元が削除責任を持つ
         * - 床にマテリアが落ちる概念
         * - メモリリーク防止は呼び出し元の責任
         */
        std::cout << "Character '" << name << "' unequipped " << materia[idx]->getType() 
                  << " materia from slot " << idx << std::endl;
        std::cout << "Materia has been dropped on the ground (memory management needed)" << std::endl;
        
        materia[idx] = NULL;  // ポインタクリア、削除はしない
    } else {
        std::cout << "Slot " << idx << " is already empty" << std::endl;
    }
}

/*
 * 【use 関数】
 * void Character::use(int idx, ICharacter& target)
 * 
 * マテリア使用処理：
 * 
 * 使用ロジック：
 * - スロット検証
 * - 装備確認
 * - マテリア能力の発動
 * - ターゲットへの効果適用
 */
void Character::use(int idx, ICharacter& target) {
    /*
     * 【使用条件の検証】
     * 
     * 事前条件チェック：
     * - インデックス範囲の確認
     * - 装備状態の確認
     * - 使用可能状態の確認
     * - エラー時の適切な処理
     */
    if (idx < 0 || idx >= 4) {
        std::cout << "Invalid slot index: " << idx << " (valid range: 0-3)" << std::endl;
        return;
    }
    
    if (materia[idx] == NULL) {
        std::cout << "No materia equipped in slot " << idx << std::endl;
        return;
    }
    
    /*
     * 【マテリア能力の発動】
     * 
     * 使用プロセス：
     * - AMateria::use() の多態的呼び出し
     * - Ice/Cure 固有の効果実行
     * - ターゲットへの影響適用
     * - 使用結果の記録
     */
    std::cout << "Character '" << name << "' uses " << materia[idx]->getType() 
              << " materia on " << target.getName() << std::endl;
    
    /*
     * 【仮想関数による多態的実行】
     * 
     * 多態性の活用：
     * - materia[idx] は AMateria* 型
     * - 実際は Ice* または Cure* オブジェクト
     * - virtual use() により適切な実装実行
     * - ターゲットに対する固有効果発動
     */
    materia[idx]->use(target);
}

/*
 * ====================================================================
 * 実装の総括と設計判断
 * ====================================================================
 * 
 * 【固定配列による管理の利点】
 * 
 * 配列選択の理由：
 * - ゲームバランス: 装備数制限
 * - メモリ効率: 動的配列より高速
 * - 実装簡素: 複雑な動的管理不要
 * - キャッシュ効率: 連続メモリ配置
 * 
 * 代替実装との比較：
 * ```cpp
 * std::vector<AMateria*> materia;  // 動的配列
 * std::list<AMateria*> materia;    // リンクリスト
 * std::array<AMateria*, 4> materia; // C++11 配列
 * ```
 * 
 * 【所有権管理の設計】
 * 
 * 明確な所有権ルール：
 * - equip(): Character が所有権を取得
 * - unequip(): Character が所有権を放棄
 * - destructor: Character が削除責任
 * - 呼び出し元: unequip 後の削除責任
 * 
 * 【インターフェース実装の一貫性】
 * 
 * ICharacter 契約の遵守：
 * - 全メソッドの適切な実装
 * - const correctness の徹底
 * - エラーハンドリングの統一
 * - デバッグ支援の充実
 * 
 * 【ゲームシステムとしての実用性】
 * 
 * 実用的な機能：
 * - 直感的な装備・解除システム
 * - 制限による戦略性向上
 * - 明確なフィードバック提供
 * - 拡張可能な基盤設計
 */

/*
 * ====================================================================
 * 期待される動作例
 * ====================================================================
 * 
 * 【基本的な使用例】
 * 
 * コード：
 * ```cpp
 * Character warrior("Cloud");
 * AMateria* ice = new Ice();
 * AMateria* cure = new Cure();
 * 
 * warrior.equip(ice);
 * warrior.equip(cure);
 * ```
 * 
 * 出力：
 * ```
 * Character constructor called
 * Character 'Cloud' has entered the battlefield!
 * Equipment slots initialized (0/4 equipped)
 * 
 * Ice constructor called
 * Ice materia created - ready to freeze enemies!
 * 
 * Cure constructor called  
 * Cure materia created - ready to heal allies!
 * 
 * Character 'Cloud' equipped ice materia in slot 0
 * Character 'Cloud' equipped cure materia in slot 1
 * ```
 * 
 * 【マテリア使用例】
 * 
 * コード：
 * ```cpp
 * Character target("Tifa");
 * warrior.use(1, target);  // Cure 使用
 * ```
 * 
 * 出力：
 * ```
 * Character 'Cloud' uses cure materia on Tifa
 * * heals Tifa *
 * ```
 * 
 * 【装備解除例】
 * 
 * コード：
 * ```cpp
 * warrior.unequip(0);  // Ice 解除
 * ```
 * 
 * 出力：
 * ```
 * Character 'Cloud' unequipped ice materia from slot 0
 * Materia has been dropped on the ground (memory management needed)
 * ```
 */

/*
 * ====================================================================
 * 学習確認チェックリスト
 * ====================================================================
 * 
 * この実装で確認すべき項目：
 * 
 * □ インターフェース実装の完全性
 * □ 固定配列による効率的管理
 * □ null ポインタ安全性の徹底
 * □ 所有権管理の明確な実装
 * □ 深いコピーによるオブジェクト独立性
 * □ 自己代入安全性の確保
 * □ リソース管理の一貫性
 * □ エラーハンドリングの適切性
 * □ デバッグ支援の充実
 * □ ゲームシステムとしての実用性
 * 
 * 【実習課題】
 * 1. より多くのマテリア種類の追加
 * 2. 装備制限の拡張（重複不可等）
 * 3. マテリア統計情報の追加
 * 4. より高度な所有権管理（スマートポインタ）
 * 5. パフォーマンス最適化の実装
 */

/*
 * ====================================================================
 * よくある実装ミスと対策
 * ====================================================================
 * 
 * 【ミス1：unequip での delete 実行】
 * 
 * 間違い例：
 * ```cpp
 * void Character::unequip(int idx) {
 *     if (materia[idx] != NULL) {
 *         delete materia[idx];  // ❌ 削除してはいけない
 *         materia[idx] = NULL;
 *     }
 * }
 * ```
 * 
 * 問題：
 * - 床に落ちたマテリアの概念に反する
 * - 呼び出し元が再利用できない
 * - ゲームシステムの制約に違反
 * 
 * 対策：
 * - ポインタクリアのみ実行
 * - 所有権の放棄を明確に文書化
 * - 呼び出し元での適切な管理
 * 
 * 【ミス2：配列初期化の不備】
 * 
 * 間違い例：
 * ```cpp
 * Character::Character(const std::string& name) : name(name) {
 *     // 配列初期化を忘れる
 * }
 * ```
 * 
 * 問題：
 * - 未初期化ポインタの使用
 * - セグメンテーション違反の可能性
 * - 予期しない動作
 * 
 * 対策：
 * - 明示的な NULL 初期化
 * - コンストラクタでの確実な初期化
 * - 防御的プログラミング
 * 
 * 【ミス3：インデックス範囲チェック忘れ】
 * 
 * 間違い例：
 * ```cpp
 * void Character::use(int idx, ICharacter& target) {
 *     materia[idx]->use(target);  // 範囲チェックなし
 * }
 * ```
 * 
 * 問題：
 * - 配列境界外アクセス
 * - システムクラッシュ
 * - セキュリティ脆弱性
 * 
 * 対策：
 * - 厳密な範囲チェック
 * - エラー時の適切な処理
 * - 防御的プログラミング
 */