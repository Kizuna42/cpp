#include "Cat.hpp"

Cat::Cat(void) : AAnimal("Cat") {
    std::cout << "Cat constructor called" << std::endl;
    this->brain = new Brain();
    // Set some default ideas for cats
    this->brain->setIdea(0, "Hunt small creatures");
    this->brain->setIdea(1, "Sleep 16 hours a day");
    this->brain->setIdea(2, "Ignore humans");
    this->brain->setIdea(3, "Knock things off tables");
    this->brain->setIdea(4, "Purr when happy");
}

Cat::Cat(const Cat& other) : AAnimal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
    this->brain = new Brain(*other.brain);  // Deep copy of Brain
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &other) {
        AAnimal::operator=(other);
        delete this->brain;  // Delete existing brain
        this->brain = new Brain(*other.brain);  // Deep copy new brain
    }
    return *this;
}

Cat::~Cat(void) {
    std::cout << "Cat destructor called" << std::endl;
    delete this->brain;
}

void Cat::makeSound(void) const {
    std::cout << "Meow! Meow!" << std::endl;
}

Brain* Cat::getBrain(void) const {
    return this->brain;
}

void Cat::setIdea(int index, const std::string& idea) {
    this->brain->setIdea(index, idea);
}

void Cat::printIdeas(int count) const {
    std::cout << "Cat's ideas:" << std::endl;
    this->brain->printIdeas(count);
}