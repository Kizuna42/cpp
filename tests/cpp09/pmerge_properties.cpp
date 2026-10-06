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

static size_t insertionCount(size_t count) {
	size_t total = 0;
	while (count >= 2) {
		total += (count + 1) / 2 - 1;
		count /= 2;
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
	PmergeMe::SortStats vectorStats;
	PmergeMe::SortStats dequeStats;
	auditComparisons = 0;
	sorter.fordJohnsonVector(data, vectorOrder, vectorStats);
	unsigned long vectorCount = auditComparisons;
	std::deque<int> dequeData(data.begin(), data.end());
	auditComparisons = 0;
	sorter.fordJohnsonDeque(dequeData, dequeOrder, dequeStats);
	unsigned long dequeCount = auditComparisons;
	if (vectorCount != dequeCount || vectorCount > comparisonBound(data.size()) ||
		vectorStats.comparisons != vectorCount || dequeStats.comparisons != dequeCount ||
		vectorStats.pairSwaps != dequeStats.pairSwaps ||
		vectorStats.pendInsertions != insertionCount(data.size()) ||
		dequeStats.pendInsertions != insertionCount(data.size())) {
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

static void requireStats(const PmergeMe::SortStats& stats,
	size_t comparisons, size_t swaps, size_t insertions) {
	if (stats.comparisons != comparisons || stats.pairSwaps != swaps ||
		stats.pendInsertions != insertions) {
		std::cerr << "Incorrect saved sort statistics\n";
		std::exit(1);
	}
}

static void requireState(const PmergeMe& actual, const PmergeMe& expected) {
	if (actual._tokens != expected._tokens || actual._vectorData != expected._vectorData ||
		actual._dequeData != expected._dequeData ||
		actual._vectorTimeUs != expected._vectorTimeUs ||
		actual._dequeTimeUs != expected._dequeTimeUs) {
		std::cerr << "Sort state changed unexpectedly\n";
		std::exit(1);
	}
	requireStats(actual._vectorStats, expected._vectorStats.comparisons,
		expected._vectorStats.pairSwaps, expected._vectorStats.pendInsertions);
	requireStats(actual._dequeStats, expected._dequeStats.comparisons,
		expected._dequeStats.pairSwaps, expected._dequeStats.pendInsertions);
}

static void checkLifecycle() {
	char name[] = "PmergeMe";
	char three[] = "3";
	char five[] = "5";
	char nine[] = "9";
	char seven[] = "7";
	char four[] = "4";
	char zero[] = "0";
	char* input[] = {name, three, five, nine, seven, four};
	PmergeMe sorter;
	requireStats(sorter._vectorStats, 0, 0, 0);
	requireStats(sorter._dequeStats, 0, 0, 0);
	sorter.parseInput(6, input);
	sorter.sortVector();
	requireStats(sorter._vectorStats, 7, 2, 2);
	requireStats(sorter._dequeStats, 0, 0, 0);
	sorter.sortDeque();
	requireStats(sorter._dequeStats, 7, 2, 2);
	sorter.sortVector();
	requireStats(sorter._vectorStats, 7, 2, 2);
	requireStats(sorter._dequeStats, 7, 2, 2);
	sorter.sortDeque();
	requireStats(sorter._vectorStats, 7, 2, 2);
	requireStats(sorter._dequeStats, 7, 2, 2);
	PmergeMe copied(sorter);
	PmergeMe assigned;
	assigned = sorter;
	requireState(copied, sorter);
	requireState(assigned, sorter);
	PmergeMe& alias = assigned;
	assigned = alias;
	requireState(assigned, sorter);
	char* invalid[] = {name, three, zero};
	try {
		sorter.parseInput(3, invalid);
		std::exit(1);
	} catch (const PmergeMe::InvalidInputException&) {
	}
	requireState(sorter, copied);
	char* single[] = {name, nine};
	sorter.parseInput(2, single);
	requireStats(sorter._vectorStats, 0, 0, 0);
	requireStats(sorter._dequeStats, 0, 0, 0);
	if (!sorter._vectorData.empty() || !sorter._dequeData.empty() ||
		sorter._vectorTimeUs != 0 || sorter._dequeTimeUs != 0)
		std::exit(1);
	sorter.sortDeque();
	sorter.sortVector();
	requireStats(sorter._vectorStats, 0, 0, 0);
	requireStats(sorter._dequeStats, 0, 0, 0);
	if (sorter._vectorData.size() != 1 || sorter._vectorData[0] != 9 ||
		sorter._dequeData.size() != 1 || sorter._dequeData[0] != 9)
		std::exit(1);
	requireState(copied, assigned);
}

int main(int argc, char** argv) {
	checkLifecycle();
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
		<< " cases, both containers, comparison bound, counters, lifecycle\n";
}
