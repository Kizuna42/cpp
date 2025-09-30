#include "Bureaucrat.hpp"

// Constructors
Bureaucrat::Bureaucrat(void) : _name("Default"), _grade(LOWEST_GRADE) {
    std::cout << "Default bureaucrat created with grade " << _grade << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
    if (grade < HIGHEST_GRADE) {
        throw GradeTooHighException();
    }
    if (grade > LOWEST_GRADE) {
        throw GradeTooLowException();
    }
    _grade = grade;
    std::cout << "Bureaucrat " << _name << " created with grade " << _grade << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {
    std::cout << "Bureaucrat " << _name << " copied with grade " << _grade << std::endl;
}

// Assignment operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        // Note: _name is const, so we can only copy _grade
        _grade = other._grade;
        std::cout << "Bureaucrat assignment: grade copied (" << _grade << ")" << std::endl;
    }
    return *this;
}

// Destructor
Bureaucrat::~Bureaucrat(void) {
    std::cout << "Bureaucrat " << _name << " destroyed" << std::endl;
}

// Getters
const std::string& Bureaucrat::getName(void) const {
    return _name;
}

int Bureaucrat::getGrade(void) const {
    return _grade;
}

// Grade manipulation
void Bureaucrat::incrementGrade(void) {
    if (_grade <= HIGHEST_GRADE) {
        throw GradeTooHighException();
    }
    _grade--;
    std::cout << "Bureaucrat " << _name << " grade incremented to " << _grade << std::endl;
}

void Bureaucrat::decrementGrade(void) {
    if (_grade >= LOWEST_GRADE) {
        throw GradeTooLowException();
    }
    _grade++;
    std::cout << "Bureaucrat " << _name << " grade decremented to " << _grade << std::endl;
}

// Exception implementations
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high! (minimum grade is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low! (maximum grade is 150)";
}

// Non-member functions
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
    out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
    return out;
}




