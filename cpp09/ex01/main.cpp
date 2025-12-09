#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	try {
		RPN calculator;
		std::string expression = argv[1];
		double result = calculator.evaluate(expression);
		std::cout << static_cast<int>(result) << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}




