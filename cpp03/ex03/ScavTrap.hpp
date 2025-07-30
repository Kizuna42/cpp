#ifndef SCAVTRAP_HPP  
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {  // Virtual inheritance to solve diamond problem
public:
    ScavTrap(void);
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& other);
    ScavTrap& operator=(const ScavTrap& other);
    ~ScavTrap(void);
    
    void attack(const std::string& target);
    void guardGate(void);
};

#endif