#include "PresidentialPardonForm.hpp"

// Constructors
PresidentialPardonForm::PresidentialPardonForm(void) 
    : AForm("Presidential Pardon Form", SIGN_GRADE, EXEC_GRADE), _target("default") {
    std::cout << "Default PresidentialPardonForm created for target: " << _target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) 
    : AForm("Presidential Pardon Form", SIGN_GRADE, EXEC_GRADE), _target(target) {
    std::cout << "PresidentialPardonForm created for target: " << _target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) 
    : AForm(other), _target(other._target) {
    std::cout << "PresidentialPardonForm copied for target: " << _target << std::endl;
}

// Assignment operator
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
        std::cout << "PresidentialPardonForm assigned for target: " << _target << std::endl;
    }
    return *this;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm(void) {
    std::cout << "PresidentialPardonForm for target " << _target << " destroyed" << std::endl;
}

// Getters
const std::string& PresidentialPardonForm::getTarget(void) const {
    return _target;
}

// Execute action implementation
void PresidentialPardonForm::executeAction(void) const {
    std::cout << "=== PRESIDENTIAL PARDON DECREE ===" << std::endl;
    std::cout << "By the power vested in me as President," << std::endl;
    std::cout << "I hereby grant a full and unconditional pardon to:" << std::endl;
    std::cout << std::endl;
    std::cout << "         " << _target << std::endl;
    std::cout << std::endl;
    std::cout << "This pardon covers all federal offenses that " << _target << std::endl;
    std::cout << "has committed or may have committed." << std::endl;
    std::cout << std::endl;
    std::cout << "Signed by Zaphod Beeblebrox" << std::endl;
    std::cout << "President of the Galaxy" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox!" << std::endl;
}
