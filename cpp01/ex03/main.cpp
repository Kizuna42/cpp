#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void) {
    std::cout << "=== Testing HumanA (Reference Design) ===" << std::endl;
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    
    std::cout << "\n=== Testing HumanB (Pointer Design) ===" << std::endl;
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        
        std::cout << "Jim without weapon:" << std::endl;
        jim.attack();
        
        std::cout << "\nArming Jim:" << std::endl;
        jim.setWeapon(club);
        jim.attack();
        
        std::cout << "\nChanging weapon type:" << std::endl;
        club.setType("upgraded battle axe");
        jim.attack();
    }
    
    std::cout << "\n=== Design Pattern Demonstration ===" << std::endl;
    std::cout << "HumanA uses reference: always has weapon, cannot be NULL" << std::endl;
    std::cout << "HumanB uses pointer: can exist without weapon, can be armed later" << std::endl;
    
    return 0;
}