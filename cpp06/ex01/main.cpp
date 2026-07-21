#include "Serializer.hpp"

#include <iostream>

int main(void)
{
	Data data;
	data.value = 42;
	uintptr_t raw = Serializer::serialize(&data);
	Data* restored = Serializer::deserialize(raw);

	std::cout << "Pointers equal: "
		<< (restored == &data ? "PASS" : "FAIL") << std::endl;
	std::cout << "Value preserved: "
		<< (restored->value == 42 ? "PASS" : "FAIL") << std::endl;
	std::cout << "NULL preserved: "
		<< (Serializer::deserialize(Serializer::serialize(NULL)) == NULL
			? "PASS" : "FAIL") << std::endl;
	return restored == &data && restored->value == 42 ? 0 : 1;
}
