#include "RPN.hpp"

#include <cctype>
#include <climits>
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

RPN::InvalidExpressionException::InvalidExpressionException(const std::string& message) : _message(message) {
}

RPN::InvalidExpressionException::~InvalidExpressionException() throw() {
}

const char* RPN::InvalidExpressionException::what() const throw() {
	return _message.c_str();
}

const char* RPN::DivisionByZeroException::what() const throw() {
	return "Division by zero";
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

int RPN::performOperation(int left, int right, const std::string& op) const {
	if (op == "+") {
		double result = static_cast<double>(left) + right;
		if (result < INT_MIN || result > INT_MAX)
			throw InvalidExpressionException("Integer overflow");
		return static_cast<int>(result);
	} else if (op == "-") {
		double result = static_cast<double>(left) - right;
		if (result < INT_MIN || result > INT_MAX)
			throw InvalidExpressionException("Integer overflow");
		return static_cast<int>(result);
	} else if (op == "*") {
		double result = static_cast<double>(left) * right;
		if (result < INT_MIN || result > INT_MAX)
			throw InvalidExpressionException("Integer overflow");
		return static_cast<int>(result);
	} else if (op == "/") {
		if (right == 0) {
			throw DivisionByZeroException();
		}
		if (left == INT_MIN && right == -1)
			throw InvalidExpressionException("Integer overflow");
		return left / right;
	} else {
		throw InvalidExpressionException("Unknown operator: " + op);
	}
}

void RPN::processToken(const std::string& token) {
	if (isNumber(token)) {
		_operands.push(token[0] - '0');
	} else if (isOperator(token)) {
		if (_operands.size() < 2) {
			throw InsufficientOperandsException();
		}
		
		int operand2 = _operands.top();
		_operands.pop();
		int operand1 = _operands.top();
		_operands.pop();
		
		int result = performOperation(operand1, operand2, token);
		_operands.push(result);
	} else {
		throw InvalidExpressionException("Invalid token: " + token);
	}
}

int RPN::evaluate(const std::string& expression) {
	reset();
	
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
	
	int result = _operands.top();
	return result;
}

void RPN::reset(void) {
	while (!_operands.empty()) {
		_operands.pop();
	}
}
