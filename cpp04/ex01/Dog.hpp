#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
private:
    Brain* brain;  // Pointer to Brain object for deep copy testing

public:
    Dog(void);
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog(void);
    
    void makeSound(void) const;  // Override virtual function
    Brain* getBrain(void) const;
    void setIdea(int index, const std::string& idea);
    void printIdeas(int count = 5) const;
};

#endif