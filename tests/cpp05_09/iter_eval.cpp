#include "iter.hpp"

#include <iostream>

class Awesome
{
public:
	Awesome(void) : _n(42) {}
	int get(void) const { return _n; }

private:
	int _n;
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

int main()
{
	int values[] = {0, 1, 2, 3, 4};
	Awesome objects[5];

	iter(values, 5, print);
	iter(objects, 5, print);
	return 0;
}
