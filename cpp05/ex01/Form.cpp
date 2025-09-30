#include "Form.hpp"
#include "Bureaucrat.hpp"

// Constructors
Form::Form(void) : _name("Default Form"), _isSigned(false), 
                   _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE) {
    std::cout << "Default form created: " << _name 
              << " (sign grade: " << _gradeToSign 
              << ", execute grade: " << _gradeToExecute << ")" << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) 
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    
    if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE) {
        throw GradeTooHighException();
    }
    if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE) {
        throw GradeTooLowException();
    }
    
    std::cout << "Form " << _name << " created with sign grade " << _gradeToSign 
              << " and execute grade " << _gradeToExecute << std::endl;
}

Form::Form(const Form& other) 
    : _name(other._name), _isSigned(other._isSigned), 
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
    std::cout << "Form " << _name << " copied" << std::endl;
}

// Assignment operator
Form& Form::operator=(const Form& other) {
    if (this != &other) {
        // Note: _name, _gradeToSign, and _gradeToExecute are const, so we can only copy _isSigned
        _isSigned = other._isSigned;
        std::cout << "Form assignment: signed status copied (" << _isSigned << ")" << std::endl;
    }
    return *this;
}

// Destructor
Form::~Form(void) {
    std::cout << "Form " << _name << " destroyed" << std::endl;
}

// Getters
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

// Form functionality
void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign) {
        throw GradeTooLowException();
    }
    if (_isSigned) {
        std::cout << "Form " << _name << " is already signed!" << std::endl;
        return;
    }
    _isSigned = true;
    std::cout << "Form " << _name << " has been signed by " << bureaucrat.getName() << std::endl;
}

// Exception implementations
const char* Form::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Grade is too low to sign this form!";
}

// Non-member functions
std::ostream& operator<<(std::ostream& out, const Form& form) {
    out << "Form " << form.getName() 
        << " (signed: " << (form.isSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute() << ")";
    return out;
}




