#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <exception>
#include <string>
#include <vector>

class PmergeMe {
private:
	std::vector<std::string> _tokens;
	std::vector<int> _vectorData;
	std::deque<int> _dequeData;
	double _vectorTimeUs;
	double _dequeTimeUs;

	void fordJohnsonVector(const std::vector<int>& values,
		std::vector<size_t>& order);
	size_t upperBoundVector(const std::vector<int>& values,
		const std::vector<size_t>& chain, size_t end, int value) const;
	std::vector<size_t> jacobsthalOrderVector(size_t pendCount) const;

	void fordJohnsonDeque(const std::deque<int>& values,
		std::deque<size_t>& order);
	size_t upperBoundDeque(const std::deque<int>& values,
		const std::deque<size_t>& chain, size_t end, int value) const;
	std::deque<size_t> jacobsthalOrderDeque(size_t pendCount) const;

	bool isValidNumber(const std::string& str) const;
	int stringToInt(const std::string& str) const;

public:
	PmergeMe(void);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe(void);

	void parseInput(int argc, char** argv);
	void sortVector(void);
	void sortDeque(void);
	void displayBefore(void) const;
	void displayAfter(void) const;
	void displayTiming(void) const;

	class InvalidInputException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
