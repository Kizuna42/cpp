#include "Brain.hpp"

Brain::Brain(void) {
    std::cout << "Brain constructor called" << std::endl;
    for (int i = 0; i < IDEA_COUNT; i++) {
        this->ideas[i] = "Empty idea";
    }
}

Brain::Brain(const Brain& other) {
    std::cout << "Brain copy constructor called" << std::endl;
    *this = other;
}

Brain& Brain::operator=(const Brain& other) {
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < IDEA_COUNT; i++) {
            this->ideas[i] = other.ideas[i];
        }
    }
    return *this;
}

Brain::~Brain(void) {
    std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, const std::string& idea) {
    if (index >= 0 && index < IDEA_COUNT) {
        this->ideas[index] = idea;
    }
}

std::string Brain::getIdea(int index) const {
    if (index >= 0 && index < IDEA_COUNT) {
        return this->ideas[index];
    }
    return "Invalid index";
}

void Brain::printIdeas(int count) const {
    if (count > IDEA_COUNT) count = IDEA_COUNT;
    for (int i = 0; i < count; i++) {
        std::cout << "  Idea " << i << ": " << this->ideas[i] << std::endl;
    }
}