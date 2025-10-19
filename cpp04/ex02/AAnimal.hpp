#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal {
protected:
	std::string type;

public:
	AAnimal(void);
	AAnimal(const std::string& type);
	AAnimal(const AAnimal& other);
	AAnimal& operator=(const AAnimal& other);
	virtual ~AAnimal(void);

	virtual void makeSound(void) const = 0;
	std::string getType(void) const;
};

#endif
