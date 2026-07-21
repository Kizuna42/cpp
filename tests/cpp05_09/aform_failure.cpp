#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
	Bureaucrat executor("Executor", 1);
	ShrubberyCreationForm form("/definitely/missing/parent/tree");
	executor.signForm(form);
	executor.executeForm(form);
	return 0;
}
