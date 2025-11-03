// test_virtual_destructor.cpp
// Ex01: virtualデストラクタの重要性を確認
#include "../ex01/Animal.hpp"
#include "../ex01/Dog.hpp"
#include <iostream>

int main() {
    std::cout << "=== Testing virtual destructor ===" << std::endl;
    std::cout << "This test demonstrates why virtual destructor is essential.\n" << std::endl;
    
    std::cout << "Creating Dog through Animal pointer:" << std::endl;
    Animal* animal = new Dog();
    
    std::cout << "\nDeleting through Animal pointer:" << std::endl;
    delete animal;  // Should call both Dog and Animal destructors
    
    std::cout << "\n=== Expected output ===" << std::endl;
    std::cout << "You should see:" << std::endl;
    std::cout << "  1. Dog destructor called" << std::endl;
    std::cout << "  2. Brain destructor called" << std::endl;
    std::cout << "  3. Animal Dog destructor called" << std::endl;
    
    std::cout << "\n=== What happens without virtual ===" << std::endl;
    std::cout << "If destructor is NOT virtual:" << std::endl;
    std::cout << "  - Only Animal destructor is called" << std::endl;
    std::cout << "  - Dog destructor is NEVER called" << std::endl;
    std::cout << "  - Brain is NEVER deleted" << std::endl;
    std::cout << "  - Result: MEMORY LEAK!" << std::endl;
    
    std::cout << "\n✅ If you saw all 3 destructor calls, virtual destructor works!" << std::endl;
    
    return 0;
}

