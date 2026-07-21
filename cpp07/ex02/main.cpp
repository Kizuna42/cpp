#include "Array.hpp"

#include <iostream>

static void printArray(const char* label, const Array<int>& array)
{
	std::cout << label << ": Array[" << array.size() << "]: {";
	for (size_t i = 0; i < array.size(); i++) {
		if (i != 0)
			std::cout << ", ";
		std::cout << array[i];
	}
	std::cout << "}" << std::endl;
}

int main(void)
{
	Array<int> empty;
	std::cout << "Empty size: " << empty.size() << std::endl;

	Array<int> original(4);
	for (size_t i = 0; i < original.size(); i++)
		original[i] = static_cast<int>(i + 1);
	Array<int> copy(original);
	Array<int> assigned;
	assigned = original;
	original[0] = 99;
	printArray("Original", original);
	printArray("Copy", copy);
	printArray("Assigned", assigned);

	Array<int>& alias = original;
	original = alias;
	std::cout << "Self assignment: " << original[0] << std::endl;
	try {
		original[original.size()] = 0;
	} catch (const std::exception& error) {
		std::cout << "Bounds: " << error.what() << std::endl;
	}
	return 0;
}
