#ifndef CAT_HPP
#define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
private:
    Brain* brain;  // Pointer to Brain object for deep copy testing

public:
    Cat(void);
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat(void);
    
    void makeSound(void) const;  // Override pure virtual function
    Brain* getBrain(void) const;
    void setIdea(int index, const std::string& idea);
    void printIdeas(int count = 5) const;
};

#endif