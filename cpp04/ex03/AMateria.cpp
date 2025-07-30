#include "AMateria.hpp"

AMateria::AMateria(void) : type("unknown") {
    std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(const std::string& type) : type(type) {
    std::cout << "AMateria " << this->type << " constructor called" << std::endl;
}

AMateria::AMateria(const AMateria& other) : type(other.type) {
    std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other) {
    std::cout << "AMateria assignment operator called" << std::endl;
    if (this != &other) {
        // Note: type should not be copied in assignment (as per subject)
        // this->type = other.type;
    }
    return *this;
}

AMateria::~AMateria(void) {
    std::cout << "AMateria " << this->type << " destructor called" << std::endl;
}

const std::string& AMateria::getType(void) const {
    return this->type;
}