#include "Base.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base(void) {}

Base* generate(void) {
	static bool initialized = false;
	if (!initialized) {
		std::srand(static_cast<unsigned int>(std::time(0)));
		initialized = true;
	}
	
	int random = std::rand() % 3;
	
	switch (random) {
		case 0:
			return new A();
		case 1:
			return new B();
		case 2:
			return new C();
	default:
			return NULL;
	}
}

void identify(Base* p) {
	if (p == NULL) {
		std::cout << "Unknown type" << std::endl;
		return;
	}
	
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	} else {
		std::cout << "Unknown type" << std::endl;
	}
}

void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return;
	} catch (...) {
	}

	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return;
	} catch (...) {
	}

	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return;
	} catch (...) {
	}

	std::cout << "Unknown type" << std::endl;
}

