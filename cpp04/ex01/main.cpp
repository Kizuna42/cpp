#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void) {
    std::cout << "=== Brain and Deep Copy Test ===" << std::endl;
    
    // Test array creation as specified in subject
    std::cout << "\n--- Creating Array of Animals ---" << std::endl;
    const int ANIMAL_COUNT = 6;
    Animal* animals[ANIMAL_COUNT];
    
    // Fill half with Dogs, half with Cats
    for (int i = 0; i < ANIMAL_COUNT / 2; i++) {
        animals[i] = new Dog();
    }
    for (int i = ANIMAL_COUNT / 2; i < ANIMAL_COUNT; i++) {
        animals[i] = new Cat();
    }
    
    // Test polymorphic behavior
    std::cout << "\n--- Testing Polymorphic Behavior ---" << std::endl;
    for (int i = 0; i < ANIMAL_COUNT; i++) {
        std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
        animals[i]->makeSound();
    }
    
    // Clean up array (tests virtual destructors)
    std::cout << "\n--- Cleaning Up Array ---" << std::endl;
    for (int i = 0; i < ANIMAL_COUNT; i++) {
        delete animals[i];
    }
    
    // Test deep copy with Dogs
    std::cout << "\n--- Deep Copy Test with Dogs ---" << std::endl;
    Dog originalDog;
    originalDog.setIdea(0, "I love my original owner!");
    originalDog.setIdea(1, "Original dog's special thought");
    
    std::cout << "\nOriginal Dog ideas:" << std::endl;
    originalDog.printIdeas(3);
    
    // Test copy constructor
    std::cout << "\n--- Copy Constructor Test ---" << std::endl;
    Dog copiedDog(originalDog);
    
    std::cout << "\nCopied Dog ideas (should be same as original):" << std::endl;
    copiedDog.printIdeas(3);
    
    // Modify original dog's ideas
    std::cout << "\n--- Modifying Original Dog ---" << std::endl;
    originalDog.setIdea(0, "I love my NEW owner!");
    originalDog.setIdea(1, "Modified original dog's thought");
    
    std::cout << "\nOriginal Dog ideas after modification:" << std::endl;
    originalDog.printIdeas(3);
    
    std::cout << "\nCopied Dog ideas (should remain unchanged - deep copy!):" << std::endl;
    copiedDog.printIdeas(3);
    
    // Test assignment operator
    std::cout << "\n--- Assignment Operator Test ---" << std::endl;
    Dog assignedDog;
    assignedDog.setIdea(0, "I'm a different dog");
    
    std::cout << "\nAssigned Dog ideas before assignment:" << std::endl;
    assignedDog.printIdeas(2);
    
    assignedDog = originalDog;  // Should deep copy
    
    std::cout << "\nAssigned Dog ideas after assignment:" << std::endl;
    assignedDog.printIdeas(3);
    
    // Modify assigned dog to verify independence
    assignedDog.setIdea(0, "I'm the assigned dog now!");
    
    std::cout << "\nOriginal Dog ideas (should be unchanged):" << std::endl;
    originalDog.printIdeas(2);
    
    std::cout << "\nAssigned Dog ideas (should be modified):" << std::endl;
    assignedDog.printIdeas(2);
    
    // Test with Cats as well
    std::cout << "\n--- Deep Copy Test with Cats ---" << std::endl;
    Cat originalCat;
    originalCat.setIdea(0, "I hate everyone equally");
    originalCat.setIdea(1, "Especially dogs");
    
    Cat copiedCat(originalCat);
    
    // Check brain addresses to prove deep copy
    std::cout << "\n--- Brain Address Verification ---" << std::endl;
    std::cout << "Original Cat brain address: " << originalCat.getBrain() << std::endl;
    std::cout << "Copied Cat brain address: " << copiedCat.getBrain() << std::endl;
    std::cout << "Same address? " << (originalCat.getBrain() == copiedCat.getBrain() ? "YES (SHALLOW COPY - BAD!)" : "NO (DEEP COPY - GOOD!)") << std::endl;
    
    std::cout << "\nOriginal Dog brain address: " << originalDog.getBrain() << std::endl;
    std::cout << "Copied Dog brain address: " << copiedDog.getBrain() << std::endl;
    std::cout << "Same address? " << (originalDog.getBrain() == copiedDog.getBrain() ? "YES (SHALLOW COPY - BAD!)" : "NO (DEEP COPY - GOOD!)") << std::endl;
    
    std::cout << "\n--- End of Tests ---" << std::endl;
    
    return 0;
}