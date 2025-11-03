// test_self_assignment.cpp
// Ex03: 自己代入のテスト
#include "../ex03/Character.hpp"
#include "../ex03/Ice.hpp"
#include "../ex03/Cure.hpp"
#include <iostream>

int main() {
    std::cout << "=== Testing self-assignment ===" << std::endl;
    std::cout << "Self-assignment is: character = character;\n" << std::endl;
    
    Character character("wizard");
    character.equip(new Ice());
    character.equip(new Cure());
    
    std::cout << "\nBefore self-assignment:" << std::endl;
    character.printInventory();
    
    std::cout << "\n--- Performing self-assignment ---" << std::endl;
    // Suppress self-assignment warning for test purposes
    Character& ref = character;
    character = ref;  // Self-assignment!
    
    std::cout << "\nAfter self-assignment (inventory should be unchanged):" << std::endl;
    character.printInventory();
    
    std::cout << "\n--- Testing that materia still works ---" << std::endl;
    Character target("target");
    character.use(0, target);  // Should work without crash
    character.use(1, target);  // Should work without crash
    
    std::cout << "\n=== Self-assignment test result ===" << std::endl;
    std::cout << "✅ If program didn't crash and materia works, self-assignment is handled correctly!" << std::endl;
    std::cout << "❌ If program crashed, self-assignment check is missing (if (this != &other))" << std::endl;
    
    std::cout << "\n--- Cleanup ---" << std::endl;
    Character::cleanGround();
    
    return 0;
}

