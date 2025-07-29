# コードレビューガイド - C++ Module 00

## 🎯 クイック評価チェックリスト

### レビュー前準備
```bash
# リポジトリのクローンと移動
git clone [repository_url]
cd cpp00

# プロジェクト構成の確認
ls -la  # ex00/, ex01/, ex02/, *.md ファイルが表示されるはず
```

---

## 🔊 演習00: メガホンテスト

### コンパイルテスト
```bash
cd ex00
make                    # 警告・エラーなしでコンパイルされるはず
make re                 # 再ビルド機能テスト
ls -la                  # 'megaphone'実行ファイルの存在確認
```

### 機能テスト

#### テスト1: 引数なし
```bash
./megaphone
# 期待される出力:
# * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

#### テスト2: 単一引数
```bash
./megaphone "shhhhh... I think the students are asleep..."
# 期待される出力:
# SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
```

#### テスト3: 複数引数
```bash
./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
# 期待される出力:
# DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
```

#### テスト4: エッジケース
```bash
./megaphone ""                          # 空文字列
./megaphone "123!@#"                   # 数字と記号
./megaphone "MixEd CaSe"               # 大文字小文字混在
./megaphone "àáâãäå"                   # 国際文字（結果は環境により異なる可能性）
```

### コード品質チェック
- ✅ `std::toupper`用に`#include <cctype>`を含む
- ✅ `printf`の代わりに`std::cout`を使用
- ✅ 適切な引数処理（`argc`、`argv`）
- ✅ 適切な終了コードを返す

---

## 📞 演習01: 電話帳テスト

### コンパイルテスト
```bash
cd ../ex01
make                    # 警告・エラーなしでコンパイルされるはず
ls -la                  # 'phonebook'実行ファイルの存在確認
```

### 機能テスト

#### テスト1: 基本コマンドフロー
```bash
./phonebook
# テストシーケンス:
# 1. "ADD"入力 → 連絡先フィールドのプロンプト表示
# 2. 全5フィールドに有効データ入力
# 3. "SEARCH"入力 → 連絡先テーブル表示
# 4. "0"入力 → 完全な連絡先詳細表示
# 5. "EXIT"入力 → 優雅な終了
```

#### テスト2: 入力検証
```bash
./phonebook
# 空フィールドテスト:
# 1. "ADD"入力
# 2. 名前でEnterキー（空）→ 再プロンプト表示
# 3. 有効な名前入力 → 姓への進行
# 4. 有効入力で継続
```

#### テスト3: 連絡先ストレージ制限
```bash
./phonebook
# 9件の連絡先追加で置換動作テスト:
# 1. 8件の連絡先追加（全スロット埋める）
# 2. "SEARCH"入力 → 8件の連絡先表示（インデックス0-7）
# 3. 9件目の連絡先追加 → インデックス0を置換
# 4. "SEARCH"入力 → まだ8件表示、ただしインデックス0は新連絡先
```

#### テスト4: 表示フォーマット
```bash
./phonebook
# 長い名前での切り詰めテスト:
# 1. 名前"VeryLongFirstName"（10文字超）の連絡先追加
# 2. "SEARCH"入力 → 名前列に"VeryLongFi."表示
# 3. テーブルの配置とパイプ区切りを確認
```

#### テスト5: エラーハンドリング
```bash
./phonebook
# 無効入力テスト:
# 1. "INVALID"入力 → エラーメッセージ表示、継続
# 2. 連絡先なしで"SEARCH"入力 → 優雅な処理
# 3. "SEARCH"後に無効インデックス入力 → エラーメッセージ表示
# 4. "SEARCH"後に非数値インデックス入力 → 優雅な処理
```

### コード品質チェック
- ✅ `std::stoi`未使用（C++98準拠）
- ✅ 適切なクラス分離（`Contact.hpp/cpp`、`PhoneBook.hpp/cpp`）
- ✅ パブリックアクセサー付きプライベートデータメンバー
- ✅ 静的配列ストレージ（動的割り当てなし）
- ✅ 空フィールドの入力検証

---

## 🏦 演習02: アカウントテスト

### コンパイルテスト
```bash
cd ../ex02
make                    # 警告・エラーなしでコンパイルされるはず
ls -la                  # 'account'実行ファイルの存在確認
```

### 機能テスト

#### テスト1: 出力フォーマット検証
```bash
./account > output.log
# 参考ログとの比較（タイムスタンプは異なる）:
diff -u 19920104_091532.log output.log --ignore-matching-lines="\[.*\]"
# 最小限または差分なし（タイムスタンプのみ）
```

#### テスト2: 手動出力解析
```bash
./account
# 出力フォーマットの手動確認:
# 1. アカウント作成メッセージ: [timestamp] index:X;amount:Y;created
# 2. 預金メッセージ: [timestamp] index:X;p_amount:Y;deposit:Z;amount:W;nb_deposits:N
# 3. 出金成功: [timestamp] index:X;p_amount:Y;withdrawal:Z;amount:W;nb_withdrawals:N
# 4. 出金拒否: [timestamp] index:X;p_amount:Y;withdrawal:refused
# 5. アカウント閉鎖: [timestamp] index:X;amount:Y;closed
```

#### テスト3: 数学的検証
```bash
./account
# 計算確認:
# 1. 初期合計: 42+54+957+432+1234+0+754+16576 = 20049
# 2. 預金後: 20049+5+765+564+2+87+23+9+20 = 21524
# 3. 出金後: 21524-34-657-4-76-657-7654 = 12442
# 4. カウント確認: 8アカウント、8預金、6出金（2拒否）
```

### 高度なテスト

#### メモリリークチェック（valgrind利用可能な場合）
```bash
# 必要に応じて先にファイルディスクリプタ制限を下げる
ulimit -n 1024
valgrind --leak-check=full --show-leak-kinds=all ./account
# "All heap blocks were freed -- no leaks are possible"が表示されるはず
```

#### コンパイルフラグ検証
```bash
# 厳格なC++98準拠テスト
c++ -Wall -Wextra -Werror -std=c++98 -pedantic *.cpp -o test_strict
./test_strict  # 同様に動作するはず
rm test_strict
```

---

## 🧪 演習間統合テスト

### Makefile標準
```bash
# 全Makefileテスト
for dir in ex00 ex01 ex02; do
    cd $dir
    make fclean  # 生成ファイル全削除
    make         # クリーンに再ビルド
    make clean   # オブジェクトファイルのみ削除
    make         # 必要な分のみ再ビルド（再リンクなし）
    cd ..
done
```

### C++98準拠検証
```bash
# 禁止構文チェック
grep -r "std::stoi\|auto\|nullptr\|using namespace" ex*/ || echo "✅ C++11+機能なし"
grep -r "printf\|malloc\|free\|alloc" ex*/ || echo "✅ 禁止C関数なし"
```

### コードスタイル一貫性
```bash
# インクルードガードチェック
find . -name "*.hpp" -exec grep -L "#ifndef\|#pragma once" {} \; || echo "✅ 全ヘッダーにインクルードガードあり"

# 適切なインクルードチェック
grep -r "#include" ex*/ | grep -v "iostream\|string\|iomanip\|cctype" || echo "✅ 標準ライブラリのみ使用"
```

---

## 📊 評価ルーブリック

### 演習00（25点）
- **コンパイル（5点）**: 必要フラグでコンパイル、警告なし
- **機能性（15点）**: 全テストケースで正しい動作  
- **コード品質（5点）**: クリーンなコード、適切なインクルード、禁止関数なし

### 演習01（40点）
- **コンパイル（5点）**: 必要フラグでコンパイル、警告なし
- **クラス設計（10点）**: カプセル化された適切なContact/PhoneBookクラス
- **機能性（20点）**: ADD/SEARCH/EXITコマンドが正しく動作
- **入力検証（5点）**: 空フィールドと無効入力の処理

### 演習02（35点）
- **コンパイル（5点）**: 提供ファイルでコンパイル、警告なし
- **出力フォーマット（15点）**: 参考ログと完全一致（タイムスタンプ除く）
- **静的管理（10点）**: アカウント、金額、取引の正しい追跡
- **実装品質（5点）**: クリーンなコード、適切な初期化

### 全体要件
- **C++98準拠**: C++11+機能を使用してはならない
- **メモリ管理**: メモリリークなし、Module 00では動的割り当てなし
- **エラーハンドリング**: エッジケースと無効入力の優雅な処理

---

## 🚨 注意すべき一般的な問題

### コンパイル問題
- 演習00で`#include <cctype>`が不足
- 手動文字列→整数変換の代わりに`std::stoi`使用
- コンパイル警告（`-Werror`でゼロであるべき）

### ロジック問題
- 演習01: 置換による8連絡先制限の未処理
- 演習02: 不正な静的メンバー初期化
- 入力検証やエラーハンドリングの不足

### フォーマット問題
- 演習01: 不正なテーブルフォーマットや切り詰め
- 演習02: 間違ったタイムスタンプフォーマットやログメッセージ構造

### スタイル問題  
- 禁止関数やC++11+機能の使用
- 不適切なカプセル化やクラス設計
- メモリリーク（静的割り当てでは稀）

---

## ✅ サインオフチェックリスト

- [ ] 全演習が必要フラグでコンパイル
- [ ] 全機能テストが合格
- [ ] 禁止関数や機能未使用
- [ ] C++98準拠確認済み
- [ ] 適切なメモリ管理（静的割り当てのみ）
- [ ] コード品質が標準を満たす
- [ ] ドキュメントが明確で完全

**推奨成績**: ___/100点

**追加コメント**:
_改善提案、注目すべき実装詳細、または具体的なフィードバックにこのスペースを使用してください。_

---

*このレビューガイドは、42 School C++ Module 00の全要件と一般的な実装パターンの包括的評価を保証します。*