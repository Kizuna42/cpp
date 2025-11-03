#include "PmergeMe.hpp"

// Constructors
PmergeMe::PmergeMe(void) : _vectorTime(0), _dequeTime(0) {
	std::cout << "PmergeMe: Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other) 
	: _vectorData(other._vectorData), _dequeData(other._dequeData),
	  _vectorTime(other._vectorTime), _dequeTime(other._dequeTime) {
	std::cout << "PmergeMe: Copy constructor called" << std::endl;
}

// Assignment operator
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	std::cout << "PmergeMe: Assignment operator called" << std::endl;
	if (this != &other) {
		_vectorData = other._vectorData;
		_dequeData = other._dequeData;
		_vectorTime = other._vectorTime;
		_dequeTime = other._dequeTime;
	}
	return *this;
}

// Destructor
PmergeMe::~PmergeMe(void) {
	std::cout << "PmergeMe: Destructor called" << std::endl;
}

// Utility functions
bool PmergeMe::isValidNumber(const std::string& str) const {
	if (str.empty()) {
		return false;
	}
	
	size_t start = 0;
	if (str[0] == '+') {
		start = 1;
		if (str.length() == 1) {
			return false;
		}
	}
	
	for (size_t i = start; i < str.length(); i++) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}
	
	return true;
}

int PmergeMe::stringToInt(const std::string& str) const {
	std::istringstream iss(str);
	int value;
	iss >> value;
	if (iss.fail() || !iss.eof()) {
		throw InvalidInputException("Invalid number format: " + str);
	}
	if (value < 0) {
		throw InvalidInputException("Negative numbers not allowed: " + str);
	}
	return value;
}

double PmergeMe::clockToMilliseconds(clock_t clocks) const {
	return (static_cast<double>(clocks) / CLOCKS_PER_SEC) * 1000.0;
}

void PmergeMe::displayContainer(const std::vector<int>& container, const std::string& name) const {
	std::cout << name << ": ";
	for (size_t i = 0; i < container.size() && i < 10; i++) {
		std::cout << container[i] << " ";
	}
	if (container.size() > 10) {
		std::cout << "[...]";
	}
	std::cout << std::endl;
}

void PmergeMe::displayContainer(const std::deque<int>& container, const std::string& name) const {
	std::cout << name << ": ";
	for (size_t i = 0; i < container.size() && i < 10; i++) {
		std::cout << container[i] << " ";
	}
	if (container.size() > 10) {
		std::cout << "[...]";
	}
	std::cout << std::endl;
}

// Vector sorting algorithms
void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;
		
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right) {
	std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
	std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
	
	size_t i = 0, j = 0;
	int k = left;
	
	while (i < leftArr.size() && j < rightArr.size()) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			i++;
		} else {
			arr[k] = rightArr[j];
			j++;
		}
		k++;
	}
	
	while (i < leftArr.size()) {
		arr[k] = leftArr[i];
		i++;
		k++;
	}
	
	while (j < rightArr.size()) {
		arr[k] = rightArr[j];
		j++;
		k++;
	}
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& arr, int left, int right) {
	if (left < right) {
		// Use insertion sort for small arrays
		if (right - left + 1 <= 10) {
			insertionSortVector(arr, left, right);
		} else {
			int mid = left + (right - left) / 2;
			
			mergeInsertSortVector(arr, left, mid);
			mergeInsertSortVector(arr, mid + 1, right);
			
			mergeVector(arr, left, mid, right);
		}
	}
}

// Deque sorting algorithms
void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;
		
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right) {
	std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
	std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
	
	size_t i = 0, j = 0;
	int k = left;
	
	while (i < leftArr.size() && j < rightArr.size()) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			i++;
		} else {
			arr[k] = rightArr[j];
			j++;
		}
		k++;
	}
	
	while (i < leftArr.size()) {
		arr[k] = leftArr[i];
		i++;
		k++;
	}
	
	while (j < rightArr.size()) {
		arr[k] = rightArr[j];
		j++;
		k++;
	}
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr, int left, int right) {
	if (left < right) {
		// Use insertion sort for small arrays
		if (right - left + 1 <= 10) {
			insertionSortDeque(arr, left, right);
		} else {
			int mid = left + (right - left) / 2;
			
			mergeInsertSortDeque(arr, left, mid);
			mergeInsertSortDeque(arr, mid + 1, right);
			
			mergeDeque(arr, left, mid, right);
		}
	}
}

// Main functionality
void PmergeMe::parseInput(int argc, char** argv) {
	if (argc < 2) {
		throw InvalidInputException("No input provided");
	}
	
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		
		if (!isValidNumber(arg)) {
			throw InvalidInputException("Invalid number: " + arg);
		}
		
		int value = stringToInt(arg);
		_vectorData.push_back(value);
		_dequeData.push_back(value);
	}
	
	std::cout << "Parsed " << _vectorData.size() << " numbers successfully" << std::endl;
}

void PmergeMe::sortVector(void) {
	if (_vectorData.empty()) {
		throw EmptyContainerException();
	}
	
	clock_t start = clock();
	mergeInsertSortVector(_vectorData, 0, _vectorData.size() - 1);
	clock_t end = clock();
	
	_vectorTime = end - start;
}

void PmergeMe::sortDeque(void) {
	if (_dequeData.empty()) {
		throw EmptyContainerException();
	}
	
	clock_t start = clock();
	mergeInsertSortDeque(_dequeData, 0, _dequeData.size() - 1);
	clock_t end = clock();
	
	_dequeTime = end - start;
}

void PmergeMe::displayResults(void) const {
	displayContainer(_vectorData, "After (vector)");
	displayContainer(_dequeData, "After (deque)");
}

void PmergeMe::displayTiming(void) const {
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vectorData.size() 
			  << " elements with std::vector : " << clockToMilliseconds(_vectorTime) << " ms" << std::endl;
	std::cout << "Time to process a range of " << _dequeData.size() 
			  << " elements with std::deque  : " << clockToMilliseconds(_dequeTime) << " ms" << std::endl;
}

// Utility functions
size_t PmergeMe::getSize(void) const {
	return _vectorData.size();
}

bool PmergeMe::isEmpty(void) const {
	return _vectorData.empty();
}

bool PmergeMe::isSorted(void) const {
	for (size_t i = 1; i < _vectorData.size(); i++) {
		if (_vectorData[i - 1] > _vectorData[i]) {
			return false;
		}
	}
	return true;
}




