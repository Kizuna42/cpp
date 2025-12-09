#include "PmergeMe.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	try {
		PmergeMe sorter;
		sorter.parseInput(argc, argv);
		
		if (sorter.isEmpty()) {
			std::cerr << "Error" << std::endl;
			return 1;
		}
		
		// Display original data
		std::cout << "Before: ";
		const std::vector<int>& original = sorter.getVectorData();
		for (size_t i = 0; i < original.size() && i < 10; i++) {
			std::cout << original[i] << " ";
		}
		if (original.size() > 10) {
			std::cout << "[...]";
		}
		std::cout << std::endl;
		
		// Sort using both containers
		sorter.sortVector();
		sorter.sortDeque();
		
		// Display results
		sorter.displayResults();
		
		// Display timing information
		sorter.displayTiming();
		
	} catch (const std::exception& e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}




