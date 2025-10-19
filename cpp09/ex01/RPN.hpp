#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <exception>
#include <climits>

class RPN {
private:
	std::stack<double> _operands;
	
	// Private helper functions
	bool isOperator(const std::string& token) const;
	bool isNumber(const std::string& token) const;
	double stringToDouble(const std::string& str) const;
	double performOperation(double operand1, double operand2, const std::string& op) const;
	void processToken(const std::string& token);
	std::string trim(const std::string& str) const;

public:
	// Orthodox Canonical Form
	RPN(void);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN(void);
	
	// Main functionality
	double evaluate(const std::string& expression);
	void reset(void);
	
	// Utility functions
	void displayStack(void) const;
	size_t stackSize(void) const;
	
	// Exception classes
	class InvalidExpressionException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidExpressionException(const std::string& message) : _message(message) {}
		virtual ~InvalidExpressionException() throw() {}
		virtual const char* what() const throw() { return _message.c_str(); }
	};
	
	class DivisionByZeroException : public std::exception {
	public:
		virtual const char* what() const throw() { return "Division by zero"; }
	};
	
	class InsufficientOperandsException : public std::exception {
	public:
		virtual const char* what() const throw() { return "Insufficient operands for operation"; }
	};
};

#endif




