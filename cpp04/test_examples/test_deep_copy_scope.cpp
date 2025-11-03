// test_deep_copy_scope.cpp
// Ex01: 評価項目で指定されたディープコピーのスコープテスト
#include "../ex01/Dog.hpp"
#include <iostream>

int main() {
    std::cout << "=== Scope Test (from evaluation sheet) ===" << std::endl;
    Dog basic;
    basic.setIdea(0, "Original idea");
    basic.setIdea(1, "Another original idea");
    
    std::cout << "\nBefore entering scope:" << std::endl;
    basic.printIdeas(2);
    
    std::cout << "\n--- Entering inner scope ---" << std::endl;
    {
        Dog tmp = basic;  // Copy constructor
        std::cout << "\nCopied dog's ideas:" << std::endl;
        tmp.printIdeas(2);
        
        tmp.setIdea(0, "Temporary idea");
        tmp.setIdea(1, "Modified in scope");
        
        std::cout << "\nModified tmp's ideas:" << std::endl;
        tmp.printIdeas(2);
    }
    std::cout << "--- Exited inner scope ---" << std::endl;
    
    // If shallow copy, basic would have a dangling pointer here!
    // This would crash or show garbage values
    std::cout << "\nbasic's ideas after scope (should be unchanged):" << std::endl;
    basic.printIdeas(2);
    
    std::cout << "\n✅ If you see the original ideas, deep copy works!" << std::endl;
    std::cout << "❌ If program crashes here, it was shallow copy!" << std::endl;
    
    return 0;
}

