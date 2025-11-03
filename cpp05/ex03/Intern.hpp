#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <string>

class Intern {
private:
	struct FormInfo {
		std::string name;
		AForm* (*creator)(const std::string& target);
	};
	
	static AForm* createShrubberyForm(const std::string& target);
	static AForm* createRobotomyForm(const std::string& target);
	static AForm* createPardonForm(const std::string& target);

public:
	// Orthodox Canonical Form
	Intern(void);
	Intern(const Intern& other);
	Intern& operator=(const Intern& other);
	~Intern(void);
	
	// Main functionality
	AForm* makeForm(const std::string& formName, const std::string& target);
	
	// Exception class
	class UnknownFormException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif




