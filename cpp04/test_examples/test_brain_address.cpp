// test_brain_address.cpp
// Ex01: Brainのアドレス比較でディープコピーを確認
#include "../ex01/Dog.hpp"
#include "../ex01/Cat.hpp"
#include <iostream>

int main() {
    std::cout << "=== Brain Address Verification ===" << std::endl;
    
    Dog dog1;
    dog1.setIdea(0, "Dog1 idea");
    
    Dog dog2(dog1);  // Copy constructor
    
    std::cout << "dog1 Brain address: " << dog1.getBrain() << std::endl;
    std::cout << "dog2 Brain address: " << dog2.getBrain() << std::endl;
    
    if (dog1.getBrain() == dog2.getBrain()) {
        std::cout << "\n❌ FAIL: Shallow copy detected!" << std::endl;
        std::cout << "   Both dogs share the same Brain object." << std::endl;
        std::cout << "   This will cause double-free or use-after-free!" << std::endl;
    } else {
        std::cout << "\n✅ PASS: Deep copy confirmed!" << std::endl;
        std::cout << "   Each dog has its own Brain object." << std::endl;
    }
    
    // Verify independence
    dog2.setIdea(0, "Dog2 different idea");
    std::cout << "\nAfter modifying dog2:" << std::endl;
    std::cout << "dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;
    
    std::cout << "\n=== Assignment Operator Test ===" << std::endl;
    Cat cat1;
    cat1.setIdea(0, "Cat1 original");
    
    Cat cat2;
    cat2.setIdea(0, "Cat2 original");
    
    std::cout << "\nBefore assignment:" << std::endl;
    std::cout << "cat1 Brain address: " << cat1.getBrain() << std::endl;
    std::cout << "cat2 Brain address: " << cat2.getBrain() << std::endl;
    
    cat2 = cat1;  // Assignment operator
    
    std::cout << "\nAfter assignment:" << std::endl;
    std::cout << "cat1 Brain address: " << cat1.getBrain() << std::endl;
    std::cout << "cat2 Brain address: " << cat2.getBrain() << std::endl;
    
    if (cat1.getBrain() == cat2.getBrain()) {
        std::cout << "\n❌ FAIL: Shallow copy in assignment!" << std::endl;
    } else {
        std::cout << "\n✅ PASS: Deep copy in assignment!" << std::endl;
    }
    
    // Verify independence
    cat1.setIdea(0, "Cat1 modified");
    std::cout << "\nAfter modifying cat1:" << std::endl;
    std::cout << "cat1 idea: " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "cat2 idea (should be old cat1 idea): " << cat2.getBrain()->getIdea(0) << std::endl;
    
    return 0;
}

