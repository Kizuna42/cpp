#include "RPN.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	try {
		RPN calculator;
		std::string expression = argv[1];
		double result = calculator.evaluate(expression);
		std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 2)
			<< result << std::endl;
	} catch (const std::exception&) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}
