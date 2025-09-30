#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

/*
 * swap: Swaps the values of two given arguments
 * Template function that works with any type
 */
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

/*
 * min: Returns the smallest of the two values
 * If the two values are equal, returns the second one
 */
template<typename T>
const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

/*
 * max: Returns the greatest of the two values
 * If the two values are equal, returns the second one
 */
template<typename T>
const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#endif




