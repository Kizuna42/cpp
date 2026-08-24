#include "Array.hpp"

#include <iostream>
#include <string>

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

static void printStringArray(const char* label, const Array<std::string>& array)
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

	Array<int> defaults(3);
	printArray("Default initialization", defaults);

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

	Array<std::string> strings(2);
	strings[0] = "alpha";
	strings[1] = "beta";
	Array<std::string> stringCopy(strings);
	Array<std::string> stringAssigned;
	stringAssigned = strings;
	strings[0] = "changed";
	printStringArray("String original", strings);
	printStringArray("String copy", stringCopy);
	printStringArray("String assigned", stringAssigned);
	const Array<std::string>& readOnlyCopy = stringCopy;
	std::cout << "Const access: " << readOnlyCopy[0] << std::endl;
	try {
		readOnlyCopy[readOnlyCopy.size()];
	} catch (const std::exception& error) {
		std::cout << "Const bounds: " << error.what() << std::endl;
	}
	return 0;
}
