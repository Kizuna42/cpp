#include "ShrubberyCreationForm.hpp"

// Constructors
ShrubberyCreationForm::ShrubberyCreationForm(void) 
	: AForm("Shrubbery Creation Form", SIGN_GRADE, EXEC_GRADE), _target("default") {
	std::cout << "Default ShrubberyCreationForm created for target: " << _target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) 
	: AForm("Shrubbery Creation Form", SIGN_GRADE, EXEC_GRADE), _target(target) {
	std::cout << "ShrubberyCreationForm created for target: " << _target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) 
	: AForm(other), _target(other._target) {
	std::cout << "ShrubberyCreationForm copied for target: " << _target << std::endl;
}

// Assignment operator
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
		std::cout << "ShrubberyCreationForm assigned for target: " << _target << std::endl;
	}
	return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "ShrubberyCreationForm for target " << _target << " destroyed" << std::endl;
}

// Getters
const std::string& ShrubberyCreationForm::getTarget(void) const {
	return _target;
}

// Execute action implementation
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
	std::cout << "ASCII trees written to file: " << filename << std::endl;
}

// Exception implementations
const char* ShrubberyCreationForm::FileCreationException::what() const throw() {
	return "Could not create shrubbery file!";
}




