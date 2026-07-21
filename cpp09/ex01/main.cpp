#include "RPN.hpp"

#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	try {
		RPN calculator;
		std::string expression = argv[1];
		int result = calculator.evaluate(expression);
		std::cout << result << std::endl;
	} catch (const std::exception&) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}

