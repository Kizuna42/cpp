#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter {
private:
	std::string name;
	static const int INVENTORY_SIZE = 4;
	AMateria* inventory[INVENTORY_SIZE];

	static const int GROUND_SIZE = 100;
	static AMateria* ground[GROUND_SIZE];
	static int groundCount;

	void addToGround(AMateria* materia);

public:
	Character(void);
	Character(const std::string& name);
	Character(const Character& other);
	Character& operator=(const Character& other);
	~Character(void);

	const std::string& getName(void) const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);

	void printInventory(void) const;
	static void cleanGround(void);
	static void printGround(void);
};

#endif
