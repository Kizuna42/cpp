#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

class Base {
public:
	virtual ~Base(void);
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

// Function declarations
Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif




