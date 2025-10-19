#include "Serializer.hpp"

// Data struct implementation
Data::Data(int v, const std::string& msg, double p, bool valid) 
	: value(v), message(msg), price(p), isValid(valid) {
}

void Data::display(void) const {
	std::cout << "Data {" << std::endl;
	std::cout << "  value: " << value << std::endl;
	std::cout << "  message: \"" << message << "\"" << std::endl;
	std::cout << "  price: " << price << std::endl;
	std::cout << "  isValid: " << (isValid ? "true" : "false") << std::endl;
	std::cout << "}" << std::endl;
}

bool Data::operator==(const Data& other) const {
	return (value == other.value && 
			message == other.message && 
			price == other.price && 
			isValid == other.isValid);
}

// Serializer class implementation
// Private constructor - cannot be instantiated
Serializer::Serializer(void) {}
Serializer::Serializer(const Serializer& other) { (void)other; }
Serializer& Serializer::operator=(const Serializer& other) { (void)other; return *this; }
Serializer::~Serializer(void) {}

// Serialization functions
uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}




