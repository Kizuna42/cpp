#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <deque>
#include <stack>

template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;

	MutantStack(void) : std::stack<T, Container>() {}
	MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {}

	MutantStack& operator=(const MutantStack& other) {
		if (this != &other)
			std::stack<T, Container>::operator=(other);
		return *this;
	}

	virtual ~MutantStack(void) {}

	iterator begin(void) { return this->c.begin(); }
	iterator end(void) { return this->c.end(); }
	const_iterator begin(void) const { return this->c.begin(); }
	const_iterator end(void) const { return this->c.end(); }
};

#endif
