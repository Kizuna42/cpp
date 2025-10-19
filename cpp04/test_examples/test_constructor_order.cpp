// test_constructor_order.cpp
// Ex00: コンストラクタ/デストラクタの順序確認テスト
#include "../ex00/Animal.hpp"
#include "../ex00/Dog.hpp"
#include <iostream>

int main() {
    std::cout << "=== Creating Dog ===" << std::endl;
    Dog dog;
    
    std::cout << "\n=== Exiting scope ===" << std::endl;
    return 0;
}

// 期待される出力:
// === Creating Dog ===
// Animal Dog constructor called
// Dog constructor called
//
// === Exiting scope ===
// Dog destructor called
// Animal Dog destructor called

