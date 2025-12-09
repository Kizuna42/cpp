#include "RPN.hpp"

// Constructors
RPN::RPN(void) {
}

RPN::RPN(const RPN& other) : _operands(other._operands) {
}

// Assignment operator
RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_operands = other._operands;
	}
	return *this;
}

// Destructor
RPN::~RPN(void) {
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
		// Check if input number is less than 10 (as per subject requirement)
		if (value >= 10) {
			throw InvalidExpressionException("Number must be less than 10");
		}
		_operands.push(value);
	} else if (isOperator(token)) {
		if (_operands.size() < 2) {
			throw InsufficientOperandsException();
		}
		
		double operand2 = _operands.top();
		_operands.pop();
		double operand1 = _operands.top();
		_operands.pop();
		
		double result = performOperation(operand2, operand1, token);
		_operands.push(result);
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
	
	while (iss >> token) {
		processToken(token);
	}
	
	if (_operands.size() != 1) {
		throw InvalidExpressionException("Invalid expression");
	}
	
	double result = _operands.top();
	return result;
}

void RPN::reset(void) {
	// Clear the stack
	while (!_operands.empty()) {
		_operands.pop();
	}
}





