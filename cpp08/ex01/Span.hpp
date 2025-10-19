#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <numeric>
#include <climits>

class Span {
private:
	unsigned int _maxSize;
	std::vector<int> _numbers;

public:
	// Orthodox Canonical Form
	Span(void);
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span(void);
	
	// Main functionality
	void addNumber(int number);
	int shortestSpan(void) const;
	int longestSpan(void) const;
	
	// Utility functions
	unsigned int size(void) const;
	unsigned int maxSize(void) const;
	bool empty(void) const;
	bool full(void) const;
	void display(void) const;
	
	// Range addition (bonus functionality)
	template<typename Iterator>
	void addRange(Iterator begin, Iterator end) {
		size_t rangeSize = std::distance(begin, end);
		if (_numbers.size() + rangeSize > _maxSize) {
			throw std::overflow_error("Adding range would exceed maximum capacity");
		}
		
		_numbers.insert(_numbers.end(), begin, end);
	}
	
	// Exception classes
	class SpanFullException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	
	class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif




