#include "iter.hpp"
#include <string>

// Custom function for testing
void toUpper(char& c) {
    if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 'A';
    }
}

// Custom function object (functor)
class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    void operator()(int& value) {
        value *= factor;
    }
};

// Custom function for strings
void addPrefix(std::string& str) {
    str = ">> " + str;
}

int main(void) {
    std::cout << "=== CPP07 ex01: Template Iteration Function ===" << std::endl;
    
    // Test 1: Integer array
    std::cout << "\n--- Test 1: Integer array ---" << std::endl;
    {
        int numbers[] = {1, 2, 3, 4, 5};
        size_t size = sizeof(numbers) / sizeof(numbers[0]);
        
        std::cout << "Original array: ";
        ::iter(numbers, size, printElement<int>);
        std::cout << std::endl;
        
        // Increment all elements
        ::iter(numbers, size, increment<int>);
        std::cout << "After increment: ";
        ::iter(numbers, size, printElement<int>);
        std::cout << std::endl;
        
        // Double all elements
        ::iter(numbers, size, doubleValue<int>);
        std::cout << "After doubling: ";
        ::iter(numbers, size, printElement<int>);
        std::cout << std::endl;
    }
    
    // Test 2: Double array
    std::cout << "\n--- Test 2: Double array ---" << std::endl;
    {
        double values[] = {1.1, 2.2, 3.3, 4.4};
        size_t size = sizeof(values) / sizeof(values[0]);
        
        std::cout << "Original values: ";
        ::iter(values, size, printElement<double>);
        std::cout << std::endl;
        
        ::iter(values, size, doubleValue<double>);
        std::cout << "After doubling: ";
        ::iter(values, size, printElement<double>);
        std::cout << std::endl;
    }
    
    // Test 3: Character array
    std::cout << "\n--- Test 3: Character array ---" << std::endl;
    {
        char text[] = {'h', 'e', 'l', 'l', 'o'};
        size_t size = sizeof(text) / sizeof(text[0]);
        
        std::cout << "Original text: ";
        ::iter(text, size, printElement<char>);
        std::cout << std::endl;
        
        ::iter(text, size, toUpper);
        std::cout << "After toUpper: ";
        ::iter(text, size, printElement<char>);
        std::cout << std::endl;
    }
    
    // Test 4: String array
    std::cout << "\n--- Test 4: String array ---" << std::endl;
    {
        std::string words[] = {"hello", "world", "template", "functions"};
        size_t size = sizeof(words) / sizeof(words[0]);
        
        std::cout << "Original words:" << std::endl;
        ::iter(words, size, println<std::string>);
        
        ::iter(words, size, addPrefix);
        std::cout << "\nAfter adding prefix:" << std::endl;
        ::iter(words, size, println<std::string>);
    }
    
    // Test 5: Const array
    std::cout << "\n--- Test 5: Const array ---" << std::endl;
    {
        const int constNumbers[] = {10, 20, 30, 40, 50};
        size_t size = sizeof(constNumbers) / sizeof(constNumbers[0]);
        
        std::cout << "Const array: ";
        ::iter(constNumbers, size, printElement<int>);
        std::cout << std::endl;
        
        // Note: Cannot use increment or doubleValue on const array
    }
    
    // Test 6: Function object (functor)
    std::cout << "\n--- Test 6: Function object (functor) ---" << std::endl;
    {
        int data[] = {1, 2, 3, 4, 5};
        size_t size = sizeof(data) / sizeof(data[0]);
        
        std::cout << "Before multiplication by 3: ";
        ::iter(data, size, printElement<int>);
        std::cout << std::endl;
        
        Multiplier multiplyBy3(3);
        ::iter(data, size, multiplyBy3);
        
        std::cout << "After multiplication by 3: ";
        ::iter(data, size, printElement<int>);
        std::cout << std::endl;
    }
    
    // Test 7: Empty array and NULL pointer
    std::cout << "\n--- Test 7: Edge cases ---" << std::endl;
    {
        int* nullPtr = NULL;
        std::cout << "Testing NULL pointer (should do nothing): ";
        ::iter(nullPtr, 5, printElement<int>);
        std::cout << "Done" << std::endl;
        
        int emptyArray[] = {};
        std::cout << "Testing empty array (length 0): ";
        ::iter(emptyArray, 0, printElement<int>);
        std::cout << "Done" << std::endl;
    }
    
    // Test 8: Different function signatures
    std::cout << "\n--- Test 8: Different function signatures ---" << std::endl;
    {
        int testArray[] = {1, 2, 3};
        size_t size = sizeof(testArray) / sizeof(testArray[0]);
        
        // Reset static counter in printElementWithIndex
        std::cout << "With index printing: ";
        ::iter(testArray, size, printElementWithIndex<int>);
        std::cout << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




