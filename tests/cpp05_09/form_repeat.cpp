#include "Bureaucrat.hpp"
#include "Form.hpp"

#include <iostream>

int main()
{
	Bureaucrat signer("Signer", 1);
	Form form("Repeat", 1, 1);

	try {
		form.beSigned(signer);
		form.beSigned(signer);
		std::cout << "repeat=ok" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "repeat=" << e.what() << std::endl;
	}
	return 0;
}
