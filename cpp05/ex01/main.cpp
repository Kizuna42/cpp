#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void) {
	std::cout << "=== CPP05 ex01: Form and Bureaucrat Interaction ===" << std::endl;

	try {
		std::cout << "\n--- Test 1: Valid form creation ---" << std::endl;
		Form taxForm("Tax Form", 50, 25);
		std::cout << taxForm << std::endl;

		std::cout << "\n--- Test 2: Valid bureaucrat creation ---" << std::endl;
		Bureaucrat alice("Alice", 30);
		std::cout << alice << std::endl;

		std::cout << "\n--- Test 3: Successful form signing ---" << std::endl;
		alice.signForm(taxForm);
		std::cout << taxForm << std::endl;

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 4: Form with invalid grades ---" << std::endl;
		Form invalidForm("Invalid Form", 0, 200);

	} catch (const Form::GradeTooHighException& e) {
		std::cout << "Caught Form::GradeTooHighException: " << e.what() << std::endl;
	} catch (const Form::GradeTooLowException& e) {
		std::cout << "Caught Form::GradeTooLowException: " << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 5: Bureaucrat can't sign form (grade too low) ---" << std::endl;
		Form importantForm("Important Form", 10, 5);
		Bureaucrat bob("Bob", 50);
		std::cout << importantForm << std::endl;
		std::cout << bob << std::endl;
		bob.signForm(importantForm);
		std::cout << importantForm << std::endl;

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 6: High-ranking bureaucrat signs form ---" << std::endl;
		Form secretForm("Secret Form", 5, 1);
		Bureaucrat director("Director", 3);
		std::cout << secretForm << std::endl;
		std::cout << director << std::endl;
		director.signForm(secretForm);
		std::cout << secretForm << std::endl;

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 7: Trying to sign already signed form ---" << std::endl;
		Form doubleForm("Double Sign Form", 20, 10);
		Bureaucrat charlie("Charlie", 15);
		Bureaucrat diana("Diana", 10);

		std::cout << doubleForm << std::endl;
		charlie.signForm(doubleForm);
		diana.signForm(doubleForm);

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 8: Copy constructor and assignment ---" << std::endl;
		Form originalForm("Original Form", 30, 20);
		Bureaucrat eve("Eve", 25);

		eve.signForm(originalForm);
		std::cout << "Original: " << originalForm << std::endl;

		Form copiedForm(originalForm);
		std::cout << "Copied: " << copiedForm << std::endl;

		Form assignedForm("Temp Form", 100, 100);
		assignedForm = originalForm;
		std::cout << "Assigned: " << assignedForm << std::endl;

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n--- Test 9: Boundary values ---" << std::endl;
		Form lowestGradeForm("Lowest Grade Form", 150, 150);
		Form highestGradeForm("Highest Grade Form", 1, 1);

		Bureaucrat intern("Intern", 150);
		Bureaucrat president("President", 1);

		std::cout << lowestGradeForm << std::endl;
		std::cout << highestGradeForm << std::endl;

		intern.signForm(lowestGradeForm);
		president.signForm(highestGradeForm);

		std::cout << "After signing:" << std::endl;
		std::cout << lowestGradeForm << std::endl;
		std::cout << highestGradeForm << std::endl;

	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== End of tests ===" << std::endl;

	return 0;
}
