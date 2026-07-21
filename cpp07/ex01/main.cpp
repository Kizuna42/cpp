#include "iter.hpp"

#include <iostream>

class Awesome
{
public:
	Awesome(void) : _value(42) {}
	int get(void) const { return _value; }

private:
	int _value;
};

std::ostream& operator<<(std::ostream& output, const Awesome& value)
{
	output << value.get();
	return output;
}

template<typename T>
void print(const T& value)
{
	std::cout << value << std::endl;
}

static void increment(int& value)
{
	value++;
}

int main(void)
{
	int values[] = {0, 1, 2, 3, 4};
	Awesome objects[5];
	::iter(values, 5, print<int>);
	::iter(objects, 5, print<Awesome>);
	::iter(values, 5, increment);
	const int immutable[] = {10, 20};
	::iter(immutable, 2, print<int>);
	::iter(values, 0, increment);
	return 0;
}
