#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class Array {
private:
	T* _elements;
	size_t _size;

	void swap(Array& other) {
		T* elements = _elements;
		size_t size = _size;

		_elements = other._elements;
		_size = other._size;
		other._elements = elements;
		other._size = size;
	}

public:
	Array(void) : _elements(NULL), _size(0) {
	}
	
	Array(unsigned int n) : _elements(NULL), _size(0) {
		if (n > 0) {
			_elements = new T[n]();
		}
		_size = n;
	}
	
	Array(const Array& other) : _elements(NULL), _size(0) {
		if (other._size > 0) {
			T* elements = new T[other._size];
			try {
				for (size_t i = 0; i < other._size; i++) {
					elements[i] = other._elements[i];
				}
			} catch (...) {
				delete[] elements;
				throw;
			}
			_elements = elements;
		}
		_size = other._size;
	}
	
	Array& operator=(const Array& other) {
		if (this != &other) {
			Array copy(other);
			swap(copy);
		}
		return *this;
	}
	
	~Array(void) {
		delete[] _elements;
	}
	
	T& operator[](size_t index) {
		if (index >= _size) {
			throw std::out_of_range("Array index out of bounds");
		}
		return _elements[index];
	}
	
	const T& operator[](size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("Array index out of bounds");
		}
		return _elements[index];
	}
	
	size_t size(void) const {
		return _size;
	}
};

#endif

