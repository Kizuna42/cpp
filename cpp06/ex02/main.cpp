#include "Base.hpp"

#include <iostream>

static void identifyBoth(const char* label, Base& value)
{
	std::cout << "Testing " << label << " instance:" << std::endl;
	identify(&value);
	identify(value);
}

int main(void)
{
	A a;
	B b;
	C c;
	identifyBoth("A", a);
	identifyBoth("B", b);
	identifyBoth("C", c);

	for (int i = 0; i < 6; i++) {
		Base* generated = generate();
		identify(generated);
		identify(*generated);
		delete generated;
	}
	identify(static_cast<Base*>(NULL));
	return 0;
}
