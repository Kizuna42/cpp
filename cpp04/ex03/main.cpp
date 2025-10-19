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
	source->learnMateria(new Ice());
	source->printTemplates();

	// Test full source
	source->learnMateria(new Cure());
	source->learnMateria(new Ice());
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
	wizard->equip(source->createMateria("ice"));

	std::cout << "\n--- Using Materia ---" << std::endl;
	wizard->use(0, *healer);
	wizard->use(1, *healer);
	wizard->use(2, *healer);
	wizard->use(3, *healer);
	wizard->use(4, *healer);

	std::cout << "\n--- Testing Unequip ---" << std::endl;
	wizard->unequip(1);
	wizard->printInventory();
	wizard->use(1, *healer);

	wizard->unequip(5);
	wizard->unequip(1);

	std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
	Character* wizardCopy = new Character(*wizard);
	wizardCopy->printInventory();

	// Test independence
	wizardCopy->use(0, *healer);
	wizardCopy->unequip(0);

	std::cout << "Original wizard after copy modification:" << std::endl;
	wizard->printInventory();
	wizard->use(0, *healer);

	std::cout << "\n--- Testing Assignment Operator ---" << std::endl;
	Character* assigned = new Character("Assigned");
	assigned->equip(source->createMateria("cure"));
	std::cout << "Before assignment:" << std::endl;
	assigned->printInventory();

	*assigned = *wizard;
	std::cout << "After assignment:" << std::endl;
	assigned->printInventory();

	std::cout << "\n--- Testing Ground System ---" << std::endl;
	Character::printGround();

	std::cout << "\n--- Testing Unknown Materia ---" << std::endl;
	AMateria* unknown = source->createMateria("fire");
	if (!unknown) {
		std::cout << "Correctly returned null for unknown materia" << std::endl;
	}

	std::cout << "\n--- Testing MateriaSource Copy ---" << std::endl;
	MateriaSource* sourceCopy = new MateriaSource(*source);
	sourceCopy->printTemplates();

	// Test that copies are independent
	sourceCopy->createMateria("ice");

	// Test self-assignment (from test_examples/test_self_assignment.cpp)
	std::cout << "\n=== Self-Assignment Test ===" << std::endl;
	std::cout << "Testing self-assignment safety (character = character)" << std::endl;

	Character selfTest("SelfTest");
	selfTest.equip(source->createMateria("ice"));
	selfTest.equip(source->createMateria("cure"));

	std::cout << "\nBefore self-assignment:" << std::endl;
	selfTest.printInventory();

	std::cout << "\n--- Performing self-assignment ---" << std::endl;
	// Suppress self-assignment warning for test purposes
	Character& ref = selfTest;
	selfTest = ref;  // Self-assignment!

	std::cout << "\nAfter self-assignment (inventory should be unchanged):" << std::endl;
	selfTest.printInventory();

	std::cout << "\n--- Testing that materia still works ---" << std::endl;
	Character victim("victim");
	selfTest.use(0, victim);  // Should work without crash
	selfTest.use(1, victim);  // Should work without crash

	std::cout << "\n✅ If program didn't crash and materia works, self-assignment is handled correctly!" << std::endl;
	std::cout << "❌ If program crashed, self-assignment check is missing (if (this != &other))" << std::endl;

	// Test clone method
	std::cout << "\n=== Clone Method Test ===" << std::endl;
	AMateria* iceOriginal = new Ice();
	AMateria* iceCloned = iceOriginal->clone();

	std::cout << "Original Ice address: " << iceOriginal << std::endl;
	std::cout << "Cloned Ice address: " << iceCloned << std::endl;

	if (iceOriginal == iceCloned) {
		std::cout << "❌ FAIL: clone() returned same object!" << std::endl;
	} else {
		std::cout << "✅ PASS: clone() created new object!" << std::endl;
	}

	delete iceOriginal;
	delete iceCloned;

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
