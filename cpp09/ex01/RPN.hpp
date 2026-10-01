#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <stack>
#include <string>

class RPN {
private:
	std::stack<double> _operands;
	
	bool isOperator(const std::string& token) const;
	bool isNumber(const std::string& token) const;
	double performOperation(double left, double right, const std::string& op) const;
	void processToken(const std::string& token);
	void reset(void);

public:
	RPN(void);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN(void);
	
	double evaluate(const std::string& expression);

	class InvalidExpressionException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidExpressionException(void);
		InvalidExpressionException(const std::string& message);
		InvalidExpressionException(const InvalidExpressionException& other);
		InvalidExpressionException& operator=(const InvalidExpressionException& other);
		virtual ~InvalidExpressionException() throw();
		virtual const char* what() const throw();
	};

	class DivisionByZeroException : public std::exception {
	public:
		DivisionByZeroException(void);
		DivisionByZeroException(const DivisionByZeroException& other);
		DivisionByZeroException& operator=(const DivisionByZeroException& other);
		virtual ~DivisionByZeroException() throw();
		virtual const char* what() const throw();
	};

	class InsufficientOperandsException : public std::exception {
	public:
		InsufficientOperandsException(void);
		InsufficientOperandsException(const InsufficientOperandsException& other);
		InsufficientOperandsException& operator=(const InsufficientOperandsException& other);
		virtual ~InsufficientOperandsException() throw();
		virtual const char* what() const throw();
	};
};

#endif
