#include "Base.hpp"

// Virtual destructor implementation
Base::~Base(void) {}

// Generate a random instance of A, B, or C
Base* generate(void) {
    // Initialize random seed once
    static bool initialized = false;
    if (!initialized) {
        std::srand(std::time(0));
        initialized = true;
    }
    
    int random = std::rand() % 3;
    
    switch (random) {
        case 0:
            std::cout << "Generated: A" << std::endl;
            return new A();
        case 1:
            std::cout << "Generated: B" << std::endl;
            return new B();
        case 2:
            std::cout << "Generated: C" << std::endl;
            return new C();
        default:
            return NULL;  // Should never happen
    }
}

// Identify the actual type using pointer and dynamic_cast
void identify(Base* p) {
    if (p == NULL) {
        std::cout << "identify(Base*): NULL pointer" << std::endl;
        return;
    }
    
    std::cout << "identify(Base*): ";
    
    // Try to cast to each type
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

// Identify the actual type using reference and dynamic_cast with exception handling
void identify(Base& p) {
    std::cout << "identify(Base&): ";
    
    // Try to cast to A
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a;  // Suppress unused variable warning
        std::cout << "A" << std::endl;
        return;
    } catch (const std::bad_cast& e) {
        // Not an A, continue trying
    }
    
    // Try to cast to B
    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;  // Suppress unused variable warning
        std::cout << "B" << std::endl;
        return;
    } catch (const std::bad_cast& e) {
        // Not a B, continue trying
    }
    
    // Try to cast to C
    try {
        C& c = dynamic_cast<C&>(p);
        (void)c;  // Suppress unused variable warning
        std::cout << "C" << std::endl;
        return;
    } catch (const std::bad_cast& e) {
        // Not a C either
    }
    
    std::cout << "Unknown type" << std::endl;
}




