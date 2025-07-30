#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

int main(void) {
    std::cout << "=== Materia System Test ===" << std::endl;
    
    // Test from subject
    std::cout << "\n--- Subject Test ---" << std::endl;
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    
    ICharacter* me = new Character("me");
    
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    ICharacter* bob = new Character("bob");
    
    me->use(0, *bob);
    me->use(1, *bob);
    
    delete bob;
    delete me;
    delete src;
    
    // Extended tests
    std::cout << "\n--- Extended Tests ---" << std::endl;
    
    std::cout << "\n--- Creating MateriaSource and Learning ---" << std::endl;
    MateriaSource* source = new MateriaSource();
    source->printTemplates();
    
    source->learnMateria(new Ice());
    source->learnMateria(new Cure());
    source->learnMateria(new Ice());  // Learn another ice
    source->printTemplates();
    
    // Test full source
    source->learnMateria(new Cure());  // This should fill the source
    source->learnMateria(new Ice());   // This should fail (full)
    source->printTemplates();
    
    std::cout << "\n--- Creating Characters ---" << std::endl;
    Character* wizard = new Character("Gandalf");
    Character* healer = new Character("Mercy");
    
    wizard->printInventory();
    
    std::cout << "\n--- Equipping Materia ---" << std::endl;
    wizard->equip(source->createMateria("ice"));
    wizard->equip(source->createMateria("cure"));
    wizard->equip(source->createMateria("ice"));
    wizard->equip(source->createMateria("cure"));
    wizard->printInventory();
    
    // Try to equip when full
    wizard->equip(source->createMateria("ice"));  // Should go to ground
    
    std::cout << "\n--- Using Materia ---" << std::endl;
    wizard->use(0, *healer);  // Ice
    wizard->use(1, *healer);  // Cure
    wizard->use(2, *healer);  // Ice
    wizard->use(3, *healer);  // Cure
    wizard->use(4, *healer);  // Invalid slot
    
    std::cout << "\n--- Testing Unequip ---" << std::endl;
    wizard->unequip(1);  // Remove cure from slot 1
    wizard->printInventory();
    wizard->use(1, *healer);  // Should fail - empty slot
    
    wizard->unequip(5);  // Invalid slot
    wizard->unequip(1);  // Already empty slot
    
    std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
    Character* wizardCopy = new Character(*wizard);
    wizardCopy->printInventory();
    
    // Test independence
    wizardCopy->use(0, *healer);  // Should work
    wizardCopy->unequip(0);       // Remove ice from copy
    
    std::cout << "Original wizard after copy modification:" << std::endl;
    wizard->printInventory();      // Should still have ice in slot 0
    wizard->use(0, *healer);       // Should still work
    
    std::cout << "\n--- Testing Assignment Operator ---" << std::endl;
    Character* assigned = new Character("Assigned");
    assigned->equip(source->createMateria("cure"));
    std::cout << "Before assignment:" << std::endl;
    assigned->printInventory();
    
    *assigned = *wizard;  // Assignment
    std::cout << "After assignment:" << std::endl;
    assigned->printInventory();
    
    std::cout << "\n--- Testing Ground System ---" << std::endl;
    Character::printGround();
    
    std::cout << "\n--- Testing Unknown Materia ---" << std::endl;
    AMateria* unknown = source->createMateria("fire");  // Should return null
    if (!unknown) {
        std::cout << "Correctly returned null for unknown materia" << std::endl;
    }
    
    std::cout << "\n--- Testing MateriaSource Copy ---" << std::endl;
    MateriaSource* sourceCopy = new MateriaSource(*source);
    sourceCopy->printTemplates();
    
    // Test that copies are independent
    sourceCopy->createMateria("ice");  // Should work
    
    std::cout << "\n--- Cleanup ---" << std::endl;
    delete wizard;
    delete healer;
    delete wizardCopy;
    delete assigned;
    delete source;
    delete sourceCopy;
    
    // Clean up ground items
    Character::cleanGround();
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}