#include "Span.hpp"

#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main(void)
{
	Span subject(5);
	subject.addNumber(6);
	subject.addNumber(3);
	subject.addNumber(17);
	subject.addNumber(9);
	subject.addNumber(11);
	std::cout << subject.shortestSpan() << std::endl;
	std::cout << subject.longestSpan() << std::endl;

	std::vector<int> values;
	for (int i = 0; i < 10000; i++)
		values.push_back(i * 2);
	Span large(10000);
	large.addRange(values.begin(), values.end());
	std::cout << "10000 spans: " << large.shortestSpan()
		<< " " << large.longestSpan() << std::endl;

	std::istringstream input("10 20 30");
	std::istream_iterator<int> begin(input);
	std::istream_iterator<int> end;
	Span singlePass(3);
	singlePass.addRange(begin, end);
	std::cout << "Input spans: " << singlePass.shortestSpan()
		<< " " << singlePass.longestSpan() << std::endl;

	try {
		subject.addNumber(99);
	} catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
	}
	try {
		Span empty(1);
		empty.shortestSpan();
	} catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
	}
	return 0;
}
