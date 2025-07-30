#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

// Abstract Animal class (cannot be instantiated)
class AAnimal {
protected:
    std::string type;

public:
    AAnimal(void);
    AAnimal(const std::string& type);
    AAnimal(const AAnimal& other);
    AAnimal& operator=(const AAnimal& other);
    virtual ~AAnimal(void);  // Virtual destructor for proper polymorphism
    
    virtual void makeSound(void) const = 0;  // Pure virtual function - makes class abstract!
    std::string getType(void) const;
};

#endif