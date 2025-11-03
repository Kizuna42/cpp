#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>

/*
 * MutantStack: A stack that can be iterated
 * Inherits from std::stack and adds iterator functionality
 * Uses the underlying container's iterators to provide iteration
 */
template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
	// Type aliases for iterators using the underlying container
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;
	typedef typename Container::reverse_iterator reverse_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;
	
	/*
	 * Orthodox Canonical Form
	 */
	
	// Default constructor
	MutantStack(void) : std::stack<T, Container>() {
		std::cout << "MutantStack: Default constructor called" << std::endl;
	}
	
	// Copy constructor
	MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {
		std::cout << "MutantStack: Copy constructor called" << std::endl;
	}
	
	// Assignment operator
	MutantStack& operator=(const MutantStack& other) {
		std::cout << "MutantStack: Assignment operator called" << std::endl;
		if (this != &other) {
			std::stack<T, Container>::operator=(other);
		}
		return *this;
	}
	
	// Destructor
	virtual ~MutantStack(void) {
		std::cout << "MutantStack: Destructor called" << std::endl;
	}
	
	/*
	 * Iterator functions
	 * These provide access to the underlying container's iterators
	 */
	
	// Forward iterators
	iterator begin(void) {
		return this->c.begin();
	}
	
	iterator end(void) {
		return this->c.end();
	}
	
	const_iterator begin(void) const {
		return this->c.begin();
	}
	
	const_iterator end(void) const {
		return this->c.end();
	}
	
	// Reverse iterators
	reverse_iterator rbegin(void) {
		return this->c.rbegin();
	}
	
	reverse_iterator rend(void) {
		return this->c.rend();
	}
	
	const_reverse_iterator rbegin(void) const {
		return this->c.rbegin();
	}
	
	const_reverse_iterator rend(void) const {
		return this->c.rend();
	}
	
	/*
	 * Utility functions for testing
	 */
	
	// Get size (already available from std::stack, but for clarity)
	size_t size(void) const {
		return std::stack<T, Container>::size();
	}
	
	// Check if empty (already available from std::stack, but for clarity)
	bool empty(void) const {
		return std::stack<T, Container>::empty();
	}
	
	// Display stack contents (from bottom to top)
	void display(void) const {
		std::cout << "MutantStack[" << this->size() << "]: {";
		if (!this->empty()) {
			const_iterator it = this->begin();
			std::cout << *it;
			++it;
			for (; it != this->end(); ++it) {
				std::cout << ", " << *it;
			}
		}
		std::cout << "} (bottom -> top)" << std::endl;
	}
	
	// Display stack contents in reverse (from top to bottom)
	void displayReverse(void) const {
		std::cout << "MutantStack[" << this->size() << "]: {";
		if (!this->empty()) {
			const_reverse_iterator it = this->rbegin();
			std::cout << *it;
			++it;
			for (; it != this->rend(); ++it) {
				std::cout << ", " << *it;
			}
		}
		std::cout << "} (top -> bottom)" << std::endl;
	}
};

#endif




