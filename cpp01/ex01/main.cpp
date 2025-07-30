#include "Zombie.hpp"

int main(void) {
    std::cout << "=== Creating zombie horde ===" << std::endl;
    int hordeSize = 5;
    Zombie* horde = zombieHorde(hordeSize, "HordeMember");
    
    if (!horde) {
        std::cout << "Failed to create horde" << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Horde announcement ===" << std::endl;
    for (int i = 0; i < hordeSize; i++) {
        std::cout << "Zombie #" << i << ": ";
        horde[i].announce();
    }
    
    std::cout << "\n=== Testing edge cases ===" << std::endl;
    
    std::cout << "Testing empty horde (N=0):" << std::endl;
    Zombie* emptyHorde = zombieHorde(0, "EmptyTest");
    if (!emptyHorde) {
        std::cout << "Correctly handled empty horde case" << std::endl;
    }
    
    std::cout << "\nTesting negative horde (N=-1):" << std::endl;
    Zombie* negativeHorde = zombieHorde(-1, "NegativeTest");
    if (!negativeHorde) {
        std::cout << "Correctly handled negative horde case" << std::endl;
    }
    
    std::cout << "\nTesting single zombie horde (N=1):" << std::endl;
    Zombie* singleHorde = zombieHorde(1, "Loner");
    if (singleHorde) {
        singleHorde[0].announce();
        delete[] singleHorde;
    }
    
    std::cout << "\n=== Destroying horde ===" << std::endl;
    delete[] horde;
    
    return 0;
}