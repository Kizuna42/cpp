#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), _name("default") {
    // DiamondTrap attributes: FragTrap HP + ScavTrap EP + FragTrap AD
    this->_hitPoints = 100;   // 100 from FragTrap
    this->_energyPoints = 50; // 50 from ScavTrap
    this->_attackDamage = 30; // 30 from FragTrap
    std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name) {
    // DiamondTrap attributes: FragTrap HP + ScavTrap EP + FragTrap AD
    this->_hitPoints = 100;   // 100 from FragTrap
    this->_energyPoints = 50; // 50 from ScavTrap  
    this->_attackDamage = 30; // 30 from FragTrap
    std::cout << "DiamondTrap " << this->_name << " constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other) {
    std::cout << "DiamondTrap copy constructor called" << std::endl;
    *this = other;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    std::cout << "DiamondTrap assignment operator called" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other);
        this->_name = other._name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap(void) {
    std::cout << "DiamondTrap " << this->_name << " destructor called" << std::endl;
}

void DiamondTrap::whoAmI(void) {
    if (this->_hitPoints == 0) {
        std::cout << "DiamondTrap is dead and cannot identify itself!" << std::endl;
        return;
    }
    std::cout << "DiamondTrap name: " << this->_name << std::endl;
    std::cout << "ClapTrap name: " << ClapTrap::_name << std::endl;
}

std::string DiamondTrap::getName(void) const {
    return this->_name;
}