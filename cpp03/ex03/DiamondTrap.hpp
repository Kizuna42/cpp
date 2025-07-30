#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string _name;  // Private name attribute separate from ClapTrap::_name

public:
    DiamondTrap(void);
    DiamondTrap(const std::string& name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap(void);
    
    using ScavTrap::attack;  // Use ScavTrap's attack method
    void whoAmI(void);
    
    // Override getName to return DiamondTrap's private name
    std::string getName(void) const;
};

#endif