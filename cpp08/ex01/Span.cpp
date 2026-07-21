#include "Span.hpp"

#include <algorithm>
#include <climits>

Span::Span(void) : _maxSize(0) {
}

Span::Span(unsigned int n) : _maxSize(n) {
	_numbers.reserve(n);
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {
}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span(void) {
}

void Span::addNumber(int number) {
	if (_numbers.size() >= _maxSize) {
		throw SpanFullException();
	}
	_numbers.push_back(number);
}

unsigned int Span::shortestSpan(void) const {
	if (_numbers.size() < 2) {
		throw NoSpanException();
	}
	
	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());
	
	unsigned int minSpan = UINT_MAX;
	
	for (size_t i = 0; i < sorted.size() - 1; i++) {
		unsigned int span = static_cast<unsigned int>(sorted[i + 1])
			- static_cast<unsigned int>(sorted[i]);
		if (span < minSpan) {
			minSpan = span;
		}
	}
	
	return minSpan;
}

unsigned int Span::longestSpan(void) const {
	if (_numbers.size() < 2) {
		throw NoSpanException();
	}
	
	std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
	
	return static_cast<unsigned int>(*maxIt)
		- static_cast<unsigned int>(*minIt);
}

const char* Span::SpanFullException::what() const throw() {
	return "Span is full - cannot add more numbers";
}

const char* Span::NoSpanException::what() const throw() {
	return "Cannot calculate span - need at least 2 numbers";
}

