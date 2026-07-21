#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(void) : _name("Default Form"), _isSigned(false),
				   _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE) {
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {

	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE) {
		throw GradeTooHighException();
	}
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE) {
		throw GradeTooLowException();
	}
}

Form::Form(const Form& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

Form& Form::operator=(const Form& other) {
	if (this != &other) {
		_isSigned = other._isSigned;
	}
	return *this;
}

Form::~Form(void) {
}

const std::string& Form::getName(void) const {
	return _name;
}

bool Form::isSigned(void) const {
	return _isSigned;
}

int Form::getGradeToSign(void) const {
	return _gradeToSign;
}

int Form::getGradeToExecute(void) const {
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign) {
		throw GradeTooLowException();
	}
	_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade is too low to sign this form!";
}

std::ostream& operator<<(std::ostream& out, const Form& form) {
	out << "Form " << form.getName()
		<< " (signed: " << (form.isSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << ")";
	return out;
}
