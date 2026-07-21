#include "RobotomyRequestForm.hpp"

#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(void) 
	: AForm("Robotomy Request Form", SIGN_GRADE, EXEC_GRADE), _target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) 
	: AForm("Robotomy Request Form", SIGN_GRADE, EXEC_GRADE), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) 
	: AForm(other), _target(other._target) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {}

const std::string& RobotomyRequestForm::getTarget(void) const {
	return _target;
}

void RobotomyRequestForm::executeAction(void) const {
	std::cout << "* DRILLING NOISES *" << std::endl;
	if (std::rand() % 2 == 0) {
		std::cout << _target << " has been robotomized successfully" << std::endl;
	} else {
		std::cout << "The robotomy of " << _target << " failed" << std::endl;
	}
}


