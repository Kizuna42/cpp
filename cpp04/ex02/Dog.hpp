#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
private:
	Brain* brain;

public:
	Dog(void);
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	~Dog(void);

	void makeSound(void) const;
	Brain* getBrain(void) const;
	void setIdea(int index, const std::string& idea);
	void printIdeas(int count = 5) const;
};

#endif
