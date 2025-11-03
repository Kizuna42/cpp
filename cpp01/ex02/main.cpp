#include <string>
#include <iostream>

int main(void) {
    std::string brain = "HI THIS IS BRAIN";
    std::string* stringPTR = &brain;
    std::string& stringREF = brain;
    
    std::cout << "=== Memory addresses ===" << std::endl;
    std::cout << "Address of brain variable: " << &brain << std::endl;
    std::cout << "Address held by stringPTR: " << stringPTR << std::endl;
    std::cout << "Address held by stringREF: " << &stringREF << std::endl;
    
    std::cout << "\n=== Values ===" << std::endl;
    std::cout << "Value of brain variable:   " << brain << std::endl;
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;
    
    std::cout << "\n=== Demonstration: Pointer vs Reference ===" << std::endl;
    
    std::cout << "Original string: \"" << brain << "\"" << std::endl;
    
    *stringPTR = "Modified via pointer";
    std::cout << "After modification via pointer: \"" << brain << "\"" << std::endl;
    std::cout << "stringREF now shows: \"" << stringREF << "\"" << std::endl;
    
    stringREF = "Modified via reference";
    std::cout << "After modification via reference: \"" << brain << "\"" << std::endl;
    std::cout << "stringPTR now points to: \"" << *stringPTR << "\"" << std::endl;
    
    std::cout << "\n=== Key Differences ===" << std::endl;
    std::cout << "1. Pointer can be reassigned, reference cannot" << std::endl;
    std::cout << "2. Pointer can be NULL, reference must be initialized" << std::endl;
    std::cout << "3. Pointer arithmetic possible, not with references" << std::endl;
    std::cout << "4. Both access the same memory location when properly set" << std::endl;
    
    return 0;
}