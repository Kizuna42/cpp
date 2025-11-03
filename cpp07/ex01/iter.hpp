#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <cstddef>

/*
 * iter: Template function that takes an array, its length, and a function
 * Calls the function on every element of the array
 * 
 * Parameters:
 * - array: Pointer to the array
 * - length: Length of the array
 * - func: Function to call on each element (can be function pointer or function object)
 */
template<typename T, typename F>
void iter(T* array, size_t length, F func) {
	if (array == NULL) {
		return;
	}
	
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

/*
 * Overload for const arrays
 */
template<typename T, typename F>
void iter(const T* array, size_t length, F func) {
	if (array == NULL) {
		return;
	}
	
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

// Some example functions to use with iter
template<typename T>
void printElement(const T& element) {
	std::cout << element << " ";
}

template<typename T>
void printElementWithIndex(const T& element) {
	static size_t index = 0;
	std::cout << "[" << index++ << "]: " << element << " ";
}

// Function to increment numeric values (for non-const arrays)
template<typename T>
void increment(T& element) {
	++element;
}

// Function to double numeric values (for non-const arrays)
template<typename T>
void doubleValue(T& element) {
	element *= 2;
}

// Function to print with newline
template<typename T>
void println(const T& element) {
	std::cout << element << std::endl;
}

#endif




