#include "Cat.hpp"

Cat::Cat(void) : Animal("Cat") {
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
    *this = other;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Cat::~Cat(void) {
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const {
    std::cout << "Meow! Meow!" << std::endl;
}