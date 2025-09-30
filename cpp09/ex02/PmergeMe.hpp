#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <exception>

class PmergeMe {
private:
    std::vector<int> _vectorData;
    std::deque<int> _dequeData;
    
    // Timing variables
    clock_t _vectorTime;
    clock_t _dequeTime;
    
    // Private helper functions for vector
    void mergeInsertSortVector(std::vector<int>& arr, int left, int right);
    void insertionSortVector(std::vector<int>& arr, int left, int right);
    void mergeVector(std::vector<int>& arr, int left, int mid, int right);
    
    // Private helper functions for deque
    void mergeInsertSortDeque(std::deque<int>& arr, int left, int right);
    void insertionSortDeque(std::deque<int>& arr, int left, int right);
    void mergeDeque(std::deque<int>& arr, int left, int mid, int right);
    
    // Utility functions
    bool isValidNumber(const std::string& str) const;
    int stringToInt(const std::string& str) const;
    void displayContainer(const std::vector<int>& container, const std::string& name) const;
    void displayContainer(const std::deque<int>& container, const std::string& name) const;
    double clockToMilliseconds(clock_t clocks) const;

public:
    // Orthodox Canonical Form
    PmergeMe(void);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe(void);
    
    // Main functionality
    void parseInput(int argc, char** argv);
    void sortVector(void);
    void sortDeque(void);
    void displayResults(void) const;
    void displayTiming(void) const;
    
    // Utility functions
    size_t getSize(void) const;
    bool isEmpty(void) const;
    bool isSorted(void) const;
    
    // Exception classes
    class InvalidInputException : public std::exception {
    private:
        std::string _message;
    public:
        InvalidInputException(const std::string& message) : _message(message) {}
        virtual ~InvalidInputException() throw() {}
        virtual const char* what() const throw() { return _message.c_str(); }
    };
    
    class EmptyContainerException : public std::exception {
    public:
        virtual const char* what() const throw() { return "Container is empty"; }
    };
};

#endif




