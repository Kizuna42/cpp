#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>
#include <cstddef>

template<typename T>
class Array {
private:
    T* _elements;
    size_t _size;

public:
    /*
     * Orthodox Canonical Form for template class
     */
    
    // Default constructor: creates empty array
    Array(void) : _elements(NULL), _size(0) {
        std::cout << "Array: Default constructor called (size 0)" << std::endl;
    }
    
    // Constructor with size
    Array(unsigned int n) : _elements(NULL), _size(n) {
        std::cout << "Array: Constructor with size " << n << " called" << std::endl;
        if (n > 0) {
            _elements = new T[n];
            // Initialize elements using default constructor
            for (size_t i = 0; i < _size; i++) {
                _elements[i] = T();
            }
        }
    }
    
    // Copy constructor
    Array(const Array& other) : _elements(NULL), _size(other._size) {
        std::cout << "Array: Copy constructor called (size " << _size << ")" << std::endl;
        if (_size > 0) {
            _elements = new T[_size];
            for (size_t i = 0; i < _size; i++) {
                _elements[i] = other._elements[i];
            }
        }
    }
    
    // Assignment operator
    Array& operator=(const Array& other) {
        std::cout << "Array: Assignment operator called" << std::endl;
        if (this != &other) {
            // Delete old array
            delete[] _elements;
            
            // Copy new size and allocate new array
            _size = other._size;
            if (_size > 0) {
                _elements = new T[_size];
                for (size_t i = 0; i < _size; i++) {
                    _elements[i] = other._elements[i];
                }
            } else {
                _elements = NULL;
            }
        }
        return *this;
    }
    
    // Destructor
    ~Array(void) {
        std::cout << "Array: Destructor called (size " << _size << ")" << std::endl;
        delete[] _elements;
    }
    
    /*
     * Member functions
     */
    
    // Subscript operator for element access
    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Array index out of bounds");
        }
        return _elements[index];
    }
    
    // Const subscript operator
    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Array index out of bounds");
        }
        return _elements[index];
    }
    
    // Size getter
    size_t size(void) const {
        return _size;
    }
    
    /*
     * Utility functions for testing
     */
    
    // Fill array with a specific value
    void fill(const T& value) {
        for (size_t i = 0; i < _size; i++) {
            _elements[i] = value;
        }
    }
    
    // Display array contents
    void display(void) const {
        std::cout << "Array[" << _size << "]: {";
        for (size_t i = 0; i < _size; i++) {
            std::cout << _elements[i];
            if (i < _size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;
    }
};

#endif




