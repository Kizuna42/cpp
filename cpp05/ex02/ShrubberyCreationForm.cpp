#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) 
	: AForm("Shrubbery Creation Form", SIGN_GRADE, EXEC_GRADE), _target("default") {
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) 
	: AForm("Shrubbery Creation Form", SIGN_GRADE, EXEC_GRADE), _target(target) {
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) 
	: AForm(other), _target(other._target) {
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
}

const std::string& ShrubberyCreationForm::getTarget(void) const {
	return _target;
}

void ShrubberyCreationForm::executeAction(void) const {
	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());
	
	if (!file.is_open()) {
		throw FileCreationException();
	}
	
	file << "       _-_" << std::endl;
	file << "    /~~   ~~\\" << std::endl;
	file << " /~~         ~~\\" << std::endl;
	file << "{               }" << std::endl;
	file << " \\  _-     -_  /" << std::endl;
	file << "   ~  \\\\ //  ~" << std::endl;
	file << "_- -   | | _- _" << std::endl;
	file << "  _ -  | |   -_" << std::endl;
	file << "      // \\\\" << std::endl;
	file << std::endl;
	file << "     /~~~~~\\" << std::endl;
	file << "  /~~       ~~\\" << std::endl;
	file << " {             }" << std::endl;
	file << "  \\  _-   -_  /" << std::endl;
	file << "    ~  \\ /  ~" << std::endl;
	file << "  _-   | |   -_" << std::endl;
	file << " _ -   | |    -_" << std::endl;
	file << "      // \\\\" << std::endl;
	file << std::endl;
	file << "        ||" << std::endl;
	file << "        ||" << std::endl;
	file << "        ||" << std::endl;
	file << "   ============" << std::endl;
	
	file.close();
}

const char* ShrubberyCreationForm::FileCreationException::what() const throw() {
	return "Could not create shrubbery file!";
}


