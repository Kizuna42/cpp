#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;  // Forward declaration

class Form {
private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;
    
    static const int HIGHEST_GRADE = 1;
    static const int LOWEST_GRADE = 150;

public:
    // Orthodox Canonical Form
    Form(void);
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form(void);
    
    // Getters
    const std::string& getName(void) const;
    bool isSigned(void) const;
    int getGradeToSign(void) const;
    int getGradeToExecute(void) const;
    
    // Form functionality
    void beSigned(const Bureaucrat& bureaucrat);
    
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
std::ostream& operator<<(std::ostream& out, const Form& form);

#endif




