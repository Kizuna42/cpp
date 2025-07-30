#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap " << this->_name << " constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    std::cout << "FragTrap copy constructor called" << std::endl;
    *this = other;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
    std::cout << "FragTrap assignment operator called" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    return *this;
}

FragTrap::~FragTrap(void) {
    std::cout << "FragTrap " << this->_name << " destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void) {
    if (this->_hitPoints == 0) {
        std::cout << "FragTrap " << this->_name << " is dead and cannot high five!" << std::endl;
        return;
    }
    std::cout << "FragTrap " << this->_name << " requests a high five! ✋" << std::endl;
}