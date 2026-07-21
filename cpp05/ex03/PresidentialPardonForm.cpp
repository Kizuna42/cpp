#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) 
	: AForm("Presidential Pardon Form", SIGN_GRADE, EXEC_GRADE), _target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) 
	: AForm("Presidential Pardon Form", SIGN_GRADE, EXEC_GRADE), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) 
	: AForm(other), _target(other._target) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {}

const std::string& PresidentialPardonForm::getTarget(void) const {
	return _target;
}

void PresidentialPardonForm::executeAction(void) const {
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox"
		<< std::endl;
}
