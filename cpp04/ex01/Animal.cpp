#include "Animal.hpp"

Animal::Animal(void) : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const std::string& type) : type(type) {
    std::cout << "Animal " << this->type << " constructor called" << std::endl;
}

Animal::Animal(const Animal& other) {
    std::cout << "Animal copy constructor called" << std::endl;
    *this = other;
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "Animal assignment operator called" << std::endl;
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}

Animal::~Animal(void) {
    std::cout << "Animal " << this->type << " destructor called" << std::endl;
}

void Animal::makeSound(void) const {
    std::cout << "Animal makes a generic animal sound" << std::endl;
}

std::string Animal::getType(void) const {
    return this->type;
}