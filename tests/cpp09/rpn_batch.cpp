#include "RPN.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

// Exercise the public API repeatedly, including reuse after an exception.
int main() {
	RPN calculator;
	std::string expression;
	std::cout << std::setprecision(std::numeric_limits<double>::digits10);
	while (std::getline(std::cin, expression)) {
		try {
			double result = calculator.evaluate(expression);
			RPN copied(calculator);
			RPN assigned;
			assigned = copied;
			if (copied.evaluate(expression) != result ||
				assigned.evaluate(expression) != result)
				return 1;
			std::cout << result << '\n';
		} catch (const std::exception&) {
			std::cout << "Error\n";
		}
	}
	return 0;
}
