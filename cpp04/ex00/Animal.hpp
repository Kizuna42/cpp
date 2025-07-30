#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
protected:
    std::string type;

public:
    Animal(void);
    Animal(const std::string& type);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal(void);  // Virtual destructor for proper polymorphism
    
    virtual void makeSound(void) const;  // Virtual function for polymorphism
    std::string getType(void) const;
};

#endif