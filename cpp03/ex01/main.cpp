#include "ScavTrap.hpp"

int main(void) {
    std::cout << "=== ScavTrap Inheritance Test ===" << std::endl;
    
    // Test constructors and inheritance
    std::cout << "\n--- Constructor Tests ---" << std::endl;
    ClapTrap clap("ClapBot");
    ScavTrap scav("ScavBot");
    
    // Test copy constructor and assignment
    std::cout << "\n--- Copy Constructor Test ---" << std::endl;
    ScavTrap scavCopy(scav);
    
    std::cout << "\n--- Assignment Operator Test ---" << std::endl;
    ScavTrap scavAssign("TempName");
    scavAssign = scav;
    
    // Compare stats
    std::cout << "\n--- Stats Comparison ---" << std::endl;
    std::cout << "ClapTrap " << clap.getName() << ": HP=" << clap.getHitPoints() 
              << ", EP=" << clap.getEnergyPoints() << ", AD=" << clap.getAttackDamage() << std::endl;
    std::cout << "ScavTrap " << scav.getName() << ": HP=" << scav.getHitPoints() 
              << ", EP=" << scav.getEnergyPoints() << ", AD=" << scav.getAttackDamage() << std::endl;
    
    // Test overridden attack method
    std::cout << "\n--- Attack Method Override Test ---" << std::endl;
    clap.attack("Enemy1");
    scav.attack("Enemy2");
    
    // Test special ScavTrap function
    std::cout << "\n--- ScavTrap Special Function Test ---" << std::endl;
    scav.guardGate();
    
    // Test inherited functions
    std::cout << "\n--- Inherited Function Tests ---" << std::endl;
    scav.takeDamage(30);
    scav.beRepaired(15);
    scav.takeDamage(50);
    scav.guardGate();  // Should still work
    
    // Test death scenario
    std::cout << "\n--- Death Scenario Test ---" << std::endl;
    scav.takeDamage(100);  // Should kill ScavTrap
    scav.attack("SomeEnemy");  // Should fail
    scav.guardGate();          // Should fail
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}