#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void) {
    std::cout << "=== Multi-Class Inheritance Test ===" << std::endl;
    
    // Test all three classes
    std::cout << "\n--- Constructor Tests ---" << std::endl;
    ClapTrap clap("ClapBot");
    ScavTrap scav("ScavBot");
    FragTrap frag("FragBot");
    
    // Compare all stats
    std::cout << "\n--- Stats Comparison ---" << std::endl;
    std::cout << "ClapTrap " << clap.getName() << ": HP=" << clap.getHitPoints() 
              << ", EP=" << clap.getEnergyPoints() << ", AD=" << clap.getAttackDamage() << std::endl;
    std::cout << "ScavTrap " << scav.getName() << ": HP=" << scav.getHitPoints() 
              << ", EP=" << scav.getEnergyPoints() << ", AD=" << scav.getAttackDamage() << std::endl;
    std::cout << "FragTrap " << frag.getName() << ": HP=" << frag.getHitPoints() 
              << ", EP=" << frag.getEnergyPoints() << ", AD=" << frag.getAttackDamage() << std::endl;
    
    // Test all attack methods
    std::cout << "\n--- Attack Method Tests ---" << std::endl;
    clap.attack("Enemy1");  // ClapTrap attack
    scav.attack("Enemy2");  // ScavTrap overridden attack
    frag.attack("Enemy3");  // FragTrap inherited ClapTrap attack
    
    // Test special abilities
    std::cout << "\n--- Special Ability Tests ---" << std::endl;
    scav.guardGate();
    frag.highFivesGuys();
    
    // Test copy constructor for FragTrap
    std::cout << "\n--- FragTrap Copy Constructor Test ---" << std::endl;
    FragTrap fragCopy(frag);
    fragCopy.highFivesGuys();
    
    // Test assignment operator for FragTrap
    std::cout << "\n--- FragTrap Assignment Operator Test ---" << std::endl;
    FragTrap fragAssign("TempFrag");
    fragAssign = frag;
    fragAssign.highFivesGuys();
    
    // Test damage scenarios
    std::cout << "\n--- Damage and Repair Tests ---" << std::endl;
    frag.takeDamage(40);
    frag.beRepaired(20);
    frag.highFivesGuys();  // Should still work
    
    // Test death scenario for FragTrap
    std::cout << "\n--- FragTrap Death Test ---" << std::endl;
    frag.takeDamage(150);  // Should kill FragTrap
    frag.attack("SomeEnemy");    // Should fail
    frag.highFivesGuys();        // Should fail
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}