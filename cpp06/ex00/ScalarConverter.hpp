#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cctype>

class ScalarConverter
{
private:
	// Private constructor to prevent instantiation
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	~ScalarConverter(void);

	// Helper functions for type detection and conversion
	static bool isChar(const std::string &literal);
	static bool isInt(const std::string &literal);
	static bool isFloat(const std::string &literal);
	static bool isDouble(const std::string &literal);
	static bool isPseudoLiteral(const std::string &literal);

	// Conversion functions
	static void convertFromChar(char c);
	static void convertFromInt(int value);
	static void convertFromFloat(float value);
	static void convertFromDouble(double value);
	static void convertPseudoLiteral(const std::string &literal);

	// Display functions
	static void displayChar(char c, bool impossible = false, bool nonDisplayable = false);
	static void displayInt(int value, bool impossible = false);
	static void displayFloat(float value, bool impossible = false);
	static void displayDouble(double value, bool impossible = false);

public:
	// Main public interface
	static void convert(const std::string &literal);
};

#endif
