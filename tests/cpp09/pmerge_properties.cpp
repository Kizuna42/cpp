#include "PmergeMe.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

// The runner exposes private helpers and counts value comparisons in a
// temporary copy only. Submitted sources and public interfaces stay intact.
extern unsigned long auditComparisons;

static unsigned long comparisonBound(size_t count) {
	unsigned long total = 0;
	for (size_t k = 1; k <= count; ++k) {
		size_t power = 4;
		while (power < 3 * k) {
			power *= 2;
			++total;
		}
	}
	return total;
}

static unsigned long check(const std::vector<int>& data) {
	std::vector<int> expected(data);
	std::sort(expected.begin(), expected.end());
	PmergeMe sorter;
	std::vector<size_t> vectorOrder(data.size());
	std::deque<size_t> dequeOrder(data.size());
	for (size_t i = 0; i < data.size(); ++i)
		vectorOrder[i] = dequeOrder[i] = i;
	auditComparisons = 0;
	sorter.fordJohnsonVector(data, vectorOrder);
	unsigned long vectorCount = auditComparisons;
	std::deque<int> dequeData(data.begin(), data.end());
	auditComparisons = 0;
	sorter.fordJohnsonDeque(dequeData, dequeOrder);
	unsigned long dequeCount = auditComparisons;
	if (vectorCount != dequeCount || vectorCount > comparisonBound(data.size())) {
		std::cerr << "Comparison bound failed for n=" << data.size() << '\n';
		std::exit(1);
	}
	for (size_t i = 0; i < data.size(); ++i) {
		if (vectorOrder[i] >= data.size() || dequeOrder[i] >= data.size() ||
			data[vectorOrder[i]] != expected[i] ||
			dequeData[dequeOrder[i]] != expected[i]) {
			std::cerr << "Sort failed for n=" << data.size() << '\n';
			std::exit(1);
		}
	}
	return vectorCount;
}

int main(int argc, char** argv) {
	const size_t maxSize = argc >= 2 ? static_cast<size_t>(std::atoi(argv[1])) : 9;
	const size_t rounds = argc >= 3 ? static_cast<size_t>(std::atoi(argv[2])) : 1000;
	unsigned long total = 0;
	for (size_t n = 0; n <= maxSize; ++n) {
		std::vector<int> values(n);
		for (size_t i = 0; i < n; ++i)
			values[i] = static_cast<int>(i + 1);
		unsigned long worst = 0;
		do {
			unsigned long count = check(values);
			if (count > worst)
				worst = count;
			++total;
		} while (std::next_permutation(values.begin(), values.end()));
		if (worst != comparisonBound(n))
			return 1;
	}
	for (size_t n = 1; n <= maxSize; ++n) {
		unsigned long combinations = 1;
		for (size_t i = 0; i < n; ++i)
			combinations *= 3;
		for (unsigned long c = 0; c < combinations; ++c) {
			std::vector<int> values(n);
			unsigned long digits = c;
			for (size_t i = 0; i < n; ++i) {
				values[i] = static_cast<int>(digits % 3 + 1);
				digits /= 3;
			}
			check(values);
			++total;
		}
	}
	std::srand(428);
	for (size_t round = 0; round < rounds; ++round) {
		size_t n = round < (rounds < 300 ? 30 : 300) ? round :
			static_cast<size_t>(std::rand() % 3001);
		std::vector<int> values(n);
		for (size_t i = 0; i < n; ++i)
			values[i] = std::rand() % 100 + 1;
		if (round % 4 < 2)
			std::sort(values.begin(), values.end());
		if (round % 4 == 1)
			std::reverse(values.begin(), values.end());
		check(values);
		++total;
	}
	const size_t sizes[] = {3000, 3001, 10000};
	for (size_t j = 0; j < 3; ++j) {
		std::vector<int> values(sizes[j]);
		for (size_t i = 0; i < values.size(); ++i)
			values[i] = std::rand() % std::numeric_limits<int>::max() + 1;
		check(values);
		++total;
		std::fill(values.begin(), values.end(), std::numeric_limits<int>::max());
		check(values);
		++total;
	}
	std::cout << "PASS PmergeMe properties: " << total
		<< " cases, both containers, comparison bound\n";
}
