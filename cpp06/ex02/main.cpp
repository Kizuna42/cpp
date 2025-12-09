#include "Base.hpp"

int main(void) {
	std::cout << "=== CPP06 ex02: Real Type Identification ===" << std::endl;
	
	// Test 1: Basic type identification
	std::cout << "\n--- Test 1: Basic type identification ---" << std::endl;
	
	for (int i = 0; i < 5; i++) {
		std::cout << "\nRound " << i + 1 << ":" << std::endl;
		
		Base* randomBase = generate();
		
		if (randomBase) {
			identify(randomBase);   // Using pointer version
			identify(*randomBase);  // Using reference version
			
			delete randomBase;
		}
	}
	
	// Test 2: Direct instantiation and identification
	std::cout << "\n--- Test 2: Direct instantiation ---" << std::endl;
	
	A instanceA;
	B instanceB;
	C instanceC;
	
	std::cout << "\nTesting A instance:" << std::endl;
	identify(&instanceA);
	identify(instanceA);
	
	std::cout << "\nTesting B instance:" << std::endl;
	identify(&instanceB);
	identify(instanceB);
	
	std::cout << "\nTesting C instance:" << std::endl;
	identify(&instanceC);
	identify(instanceC);
	
	// Test 3: Polymorphic array
	std::cout << "\n--- Test 3: Polymorphic array ---" << std::endl;
	
	Base* bases[] = {new A(), new B(), new C(), new A(), new B()};
	const int arraySize = sizeof(bases) / sizeof(bases[0]);
	
	for (int i = 0; i < arraySize; i++) {
		std::cout << "\nArray element " << i << ":" << std::endl;
		identify(bases[i]);
		identify(*bases[i]);
	}
	
	// Clean up array
	for (int i = 0; i < arraySize; i++) {
		delete bases[i];
	}
	
	// Test 4: NULL pointer handling
	std::cout << "\n--- Test 4: NULL pointer handling ---" << std::endl;
	
	Base* nullPtr = NULL;
	identify(nullPtr);  // Should handle NULL gracefully
	
	// Test 5: Base class pointer to derived instance
	std::cout << "\n--- Test 5: Base class pointer to derived instance ---" << std::endl;
	
	Base* basePtr = new A();
	std::cout << "Base* pointing to A instance:" << std::endl;
	identify(basePtr);
	identify(*basePtr);
	delete basePtr;
	
	basePtr = new B();
	std::cout << "\nBase* pointing to B instance:" << std::endl;
	identify(basePtr);
	identify(*basePtr);
	delete basePtr;
	
	basePtr = new C();
	std::cout << "\nBase* pointing to C instance:" << std::endl;
	identify(basePtr);
	identify(*basePtr);
	delete basePtr;
	
	// Test 6: Function demonstration
	std::cout << "\n--- Test 6: Function demonstration ---" << std::endl;
	
	std::cout << "\nDemonstrating the difference between pointer and reference identification:" << std::endl;
	
	for (int i = 0; i < 3; i++) {
		Base* testBase = generate();
		if (testBase) {
			std::cout << "Pointer method: ";
			identify(testBase);
			
			std::cout << "Reference method: ";
			identify(*testBase);
			
			delete testBase;
			std::cout << "---" << std::endl;
		}
	}
	
	std::cout << "\n=== End of tests ===" << std::endl;
	
	return 0;
}




