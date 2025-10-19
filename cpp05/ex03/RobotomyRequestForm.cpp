#include "RobotomyRequestForm.hpp"

// Constructors
RobotomyRequestForm::RobotomyRequestForm(void) 
	: AForm("Robotomy Request Form", SIGN_GRADE, EXEC_GRADE), _target("default") {
	std::cout << "Default RobotomyRequestForm created for target: " << _target << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) 
	: AForm("Robotomy Request Form", SIGN_GRADE, EXEC_GRADE), _target(target) {
	std::cout << "RobotomyRequestForm created for target: " << _target << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) 
	: AForm(other), _target(other._target) {
	std::cout << "RobotomyRequestForm copied for target: " << _target << std::endl;
}

// Assignment operator
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
		std::cout << "RobotomyRequestForm assigned for target: " << _target << std::endl;
	}
	return *this;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "RobotomyRequestForm for target " << _target << " destroyed" << std::endl;
}

// Getters
const std::string& RobotomyRequestForm::getTarget(void) const {
	return _target;
}

// Execute action implementation
void RobotomyRequestForm::executeAction(void) const {
	std::cout << "* DRILLING NOISES *" << std::endl;
	std::cout << "BZZZZZZT! WHIRRRR! CLANK CLANK!" << std::endl;
	std::cout << "* MECHANICAL SOUNDS INTENSIFY *" << std::endl;
	
	// Initialize random seed
	static bool initialized = false;
	if (!initialized) {
		std::srand(std::time(0));
		initialized = true;
	}
	
	// 50% chance of success
	if (std::rand() % 2 == 0) {
		std::cout << _target << " has been robotomized successfully!" << std::endl;
		std::cout << _target << " is now a loyal robot servant." << std::endl;
	} else {
		std::cout << "Robotomy of " << _target << " has failed!" << std::endl;
		std::cout << _target << " remains fully human... for now." << std::endl;
	}
}
