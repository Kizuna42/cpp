#include "easyfind.hpp"

#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main(void)
{
	std::vector<int> values;
	values.push_back(5);
	values.push_back(3);
	values.push_back(5);
	std::vector<int>::iterator found = easyfind(values, 5);
	std::cout << "Found first occurrence of 5 at position: "
		<< std::distance(values.begin(), found) << std::endl;

	std::list<int> linked;
	linked.push_back(10);
	linked.push_back(20);
	linked.push_back(30);
	std::cout << "List value: " << *easyfind(linked, 30) << std::endl;

	std::deque<int> queued;
	queued.push_back(1);
	queued.push_back(2);
	const std::deque<int> immutable(queued);
	std::cout << "Const deque value: " << *easyfind(immutable, 1) << std::endl;

	try {
		easyfind(values, 99);
	} catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
	}
	return 0;
}
