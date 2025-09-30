#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <set>

int main(void) {
    std::cout << "=== CPP08 ex00: Easy Find Algorithm ===" << std::endl;
    
    // Test 1: std::vector
    std::cout << "\n--- Test 1: std::vector ---" << std::endl;
    try {
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
        
        std::cout << "Vector contents: ";
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Search for existing element
        std::vector<int>::iterator found = easyfind(vec, 3);
        std::cout << "Found element 3 at position: " << std::distance(vec.begin(), found) << std::endl;
        std::cout << "Value at found position: " << *found << std::endl;
        
        // Search for non-existing element
        std::cout << "Searching for element 10..." << std::endl;
        easyfind(vec, 10);  // Should throw exception
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 2: std::list
    std::cout << "\n--- Test 2: std::list ---" << std::endl;
    try {
        std::list<int> lst;
        lst.push_back(10);
        lst.push_back(20);
        lst.push_back(30);
        lst.push_back(40);
        
        std::cout << "List contents: ";
        for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Search for existing element
        std::list<int>::iterator found = easyfind(lst, 20);
        std::cout << "Found element 20 in list" << std::endl;
        std::cout << "Value at found position: " << *found << std::endl;
        
        // Search for first element
        found = easyfind(lst, 10);
        std::cout << "Found element 10 (first element)" << std::endl;
        
        // Search for last element
        found = easyfind(lst, 40);
        std::cout << "Found element 40 (last element)" << std::endl;
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 3: std::deque
    std::cout << "\n--- Test 3: std::deque ---" << std::endl;
    try {
        std::deque<int> deq;
        deq.push_back(100);
        deq.push_front(50);
        deq.push_back(150);
        deq.push_front(25);
        
        std::cout << "Deque contents: ";
        for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Search for middle element
        std::deque<int>::iterator found = easyfind(deq, 100);
        std::cout << "Found element 100 at position: " << std::distance(deq.begin(), found) << std::endl;
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 4: Empty container
    std::cout << "\n--- Test 4: Empty container ---" << std::endl;
    try {
        std::vector<int> emptyVec;
        std::cout << "Searching in empty vector..." << std::endl;
        easyfind(emptyVec, 1);
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 5: Const container
    std::cout << "\n--- Test 5: Const container ---" << std::endl;
    try {
        std::vector<int> normalVec;
        normalVec.push_back(7);
        normalVec.push_back(14);
        normalVec.push_back(21);
        
        const std::vector<int> constVec(normalVec);
        
        std::cout << "Const vector contents: ";
        for (std::vector<int>::const_iterator it = constVec.begin(); it != constVec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::vector<int>::const_iterator found = easyfind(constVec, 14);
        std::cout << "Found element 14 in const vector" << std::endl;
        std::cout << "Value: " << *found << std::endl;
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 6: Large container
    std::cout << "\n--- Test 6: Large container ---" << std::endl;
    try {
        std::vector<int> largeVec;
        for (int i = 0; i < 1000; i++) {
            largeVec.push_back(i * 2);  // Even numbers 0, 2, 4, 6, ..., 1998
        }
        
        std::cout << "Large vector created with " << largeVec.size() << " elements" << std::endl;
        
        // Search for element in the middle
        std::vector<int>::iterator found = easyfind(largeVec, 1000);  // Should be at index 500
        std::cout << "Found element 1000 at position: " << std::distance(largeVec.begin(), found) << std::endl;
        
        // Search for odd number (should not be found)
        std::cout << "Searching for odd number 999..." << std::endl;
        easyfind(largeVec, 999);
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 7: Duplicate elements
    std::cout << "\n--- Test 7: Duplicate elements ---" << std::endl;
    try {
        std::vector<int> dupVec;
        dupVec.push_back(5);
        dupVec.push_back(3);
        dupVec.push_back(5);  // Duplicate
        dupVec.push_back(1);
        dupVec.push_back(5);  // Another duplicate
        
        std::cout << "Vector with duplicates: ";
        for (std::vector<int>::iterator it = dupVec.begin(); it != dupVec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // easyfind should return the first occurrence
        std::vector<int>::iterator found = easyfind(dupVec, 5);
        std::cout << "Found first occurrence of 5 at position: " << std::distance(dupVec.begin(), found) << std::endl;
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Test 8: Different container type - std::set
    std::cout << "\n--- Test 8: std::set ---" << std::endl;
    try {
        std::set<int> intSet;
        intSet.insert(15);
        intSet.insert(5);
        intSet.insert(25);
        intSet.insert(10);
        
        std::cout << "Set contents (sorted): ";
        for (std::set<int>::iterator it = intSet.begin(); it != intSet.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::set<int>::iterator found = easyfind(intSet, 10);
        std::cout << "Found element 10 in set" << std::endl;
        std::cout << "Value: " << *found << std::endl;
        
        // Try to find non-existing element
        std::cout << "Searching for element 30..." << std::endl;
        easyfind(intSet, 30);
        
    } catch (const NotFoundException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




