#ifndef ICHARACTER_HPP
#define ICHARACTER_HPP

#include <string>

class AMateria;  // Forward declaration

class ICharacter {
public:
    virtual ~ICharacter(void) {}
    virtual const std::string& getName(void) const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};

#endif