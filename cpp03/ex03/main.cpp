#include "DiamondTrap.hpp"

int main(void) {
    std::cout << "=== DiamondTrap Multiple Inheritance Test ===" << std::endl;
    
    // Test constructor
    std::cout << "\n--- Constructor Test ---" << std::endl;
    DiamondTrap diamond("DiamondBot");
    
    // Test stats (should be combination of FragTrap HP, ScavTrap EP, FragTrap AD)
    std::cout << "\n--- DiamondTrap Stats ---" << std::endl;
    std::cout << "DiamondTrap " << diamond.getName() << ":" << std::endl;
    std::cout << "  HP: " << diamond.getHitPoints() << " (should be 100 from FragTrap)" << std::endl;
    std::cout << "  EP: " << diamond.getEnergyPoints() << " (should be 50 from ScavTrap)" << std::endl;
    std::cout << "  AD: " << diamond.getAttackDamage() << " (should be 30 from FragTrap)" << std::endl;
    
    // Test whoAmI function
    std::cout << "\n--- whoAmI Test ---" << std::endl;
    diamond.whoAmI();
    
    // Test attack (should use ScavTrap's attack)
    std::cout << "\n--- Attack Test (using ScavTrap::attack) ---" << std::endl;
    diamond.attack("Enemy");
    
    // Test inherited special abilities
    std::cout << "\n--- Inherited Special Abilities ---" << std::endl;
    diamond.guardGate();     // From ScavTrap
    diamond.highFivesGuys(); // From FragTrap
    
    // Test copy constructor
    std::cout << "\n--- Copy Constructor Test ---" << std::endl;
    DiamondTrap diamondCopy(diamond);
    diamondCopy.whoAmI();
    
    // Test assignment operator
    std::cout << "\n--- Assignment Operator Test ---" << std::endl;
    DiamondTrap diamondAssign("TempDiamond");
    diamondAssign = diamond;
    diamondAssign.whoAmI();
    
    // Test damage and repair
    std::cout << "\n--- Damage and Repair Test ---" << std::endl;
    diamond.takeDamage(50);
    diamond.beRepaired(25);
    diamond.whoAmI();  // Should still work
    
    // Test death scenario
    std::cout << "\n--- Death Test ---" << std::endl;
    diamond.takeDamage(200);  // Should kill DiamondTrap
    diamond.attack("SomeEnemy");  // Should fail
    diamond.guardGate();          // Should fail
    diamond.highFivesGuys();      // Should fail
    diamond.whoAmI();             // Should fail
    
    // Compare with regular classes for verification
    std::cout << "\n--- Comparison with Base Classes ---" << std::endl;
    ClapTrap clap("ClapBot");
    ScavTrap scav("ScavBot");
    FragTrap frag("FragBot");
    
    std::cout << "ClapTrap: HP=" << clap.getHitPoints() << ", EP=" << clap.getEnergyPoints() << ", AD=" << clap.getAttackDamage() << std::endl;
    std::cout << "ScavTrap: HP=" << scav.getHitPoints() << ", EP=" << scav.getEnergyPoints() << ", AD=" << scav.getAttackDamage() << std::endl;
    std::cout << "FragTrap: HP=" << frag.getHitPoints() << ", EP=" << frag.getEnergyPoints() << ", AD=" << frag.getAttackDamage() << std::endl;
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}