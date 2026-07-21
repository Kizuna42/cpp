#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	Bureaucrat admin("Admin", 1);
	Bureaucrat lowGrade("LowGrade", 150);

	ShrubberyCreationForm shrubbery("garden");
	std::cout << shrubbery << std::endl;
	admin.executeForm(shrubbery);
	admin.signForm(shrubbery);
	admin.executeForm(shrubbery);

	RobotomyRequestForm robotomy("Bender");
	admin.signForm(robotomy);
	admin.executeForm(robotomy);

	PresidentialPardonForm pardon("Arthur Dent");
	lowGrade.signForm(pardon);
	admin.signForm(pardon);
	admin.executeForm(pardon);

	ShrubberyCreationForm copy(shrubbery);
	ShrubberyCreationForm assigned("temporary");
	assigned = shrubbery;
	std::cout << copy << std::endl;
	std::cout << assigned << std::endl;
	return 0;
}
