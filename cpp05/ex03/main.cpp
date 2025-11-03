#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void) {
	std::cout << "=== CPP05 ex03: Intern Factory Pattern ===" << std::endl;
	
	try {
		std::cout << "\n--- Test 1: Create intern and bureaucrats ---" << std::endl;
		Intern intern;
		Bureaucrat director("Director", 5);
		Bureaucrat manager("Manager", 50);
		
		std::cout << director << std::endl;
		std::cout << manager << std::endl;
		
	} catch (const std::exception& e) {
		std::cout << "Exception in setup: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 2: Create shrubbery creation form ---" << std::endl;
		Intern intern;
		Bureaucrat gardener("Gardener", 100);
		
		AForm* form = intern.makeForm("shrubbery creation", "garden");
		if (form) {
			std::cout << *form << std::endl;
			gardener.signForm(*form);
			gardener.executeForm(*form);
			delete form;
		}
		
	} catch (const std::exception& e) {
		std::cout << "Exception with shrubbery form: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 3: Create robotomy request form ---" << std::endl;
		Intern intern;
		Bureaucrat engineer("Engineer", 30);
		
		AForm* form = intern.makeForm("robotomy request", "Bender");
		if (form) {
			std::cout << *form << std::endl;
			engineer.signForm(*form);
			engineer.executeForm(*form);
			delete form;
		}
		
	} catch (const std::exception& e) {
		std::cout << "Exception with robotomy form: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 4: Create presidential pardon form ---" << std::endl;
		Intern intern;
		Bureaucrat president("President", 1);
		
		AForm* form = intern.makeForm("presidential pardon", "Arthur Dent");
		if (form) {
			std::cout << *form << std::endl;
			president.signForm(*form);
			president.executeForm(*form);
			delete form;
		}
		
	} catch (const std::exception& e) {
		std::cout << "Exception with pardon form: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 5: Unknown form type ---" << std::endl;
		Intern intern;
		
		AForm* form = intern.makeForm("coffee making", "strong espresso");
		// This should throw an exception, so we shouldn't reach this point
		if (form) {
			delete form;
		}
		
	} catch (const Intern::UnknownFormException& e) {
		std::cout << "Caught Intern::UnknownFormException: " << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 6: Multiple forms with one intern ---" << std::endl;
		Intern intern;
		Bureaucrat master("Master", 1);
		AForm* forms[3];
		
		std::string formTypes[] = {
			"shrubbery creation",
			"robotomy request", 
			"presidential pardon"
		};
		
		std::string targets[] = {
			"office",
			"C3PO",
			"Han Solo"
		};
		
		// Create forms
		for (int i = 0; i < 3; i++) {
			forms[i] = intern.makeForm(formTypes[i], targets[i]);
		}
		
		// Process forms
		for (int i = 0; i < 3; i++) {
			if (forms[i]) {
				std::cout << "\n--- Processing form " << i + 1 << " ---" << std::endl;
				std::cout << *forms[i] << std::endl;
				master.signForm(*forms[i]);
				master.executeForm(*forms[i]);
			}
		}
		
		// Clean up
		for (int i = 0; i < 3; i++) {
			delete forms[i];
		}
		
	} catch (const std::exception& e) {
		std::cout << "Exception in multiple forms test: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 7: Case sensitivity test ---" << std::endl;
		Intern intern;
		
		// Try with different cases (should fail)
		AForm* form1 = NULL;
		AForm* form2 = NULL;
		AForm* form3 = NULL;
		
		try {
			form1 = intern.makeForm("Shrubbery Creation", "test1");
		} catch (const std::exception& e) {
			std::cout << "Capital case failed as expected: " << e.what() << std::endl;
		}
		
		try {
			form2 = intern.makeForm("ROBOTOMY REQUEST", "test2");
		} catch (const std::exception& e) {
			std::cout << "Upper case failed as expected: " << e.what() << std::endl;
		}
		
		try {
			form3 = intern.makeForm("Presidential Pardon", "test3");
		} catch (const std::exception& e) {
			std::cout << "Title case failed as expected: " << e.what() << std::endl;
		}
		
		// Clean up (shouldn't be necessary but just in case)
		if (form1) delete form1;
		if (form2) delete form2;
		if (form3) delete form3;
		
	} catch (const std::exception& e) {
		std::cout << "Exception in case sensitivity test: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "\n--- Test 8: Intern copy constructor and assignment ---" << std::endl;
		Intern intern1;
		Intern intern2(intern1);  // Copy constructor
		Intern intern3;
		intern3 = intern1;        // Assignment operator
		
		// Test that all interns work the same
		AForm* form1 = intern1.makeForm("shrubbery creation", "from_intern1");
		AForm* form2 = intern2.makeForm("robotomy request", "from_intern2");
		AForm* form3 = intern3.makeForm("presidential pardon", "from_intern3");
		
		std::cout << "Form 1: " << *form1 << std::endl;
		std::cout << "Form 2: " << *form2 << std::endl;
		std::cout << "Form 3: " << *form3 << std::endl;
		
		delete form1;
		delete form2;
		delete form3;
		
	} catch (const std::exception& e) {
		std::cout << "Exception in intern copy test: " << e.what() << std::endl;
	}
	
	std::cout << "\n=== End of tests ===" << std::endl;
	
	return 0;
}