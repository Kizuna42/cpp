#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
protected:
    std::string type;

public:
    WrongAnimal(void);
    WrongAnimal(const std::string& type);
    WrongAnimal(const WrongAnimal& other);
    WrongAnimal& operator=(const WrongAnimal& other);
    ~WrongAnimal(void);  // Non-virtual destructor (wrong!)
    
    void makeSound(void) const;  // Non-virtual function (wrong!)
    std::string getType(void) const;
};

#endif