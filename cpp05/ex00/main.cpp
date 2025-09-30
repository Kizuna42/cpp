#include "Bureaucrat.hpp"

int main(void) {
    std::cout << "=== CPP05 ex00: Bureaucrat Exception Testing ===" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Valid bureaucrat creation ---" << std::endl;
        Bureaucrat alice("Alice", 75);
        std::cout << alice << std::endl;
        
        std::cout << "\n--- Test 2: Grade increment/decrement ---" << std::endl;
        alice.incrementGrade();  // 74
        std::cout << alice << std::endl;
        alice.decrementGrade();  // 75
        std::cout << alice << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Grade too high exception ---" << std::endl;
        Bureaucrat bob("Bob", 0);  // Should throw GradeTooHighException
        
    } catch (const Bureaucrat::GradeTooHighException& e) {
        std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 4: Grade too low exception ---" << std::endl;
        Bureaucrat charlie("Charlie", 151);  // Should throw GradeTooLowException
        
    } catch (const Bureaucrat::GradeTooLowException& e) {
        std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 5: Grade manipulation exceptions ---" << std::endl;
        Bureaucrat david("David", 1);  // Highest grade
        std::cout << david << std::endl;
        david.incrementGrade();  // Should throw GradeTooHighException
        
    } catch (const Bureaucrat::GradeTooHighException& e) {
        std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 6: Grade manipulation exceptions (low) ---" << std::endl;
        Bureaucrat eve("Eve", 150);  // Lowest grade
        std::cout << eve << std::endl;
        eve.decrementGrade();  // Should throw GradeTooLowException
        
    } catch (const Bureaucrat::GradeTooLowException& e) {
        std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Test 7: Copy constructor and assignment ---" << std::endl;
    try {
        Bureaucrat frank("Frank", 42);
        Bureaucrat frankCopy(frank);  // Copy constructor
        std::cout << "Original: " << frank << std::endl;
        std::cout << "Copy: " << frankCopy << std::endl;
        
        Bureaucrat george("George", 100);
        george = frank;  // Assignment operator
        std::cout << "After assignment: " << george << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Test 8: Boundary values ---" << std::endl;
    try {
        Bureaucrat highest("Highest", 1);
        Bureaucrat lowest("Lowest", 150);
        std::cout << "Highest: " << highest << std::endl;
        std::cout << "Lowest: " << lowest << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




