#include "RPN.hpp"

int main(int argc, char** argv) {
    std::cout << "=== CPP09 ex01: Reverse Polish Notation Calculator ===" << std::endl;
    
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
        std::cout << "Example: " << argv[0] << " \"8 9 * 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
        std::cout << "Example: " << argv[0] << " \"7 7 * 7 -\"" << std::endl;
        std::cout << "Example: " << argv[0] << " \"1 2 * 2 / 2 * 2 4 - +\"" << std::endl;
        return 1;
    }
    
    try {
        RPN calculator;
        std::string expression = argv[1];
        
        std::cout << "\nCalculating: " << expression << std::endl;
        std::cout << "---" << std::endl;
        
        double result = calculator.evaluate(expression);
        
        std::cout << "---" << std::endl;
        std::cout << "Result: " << result << std::endl;
        
    } catch (const RPN::InvalidExpressionException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const RPN::DivisionByZeroException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const RPN::InsufficientOperandsException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}




