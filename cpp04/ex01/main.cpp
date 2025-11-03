#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void) {
	std::cout << "=== Brain and Deep Copy Test ===" << std::endl;

	std::cout << "\n--- Creating Array of Animals ---" << std::endl;
	const int ANIMAL_COUNT = 6;
	Animal* animals[ANIMAL_COUNT];

	for (int i = 0; i < ANIMAL_COUNT / 2; i++) {
		animals[i] = new Dog();
	}
	for (int i = ANIMAL_COUNT / 2; i < ANIMAL_COUNT; i++) {
		animals[i] = new Cat();
	}

	std::cout << "\n--- Testing Polymorphic Behavior ---" << std::endl;
	for (int i = 0; i < ANIMAL_COUNT; i++) {
		std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
		animals[i]->makeSound();
	}

	std::cout << "\n--- Cleaning Up Array ---" << std::endl;
	for (int i = 0; i < ANIMAL_COUNT; i++) {
		delete animals[i];
	}

	std::cout << "\n--- Deep Copy Test with Dogs ---" << std::endl;
	Dog originalDog;
	originalDog.setIdea(0, "I love my original owner!");
	originalDog.setIdea(1, "Original dog's special thought");

	std::cout << "\nOriginal Dog ideas:" << std::endl;
	originalDog.printIdeas(3);

	std::cout << "\n--- Copy Constructor Test ---" << std::endl;
	Dog copiedDog(originalDog);

	std::cout << "\nCopied Dog ideas (should be same as original):" << std::endl;
	copiedDog.printIdeas(3);

	std::cout << "\n--- Modifying Original Dog ---" << std::endl;
	originalDog.setIdea(0, "I love my NEW owner!");
	originalDog.setIdea(1, "Modified original dog's thought");

	std::cout << "\nOriginal Dog ideas after modification:" << std::endl;
	originalDog.printIdeas(3);

	std::cout << "\nCopied Dog ideas (should remain unchanged - deep copy!):" << std::endl;
	copiedDog.printIdeas(3);

	std::cout << "\n--- Assignment Operator Test ---" << std::endl;
	Dog assignedDog;
	assignedDog.setIdea(0, "I'm a different dog");

	std::cout << "\nAssigned Dog ideas before assignment:" << std::endl;
	assignedDog.printIdeas(2);

	assignedDog = originalDog;

	std::cout << "\nAssigned Dog ideas after assignment:" << std::endl;
	assignedDog.printIdeas(3);

	assignedDog.setIdea(0, "I'm the assigned dog now!");

	std::cout << "\nOriginal Dog ideas (should be unchanged):" << std::endl;
	originalDog.printIdeas(2);

	std::cout << "\nAssigned Dog ideas (should be modified):" << std::endl;
	assignedDog.printIdeas(2);

	std::cout << "\n--- Deep Copy Test with Cats ---" << std::endl;
	Cat originalCat;
	originalCat.setIdea(0, "I hate everyone equally");
	originalCat.setIdea(1, "Especially dogs");

	Cat copiedCat(originalCat);

	std::cout << "\n--- Brain Address Verification ---" << std::endl;
	std::cout << "Original Cat brain address: " << originalCat.getBrain() << std::endl;
	std::cout << "Copied Cat brain address: " << copiedCat.getBrain() << std::endl;
	std::cout << "Same address? " << (originalCat.getBrain() == copiedCat.getBrain() ? "YES (SHALLOW COPY - BAD!)" : "NO (DEEP COPY - GOOD!)") << std::endl;

	std::cout << "\nOriginal Dog brain address: " << originalDog.getBrain() << std::endl;
	std::cout << "Copied Dog brain address: " << copiedDog.getBrain() << std::endl;
	std::cout << "Same address? " << (originalDog.getBrain() == copiedDog.getBrain() ? "YES (SHALLOW COPY - BAD!)" : "NO (DEEP COPY - GOOD!)") << std::endl;

	std::cout << "\n=== Scope-Based Deep Copy Test ===" << std::endl;
	std::cout << "This test verifies deep copy using scope (from evaluation sheet)" << std::endl;
	Dog basic;
	basic.setIdea(0, "Original idea in basic");
	basic.setIdea(1, "Another original idea");

	std::cout << "\nBefore entering scope:" << std::endl;
	basic.printIdeas(2);

	std::cout << "\n--- Entering inner scope ---" << std::endl;
	{
		Dog tmp = basic;
		std::cout << "\nCopied dog's ideas:" << std::endl;
		tmp.printIdeas(2);

		tmp.setIdea(0, "Temporary idea");
		tmp.setIdea(1, "Modified in scope");

		std::cout << "\nModified tmp's ideas:" << std::endl;
		tmp.printIdeas(2);
	}
	std::cout << "--- Exited inner scope ---" << std::endl;

	std::cout << "\nbasic's ideas after scope (should be unchanged):" << std::endl;
	basic.printIdeas(2);

	std::cout << "\n=== Virtual Destructor Test ===" << std::endl;
	std::cout << "Creating Dog through Animal pointer:" << std::endl;
	Animal* animalPtr = new Dog();

	std::cout << "\nDeleting through Animal pointer (watch destructor order):" << std::endl;
	delete animalPtr;

	std::cout << "\n--- End of Tests ---" << std::endl;

	return 0;
}
