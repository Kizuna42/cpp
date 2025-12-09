#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;  // Forward declaration

class AForm {
private:
	const std::string _name;
	bool _isSigned;
	const int _gradeToSign;
	const int _gradeToExecute;
	
	static const int HIGHEST_GRADE = 1;
	static const int LOWEST_GRADE = 150;

public:
	// Orthodox Canonical Form
	AForm(void);
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm(void);
	
	// Getters
	const std::string& getName(void) const;
	bool isSigned(void) const;
	int getGradeToSign(void) const;
	int getGradeToExecute(void) const;
	
	// Form functionality
	void beSigned(const Bureaucrat& bureaucrat);
	void execute(const Bureaucrat& executor) const;
	
	// Pure virtual function - must be implemented by derived classes
	virtual void executeAction(void) const = 0;
	
	// Exception classes
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class FormNotSignedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class AlreadySignedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

// Non-member functions
std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
