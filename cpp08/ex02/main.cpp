#include "MutantStack.hpp"

#include <iostream>
#include <vector>

int main(void)
{
	MutantStack<int> stack;
	stack.push(5);
	stack.push(17);
	std::cout << stack.top() << std::endl;
	stack.pop();
	std::cout << stack.size() << std::endl;
	stack.push(3);
	stack.push(5);
	stack.push(737);
	stack.push(0);
	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
		std::cout << *it << std::endl;
	std::stack<int> regular(stack);

	const MutantStack<int> immutable(stack);
	int sum = 0;
	for (MutantStack<int>::const_iterator it = immutable.begin();
		it != immutable.end(); ++it)
		sum += *it;
	std::cout << "Const sum: " << sum << std::endl;

	MutantStack<int> copied(stack);
	MutantStack<int> assigned;
	assigned = stack;
	stack.push(42);
	std::cout << "Copy top: " << copied.top()
		<< ", assigned top: " << assigned.top() << std::endl;

	MutantStack<int, std::vector<int> > vectorStack;
	vectorStack.push(10);
	vectorStack.push(20);
	std::cout << "Vector top: " << vectorStack.top() << std::endl;

	MutantStack<int> empty;
	std::cout << "Empty iterators equal: "
		<< (empty.begin() == empty.end() ? "yes" : "no") << std::endl;
	return regular.top() == 0 ? 0 : 1;
}
