#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
    std::cout << "HumanB " << this->_name << " created without weapon" << std::endl;
}

HumanB::~HumanB(void) {
    std::cout << "HumanB " << this->_name << " destroyed" << std::endl;
}

void HumanB::setWeapon(Weapon& weapon) {
    this->_weapon = &weapon;
    std::cout << this->_name << " is now armed with " << weapon.getType() << std::endl;
}

void HumanB::attack(void) const {
    if (this->_weapon) {
        std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
    } else {
        std::cout << this->_name << " has no weapon to attack with!" << std::endl;
    }
}