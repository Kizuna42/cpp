#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

static void processForm(Intern& intern, Bureaucrat& executor,
	const std::string& name, const std::string& target)
{
	AForm* form = NULL;
	try {
		form = intern.makeForm(name, target);
		std::cout << *form << std::endl;
		executor.signForm(*form);
		executor.executeForm(*form);
	} catch (...) {
		delete form;
		throw;
	}
	delete form;
}

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	Intern intern;
	Intern copy(intern);
	Intern assigned;
	assigned = intern;
	Bureaucrat master("Master", 1);

	try {
		processForm(intern, master, "shrubbery creation", "garden");
		processForm(copy, master, "robotomy request", "Bender");
		processForm(assigned, master, "presidential pardon", "Arthur Dent");
	} catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
	}

	try {
		processForm(intern, master, "coffee making", "espresso");
	} catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
	}
	return 0;
}
