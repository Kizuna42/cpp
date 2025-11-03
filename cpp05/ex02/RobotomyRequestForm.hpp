#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm {
private:
	std::string _target;
	
	static const int SIGN_GRADE = 72;
	static const int EXEC_GRADE = 45;

public:
	// Orthodox Canonical Form
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
	virtual ~RobotomyRequestForm(void);
	
	// Getters
	const std::string& getTarget(void) const;
	
	// Execute action implementation
	virtual void executeAction(void) const;
};

#endif




