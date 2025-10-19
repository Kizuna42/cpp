#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm {
private:
	std::string _target;
	
	static const int SIGN_GRADE = 145;
	static const int EXEC_GRADE = 137;

public:
	// Orthodox Canonical Form
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
	virtual ~ShrubberyCreationForm(void);
	
	// Getters
	const std::string& getTarget(void) const;
	
	// Execute action implementation
	virtual void executeAction(void) const;
	
	// Exception classes
	class FileCreationException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
