#include "Character.hpp"

// Static member initialization
AMateria* Character::ground[Character::GROUND_SIZE] = {0};
int Character::groundCount = 0;

Character::Character(void) : name("unnamed") {
    std::cout << "Character default constructor called" << std::endl;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        this->inventory[i] = 0;
    }
}

Character::Character(const std::string& name) : name(name) {
    std::cout << "Character " << this->name << " constructor called" << std::endl;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        this->inventory[i] = 0;
    }
}

Character::Character(const Character& other) : name(other.name + "_copy") {
    std::cout << "Character copy constructor called" << std::endl;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (other.inventory[i]) {
            this->inventory[i] = other.inventory[i]->clone();  // Deep copy
        } else {
            this->inventory[i] = 0;
        }
    }
}

Character& Character::operator=(const Character& other) {
    std::cout << "Character assignment operator called" << std::endl;
    if (this != &other) {
        this->name = other.name + "_assigned";
        
        // Clean up existing inventory
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            if (this->inventory[i]) {
                addToGround(this->inventory[i]);
                this->inventory[i] = 0;
            }
        }
        
        // Deep copy new inventory
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            if (other.inventory[i]) {
                this->inventory[i] = other.inventory[i]->clone();
            } else {
                this->inventory[i] = 0;
            }
        }
    }
    return *this;
}

Character::~Character(void) {
    std::cout << "Character " << this->name << " destructor called" << std::endl;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (this->inventory[i]) {
            delete this->inventory[i];
        }
    }
}

const std::string& Character::getName(void) const {
    return this->name;
}

void Character::equip(AMateria* m) {
    if (!m) {
        std::cout << "Cannot equip null materia!" << std::endl;
        return;
    }
    
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (!this->inventory[i]) {
            this->inventory[i] = m;
            std::cout << this->name << " equipped " << m->getType() << " in slot " << i << std::endl;
            return;
        }
    }
    
    std::cout << this->name << "'s inventory is full! Cannot equip " << m->getType() << std::endl;
    addToGround(m);  // Add to ground if inventory is full
}

void Character::unequip(int idx) {
    if (idx < 0 || idx >= INVENTORY_SIZE) {
        std::cout << "Invalid inventory slot: " << idx << std::endl;
        return;
    }
    
    if (!this->inventory[idx]) {
        std::cout << "Slot " << idx << " is already empty!" << std::endl;
        return;
    }
    
    addToGround(this->inventory[idx]);  // Add to ground instead of deleting
    std::cout << this->name << " unequipped " << this->inventory[idx]->getType() << " from slot " << idx << std::endl;
    this->inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx >= INVENTORY_SIZE) {
        std::cout << "Invalid inventory slot: " << idx << std::endl;
        return;
    }
    
    if (!this->inventory[idx]) {
        std::cout << "No materia in slot " << idx << "!" << std::endl;
        return;
    }
    
    this->inventory[idx]->use(target);
}

void Character::printInventory(void) const {
    std::cout << this->name << "'s inventory:" << std::endl;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        std::cout << "  [" << i << "] ";
        if (this->inventory[i]) {
            std::cout << this->inventory[i]->getType();
        } else {
            std::cout << "empty";
        }
        std::cout << std::endl;
    }
}

void Character::addToGround(AMateria* materia) {
    if (groundCount < GROUND_SIZE) {
        ground[groundCount++] = materia;
        std::cout << "Added " << materia->getType() << " to ground (total: " << groundCount << ")" << std::endl;
    } else {
        std::cout << "Ground is full! Deleting " << materia->getType() << std::endl;
        delete materia;
    }
}

void Character::cleanGround(void) {
    std::cout << "Cleaning ground (" << groundCount << " items)..." << std::endl;
    for (int i = 0; i < groundCount; i++) {
        delete ground[i];
        ground[i] = 0;
    }
    groundCount = 0;
}

void Character::printGround(void) {
    std::cout << "Ground contains " << groundCount << " items:" << std::endl;
    for (int i = 0; i < groundCount; i++) {
        std::cout << "  " << i << ": " << ground[i]->getType() << std::endl;
    }
}