#include "ScalarConverter.hpp"

#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

static bool isChar(const std::string &literal);
static bool isInt(const std::string &literal);
static bool isFloat(const std::string &literal);
static bool isDouble(const std::string &literal);
static bool isPseudoLiteral(const std::string &literal);
static void convertFromChar(char c);
static void convertFromInt(int value);
static void convertFromFloat(float value);
static void convertFromDouble(double value);
static void convertPseudoLiteral(const std::string &literal);
static void displayChar(char c, bool impossible = false,
	bool nonDisplayable = false);
static void displayInt(int value, bool impossible = false);
static void displayFloat(float value, bool impossible = false);
static void displayDouble(double value, bool impossible = false);

static bool isNanValue(double value)
{
	return value != value;
}

static bool isInfValue(double value)
{
	return value == std::numeric_limits<double>::infinity() ||
		   value == -std::numeric_limits<double>::infinity();
}

static bool parseDouble(const std::string &literal, double &value)
{
	char *end;

	errno = 0;
	value = std::strtod(literal.c_str(), &end);
	if (end == literal.c_str() || *end != '\0')
		return false;
	if (errno == ERANGE && (value == 0.0 || isInfValue(value)))
		return false;
	return true;
}

static void displayAllImpossible(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

static bool isIntRange(double value)
{
	double truncated = value < 0.0 ? std::ceil(value) : std::floor(value);

	return truncated >= static_cast<double>(std::numeric_limits<int>::min()) &&
		   truncated <= static_cast<double>(std::numeric_limits<int>::max());
}

static bool isCharRange(double value)
{
	double truncated = value < 0.0 ? std::ceil(value) : std::floor(value);

	return truncated >= 0.0 && truncated <= 127.0;
}

ScalarConverter::ScalarConverter(void) {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return *this;
}
ScalarConverter::~ScalarConverter(void) {}

static bool isChar(const std::string &literal)
{
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') ||
		   (literal.length() == 1 &&
			!std::isdigit(static_cast<unsigned char>(literal[0])));
}

static bool isInt(const std::string &literal)
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
		if (!std::isdigit(static_cast<unsigned char>(literal[i])))
			return false;
	}
	return true;
}

static bool isFloat(const std::string &literal)
{
	if (literal.empty() || literal[literal.size() - 1] != 'f')
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
	bool hasDigit = false;
	for (size_t i = start; i < withoutF.length(); i++)
	{
		if (withoutF[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!std::isdigit(static_cast<unsigned char>(withoutF[i])))
		{
			return false;
		}
		else
			hasDigit = true;
	}

	return hasDot && hasDigit;
}

static bool isDouble(const std::string &literal)
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
	bool hasDigit = false;
	for (size_t i = start; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!std::isdigit(static_cast<unsigned char>(literal[i])))
		{
			return false;
		}
		else
			hasDigit = true;
	}

	return hasDot && hasDigit;
}

static bool isPseudoLiteral(const std::string &literal)
{
	return (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
			literal == "-inf" || literal == "+inf" || literal == "nan");
}

static void convertFromChar(char c)
{
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void convertFromInt(int value)
{
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

static void convertFromFloat(float value)
{
	if (isNanValue(value) || isInfValue(value) || !isCharRange(value))
	{
		displayChar(0, true);
	}
	else if (static_cast<char>(value) < 32 || static_cast<char>(value) == 127)
	{
		displayChar(static_cast<char>(value), false, true);
	}
	else
	{
		displayChar(static_cast<char>(value));
	}

	if (isNanValue(value) || isInfValue(value) || !isIntRange(value))
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

static void convertFromDouble(double value)
{
	if (isNanValue(value) || isInfValue(value) || !isCharRange(value))
	{
		displayChar(0, true);
	}
	else if (static_cast<char>(value) < 32 || static_cast<char>(value) == 127)
	{
		displayChar(static_cast<char>(value), false, true);
	}
	else
	{
		displayChar(static_cast<char>(value));
	}

	if (isNanValue(value) || isInfValue(value) || !isIntRange(value))
	{
		displayInt(0, true);
	}
	else
	{
		displayInt(static_cast<int>(value));
	}

	if (isNanValue(value) || isInfValue(value))
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

static void convertPseudoLiteral(const std::string &literal)
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
		{
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
		{
			displayFloat(std::numeric_limits<float>::quiet_NaN());
			displayDouble(std::numeric_limits<double>::quiet_NaN());
		}
	}
}

static void displayChar(char c, bool impossible, bool nonDisplayable)
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

static void displayInt(int value, bool impossible)
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

static void displayFloat(float value, bool impossible)
{
	std::cout << "float: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else if (isNanValue(value))
	{
		std::cout << "nanf";
	}
	else if (isInfValue(value))
	{
		std::cout << (value < 0 ? "-inff" : "+inff");
	}
	else
	{
		std::ostringstream oss;
		oss << value;
		std::string output = oss.str();
		std::cout << output;
		if (output.find('.') == std::string::npos &&
			output.find('e') == std::string::npos &&
			output.find('E') == std::string::npos)
			std::cout << ".0";
		std::cout << "f";
	}
	std::cout << std::endl;
}

static void displayDouble(double value, bool impossible)
{
	std::cout << "double: ";
	if (impossible)
	{
		std::cout << "impossible";
	}
	else if (isNanValue(value))
	{
		std::cout << "nan";
	}
	else if (isInfValue(value))
	{
		std::cout << (value < 0 ? "-inf" : "+inf");
	}
	else
	{
		std::ostringstream oss;
		oss << value;
		std::string output = oss.str();
		std::cout << output;
		if (output.find('.') == std::string::npos &&
			output.find('e') == std::string::npos &&
			output.find('E') == std::string::npos)
			std::cout << ".0";
	}
	std::cout << std::endl;
}

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
			c = literal[1];
		}
		else
		{
			c = literal[0];
		}
		convertFromChar(c);
	}
	else if (isInt(literal))
	{
		double value;
		if (!parseDouble(literal, value))
		{
			displayAllImpossible();
			return;
		}
		// Overflow is judged per conversion (subject): an int-overflowing
		// literal keeps its meaningful float/double conversions.
		if (isIntRange(value))
			convertFromInt(static_cast<int>(value));
		else
			convertFromDouble(value);
	}
	else if (isFloat(literal))
	{
		std::string withoutF = literal.substr(0, literal.length() - 1);
		double value;
		if (!parseDouble(withoutF, value))
		{
			displayAllImpossible();
			return;
		}
		if (value < -std::numeric_limits<float>::max() ||
			value > std::numeric_limits<float>::max())
			convertFromDouble(value);
		else
			convertFromFloat(static_cast<float>(value));
	}
	else if (isDouble(literal))
	{
		double value;
		if (!parseDouble(literal, value))
		{
			displayAllImpossible();
			return;
		}
		convertFromDouble(value);
	}
	else
	{
		displayChar(0, true);
		displayInt(0, true);
		displayFloat(0.0f, true);
		displayDouble(0.0, true);
	}
}
