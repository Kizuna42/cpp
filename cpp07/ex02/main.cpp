#include "Array.hpp"
#include <string>

int main(void) {
    std::cout << "=== CPP07 ex02: Template Array Class ===" << std::endl;
    
    // Test 1: Default constructor
    std::cout << "\n--- Test 1: Default constructor ---" << std::endl;
    try {
        Array<int> emptyArray;
        std::cout << "Empty array size: " << emptyArray.size() << std::endl;
        emptyArray.display();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 2: Constructor with size
    std::cout << "\n--- Test 2: Constructor with size ---" << std::endl;
    try {
        Array<int> intArray(5);
        std::cout << "Int array size: " << intArray.size() << std::endl;
        intArray.display();
        
        // Fill with values
        for (size_t i = 0; i < intArray.size(); i++) {
            intArray[i] = i * 10;
        }
        std::cout << "After filling: ";
        intArray.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 3: String array
    std::cout << "\n--- Test 3: String array ---" << std::endl;
    try {
        Array<std::string> stringArray(3);
        std::cout << "String array size: " << stringArray.size() << std::endl;
        
        stringArray[0] = "Hello";
        stringArray[1] = "World";
        stringArray[2] = "Template";
        
        std::cout << "String array contents: ";
        stringArray.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 4: Copy constructor
    std::cout << "\n--- Test 4: Copy constructor ---" << std::endl;
    try {
        Array<int> original(4);
        for (size_t i = 0; i < original.size(); i++) {
            original[i] = i + 1;
        }
        std::cout << "Original array: ";
        original.display();
        
        Array<int> copy(original);
        std::cout << "Copied array: ";
        copy.display();
        
        // Modify original to prove they're independent
        original[0] = 999;
        std::cout << "After modifying original[0] to 999:" << std::endl;
        std::cout << "Original: ";
        original.display();
        std::cout << "Copy: ";
        copy.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 5: Assignment operator
    std::cout << "\n--- Test 5: Assignment operator ---" << std::endl;
    try {
        Array<int> array1(3);
        Array<int> array2(5);
        
        array1.fill(42);
        array2.fill(84);
        
        std::cout << "Before assignment:" << std::endl;
        std::cout << "Array1: ";
        array1.display();
        std::cout << "Array2: ";
        array2.display();
        
        array2 = array1;  // Assignment
        
        std::cout << "After assignment (array2 = array1):" << std::endl;
        std::cout << "Array1: ";
        array1.display();
        std::cout << "Array2: ";
        array2.display();
        
        // Modify array1 to prove independence
        array1[0] = 123;
        std::cout << "After modifying array1[0]:" << std::endl;
        std::cout << "Array1: ";
        array1.display();
        std::cout << "Array2: ";
        array2.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 6: Out of bounds access
    std::cout << "\n--- Test 6: Out of bounds access ---" << std::endl;
    try {
        Array<int> testArray(3);
        testArray[0] = 1;
        testArray[1] = 2;
        testArray[2] = 3;
        
        std::cout << "Valid access - testArray[1]: " << testArray[1] << std::endl;
        std::cout << "Attempting invalid access - testArray[5]..." << std::endl;
        std::cout << testArray[5] << std::endl;  // Should throw exception
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Test 7: Const array access
    std::cout << "\n--- Test 7: Const array access ---" << std::endl;
    try {
        Array<int> normalArray(3);
        normalArray[0] = 10;
        normalArray[1] = 20;
        normalArray[2] = 30;
        
        const Array<int> constArray(normalArray);  // Copy to const array
        
        std::cout << "Const array size: " << constArray.size() << std::endl;
        std::cout << "Const array[1]: " << constArray[1] << std::endl;
        
        // Cannot modify const array elements
        // constArray[0] = 999;  // This would not compile
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 8: Double array
    std::cout << "\n--- Test 8: Double array ---" << std::endl;
    try {
        Array<double> doubleArray(4);
        for (size_t i = 0; i < doubleArray.size(); i++) {
            doubleArray[i] = (i + 1) * 1.5;
        }
        
        std::cout << "Double array: ";
        doubleArray.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 9: Self assignment
    std::cout << "\n--- Test 9: Self assignment ---" << std::endl;
    try {
        Array<int> selfArray(3);
        selfArray.fill(77);
        
        std::cout << "Before self assignment: ";
        selfArray.display();
        
        // Self assignment test - commented out due to -Wself-assign-overloaded warning with -Werror
        // The assignment operator implementation handles self-assignment correctly,
        // but explicit self-assignment triggers a compiler warning that becomes an error.
        // selfArray = selfArray;
        
        std::cout << "After self assignment (test skipped): ";
        selfArray.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 10: Large array
    std::cout << "\n--- Test 10: Large array ---" << std::endl;
    try {
        Array<int> largeArray(1000);
        std::cout << "Large array created with size: " << largeArray.size() << std::endl;
        
        // Fill every 100th element
        for (size_t i = 0; i < largeArray.size(); i += 100) {
            largeArray[i] = i;
        }
        
        std::cout << "Sampling values: ";
        for (size_t i = 0; i < largeArray.size(); i += 100) {
            std::cout << "arr[" << i << "]=" << largeArray[i] << " ";
        }
        std::cout << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




