#include "Intern.hpp"

// Constructors
Intern::Intern(void) {
	std::cout << "Intern hired and ready to work!" << std::endl;
}

Intern::Intern(const Intern& other) {
	(void)other;  // Intern has no data members to copy
	std::cout << "Intern cloned (probably an illegal practice)" << std::endl;
}

// Assignment operator
Intern& Intern::operator=(const Intern& other) {
	(void)other;  // Intern has no data members to assign
	std::cout << "Intern assignment (all interns are the same anyway)" << std::endl;
	return *this;
}

// Destructor
Intern::~Intern(void) {
	std::cout << "Intern fired (or quit due to unpaid overtime)" << std::endl;
}

// Static form creation functions
AForm* Intern::createShrubberyForm(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPardonForm(const std::string& target) {
	return new PresidentialPardonForm(target);
}

// Main functionality
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
	// Define available forms and their creators
	FormInfo forms[] = {
		{"shrubbery creation", &createShrubberyForm},
		{"robotomy request", &createRobotomyForm},
		{"presidential pardon", &createPardonForm}
	};
	
	const int numForms = sizeof(forms) / sizeof(forms[0]);
	
	// Search for the requested form
	for (int i = 0; i < numForms; i++) {
		if (forms[i].name == formName) {
			AForm* newForm = forms[i].creator(target);
			std::cout << "Intern creates " << formName << " form for target: " << target << std::endl;
			return newForm;
		}
	}
	
	// Form not found
	std::cout << "Intern cannot create " << formName << " form (unknown form type)" << std::endl;
	throw UnknownFormException();
}

// Exception implementation
const char* Intern::UnknownFormException::what() const throw() {
	return "Unknown form type! Intern doesn't know how to create this form.";
}




