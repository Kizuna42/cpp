#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void) {
	std::cout << "=== Animal Polymorphism Test ===" << std::endl;

	// Test correct polymorphism with virtual functions
	std::cout << "\n--- Correct Polymorphism (Virtual Functions) ---" << std::endl;

	const Animal* meta = new Animal();
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << "\nTesting polymorphic behavior:" << std::endl;
	std::cout << "Animal type: " << meta->getType() << std::endl;
	meta->makeSound();

	std::cout << "\nDog type: " << dog->getType() << std::endl;
	dog->makeSound();

	std::cout << "\nCat type: " << cat->getType() << std::endl;
	cat->makeSound();

	// Clean up - virtual destructors ensure proper cleanup
	std::cout << "\nDeleting animals (virtual destructors):" << std::endl;
	delete meta;
	delete dog;
	delete cat;

	// Test wrong implementation (non-virtual functions)
	std::cout << "\n--- Wrong Implementation (Non-Virtual Functions) ---" << std::endl;

	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();

	std::cout << "\nTesting non-polymorphic behavior:" << std::endl;
	std::cout << "WrongAnimal type: " << wrongMeta->getType() << std::endl;
	wrongMeta->makeSound();

	std::cout << "\nWrongCat type: " << wrongCat->getType() << std::endl;
	wrongCat->makeSound();

	// Clean up - non-virtual destructors (problematic)
	std::cout << "\nDeleting wrong animals (non-virtual destructors):" << std::endl;
	delete wrongMeta;
	delete wrongCat;

	// Direct instantiation tests
	std::cout << "\n--- Direct Instantiation Tests ---" << std::endl;
	Dog directDog;
	Cat directCat;

	std::cout << "\nDirect Dog:" << std::endl;
	directDog.makeSound();

	std::cout << "\nDirect Cat:" << std::endl;
	directCat.makeSound();

	// Array of Animal pointers
	std::cout << "\n--- Array of Animal Pointers ---" << std::endl;
	const Animal* animals[4] = {
		new Animal(),
		new Dog(),
		new Cat(),
		new Dog()
	};

	for (int i = 0; i < 4; i++) {
		std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
		animals[i]->makeSound();
	}

	std::cout << "\nCleaning up array:" << std::endl;
	for (int i = 0; i < 4; i++) {
		delete animals[i];
	}

	std::cout << "\n=== Constructor/Destructor Order Test ===" << std::endl;
	std::cout << "Creating Dog in local scope..." << std::endl;
	{
		Dog scopedDog;
		std::cout << "Dog created. Exiting scope..." << std::endl;
	}
	std::cout << "Scope exited." << std::endl;

	std::cout << "\n--- End of Tests ---" << std::endl;

	return 0;
}
