#include "Span.hpp"
#include <cstdlib>
#include <ctime>

int main(void) {
    std::cout << "=== CPP08 ex01: Span Class ===" << std::endl;
    
    // Test 1: Basic functionality (from subject)
    std::cout << "\n--- Test 1: Basic functionality (from subject) ---" << std::endl;
    try {
        Span sp = Span(5);
        
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        sp.display();
        
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 2: Exception handling - span full
    std::cout << "\n--- Test 2: Exception handling - span full ---" << std::endl;
    try {
        Span smallSpan(2);
        
        smallSpan.addNumber(1);
        smallSpan.addNumber(2);
        smallSpan.display();
        
        std::cout << "Attempting to add third number..." << std::endl;
        smallSpan.addNumber(3);  // Should throw exception
        
    } catch (const Span::SpanFullException& e) {
        std::cout << "Caught SpanFullException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 3: Exception handling - no span possible
    std::cout << "\n--- Test 3: Exception handling - no span possible ---" << std::endl;
    try {
        Span emptySpan(5);
        std::cout << "Trying to get span from empty Span..." << std::endl;
        emptySpan.shortestSpan();  // Should throw exception
        
    } catch (const Span::NoSpanException& e) {
        std::cout << "Caught NoSpanException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        Span singleSpan(5);
        singleSpan.addNumber(42);
        singleSpan.display();
        
        std::cout << "Trying to get span from single-element Span..." << std::endl;
        singleSpan.longestSpan();  // Should throw exception
        
    } catch (const Span::NoSpanException& e) {
        std::cout << "Caught NoSpanException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 4: Large number of elements
    std::cout << "\n--- Test 4: Large number of elements ---" << std::endl;
    try {
        const unsigned int SIZE = 10000;
        Span largeSpan(SIZE);
        
        // Initialize random seed
        std::srand(std::time(0));
        
        std::cout << "Adding " << SIZE << " random numbers..." << std::endl;
        for (unsigned int i = 0; i < SIZE; i++) {
            largeSpan.addNumber(std::rand() % 100000);
        }
        
        std::cout << "Large span size: " << largeSpan.size() << "/" << largeSpan.maxSize() << std::endl;
        std::cout << "Shortest span: " << largeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << largeSpan.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 5: Range addition (template function)
    std::cout << "\n--- Test 5: Range addition ---" << std::endl;
    try {
        Span rangeSpan(10);
        
        // Create a vector to add as range
        std::vector<int> numbers;
        for (int i = 1; i <= 8; i++) {
            numbers.push_back(i * 10);
        }
        
        std::cout << "Adding range of numbers: ";
        for (size_t i = 0; i < numbers.size(); i++) {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;
        
        rangeSpan.addRange(numbers.begin(), numbers.end());
        rangeSpan.display();
        
        std::cout << "Shortest span: " << rangeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << rangeSpan.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 6: Range addition overflow
    std::cout << "\n--- Test 6: Range addition overflow ---" << std::endl;
    try {
        Span smallSpan(3);
        
        std::vector<int> largeRange;
        for (int i = 0; i < 5; i++) {
            largeRange.push_back(i);
        }
        
        std::cout << "Attempting to add range of size " << largeRange.size() 
                  << " to span with capacity " << smallSpan.maxSize() << std::endl;
        
        smallSpan.addRange(largeRange.begin(), largeRange.end());  // Should throw
        
    } catch (const std::overflow_error& e) {
        std::cout << "Caught overflow_error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 7: Copy constructor and assignment
    std::cout << "\n--- Test 7: Copy constructor and assignment ---" << std::endl;
    try {
        Span original(5);
        original.addNumber(1);
        original.addNumber(100);
        original.addNumber(50);
        
        std::cout << "Original span: ";
        original.display();
        
        // Copy constructor
        Span copied(original);
        std::cout << "Copied span: ";
        copied.display();
        
        // Assignment operator
        Span assigned(10);
        assigned = original;
        std::cout << "Assigned span: ";
        assigned.display();
        
        // Verify independence
        original.addNumber(200);
        std::cout << "After modifying original:" << std::endl;
        std::cout << "Original: ";
        original.display();
        std::cout << "Copied: ";
        copied.display();
        std::cout << "Assigned: ";
        assigned.display();
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 8: Edge cases
    std::cout << "\n--- Test 8: Edge cases ---" << std::endl;
    try {
        // Same numbers
        Span sameNumbers(4);
        sameNumbers.addNumber(5);
        sameNumbers.addNumber(5);
        sameNumbers.addNumber(5);
        sameNumbers.addNumber(5);
        
        std::cout << "Span with same numbers: ";
        sameNumbers.display();
        std::cout << "Shortest span (should be 0): " << sameNumbers.shortestSpan() << std::endl;
        std::cout << "Longest span (should be 0): " << sameNumbers.longestSpan() << std::endl;
        
        // Negative numbers
        Span negativeSpan(3);
        negativeSpan.addNumber(-10);
        negativeSpan.addNumber(0);
        negativeSpan.addNumber(10);
        
        std::cout << "\nSpan with negative numbers: ";
        negativeSpan.display();
        std::cout << "Shortest span: " << negativeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << negativeSpan.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test 9: Very large numbers
    std::cout << "\n--- Test 9: Very large numbers ---" << std::endl;
    try {
        Span largeNumbers(3);
        largeNumbers.addNumber(INT_MAX);
        largeNumbers.addNumber(0);
        largeNumbers.addNumber(INT_MIN);
        
        std::cout << "Span with extreme values: ";
        largeNumbers.display();
        std::cout << "Longest span: " << largeNumbers.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




