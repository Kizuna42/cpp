#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
private:
	std::string _target;
	
	static const int SIGN_GRADE = 25;
	static const int EXEC_GRADE = 5;

public:
	// Orthodox Canonical Form
	PresidentialPardonForm(void);
	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(const PresidentialPardonForm& other);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
	virtual ~PresidentialPardonForm(void);
	
	// Getters
	const std::string& getTarget(void) const;
	
	// Execute action implementation
	virtual void executeAction(void) const;
};

#endif
