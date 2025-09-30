#include "ScalarConverter.hpp"

int main(int argc, char** argv) {
    std::cout << "=== CPP06 ex00: Scalar Type Conversion ===" << std::endl;
    
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <literal>" << std::endl;
        std::cout << "\nExample literals to try:" << std::endl;
        std::cout << "Characters: 'a', 'Z', '0'" << std::endl;
        std::cout << "Integers: 42, -42, 0, 2147483647" << std::endl;
        std::cout << "Floats: 42.0f, -42.42f, 0.0f" << std::endl;
        std::cout << "Doubles: 42.0, -42.42, 0.0" << std::endl;
        std::cout << "Special: nan, nanf, +inf, -inf, +inff, -inff" << std::endl;
        return 1;
    }
    
    std::string literal = argv[1];
    std::cout << "Converting literal: \"" << literal << "\"" << std::endl;
    std::cout << std::endl;
    
    ScalarConverter::convert(literal);
    
    return 0;
}




