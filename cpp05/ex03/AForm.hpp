#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm {
private:
	const std::string _name;
	bool _isSigned;
	const int _gradeToSign;
	const int _gradeToExecute;
	
	static const int HIGHEST_GRADE = 1;
	static const int LOWEST_GRADE = 150;

protected:
	virtual void executeAction(void) const = 0;

public:
	AForm(void);
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm(void);
	
	const std::string& getName(void) const;
	bool isSigned(void) const;
	int getGradeToSign(void) const;
	int getGradeToExecute(void) const;
	
	void beSigned(const Bureaucrat& bureaucrat);
	void execute(const Bureaucrat& executor) const;

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

};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
