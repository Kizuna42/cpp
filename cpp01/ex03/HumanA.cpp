#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon) {
    std::cout << "HumanA " << this->_name << " created with " << this->_weapon.getType() << std::endl;
}

HumanA::~HumanA(void) {
    std::cout << "HumanA " << this->_name << " destroyed" << std::endl;
}

void HumanA::attack(void) const {
    std::cout << this->_name << " attacks with their " << this->_weapon.getType() << std::endl;
}