#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void) {
    std::cout << "=== CPP05 ex02: Abstract Forms and Concrete Implementations ===" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Create bureaucrats with different grades ---" << std::endl;
        Bureaucrat intern("Intern", 150);
        Bureaucrat manager("Manager", 50);
        Bureaucrat director("Director", 10);
        Bureaucrat president("President", 1);
        
        std::cout << intern << std::endl;
        std::cout << manager << std::endl;
        std::cout << director << std::endl;
        std::cout << president << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception in bureaucrat creation: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: ShrubberyCreationForm ---" << std::endl;
        ShrubberyCreationForm shrubForm("garden");
        Bureaucrat gardener("Gardener", 140);
        
        std::cout << shrubForm << std::endl;
        std::cout << gardener << std::endl;
        
        gardener.signForm(shrubForm);
        gardener.executeForm(shrubForm);
        
    } catch (const std::exception& e) {
        std::cout << "Exception with ShrubberyCreationForm: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: RobotomyRequestForm ---" << std::endl;
        RobotomyRequestForm robotForm("Bender");
        Bureaucrat engineer("Engineer", 40);
        
        std::cout << robotForm << std::endl;
        std::cout << engineer << std::endl;
        
        engineer.signForm(robotForm);
        engineer.executeForm(robotForm);
        
        // Try multiple executions to see randomization
        std::cout << "\n--- Multiple robotomy attempts ---" << std::endl;
        engineer.executeForm(robotForm);
        engineer.executeForm(robotForm);
        
    } catch (const std::exception& e) {
        std::cout << "Exception with RobotomyRequestForm: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 4: PresidentialPardonForm ---" << std::endl;
        PresidentialPardonForm pardonForm("Arthur Dent");
        Bureaucrat vicePresident("Vice President", 3);
        
        std::cout << pardonForm << std::endl;
        std::cout << vicePresident << std::endl;
        
        vicePresident.signForm(pardonForm);
        vicePresident.executeForm(pardonForm);
        
    } catch (const std::exception& e) {
        std::cout << "Exception with PresidentialPardonForm: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 5: Form execution without signing ---" << std::endl;
        RobotomyRequestForm unsignedForm("Marvin");
        Bureaucrat admin("Admin", 30);
        
        std::cout << "Attempting to execute unsigned form..." << std::endl;
        admin.executeForm(unsignedForm);  // Should fail
        
    } catch (const std::exception& e) {
        std::cout << "Exception with unsigned form: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 6: Insufficient grade for signing ---" << std::endl;
        PresidentialPardonForm highGradeForm("Ford Prefect");
        Bureaucrat lowGrade("Low Grade", 100);
        
        std::cout << highGradeForm << std::endl;
        std::cout << lowGrade << std::endl;
        lowGrade.signForm(highGradeForm);  // Should fail
        
    } catch (const std::exception& e) {
        std::cout << "Exception with insufficient grade: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 7: Insufficient grade for execution ---" << std::endl;
        ShrubberyCreationForm signedForm("office");
        Bureaucrat signer("Signer", 130);    // Can sign (grade 145)
        Bureaucrat executor("Executor", 140); // Cannot execute (grade 137)
        
        signer.signForm(signedForm);
        executor.executeForm(signedForm);  // Should fail
        
    } catch (const std::exception& e) {
        std::cout << "Exception with execution grade: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 8: Polymorphism with AForm* ---" << std::endl;
        AForm* forms[3] = {
            new ShrubberyCreationForm("home"),
            new RobotomyRequestForm("R2D2"),
            new PresidentialPardonForm("Luke Skywalker")
        };
        
        Bureaucrat master("Master", 1);  // Highest grade
        
        for (int i = 0; i < 3; i++) {
            std::cout << "\n--- Processing form " << i + 1 << " ---" << std::endl;
            std::cout << *forms[i] << std::endl;
            master.signForm(*forms[i]);
            master.executeForm(*forms[i]);
        }
        
        // Clean up
        for (int i = 0; i < 3; i++) {
            delete forms[i];
        }
        
    } catch (const std::exception& e) {
        std::cout << "Exception in polymorphism test: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 9: Copy constructor and assignment ---" << std::endl;
        ShrubberyCreationForm original("original");
        Bureaucrat signer("Signer", 100);
        
        signer.signForm(original);
        std::cout << "Original: " << original << std::endl;
        
        ShrubberyCreationForm copy(original);
        std::cout << "Copy: " << copy << std::endl;
        
        ShrubberyCreationForm assigned("temp");
        assigned = original;
        std::cout << "Assigned: " << assigned << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception in copy/assignment test: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}






