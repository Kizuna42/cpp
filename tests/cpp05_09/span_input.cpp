#include "Span.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
	std::istringstream input("10 20 30");
	std::istream_iterator<int> begin(input);
	std::istream_iterator<int> end;
	Span span(3);
	span.addRange(begin, end);
	std::cout << span.shortestSpan() << " " << span.longestSpan() << std::endl;
	return 0;
}
