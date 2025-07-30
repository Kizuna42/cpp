#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource {
private:
    static const int MATERIA_COUNT = 4;
    AMateria* templates[MATERIA_COUNT];

public:
    MateriaSource(void);
    MateriaSource(const MateriaSource& other);
    MateriaSource& operator=(const MateriaSource& other);
    ~MateriaSource(void);
    
    void learnMateria(AMateria* m);
    AMateria* createMateria(const std::string& type);
    
    // Utility function for testing
    void printTemplates(void) const;
};

#endif