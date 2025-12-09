#include "whatever.hpp"
#include <string>

class Awesome {
private:
	int _n;

public:
	Awesome(void) : _n(0) {}
	Awesome(int n) : _n(n) {}
	Awesome& operator=(const Awesome& other) {
		_n = other._n;
		return *this;
	}
	bool operator==(Awesome const& rhs) const { return _n == rhs._n; }
	bool operator!=(Awesome const& rhs) const { return _n != rhs._n; }
	bool operator>(Awesome const& rhs) const { return _n > rhs._n; }
	bool operator<(Awesome const& rhs) const { return _n < rhs._n; }
	bool operator>=(Awesome const& rhs) const { return _n >= rhs._n; }
	bool operator<=(Awesome const& rhs) const { return _n <= rhs._n; }
	int get_n() const { return _n; }
};

std::ostream& operator<<(std::ostream& o, const Awesome& a) {
	o << a.get_n();
	return o;
}

int main(void) {
	std::cout << "=== CPP07 ex00: Template Functions ===" << std::endl;
	
	// Test 1: Required test from subject
	std::cout << "\n--- Test 1: Subject required test ---" << std::endl;
	{
		int a = 2;
		int b = 3;
		
		std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
		
		std::string c = "chaine1";
		std::string d = "chaine2";
		
		std::cout << "\nBefore swap: c = " << c << ", d = " << d << std::endl;
		::swap(c, d);
		std::cout << "After swap: c = " << c << ", d = " << d << std::endl;
		std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
		std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
	}
	
	// Test 2: Integer types
	std::cout << "\n--- Test 2: Integer types ---" << std::endl;
	{
		int x = 42, y = 24;
		std::cout << "Before: x = " << x << ", y = " << y << std::endl;
		std::cout << "min(x, y) = " << ::min(x, y) << std::endl;
		std::cout << "max(x, y) = " << ::max(x, y) << std::endl;
		::swap(x, y);
		std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
	}
	
	// Test 3: Floating point types
	std::cout << "\n--- Test 3: Floating point types ---" << std::endl;
	{
		double pi = 3.14159, e = 2.71828;
		std::cout << "Before: pi = " << pi << ", e = " << e << std::endl;
		std::cout << "min(pi, e) = " << ::min(pi, e) << std::endl;
		std::cout << "max(pi, e) = " << ::max(pi, e) << std::endl;
		::swap(pi, e);
		std::cout << "After swap: pi = " << pi << ", e = " << e << std::endl;
	}
	
	// Test 4: Character types
	std::cout << "\n--- Test 4: Character types ---" << std::endl;
	{
		char first = 'A', second = 'Z';
		std::cout << "Before: first = '" << first << "', second = '" << second << "'" << std::endl;
		std::cout << "min(first, second) = '" << ::min(first, second) << "'" << std::endl;
		std::cout << "max(first, second) = '" << ::max(first, second) << "'" << std::endl;
		::swap(first, second);
		std::cout << "After swap: first = '" << first << "', second = '" << second << "'" << std::endl;
	}
	
	// Test 5: Equal values (test the "second value" rule)
	std::cout << "\n--- Test 5: Equal values ---" << std::endl;
	{
		int equal1 = 100, equal2 = 100;
		std::cout << "Both values are 100" << std::endl;
		std::cout << "min(equal1, equal2) returns address of: " << &::min(equal1, equal2) << std::endl;
		std::cout << "Address of equal1: " << &equal1 << std::endl;
		std::cout << "Address of equal2: " << &equal2 << std::endl;
		std::cout << "min returns second value: " << (&::min(equal1, equal2) == &equal2 ? "YES" : "NO") << std::endl;
		
		std::cout << "max(equal1, equal2) returns address of: " << &::max(equal1, equal2) << std::endl;
		std::cout << "max returns second value: " << (&::max(equal1, equal2) == &equal2 ? "YES" : "NO") << std::endl;
	}
	
	// Test 6: String comparison
	std::cout << "\n--- Test 6: String comparison ---" << std::endl;
	{
		std::string str1 = "apple";
		std::string str2 = "banana";
		std::string str3 = "cherry";
		
		std::cout << "Strings: \"" << str1 << "\", \"" << str2 << "\", \"" << str3 << "\"" << std::endl;
		std::cout << "min(str1, str2) = \"" << ::min(str1, str2) << "\"" << std::endl;
		std::cout << "max(str2, str3) = \"" << ::max(str2, str3) << "\"" << std::endl;
		std::cout << "min(str1, str3) = \"" << ::min(str1, str3) << "\"" << std::endl;
	}
	
	// Test 7: Template type deduction
	std::cout << "\n--- Test 7: Template type deduction ---" << std::endl;
	{
		// The compiler should deduce the types automatically
		std::cout << "Type deduction test:" << std::endl;
		std::cout << "min(5, 10) = " << ::min(5, 10) << std::endl;
		std::cout << "max(3.14, 2.71) = " << ::max(3.14, 2.71) << std::endl;
		std::cout << "min('x', 'y') = '" << ::min('x', 'y') << "'" << std::endl;
	}
	
	// Test 8: Const correctness
	std::cout << "\n--- Test 8: Const correctness ---" << std::endl;
	{
		const int const_a = 10;
		const int const_b = 20;
		
		std::cout << "Const integers: const_a = " << const_a << ", const_b = " << const_b << std::endl;
		std::cout << "min(const_a, const_b) = " << ::min(const_a, const_b) << std::endl;
		std::cout << "max(const_a, const_b) = " << ::max(const_a, const_b) << std::endl;
		
		// Note: We can't test swap with const values as it would modify them
	}

	// Test 9: Awesome class (complex type)
	std::cout << "\n--- Test 9: Awesome class (complex type) ---" << std::endl;
	{
		Awesome a(2);
		Awesome b(4);
		std::cout << "a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "after swap a = " << a << ", b = " << b << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	}
	
	std::cout << "\n=== End of tests ===" << std::endl;
	
	return 0;
}




