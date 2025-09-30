#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    std::cout << "=== CPP09 ex02: PmergeMe (Ford-Johnson Merge-Insert Sort) ===" << std::endl;
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <positive integers>" << std::endl;
        std::cout << "Example: " << argv[0] << " 3 5 9 7 4" << std::endl;
        std::cout << "Example: " << argv[0] << " `shuf -i 1-100000 -n 3000 | tr \"\\n\" \" \"`" << std::endl;
        return 1;
    }
    
    try {
        PmergeMe sorter;
        
        // Parse input
        std::cout << "\nParsing input..." << std::endl;
        sorter.parseInput(argc, argv);
        
        if (sorter.isEmpty()) {
            std::cout << "No valid numbers to sort" << std::endl;
            return 1;
        }
        
        // Display original data (limited to first 10 elements)
        std::cout << "\nBefore: ";
        for (int i = 1; i < argc && i <= 10; i++) {
            std::cout << argv[i] << " ";
        }
        if (argc > 11) {
            std::cout << "[...]";
        }
        std::cout << std::endl;
        
        // Check if already sorted
        if (sorter.isSorted()) {
            std::cout << "Data is already sorted!" << std::endl;
        }
        
        // Sort using both containers
        std::cout << "\nSorting with std::vector..." << std::endl;
        sorter.sortVector();
        
        std::cout << "Sorting with std::deque..." << std::endl;
        sorter.sortDeque();
        
        // Display results
        std::cout << "\nResults:" << std::endl;
        sorter.displayResults();
        
        // Verify sorting
        if (sorter.isSorted()) {
            std::cout << "✓ Data is correctly sorted!" << std::endl;
        } else {
            std::cout << "✗ Sorting failed!" << std::endl;
        }
        
        // Display timing information
        std::cout << "\nPerformance:" << std::endl;
        sorter.displayTiming();
        
    } catch (const PmergeMe::InvalidInputException& e) {
        std::cout << "Input Error: " << e.what() << std::endl;
        return 1;
    } catch (const PmergeMe::EmptyContainerException& e) {
        std::cout << "Container Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}




