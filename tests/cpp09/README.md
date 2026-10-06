# CPP09 回帰テスト

リポジトリのルートで実行する。Python 3.9 以降と `c++`・`make` が必要。

```sh
python3 scripts/verify_cpp09.py
python3 scripts/verify_cpp09.py --sanitize --quick
python3 scripts/verify_cpp09.py --valgrind  # Linux、Valgrind 導入済みの場合
```

提出コードを一時ディレクトリへコピーしてビルドするため、元の実行ファイルやソースには変更を加えない。外部の Python パッケージやネットワークは不要。

- 全課題を `c++ -Wall -Wextra -Werror -std=c++98 -pedantic-errors` でビルド。ヘッダー単独・二重 include、Makefile の再リンク防止・clean・fclean・re を確認する。
- ex00 は Python `Decimal` で入力値を独立判定し、日付は `datetime`、直前のレートは `bisect` で求める。厳密な 1000 超過、微小な負数、指数表記、閏年、CRLF、不正行からの復帰、壊れた DB、コピーと再読込を検証する。
- ex01 は Python `Fraction` で 4 演算の全 1 桁組合せと、固定 seed の生成式を照合する。入力の小数は拒否し、途中計算の小数は保持する。評価指摘の 6912、結果の INT_MAX 超過、0 除算、オーバーフロー、ゼロへのアンダーフロー、コピーと失敗後の再利用も検証する。`9^11`〜`9^16` と 6912・5・−1.5 の出力値は `Decimal` で厳密に比較し、表示時の桁落ちを検出する。
- ex02 は CLI の結果を Python `sorted` と照合する。さらに一時コピーの値比較 2 箇所だけを計測し、vector と deque を別々に C++ `std::sort` と照合する。9 要素までの全順列と `{1,2,3}` の全組合せ、大量の乱数・整列済み・逆順・重複を検査し、比較回数が `Σ ceil(log₂(3k/4))` 以下であること、本体の比較カウンターが独立計測と一致すること、挿入回数が入力サイズから求めた期待値と一致することも確認する。

`--quick` は全順列と全組合せの上限を 7 要素にし、乱数による整列を 1000 回から 100 回にする。3000・3001・10000 要素の固定テストと他の検証は同じ。比較回数の計測では一時ヘッダーだけで private を公開する。本体は比較・ペア交換・挿入の回数を時間行に表示する。テスト専用の公開メソッドは追加しない。小入力 7 パターンで 3 種の回数を手計算と照合し、再ソート・片側だけのソート・入力成功／失敗・コピー・代入・自己代入でも統計の保持とリセットを確認する。

Sanitizer は ASan と UBSan を使用する。macOS では非対応の LeakSanitizer を無効にする。リーク確認には Linux の LeakSanitizer または Valgrind を使う。換算・RPN の計算は double の精度で照合し、表現範囲を越える値と非ゼロ値がゼロへ消失する演算はエラーを期待する。

`--valgrind` は正常入力・不正入力・数値範囲エラー・例外後の再利用・DB 再読込・3000 要素について、11 ケースのエラー 0 と終了時の未解放メモリ 0 バイトを検査する。Sanitizer 版とは別に実行する。

参考にした公開資料：

- [leske42/CPP09 の Ford–Johnson 解説](https://github.com/leske42/CPP09)：再帰による勝者の整列、ペア対応、Jacobsthal 順、探索範囲と比較回数の検証。
- [tigran-sargsyan-w/cpp-module-09 のテスト例](https://github.com/tigran-sargsyan-w/cpp-module-09#-testing-tips)：壊れた日付・値・式、不足する演算子、重複、大量入力。ただし公開実装の整数除算は今回の評価指摘を満たさないため採用しない。
- [qduong42/42_cpp_Module09 の RPN](https://github.com/qduong42/42_cpp_Module09/blob/master/ex01/include/RPN.hpp)：stack に浮動小数点を保持する実装例。コードはコピーせず、今回の仕様と独立した正解で検証する。
