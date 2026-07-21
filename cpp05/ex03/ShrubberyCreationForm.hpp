#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm {
private:
	std::string _target;
	virtual void executeAction(void) const;

	static const int SIGN_GRADE = 145;
	static const int EXEC_GRADE = 137;

public:
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
	virtual ~ShrubberyCreationForm(void);
	
	const std::string& getTarget(void) const;

	class FileCreationException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
