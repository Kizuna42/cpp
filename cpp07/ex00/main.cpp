#include "whatever.hpp"

#include <iostream>
#include <string>

int main(void)
{
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	int first = 42;
	int second = 42;
	std::cout << "equal min returns second: "
		<< (&::min(first, second) == &second ? "yes" : "no") << std::endl;
	std::cout << "equal max returns second: "
		<< (&::max(first, second) == &second ? "yes" : "no") << std::endl;
	return 0;
}
