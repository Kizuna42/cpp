#include "Span.hpp"

#include <climits>
#include <iostream>

int main()
{
	Span span(2);
	span.addNumber(INT_MIN);
	span.addNumber(INT_MAX);
	std::cout << span.shortestSpan() << std::endl;
	std::cout << span.longestSpan() << std::endl;
	return 0;
}
