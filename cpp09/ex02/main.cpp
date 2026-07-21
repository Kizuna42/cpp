#include "PmergeMe.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try {
		PmergeMe sorter;
		sorter.parseInput(argc, argv);
		sorter.displayBefore();
		sorter.sortVector();
		sorter.sortDeque();
		sorter.displayAfter();
		sorter.displayTiming();
	} catch (const std::exception&) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
