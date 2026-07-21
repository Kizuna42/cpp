#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <list>
#include <stack>
#include <string>

class RPN {
private:
	std::stack<int, std::list<int> > _operands;
	
	bool isOperator(const std::string& token) const;
	bool isNumber(const std::string& token) const;
	int performOperation(int left, int right, const std::string& op) const;
	void processToken(const std::string& token);
	void reset(void);

public:
	RPN(void);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN(void);
	
	int evaluate(const std::string& expression);

	class InvalidExpressionException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidExpressionException(const std::string& message);
		virtual ~InvalidExpressionException() throw();
		virtual const char* what() const throw();
	};
	
	class DivisionByZeroException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class InsufficientOperandsException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
