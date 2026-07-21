#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Array.hpp"

#define MAX_VAL 750

int main()
{
	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	std::srand(std::time(NULL));
	for (int i = 0; i < MAX_VAL; i++) {
		const int value = std::rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}
	for (int i = 0; i < MAX_VAL; i++) {
		if (mirror[i] != numbers[i]) {
			delete [] mirror;
			return 1;
		}
	}
	try {
		numbers[-2] = 0;
		return 2;
	} catch (const std::exception&) {
	}
	try {
		numbers[MAX_VAL] = 0;
		return 3;
	} catch (const std::exception&) {
	}
	delete [] mirror;
	return 0;
}
