#include "Array.hpp"

#include <exception>

class CopyFailure : public std::exception
{
};

class Throwing
{
private:
	static int _assignmentsBeforeThrow;
	int _value;

public:
	Throwing() : _value(0) {}
	Throwing(const Throwing& other) : _value(other._value) {}
	Throwing& operator=(const Throwing& other)
	{
		if (_assignmentsBeforeThrow == 0)
			throw CopyFailure();
		if (_assignmentsBeforeThrow > 0)
			_assignmentsBeforeThrow--;
		_value = other._value;
		return *this;
	}
	static void throwAfter(int assignments)
	{
		_assignmentsBeforeThrow = assignments;
	}
};

int Throwing::_assignmentsBeforeThrow = -1;

int main()
{
	Array<Throwing> source(3);
	Throwing::throwAfter(1);
	try {
		Array<Throwing> copy(source);
		return 1;
	} catch (const CopyFailure&) {
	}

	Array<Throwing> destination(1);
	Throwing::throwAfter(1);
	try {
		destination = source;
		return 2;
	} catch (const CopyFailure&) {
	}
	if (destination.size() != 1)
		return 3;
	return 0;
}
