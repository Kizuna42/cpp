#include "Dog.hpp"

Dog::Dog(void) : AAnimal("Dog") {
    std::cout << "Dog constructor called" << std::endl;
    this->brain = new Brain();
    // Set some default ideas for dogs
    this->brain->setIdea(0, "Chase the ball!");
    this->brain->setIdea(1, "Bark at strangers");
    this->brain->setIdea(2, "Eat delicious food");
    this->brain->setIdea(3, "Sleep in the sun");
    this->brain->setIdea(4, "Play with owner");
}

Dog::Dog(const Dog& other) : AAnimal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    this->brain = new Brain(*other.brain);  // Deep copy of Brain
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
        AAnimal::operator=(other);
        delete this->brain;  // Delete existing brain
        this->brain = new Brain(*other.brain);  // Deep copy new brain
    }
    return *this;
}

Dog::~Dog(void) {
    std::cout << "Dog destructor called" << std::endl;
    delete this->brain;
}

void Dog::makeSound(void) const {
    std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain(void) const {
    return this->brain;
}

void Dog::setIdea(int index, const std::string& idea) {
    this->brain->setIdea(index, idea);
}

void Dog::printIdeas(int count) const {
    std::cout << "Dog's ideas:" << std::endl;
    this->brain->printIdeas(count);
}