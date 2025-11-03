#include "Span.hpp"

// Constructors
Span::Span(void) : _maxSize(0) {
	std::cout << "Span: Default constructor called (maxSize: 0)" << std::endl;
}

Span::Span(unsigned int n) : _maxSize(n) {
	std::cout << "Span: Constructor called (maxSize: " << n << ")" << std::endl;
	_numbers.reserve(n);  // Reserve memory for efficiency
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {
	std::cout << "Span: Copy constructor called" << std::endl;
}

// Assignment operator
Span& Span::operator=(const Span& other) {
	std::cout << "Span: Assignment operator called" << std::endl;
	if (this != &other) {
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

// Destructor
Span::~Span(void) {
	std::cout << "Span: Destructor called" << std::endl;
}

// Main functionality
void Span::addNumber(int number) {
	if (_numbers.size() >= _maxSize) {
		throw SpanFullException();
	}
	_numbers.push_back(number);
	std::cout << "Added number " << number << " to span (size: " << _numbers.size() << "/" << _maxSize << ")" << std::endl;
}

int Span::shortestSpan(void) const {
	if (_numbers.size() < 2) {
		throw NoSpanException();
	}
	
	// Create a sorted copy of the vector
	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());
	
	int minSpan = INT_MAX;
	
	// Find minimum difference between adjacent elements in sorted array
	for (size_t i = 0; i < sorted.size() - 1; i++) {
		int span = sorted[i + 1] - sorted[i];
		if (span < minSpan) {
			minSpan = span;
		}
	}
	
	return minSpan;
}

int Span::longestSpan(void) const {
	if (_numbers.size() < 2) {
		throw NoSpanException();
	}
	
	// Find min and max elements
	std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
	
	return *maxIt - *minIt;
}

// Utility functions
unsigned int Span::size(void) const {
	return _numbers.size();
}

unsigned int Span::maxSize(void) const {
	return _maxSize;
}

bool Span::empty(void) const {
	return _numbers.empty();
}

bool Span::full(void) const {
	return _numbers.size() >= _maxSize;
}

void Span::display(void) const {
	std::cout << "Span[" << _numbers.size() << "/" << _maxSize << "]: {";
	for (size_t i = 0; i < _numbers.size(); i++) {
		std::cout << _numbers[i];
		if (i < _numbers.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "}" << std::endl;
}

// Exception implementations
const char* Span::SpanFullException::what() const throw() {
	return "Span is full - cannot add more numbers";
}

const char* Span::NoSpanException::what() const throw() {
	return "Cannot calculate span - need at least 2 numbers";
}




