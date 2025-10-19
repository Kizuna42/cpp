#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
private:
	Brain* brain;

public:
	Cat(void);
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);
	~Cat(void);

	void makeSound(void) const;
	Brain* getBrain(void) const;
	void setIdea(int index, const std::string& idea);
	void printIdeas(int count = 5) const;
};

#endif
