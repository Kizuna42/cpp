#include "AForm.hpp"
#include "Bureaucrat.hpp"

// Constructors
AForm::AForm(void) : _name("Default AForm"), _isSigned(false), 
					 _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE) {
	std::cout << "Default AForm created: " << _name 
			  << " (sign grade: " << _gradeToSign 
			  << ", execute grade: " << _gradeToExecute << ")" << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute) 
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	
	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE) {
		throw GradeTooHighException();
	}
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE) {
		throw GradeTooLowException();
	}
	
	std::cout << "AForm " << _name << " created with sign grade " << _gradeToSign 
			  << " and execute grade " << _gradeToExecute << std::endl;
}

AForm::AForm(const AForm& other) 
	: _name(other._name), _isSigned(other._isSigned), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
	std::cout << "AForm " << _name << " copied" << std::endl;
}

// Assignment operator
AForm& AForm::operator=(const AForm& other) {
	if (this != &other) {
		// Note: _name, _gradeToSign, and _gradeToExecute are const, so we can only copy _isSigned
		_isSigned = other._isSigned;
		std::cout << "AForm assignment: signed status copied (" << _isSigned << ")" << std::endl;
	}
	return *this;
}

// Destructor
AForm::~AForm(void) {
	std::cout << "AForm " << _name << " destroyed" << std::endl;
}

// Getters
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

// Form functionality
void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign) {
		throw GradeTooLowException();
	}
	if (_isSigned) {
		throw AlreadySignedException();
	}
	_isSigned = true;
	std::cout << "AForm " << _name << " has been signed by " << bureaucrat.getName() << std::endl;
}

void AForm::execute(const Bureaucrat& executor) const {
	if (!_isSigned) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > _gradeToExecute) {
		throw GradeTooLowException();
	}
	
	std::cout << executor.getName() << " executes " << _name << std::endl;
	executeAction();  // Call the pure virtual function
}

// Exception implementations
const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
	return "Form is not signed!";
}

const char* AForm::AlreadySignedException::what() const throw() {
	return "Form is already signed!";
}

// Non-member functions
std::ostream& operator<<(std::ostream& out, const AForm& form) {
	out << "AForm " << form.getName() 
		<< " (signed: " << (form.isSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << ")";
	return out;
}
