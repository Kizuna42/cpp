#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class AForm;  // Forward declaration

class Bureaucrat {
private:
    const std::string _name;
    int _grade;
    
    static const int HIGHEST_GRADE = 1;
    static const int LOWEST_GRADE = 150;

public:
    // Orthodox Canonical Form
    Bureaucrat(void);
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat(void);
    
    // Getters
    const std::string& getName(void) const;
    int getGrade(void) const;
    
    // Grade manipulation
    void incrementGrade(void);
    void decrementGrade(void);
    
    // Form-related functionality
    void signForm(AForm& form);
    void executeForm(const AForm& form);
    
    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

// Non-member functions
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif




