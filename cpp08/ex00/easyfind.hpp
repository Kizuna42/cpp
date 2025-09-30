#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <exception>

/*
 * Exception class for when element is not found
 */
class NotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Element not found in container";
    }
};

/*
 * easyfind: Template function to find an element in any STL container
 * Uses std::find algorithm to search for the first occurrence of 'value'
 * Returns an iterator to the found element, throws exception if not found
 */
template<typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    
    if (it == container.end()) {
        throw NotFoundException();
    }
    
    return it;
}

/*
 * Const version of easyfind for const containers
 */
template<typename T>
typename T::const_iterator easyfind(const T& container, int value) {
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    
    if (it == container.end()) {
        throw NotFoundException();
    }
    
    return it;
}

#endif




