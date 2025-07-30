#ifndef IMATERIASOURCE_HPP
#define IMATERIASOURCE_HPP

#include <string>

class AMateria;  // Forward declaration

class IMateriaSource {
public:
    virtual ~IMateriaSource(void) {}
    virtual void learnMateria(AMateria* m) = 0;
    virtual AMateria* createMateria(const std::string& type) = 0;
};

#endif