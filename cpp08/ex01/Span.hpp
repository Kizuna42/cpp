#ifndef SPAN_HPP
#define SPAN_HPP

#include <exception>
#include <stdexcept>
#include <vector>

class Span {
private:
	unsigned int _maxSize;
	std::vector<int> _numbers;

public:
	Span(void);
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span(void);
	
	void addNumber(int number);
	unsigned int shortestSpan(void) const;
	unsigned int longestSpan(void) const;
	
	template<typename Iterator>
	void addRange(Iterator begin, Iterator end) {
		std::vector<int> values(begin, end);
		if (values.size() > static_cast<size_t>(_maxSize) - _numbers.size()) {
			throw std::overflow_error("Adding range would exceed maximum capacity");
		}
		
		_numbers.insert(_numbers.end(), values.begin(), values.end());
	}
	
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


