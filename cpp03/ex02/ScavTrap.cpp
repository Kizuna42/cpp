#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap " << this->_name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called" << std::endl;
    *this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    std::cout << "ScavTrap assignment operator called" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    return *this;
}

ScavTrap::~ScavTrap(void) {
    std::cout << "ScavTrap " << this->_name << " destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (this->_hitPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " is already dead and cannot attack!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " has no energy points left to attack!" << std::endl;
        return;
    }
    
    this->_energyPoints--;
    std::cout << "ScavTrap " << this->_name << " attacks " << target 
              << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate(void) {
    if (this->_hitPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " is dead and cannot enter Gate keeper mode!" << std::endl;
        return;
    }
    std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode" << std::endl;
}