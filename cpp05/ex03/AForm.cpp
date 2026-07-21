#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(void) : _name("Default AForm"), _isSigned(false), 
					 _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE) {
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute) 
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	
	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE) {
		throw GradeTooHighException();
	}
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE) {
		throw GradeTooLowException();
	}
}

AForm::AForm(const AForm& other) 
	: _name(other._name), _isSigned(other._isSigned), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other) {
		_isSigned = other._isSigned;
	}
	return *this;
}

AForm::~AForm(void) {
}

const std::string& AForm::getName(void) const {
	return _name;
}

bool AForm::isSigned(void) const {
	return _isSigned;
}

int AForm::getGradeToSign(void) const {
	return _gradeToSign;
}

int AForm::getGradeToExecute(void) const {
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign) {
		throw GradeTooLowException();
	}
	_isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
	if (!_isSigned) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > _gradeToExecute) {
		throw GradeTooLowException();
	}
	executeAction();
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
	return "Form is not signed!";
}

std::ostream& operator<<(std::ostream& out, const AForm& form) {
	out << "AForm " << form.getName() 
		<< " (signed: " << (form.isSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << ")";
	return out;
}
