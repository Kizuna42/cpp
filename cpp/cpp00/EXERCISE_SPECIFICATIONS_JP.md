# 演習仕様書 - C++ Module 00

## 🔊 演習00: メガホン

### 要件
コマンドライン引数を大文字に変換して出力する。引数がない場合の特別なケースを処理する。

### 詳細仕様

#### 入力/出力動作
```bash
# 引数なし
$> ./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *

# 単一引数
$> ./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

# 複数引数
$> ./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
```

#### 技術要件
- **ファイル**: `megaphone.cpp`、`Makefile`
- **関数**: 禁止関数なし
- **ライブラリ**: 標準C++ライブラリのみ
- **実行ファイル**: `megaphone`という名前

#### 実装詳細
- 文字変換に`std::toupper()`を使用
- 全引数を間にスペースなしで順次処理
- 変換後に改行を出力
- 成功時は0を返す

---

## 📞 演習01: 私の素晴らしい電話帳

### 要件
`PhoneBook`と`Contact`の2つのクラスを使用したインタラクティブ電話帳プログラムを作成する。

### 詳細仕様

#### クラス設計要件

##### Contactクラス
- **フィールド**（全て必須、空フィールド不可）:
  - 名前
  - 姓  
  - ニックネーム
  - 電話番号
  - 最も暗い秘密
- **カプセル化**: パブリックアクセサー付きプライベートデータメンバー
- **検証**: 空フィールドを拒否する必要あり

##### PhoneBookクラス
- **ストレージ**: ちょうど8個の`Contact`オブジェクトの配列
- **制限**: 動的割り当て禁止
- **置換ポリシー**: 9番目の連絡先は1番目を置換、10番目は2番目を置換、など
- **検索表示**: 4列のフォーマットテーブル

#### ユーザーインターフェース要件

##### コマンド
1. **ADD**: 全連絡先フィールドの入力促進、空でない入力の検証
2. **SEARCH**: 連絡先テーブル表示 + インデックスによる詳細表示
3. **EXIT**: プログラム終了（全データ消失）

##### 検索表示フォーマット
```
     Index|First Name| Last Name|  Nickname
         0|      John|     Smith|    Johnny
         1|      Jane|       Doe|      Jany
```

**フォーマットルール**:
- 各列ちょうど10文字幅
- 右揃えテキスト
- パイプ（'|'）区切り
- 切り詰め: テキストが10文字超の場合、切り詰めて最後の文字をドット（'.'）で置換

##### 連絡先詳細表示
```
First Name: John
Last Name: Smith  
Nickname: Johnny
Phone Number: 555-1234
Darkest Secret: Afraid of spiders
```

#### 技術要件
- **ファイル**: `Makefile`、`*.cpp`、`*.{h,hpp}`
- **メモリ**: 静的割り当てのみ（`new`/`delete`なし）
- **入力**: 堅牢な入力処理に`std::getline()`を使用
- **実行ファイル**: 意味のある名前を選択（例：`phonebook`）

#### エラーハンドリング
- 無効コマンド: エラーメッセージ表示、継続
- 空フィールド: 有効入力まで再プロンプト
- 無効インデックス: エラーメッセージ表示
- EOF処理: 優雅な終了

---

## 🏦 演習02: 夢の仕事

### 要件
提供されたヘッダーファイルと実行ログに基づいて、紛失した`Account.cpp`ファイルを再構築する。

### 提供ファイル
- `Account.hpp`: 完全なクラスインターフェース（変更禁止）
- `tests.cpp`: テストプログラム（変更禁止）  
- `19920104_091532.log`: 期待される出力フォーマット

### 詳細仕様

#### クラスインターフェース解析
```cpp
class Account {
public:
    // 静的情報ゲッター
    static int getNbAccounts(void);
    static int getTotalAmount(void);
    static int getNbDeposits(void);
    static int getNbWithdrawals(void);
    static void displayAccountsInfos(void);

    // インスタンスライフサイクル
    Account(int initial_deposit);
    ~Account(void);

    // 取引メソッド
    void makeDeposit(int deposit);
    bool makeWithdrawal(int withdrawal);
    int checkAmount(void) const;
    void displayStatus(void) const;

private:
    // 静的追跡変数
    static int _nbAccounts;
    static int _totalAmount;
    static int _totalNbDeposits;
    static int _totalNbWithdrawals;

    // ユーティリティ
    static void _displayTimestamp(void);

    // インスタンス変数
    int _accountIndex;
    int _amount;
    int _nbDeposits;
    int _nbWithdrawals;

    // プライベートデフォルトコンストラクタ
    Account(void);
};
```

#### 出力フォーマット要件

##### タイムスタンプフォーマット
```
[YYYYMMDD_HHMMSS]
```

##### アカウント作成
```
[timestamp] index:X;amount:Y;created
```

##### アカウント情報表示
```
[timestamp] accounts:N;total:X;deposits:Y;withdrawals:Z
```

##### アカウント状態表示
```
[timestamp] index:X;amount:Y;deposits:Z;withdrawals:W
```

##### 預金取引
```
[timestamp] index:X;p_amount:Y;deposit:Z;amount:W;nb_deposits:N
```

##### 出金取引（成功）
```
[timestamp] index:X;p_amount:Y;withdrawal:Z;amount:W;nb_withdrawals:N
```

##### 出金取引（拒否）
```
[timestamp] index:X;p_amount:Y;withdrawal:refused
```

##### アカウント破棄
```
[timestamp] index:X;amount:Y;closed
```

#### 実装要件

##### 静的メンバー管理
- `_nbAccounts`: 作成されたアカウント総数の追跡
- `_totalAmount`: 全アカウント残高の合計
- `_totalNbDeposits`: 成功した預金の総数
- `_totalNbWithdrawals`: 成功した出金の総数

##### インスタンス管理
- `_accountIndex`: 0から始まる固有の連続インデックス
- `_amount`: 現在のアカウント残高
- `_nbDeposits`: このアカウントの預金数
- `_nbWithdrawals`: このアカウントの出金数

##### 取引ロジック
- **預金**: 常に成功、金額とカウンターを更新
- **出金**: 十分な資金をチェック、不十分なら拒否
- **静的更新**: 成功した操作でグローバルカウンターを変更

#### 技術要件
- **ファイル**: `Makefile`、`Account.cpp`、`Account.hpp`、`tests.cpp`
- **タイムスタンプ**: 現在のシステム時刻（ログファイルと異なる）
- **出力一致**: フォーマットがログと完全一致（タイムスタンプ除く）
- **デストラクタ順序**: コンパイラ/OSにより異なる可能性（許容される差異）

#### 検証基準
1. 提供された`tests.cpp`でのコンパイル成功
2. 出力フォーマットが参考ログと完全一致
3. 全アカウント操作が正しく機能
4. 静的メンバー追跡が正確
5. 適切なメモリ管理（リークなし）

---

## 🎯 共通要件（全演習）

### コンパイル標準
```bash
c++ -Wall -Wextra -Werror -std=c++98 [source_files] -o [executable]
```

### Makefile要件
- ルール: `all`、`clean`、`fclean`、`re`
- 変数: `NAME`、`SRCS`、`OBJS`、`CXX`、`CXXFLAGS`
- オブジェクトファイルが最新の場合は再リンクしない

### 禁止要素
- `printf()`と変種（`std::cout`を使用）
- `*alloc()`と`free()`（自動ストレージを使用）
- `using namespace`宣言
- `friend`キーワード
- STLコンテナとアルゴリズム（Module 08まで）
- C++11+機能

### コード品質
- 警告なしでコンパイル
- メモリリークなし
- 適切なエラーハンドリング
- 読みやすく保守可能なコード
- 一貫した命名規則

---

*これらの仕様は公式の42 School C++ Module 00課題に基づき、コミュニティ実装と照合して検証されています。*