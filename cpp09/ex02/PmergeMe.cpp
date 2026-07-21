#include "PmergeMe.hpp"

#include <cctype>
#include <climits>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sys/time.h>

PmergeMe::PmergeMe(void)
	: _vectorTimeUs(0.0), _dequeTimeUs(0.0) {
}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _tokens(other._tokens), _vectorData(other._vectorData),
	  _dequeData(other._dequeData), _vectorTimeUs(other._vectorTimeUs),
	  _dequeTimeUs(other._dequeTimeUs) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_tokens = other._tokens;
		_vectorData = other._vectorData;
		_dequeData = other._dequeData;
		_vectorTimeUs = other._vectorTimeUs;
		_dequeTimeUs = other._dequeTimeUs;
	}
	return *this;
}

PmergeMe::~PmergeMe(void) {
}

bool PmergeMe::isValidNumber(const std::string& str) const {
	if (str.empty())
		return false;
	size_t start = 0;
	if (str[0] == '+') {
		start = 1;
		if (str.length() == 1)
			return false;
	}
	unsigned long value = 0;
	for (size_t i = start; i < str.length(); i++) {
		unsigned char character = static_cast<unsigned char>(str[i]);
		if (!std::isdigit(character))
			return false;
		unsigned long digit = static_cast<unsigned long>(str[i] - '0');
		if (value > (static_cast<unsigned long>(INT_MAX) - digit) / 10)
			return false;
		value = value * 10 + digit;
	}
	return value > 0;
}

int PmergeMe::stringToInt(const std::string& str) const {
	std::istringstream stream(str);
	int value;
	stream >> value;
	if (stream.fail() || !stream.eof() || value <= 0)
		throw InvalidInputException();
	return value;
}

size_t PmergeMe::upperBoundVector(const std::vector<int>& values,
	const std::vector<size_t>& chain, size_t end, int value) const {
	size_t lo = 0;
	size_t hi = end;
	while (lo < hi) {
		size_t mid = lo + (hi - lo) / 2;
		if (values[chain[mid]] <= value)
			lo = mid + 1;
		else
			hi = mid;
	}
	return lo;
}

std::vector<size_t> PmergeMe::jacobsthalOrderVector(
	size_t pendCount) const {
	std::vector<size_t> result;
	if (pendCount == 0)
		return result;
	size_t prev = 1;
	size_t cur = 3;
	while (result.size() < pendCount) {
		size_t upper = cur;
		if (upper > pendCount + 1)
			upper = pendCount + 1;
		for (size_t b = upper; b > prev; b--)
			result.push_back(b - 1);
		size_t next = cur + 2 * prev;
		prev = cur;
		cur = next;
	}
	return result;
}

void PmergeMe::fordJohnsonVector(const std::vector<int>& values,
	std::vector<size_t>& order) {
	size_t n = order.size();
	if (n < 2)
		return;
	bool hasStraggler = (n % 2 != 0);
	size_t stragglerIdx = hasStraggler ? order[n - 1] : 0;

	std::vector<size_t> winners;
	std::vector<size_t> partnerOf(values.size(), 0);
	winners.reserve(n / 2);
	for (size_t i = 0; i + 1 < n; i += 2) {
		size_t a = order[i];
		size_t b = order[i + 1];
		if (values[a] < values[b]) {
			size_t tmp = a;
			a = b;
			b = tmp;
		}
		winners.push_back(a);
		partnerOf[a] = b;
	}

	fordJohnsonVector(values, winners);

	std::vector<size_t> chain;
	chain.reserve(n);
	chain.push_back(partnerOf[winners[0]]);
	for (size_t i = 0; i < winners.size(); i++)
		chain.push_back(winners[i]);

	std::vector<size_t> winnerPos(winners.size());
	for (size_t i = 0; i < winners.size(); i++)
		winnerPos[i] = i + 1;

	size_t pendCount = winners.size() - 1;
	if (hasStraggler)
		pendCount++;
	std::vector<size_t> jacobs = jacobsthalOrderVector(pendCount);
	for (size_t t = 0; t < jacobs.size(); t++) {
		size_t winnerIndex = jacobs[t];
		size_t loser;
		size_t limit;
		if (winnerIndex == winners.size()) {
			loser = stragglerIdx;
			limit = chain.size();
		} else {
			loser = partnerOf[winners[winnerIndex]];
			limit = winnerPos[winnerIndex];
		}
		size_t pos = upperBoundVector(values, chain, limit, values[loser]);
		chain.insert(chain.begin() + pos, loser);
		for (size_t i = 0; i < winnerPos.size(); i++) {
			if (winnerPos[i] >= pos)
				winnerPos[i]++;
		}
	}

	order.swap(chain);
}

size_t PmergeMe::upperBoundDeque(const std::deque<int>& values,
	const std::deque<size_t>& chain, size_t end, int value) const {
	size_t lo = 0;
	size_t hi = end;
	while (lo < hi) {
		size_t mid = lo + (hi - lo) / 2;
		if (values[chain[mid]] <= value)
			lo = mid + 1;
		else
			hi = mid;
	}
	return lo;
}

std::deque<size_t> PmergeMe::jacobsthalOrderDeque(size_t pendCount) const {
	std::deque<size_t> result;
	if (pendCount == 0)
		return result;
	size_t prev = 1;
	size_t cur = 3;
	while (result.size() < pendCount) {
		size_t upper = cur;
		if (upper > pendCount + 1)
			upper = pendCount + 1;
		for (size_t b = upper; b > prev; b--)
			result.push_back(b - 1);
		size_t next = cur + 2 * prev;
		prev = cur;
		cur = next;
	}
	return result;
}

void PmergeMe::fordJohnsonDeque(const std::deque<int>& values,
	std::deque<size_t>& order) {
	size_t n = order.size();
	if (n < 2)
		return;
	bool hasStraggler = (n % 2 != 0);
	size_t stragglerIdx = hasStraggler ? order[n - 1] : 0;

	std::deque<size_t> winners;
	std::deque<size_t> partnerOf(values.size(), 0);
	for (size_t i = 0; i + 1 < n; i += 2) {
		size_t a = order[i];
		size_t b = order[i + 1];
		if (values[a] < values[b]) {
			size_t tmp = a;
			a = b;
			b = tmp;
		}
		winners.push_back(a);
		partnerOf[a] = b;
	}

	fordJohnsonDeque(values, winners);

	std::deque<size_t> chain;
	chain.push_back(partnerOf[winners[0]]);
	for (size_t i = 0; i < winners.size(); i++)
		chain.push_back(winners[i]);

	std::deque<size_t> winnerPos(winners.size());
	for (size_t i = 0; i < winners.size(); i++)
		winnerPos[i] = i + 1;

	size_t pendCount = winners.size() - 1;
	if (hasStraggler)
		pendCount++;
	std::deque<size_t> jacobs = jacobsthalOrderDeque(pendCount);
	for (size_t t = 0; t < jacobs.size(); t++) {
		size_t winnerIndex = jacobs[t];
		size_t loser;
		size_t limit;
		if (winnerIndex == winners.size()) {
			loser = stragglerIdx;
			limit = chain.size();
		} else {
			loser = partnerOf[winners[winnerIndex]];
			limit = winnerPos[winnerIndex];
		}
		size_t pos = upperBoundDeque(values, chain, limit, values[loser]);
		chain.insert(chain.begin() + pos, loser);
		for (size_t i = 0; i < winnerPos.size(); i++) {
			if (winnerPos[i] >= pos)
				winnerPos[i]++;
		}
	}

	order.swap(chain);
}

void PmergeMe::parseInput(int argc, char** argv) {
	std::vector<std::string> tokens;
	tokens.reserve(argc > 1 ? static_cast<size_t>(argc - 1) : 0);
	for (int i = 1; i < argc; i++) {
		std::string token(argv[i]);
		if (!isValidNumber(token))
			throw InvalidInputException();
		tokens.push_back(token);
	}
	_tokens.swap(tokens);
	_vectorData.clear();
	_dequeData.clear();
	_vectorTimeUs = 0.0;
	_dequeTimeUs = 0.0;
}

void PmergeMe::sortVector(void) {
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	_vectorData.clear();
	_vectorData.reserve(_tokens.size());
	for (size_t i = 0; i < _tokens.size(); i++)
		_vectorData.push_back(stringToInt(_tokens[i]));
	std::vector<size_t> order(_vectorData.size());
	for (size_t i = 0; i < order.size(); i++)
		order[i] = i;
	fordJohnsonVector(_vectorData, order);
	std::vector<int> sorted;
	sorted.reserve(order.size());
	for (size_t i = 0; i < order.size(); i++)
		sorted.push_back(_vectorData[order[i]]);
	_vectorData.swap(sorted);
	gettimeofday(&end, NULL);
	_vectorTimeUs = (end.tv_sec - start.tv_sec) * 1000000.0
		+ (end.tv_usec - start.tv_usec);
}

void PmergeMe::sortDeque(void) {
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	_dequeData.clear();
	for (size_t i = 0; i < _tokens.size(); i++)
		_dequeData.push_back(stringToInt(_tokens[i]));
	std::deque<size_t> order(_dequeData.size());
	for (size_t i = 0; i < order.size(); i++)
		order[i] = i;
	fordJohnsonDeque(_dequeData, order);
	std::deque<int> sorted;
	for (size_t i = 0; i < order.size(); i++)
		sorted.push_back(_dequeData[order[i]]);
	_dequeData.swap(sorted);
	gettimeofday(&end, NULL);
	_dequeTimeUs = (end.tv_sec - start.tv_sec) * 1000000.0
		+ (end.tv_usec - start.tv_usec);
}

void PmergeMe::displayBefore(void) const {
	std::cout << "Before: ";
	for (size_t i = 0; i < _tokens.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _tokens[i];
	}
	std::cout << std::endl;
}

void PmergeMe::displayAfter(void) const {
	if (_vectorData.size() != _dequeData.size())
		throw InvalidInputException();
	for (size_t i = 0; i < _vectorData.size(); i++) {
		if (_vectorData[i] != _dequeData[i])
			throw InvalidInputException();
	}
	std::cout << "After:  ";
	for (size_t i = 0; i < _vectorData.size(); i++) {
		if (i != 0)
			std::cout << " ";
		std::cout << _vectorData[i];
	}
	std::cout << std::endl;
}

void PmergeMe::displayTiming(void) const {
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vectorData.size()
		<< " elements with std::vector : " << _vectorTimeUs << " us"
		<< std::endl;
	std::cout << "Time to process a range of " << _dequeData.size()
		<< " elements with std::deque  : " << _dequeTimeUs << " us"
		<< std::endl;
}

const char* PmergeMe::InvalidInputException::what() const throw() {
	return "Invalid input";
}
