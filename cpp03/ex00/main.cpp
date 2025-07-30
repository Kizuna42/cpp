#include "ClapTrap.hpp"

int main(void) {
    std::cout << "=== ClapTrap Test ===" << std::endl;
    
    // Test constructors
    std::cout << "\n--- Constructor Tests ---" << std::endl;
    ClapTrap clap1("CT-001");
    ClapTrap clap2("CT-002");
    ClapTrap clap3(clap1);  // Copy constructor
    
    // Test assignment operator
    std::cout << "\n--- Assignment Operator Test ---" << std::endl;
    ClapTrap clap4("CT-004");
    clap4 = clap2;
    
    // Test attack functionality
    std::cout << "\n--- Attack Tests ---" << std::endl;
    clap1.attack("Enemy1");
    clap1.attack("Enemy2");
    clap1.attack("Enemy3");
    
    // Test damage and repair
    std::cout << "\n--- Damage and Repair Tests ---" << std::endl;
    std::cout << "Initial HP: " << clap2.getHitPoints() << std::endl;
    
    clap2.takeDamage(3);
    clap2.beRepaired(2);
    clap2.takeDamage(5);
    clap2.beRepaired(1);
    
    // Test energy depletion
    std::cout << "\n--- Energy Depletion Test ---" << std::endl;
    ClapTrap energyTest("Energy-Test");
    std::cout << "Initial Energy: " << energyTest.getEnergyPoints() << std::endl;
    
    // Use up all energy points (10 actions)
    for (int i = 0; i < 11; i++) {
        std::cout << "Action " << (i + 1) << ": ";
        if (i % 2 == 0) {
            energyTest.attack("Target");
        } else {
            energyTest.beRepaired(1);
        }
    }
    
    // Test death scenario
    std::cout << "\n--- Death Test ---" << std::endl;
    ClapTrap deathTest("Death-Test");
    deathTest.takeDamage(15);  // More than 10 HP
    deathTest.attack("Someone");  // Should fail - dead
    deathTest.beRepaired(5);     // Should fail - dead
    deathTest.takeDamage(5);     // Should show already dead message
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}