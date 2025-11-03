// ===============================================
// Exercise 00: Megaphone - 完全解説版
// ===============================================

// ヘッダーファイルのインクルード
#include <iostream>   // std::cout, std::endl用
#include <string>     // std::string用
#include <cctype>     // std::toupper用

/*
 * main関数 - プログラムの開始地点
 * argc: コマンドライン引数の個数
 * argv: コマンドライン引数の文字列配列
 *
 * 例: ./megaphone hello world
 * argc = 3 (プログラム名 + 2つの引数)
 * argv[0] = "./megaphone"
 * argv[1] = "hello"
 * argv[2] = "world"
 */
int main(int argc, char **argv)
{
    // 引数が1つ（プログラム名のみ）の場合
    if (argc == 1)
    {
        // C++の標準出力 - std::cout
        // << 演算子で文字列を出力に送る
        // std::endl は改行 + 出力バッファのフラッシュ
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);  // プログラム正常終了
    }
    
    // 引数が2つ以上ある場合
    // i=1から開始（argv[0]はプログラム名なので除外）
    for (int i = 1; i < argc; i++)
    {
        // C++の文字列クラス - char*より安全で便利
        std::string arg = argv[i];
        
        // 文字列の各文字をループ処理
        // size_t: 配列サイズ等を表す符号なし整数型
        for (size_t j = 0; j < arg.length(); j++)
        {
            // std::toupper: 文字を大文字に変換
            // (char)でキャスト: 戻り値をchar型に明示的変換
            std::cout << (char)std::toupper(arg[j]);
        }
        // 注意: 引数間にスペースは入れない
    }

    // 全ての引数処理後に改行
    std::cout << std::endl;
    return (0);
}

/*
 * 実行例とその動作:
 * 
 * $ ./megaphone
 * 出力: * LOUD AND UNBEARABLE FEEDBACK NOISE *
 * 
 * $ ./megaphone "hello world"
 * 出力: HELLO WORLD
 * 
 * $ ./megaphone hello world
 * 出力: HELLOWORLD （スペースなし）
 * 
 * $ ./megaphone "This is" "a test"
 * 出力: THIS ISTEST
 */