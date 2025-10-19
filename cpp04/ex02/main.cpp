#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void) {
	std::cout << "=== Abstract Animal Class Test ===" << std::endl;

	// This line should cause compilation error - AAnimal is abstract!
	// Uncomment to test:
	// AAnimal test;  // ERROR: Cannot instantiate abstract class!

	std::cout << "\n--- Creating Concrete Animals ---" << std::endl;

	// These work because Dog and Cat implement the pure virtual function
	const AAnimal* dog = new Dog();
	const AAnimal* cat = new Cat();

	std::cout << "\n--- Testing Abstract Polymorphism ---" << std::endl;
	std::cout << "Dog type: " << dog->getType() << ", sound: ";
	dog->makeSound();

	std::cout << "Cat type: " << cat->getType() << ", sound: ";
	cat->makeSound();

	// Test array creation with abstract base class
	std::cout << "\n--- Creating Array of Abstract Animals ---" << std::endl;
	const int ANIMAL_COUNT = 6;
	AAnimal* animals[ANIMAL_COUNT];

	// Fill half with Dogs, half with Cats
	for (int i = 0; i < ANIMAL_COUNT / 2; i++) {
		animals[i] = new Dog();
	}
	for (int i = ANIMAL_COUNT / 2; i < ANIMAL_COUNT; i++) {
		animals[i] = new Cat();
	}

	// Test polymorphic behavior with abstract base class
	std::cout << "\n--- Testing Polymorphic Behavior ---" << std::endl;
	for (int i = 0; i < ANIMAL_COUNT; i++) {
		std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
		animals[i]->makeSound();
	}

	// Test deep copy with concrete classes
	std::cout << "\n--- Deep Copy Test (Concrete Classes) ---" << std::endl;
	Dog originalDog;
	originalDog.setIdea(0, "I'm the original abstract dog!");

	Dog copiedDog(originalDog);

	std::cout << "\nOriginal Dog ideas:" << std::endl;
	originalDog.printIdeas(2);

	std::cout << "\nCopied Dog ideas:" << std::endl;
	copiedDog.printIdeas(2);

	// Modify original to test independence
	originalDog.setIdea(0, "I've been modified!");

	std::cout << "\nAfter modification:" << std::endl;
	std::cout << "Original Dog ideas:" << std::endl;
	originalDog.printIdeas(1);

	std::cout << "Copied Dog ideas (should be unchanged):" << std::endl;
	copiedDog.printIdeas(1);

	// Clean up single instances
	std::cout << "\n--- Cleaning Up Single Instances ---" << std::endl;
	delete dog;
	delete cat;

	// Clean up array
	std::cout << "\n--- Cleaning Up Array ---" << std::endl;
	for (int i = 0; i < ANIMAL_COUNT; i++) {
		delete animals[i];
	}

	// Test that we cannot create an array of abstract objects directly
	std::cout << "\n--- Abstract Class Verification ---" << std::endl;
	std::cout << "Note: The following line would cause a compilation error:" << std::endl;
	std::cout << "// AAnimal abstractTest;  // ERROR!" << std::endl;
	std::cout << "This proves AAnimal is truly abstract and cannot be instantiated." << std::endl;

	std::cout << "\n--- End of Tests ---" << std::endl;

	return 0;
}
