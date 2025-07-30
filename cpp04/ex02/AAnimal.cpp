#include "AAnimal.hpp"

AAnimal::AAnimal(void) : type("AAnimal") {
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(const std::string& type) : type(type) {
    std::cout << "AAnimal " << this->type << " constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) {
    std::cout << "AAnimal copy constructor called" << std::endl;
    *this = other;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
    std::cout << "AAnimal assignment operator called" << std::endl;
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}

AAnimal::~AAnimal(void) {
    std::cout << "AAnimal " << this->type << " destructor called" << std::endl;
}

std::string AAnimal::getType(void) const {
    return this->type;
}