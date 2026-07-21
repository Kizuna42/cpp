#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

Intern::Intern(void) {
}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

Intern::~Intern(void) {
}

AForm* Intern::createShrubberyForm(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPardonForm(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
	FormInfo forms[] = {
		{"shrubbery creation", &createShrubberyForm},
		{"robotomy request", &createRobotomyForm},
		{"presidential pardon", &createPardonForm}
	};
	
	const int numForms = sizeof(forms) / sizeof(forms[0]);
	
	for (int i = 0; i < numForms; i++) {
		if (forms[i].name == formName) {
			AForm* newForm = forms[i].creator(target);
			std::cout << "Intern creates " << formName << std::endl;
			return newForm;
		}
	}
	
	throw UnknownFormException();
}

const char* Intern::UnknownFormException::what() const throw() {
	return "Unknown form type";
}


