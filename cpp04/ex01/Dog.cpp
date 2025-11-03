#include "Dog.hpp"

Dog::Dog(void) : Animal("Dog") {
	std::cout << "Dog constructor called" << std::endl;
	this->brain = new Brain();
	this->brain->setIdea(0, "Chase the ball!");
	this->brain->setIdea(1, "Bark at strangers");
	this->brain->setIdea(2, "Eat delicious food");
	this->brain->setIdea(3, "Sleep in the sun");
	this->brain->setIdea(4, "Play with owner");
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog copy constructor called" << std::endl;
	this->brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
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
