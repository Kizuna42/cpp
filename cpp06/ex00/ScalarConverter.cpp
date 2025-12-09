#include "ScalarConverter.hpp"

// Private constructor - cannot be instantiated
ScalarConverter::ScalarConverter(void) {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return *this;
}
ScalarConverter::~ScalarConverter(void) {}

// Helper functions for type detection
bool ScalarConverter::isChar(const std::string &literal)
{
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') ||
		   (literal.length() == 1 && !std::isdigit(literal[0]));
}

bool ScalarConverter::isInt(const std::string &literal)
{
	if (literal.empty())
		return false;

	size_t start = 0;
	if (literal[0] == '+' || literal[0] == '-')
	{
		start = 1;
		if (literal.length() == 1)
			return false;
	}

	for (size_t i = start; i < literal.length(); i++)
	{
		if (!std::isdigit(literal[i]))
			return false;
	}

	// Check for overflow
	std::istringstream iss(literal);
	long long value;
	iss >> value;
	return (value >= std::numeric_limits<int>::min() &&
			value <= std::numeric_limits<int>::max());
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	if (literal.empty() || literal.back() != 'f')
		return false;

	std::string withoutF = literal.substr(0, literal.length() - 1);
	if (withoutF.empty())
		return false;

	size_t start = 0;
	if (withoutF[0] == '+' || withoutF[0] == '-')
	{
		start = 1;
		if (withoutF.length() == 1)
			return false;
	}

	bool hasDot = false;
	for (size_t i = start; i < withoutF.length(); i++)
	{
		if (withoutF[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!std::isdigit(withoutF[i]))
		{
			return false;
		}
	}

	return hasDot;
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	if (literal.empty())
		return false;

	size_t start = 0;
	if (literal[0] == '+' || literal[0] == '-')
	{
		start = 1;
		if (literal.length() == 1)
			return false;
	}

	bool hasDot = false;
	for (size_t i = start; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!std::isdigit(literal[i]))
		{
			return false;
		}
	}

	return hasDot;
}

bool ScalarConverter::isPseudoLiteral(const std::string &literal)
{
	return (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
			literal == "-inf" || literal == "+inf" || literal == "nan");
}

// Conversion functions
void ScalarConverter::convertFromChar(char c)
{
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(int value)
{
	// char conversion
	if (value < 0 || value > 127)
	{
		displayChar(0, true);
	}
	else if (value < 32 || value == 127)
	{
		displayChar(static_cast<char>(value), false, true);
	}
	else
	{
		displayChar(static_cast<char>(value));
	}

	displayInt(value);
	displayFloat(static_cast<float>(value));
	displayDouble(static_cast<double>(value));
}

void ScalarConverter::convertFromFloat(float value)
{
	// char conversion
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
	{
		displayChar(0, true);
	}
	else if (value < 32 || value == 127)
	{
		displayChar(static_cast<char>(value), false, true);
	}
	else
	{
		displayChar(static_cast<char>(value));
	}

	// int conversion
	if (std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<int>::min() ||
		value > std::numeric_limits<int>::max())
	{
		displayInt(0, true);
	}
	else
	{
		displayInt(static_cast<int>(value));
	}

	displayFloat(value);
	displayDouble(static_cast<double>(value));
}

void ScalarConverter::convertFromDouble(double value)
{
	// char conversion
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
	{
		displayChar(0, true);
	}
	else if (value < 32 || value == 127)
	{
		displayChar(static_cast<char>(value), false, true);
	}
	else
	{
		displayChar(static_cast<char>(value));
	}

	// int conversion
	if (std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<int>::min() ||
		value > std::numeric_limits<int>::max())
	{
		displayInt(0, true);
	}
	else
	{
		displayInt(static_cast<int>(value));
	}

	// float conversion
	if (std::isnan(value) || std::isinf(value))
	{
		displayFloat(static_cast<float>(value));
	}
	else if (value < -std::numeric_limits<float>::max() ||
			 value > std::numeric_limits<float>::max())
	{
		displayFloat(0, true);
	}
	else
	{
		displayFloat(static_cast<float>(value));
	}

	displayDouble(value);
}

void ScalarConverter::convertPseudoLiteral(const std::string &literal)
{
	displayChar(0, true);
	displayInt(0, true);

	if (literal == "-inff" || literal == "+inff" || literal == "nanf")
	{
		if (literal == "-inff")
		{
			displayFloat(-std::numeric_limits<float>::infinity());
			displayDouble(-std::numeric_limits<double>::infinity());
		}
		else if (literal == "+inff")
		{
			displayFloat(std::numeric_limits<float>::infinity());
			displayDouble(std::numeric_limits<double>::infinity());
		}
		else
		{ // "nanf"
			displayFloat(std::numeric_limits<float>::quiet_NaN());
			displayDouble(std::numeric_limits<double>::quiet_NaN());
		}
	}
	else
	{
		if (literal == "-inf")
		{
			displayFloat(-std::numeric_limits<float>::infinity());
			displayDouble(-std::numeric_limits<double>::infinity());
		}
		else if (literal == "+inf")
		{
			displayFloat(std::numeric_limits<float>::infinity());
			displayDouble(std::numeric_limits<double>::infinity());
		}
		else
		{ // "nan"
			displayFloat(std::numeric_limits<float>::quiet_NaN());
			displayDouble(std::numeric_limits<double>::quiet_NaN());
		}
	}
}

// Display functions
void ScalarConverter::displayChar(char c, bool impossible, bool nonDisplayable)
{
	std::cout << "char: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else if (nonDisplayable)
	{
		std::cout << "Non displayable";
	}
	else
	{
		std::cout << "'" << c << "'";
	}
	std::cout << std::endl;
}

void ScalarConverter::displayInt(int value, bool impossible)
{
	std::cout << "int: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else
	{
		std::cout << value;
	}
	std::cout << std::endl;
}

void ScalarConverter::displayFloat(float value, bool impossible)
{
	std::cout << "float: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else if (std::isnan(value))
	{
		std::cout << "nanf";
	}
	else if (std::isinf(value))
	{
		std::cout << (value < 0 ? "-inff" : "+inff");
	}
	else
	{
		std::cout << value;
		if (value == static_cast<int>(value))
		{
			std::cout << ".0";
		}
		std::cout << "f";
	}
	std::cout << std::endl;
}

void ScalarConverter::displayDouble(double value, bool impossible)
{
	std::cout << "double: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else if (std::isnan(value))
	{
		std::cout << "nan";
	}
	else if (std::isinf(value))
	{
		std::cout << (value < 0 ? "-inf" : "+inf");
	}
	else
	{
		std::cout << value;
		if (value == static_cast<int>(value))
		{
			std::cout << ".0";
		}
	}
	std::cout << std::endl;
}

// Main public interface
void ScalarConverter::convert(const std::string &literal)
{
	if (literal.empty())
	{
		displayChar(0, true);
		displayInt(0, true);
		displayFloat(0.0f, true);
		displayDouble(0.0, true);
		return;
	}

	if (isPseudoLiteral(literal))
	{
		convertPseudoLiteral(literal);
	}
	else if (isChar(literal))
	{
		char c;
		if (literal.length() == 3)
		{
			c = literal[1]; // Character between quotes
		}
		else
		{
			c = literal[0]; // Single character
		}
		convertFromChar(c);
	}
	else if (isInt(literal))
	{
		int value = std::atoi(literal.c_str());
		convertFromInt(value);
	}
	else if (isFloat(literal))
	{
		float value = std::atof(literal.c_str());
		convertFromFloat(value);
	}
	else if (isDouble(literal))
	{
		double value = std::atof(literal.c_str());
		convertFromDouble(value);
	}
	else
	{
		// Invalid format: report impossible for all types
		displayChar(0, true);
		displayInt(0, true);
		displayFloat(0.0f, true);
		displayDouble(0.0, true);
	}
}
