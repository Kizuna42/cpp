#include "RPN.hpp"

#include <cctype>
#include <limits>
#include <locale>
#include <sstream>

RPN::RPN(void) {
}

RPN::RPN(const RPN& other) : _operands(other._operands) {
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_operands = other._operands;
	}
	return *this;
}

RPN::~RPN(void) {
}

RPN::InvalidExpressionException::InvalidExpressionException(void) : _message("Invalid expression") {
}

RPN::InvalidExpressionException::InvalidExpressionException(const std::string& message) : _message(message) {
}

RPN::InvalidExpressionException::InvalidExpressionException(const InvalidExpressionException& other)
	: std::exception(other), _message(other._message) {
}

RPN::InvalidExpressionException& RPN::InvalidExpressionException::operator=(
	const InvalidExpressionException& other) {
	if (this != &other) {
		std::exception::operator=(other);
		_message = other._message;
	}
	return *this;
}

RPN::InvalidExpressionException::~InvalidExpressionException() throw() {
}

const char* RPN::InvalidExpressionException::what() const throw() {
	return _message.c_str();
}

RPN::DivisionByZeroException::DivisionByZeroException(void) {
}

RPN::DivisionByZeroException::DivisionByZeroException(const DivisionByZeroException& other)
	: std::exception(other) {
}

RPN::DivisionByZeroException& RPN::DivisionByZeroException::operator=(
	const DivisionByZeroException& other) {
	if (this != &other) {
		std::exception::operator=(other);
	}
	return *this;
}

RPN::DivisionByZeroException::~DivisionByZeroException() throw() {
}

const char* RPN::DivisionByZeroException::what() const throw() {
	return "Division by zero";
}

RPN::InsufficientOperandsException::InsufficientOperandsException(void) {
}

RPN::InsufficientOperandsException::InsufficientOperandsException(const InsufficientOperandsException& other)
	: std::exception(other) {
}

RPN::InsufficientOperandsException& RPN::InsufficientOperandsException::operator=(
	const InsufficientOperandsException& other) {
	if (this != &other) {
		std::exception::operator=(other);
	}
	return *this;
}

RPN::InsufficientOperandsException::~InsufficientOperandsException() throw() {
}

const char* RPN::InsufficientOperandsException::what() const throw() {
	return "Insufficient operands for operation";
}

bool RPN::isOperator(const std::string& token) const {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool RPN::isNumber(const std::string& token) const {
	return token.length() == 1 &&
		std::isdigit(static_cast<unsigned char>(token[0]));
}

double RPN::performOperation(double left, double right, const std::string& op) const {
	double result;
	if (op == "+") {
		result = left + right;
	} else if (op == "-") {
		result = left - right;
	} else if (op == "*") {
		result = left * right;
	} else if (op == "/") {
		if (right == 0) {
			throw DivisionByZeroException();
		}
		result = left / right;
	} else {
		throw InvalidExpressionException("Unknown operator: " + op);
	}
	if (result != result || result > std::numeric_limits<double>::max() ||
		result < -std::numeric_limits<double>::max())
		throw InvalidExpressionException("Floating-point overflow");
	if ((op == "*" || op == "/") && left != 0 && right != 0 && result == 0)
		throw InvalidExpressionException("Floating-point underflow");
	if (result == 0)
		return 0;
	return result;
}

void RPN::processToken(const std::string& token) {
	if (isNumber(token)) {
		_operands.push(token[0] - '0');
	} else if (isOperator(token)) {
		if (_operands.size() < 2) {
			throw InsufficientOperandsException();
		}
		
		double operand2 = _operands.top();
		_operands.pop();
		double operand1 = _operands.top();
		_operands.pop();
		
		double result = performOperation(operand1, operand2, token);
		_operands.push(result);
	} else {
		throw InvalidExpressionException("Invalid token: " + token);
	}
}

double RPN::evaluate(const std::string& expression) {
	reset();
	
	if (expression.empty()) {
		throw InvalidExpressionException("Empty expression");
	}
	
	std::istringstream iss(expression);
	iss.imbue(std::locale::classic());
	std::string token;
	
	while (iss >> token) {
		processToken(token);
	}
	
	if (_operands.size() != 1) {
		throw InvalidExpressionException("Invalid expression");
	}
	
	return _operands.top();
}

void RPN::reset(void) {
	while (!_operands.empty()) {
		_operands.pop();
	}
}
