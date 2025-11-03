#include "RPN.hpp"

// Constructors
RPN::RPN(void) {
	std::cout << "RPN: Default constructor called" << std::endl;
}

RPN::RPN(const RPN& other) : _operands(other._operands) {
	std::cout << "RPN: Copy constructor called" << std::endl;
}

// Assignment operator
RPN& RPN::operator=(const RPN& other) {
	std::cout << "RPN: Assignment operator called" << std::endl;
	if (this != &other) {
		_operands = other._operands;
	}
	return *this;
}

// Destructor
RPN::~RPN(void) {
	std::cout << "RPN: Destructor called" << std::endl;
}

// Helper functions
std::string RPN::trim(const std::string& str) const {
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

bool RPN::isOperator(const std::string& token) const {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool RPN::isNumber(const std::string& token) const {
	if (token.empty()) {
		return false;
	}
	
	size_t start = 0;
	if (token[0] == '+' || token[0] == '-') {
		start = 1;
		if (token.length() == 1) {
			return false;  // Just a sign, not a number
		}
	}
	
	bool hasDecimalPoint = false;
	for (size_t i = start; i < token.length(); i++) {
		if (token[i] == '.') {
			if (hasDecimalPoint) {
				return false;  // Multiple decimal points
			}
			hasDecimalPoint = true;
		} else if (!std::isdigit(token[i])) {
			return false;
		}
	}
	
	return true;
}

double RPN::stringToDouble(const std::string& str) const {
	std::istringstream iss(str);
	double value;
	iss >> value;
	if (iss.fail() || !iss.eof()) {
		throw InvalidExpressionException("Invalid number format: " + str);
	}
	return value;
}

double RPN::performOperation(double operand2, double operand1, const std::string& op) const {
	if (op == "+") {
		return operand1 + operand2;
	} else if (op == "-") {
		return operand1 - operand2;
	} else if (op == "*") {
		return operand1 * operand2;
	} else if (op == "/") {
		if (operand2 == 0) {
			throw DivisionByZeroException();
		}
		return operand1 / operand2;
	} else {
		throw InvalidExpressionException("Unknown operator: " + op);
	}
}

void RPN::processToken(const std::string& token) {
	if (isNumber(token)) {
		double value = stringToDouble(token);
		_operands.push(value);
		std::cout << "Pushed: " << value << " (stack size: " << _operands.size() << ")" << std::endl;
	} else if (isOperator(token)) {
		if (_operands.size() < 2) {
			throw InsufficientOperandsException();
		}
		
		double operand2 = _operands.top();
		_operands.pop();
		double operand1 = _operands.top();
		_operands.pop();
		
		std::cout << "Operation: " << operand1 << " " << token << " " << operand2;
		
		double result = performOperation(operand2, operand1, token);
		_operands.push(result);
		
		std::cout << " = " << result << " (stack size: " << _operands.size() << ")" << std::endl;
	} else {
		throw InvalidExpressionException("Invalid token: " + token);
	}
}

// Main functionality
double RPN::evaluate(const std::string& expression) {
	reset();  // Clear any previous state
	
	if (expression.empty()) {
		throw InvalidExpressionException("Empty expression");
	}
	
	std::istringstream iss(expression);
	std::string token;
	
	std::cout << "Evaluating RPN expression: " << expression << std::endl;
	
	while (iss >> token) {
		processToken(token);
	}
	
	if (_operands.size() != 1) {
		throw InvalidExpressionException("Invalid expression: stack should contain exactly one result");
	}
	
	double result = _operands.top();
	std::cout << "Final result: " << result << std::endl;
	return result;
}

void RPN::reset(void) {
	// Clear the stack
	while (!_operands.empty()) {
		_operands.pop();
	}
}

// Utility functions
void RPN::displayStack(void) const {
	std::stack<double> temp = _operands;
	std::stack<double> display;
	
	// Reverse the stack for bottom-to-top display
	while (!temp.empty()) {
		display.push(temp.top());
		temp.pop();
	}
	
	std::cout << "Stack[" << _operands.size() << "]: {";
	bool first = true;
	while (!display.empty()) {
		if (!first) {
			std::cout << ", ";
		}
		std::cout << display.top();
		display.pop();
		first = false;
	}
	std::cout << "} (bottom -> top)" << std::endl;
}

size_t RPN::stackSize(void) const {
	return _operands.size();
}




