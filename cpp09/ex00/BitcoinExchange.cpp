#include "BitcoinExchange.hpp"

#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <utility>

namespace {

enum ValueStatus {
	VALUE_OK,
	BAD_FORMAT,
	NEGATIVE_VALUE,
	TOO_LARGE
};

// Check the decimal text before double conversion can round it to 0 or 1000.
// Scientific notation is accepted too, as it was by the numeric parser.
ValueStatus validateDecimalValue(const std::string& text, bool checkUpperBound) {
	if (text.empty())
		return BAD_FORMAT;
	size_t start = (text[0] == '+' || text[0] == '-') ? 1 : 0;
	size_t exponentPos = text.find_first_of("eE", start);
	size_t mantissaEnd = exponentPos == std::string::npos ? text.size() : exponentPos;
	std::string digits;
	size_t wholeDigits = 0;
	bool hasDot = false;
	for (size_t i = start; i < mantissaEnd; ++i) {
		if (text[i] == '.' && !hasDot)
			hasDot = true;
		else if (text[i] >= '0' && text[i] <= '9') {
			digits += text[i];
			if (!hasDot)
				++wholeDigits;
		} else
			return BAD_FORMAT;
	}
	if (digits.empty())
		return BAD_FORMAT;

	size_t exponent = 0;
	bool negativeExponent = false;
	if (exponentPos != std::string::npos) {
		size_t i = exponentPos + 1;
		if (i < text.size() && (text[i] == '+' || text[i] == '-')) {
			negativeExponent = (text[i] == '-');
			++i;
		}
		if (i == text.size())
			return BAD_FORMAT;
		// Larger exponents cannot change which side of 1000 this value is on.
		const size_t cap = text.size() + 4;
		for (; i < text.size(); ++i) {
			if (text[i] < '0' || text[i] > '9')
				return BAD_FORMAT;
			size_t digit = static_cast<size_t>(text[i] - '0');
			if (exponent > cap / 10 || digit > cap - exponent * 10)
				exponent = cap;
			else
				exponent = exponent * 10 + digit;
		}
	}
	size_t first = digits.find_first_not_of('0');
	if (first == std::string::npos)
		return VALUE_OK;
	if (text[0] == '-')
		return NEGATIVE_VALUE;
	if (!checkUpperBound)
		return VALUE_OK;
	if (negativeExponent) {
		if (exponent >= wholeDigits)
			return VALUE_OK;
		wholeDigits -= exponent;
	} else
		wholeDigits += exponent;
	if (wholeDigits <= first || wholeDigits - first < 4)
		return VALUE_OK;
	if (wholeDigits - first > 4 || digits[first] != '1' ||
		digits.find_first_not_of('0', first + 1) != std::string::npos)
		return TOO_LARGE;
	return VALUE_OK;
}

}

BitcoinExchange::BitcoinExchange(void) {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_exchangeRates = other._exchangeRates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
}

BitcoinExchange::FileException::FileException(void) : _message("Could not open file") {
}

BitcoinExchange::FileException::FileException(const std::string& message) : _message(message) {
}

BitcoinExchange::FileException::FileException(const FileException& other)
	: std::exception(other), _message(other._message) {
}

BitcoinExchange::FileException& BitcoinExchange::FileException::operator=(const FileException& other) {
	if (this != &other) {
		std::exception::operator=(other);
		_message = other._message;
	}
	return *this;
}

BitcoinExchange::FileException::~FileException() throw() {
}

const char* BitcoinExchange::FileException::what() const throw() {
	return _message.c_str();
}

BitcoinExchange::InvalidFormatException::InvalidFormatException(void) : _message("Invalid format") {
}

BitcoinExchange::InvalidFormatException::InvalidFormatException(const std::string& message) : _message(message) {
}

BitcoinExchange::InvalidFormatException::InvalidFormatException(const InvalidFormatException& other)
	: std::exception(other), _message(other._message) {
}

BitcoinExchange::InvalidFormatException& BitcoinExchange::InvalidFormatException::operator=(
	const InvalidFormatException& other) {
	if (this != &other) {
		std::exception::operator=(other);
		_message = other._message;
	}
	return *this;
}

BitcoinExchange::InvalidFormatException::~InvalidFormatException() throw() {
}

const char* BitcoinExchange::InvalidFormatException::what() const throw() {
	return _message.c_str();
}

BitcoinExchange::InvalidValueException::InvalidValueException(void) : _message("Invalid value") {
}

BitcoinExchange::InvalidValueException::InvalidValueException(const std::string& message) : _message(message) {
}

BitcoinExchange::InvalidValueException::InvalidValueException(const InvalidValueException& other)
	: std::exception(other), _message(other._message) {
}

BitcoinExchange::InvalidValueException& BitcoinExchange::InvalidValueException::operator=(
	const InvalidValueException& other) {
	if (this != &other) {
		std::exception::operator=(other);
		_message = other._message;
	}
	return *this;
}

BitcoinExchange::InvalidValueException::~InvalidValueException() throw() {
}

const char* BitcoinExchange::InvalidValueException::what() const throw() {
	return _message.c_str();
}

std::string BitcoinExchange::trim(const std::string& str) const {
	size_t first = str.find_first_not_of(" \t\r\n");
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(" \t\r\n");
	return str.substr(first, (last - first + 1));
}

double BitcoinExchange::stringToDouble(const std::string& str) const {
	char* end;
	errno = 0;
	double value = std::strtod(str.c_str(), &end);
	if (end == str.c_str() || end != str.c_str() + str.size())
		throw InvalidFormatException("Invalid number format");
	if (value != value || value > std::numeric_limits<double>::max() ||
		value < -std::numeric_limits<double>::max() || (errno == ERANGE && value == 0))
		throw InvalidValueException("Number out of range");
	return value;
}

bool BitcoinExchange::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::validateDateFormat(const std::string& date) const {
	if (date.length() != 10) {
		return false;
	}
	if (date[4] != '-' || date[7] != '-') {
		return false;
	}
	
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i]))) {
			return false;
		}
	}
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	if (!validateDateFormat(date)) {
		return false;
	}
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	if (year < 1) {
		return false;
	}
	if (month < 1 || month > 12) {
		return false;
	}
	
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year)) {
		daysInMonth[1] = 29;
	}
	
	if (day < 1 || day > daysInMonth[month - 1]) {
		return false;
	}
	
	return true;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw FileException("Could not open database file: " + filename);
	}
	
	std::string line;
	bool firstLine = true;
	std::map<std::string, double> rates;
	
	while (std::getline(file, line)) {
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (firstLine) {
			firstLine = false;
			if (line == "date,exchange_rate") {
				continue;
			}
		}
		
		if (line.empty()) {
			continue;
		}
		
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos) {
			throw InvalidFormatException("Invalid database format: " + line);
		}
		
		std::string date = trim(line.substr(0, commaPos));
		std::string rateStr = trim(line.substr(commaPos + 1));
		
		if (!isValidDate(date)) {
			throw InvalidFormatException("Invalid date in database: " + date);
		}
		
		ValueStatus status = validateDecimalValue(rateStr, false);
		if (status == BAD_FORMAT)
			throw InvalidFormatException("Invalid exchange rate format: " + rateStr);
		if (status == NEGATIVE_VALUE)
			throw InvalidValueException("Negative exchange rate in database: " + rateStr);
		double rate = stringToDouble(rateStr);
		if (!rates.insert(std::make_pair(date, rate)).second)
			throw InvalidFormatException("Duplicate date in database: " + date);
	}

	if (!file.eof())
		throw FileException("Could not read database file: " + filename);
	if (rates.empty())
		throw InvalidFormatException("Empty exchange rate database");
	_exchangeRates.swap(rates);
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
	std::map<std::string, double>::const_iterator it = _exchangeRates.find(date);
	
	if (it != _exchangeRates.end()) {
		return it->second;
	}
	
	it = _exchangeRates.lower_bound(date);
	if (it == _exchangeRates.begin()) {
		throw InvalidValueException("No exchange rate available for date: " + date);
	}
	
	--it;
	return it->second;
}

void BitcoinExchange::processInput(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw FileException("Could not open input file: " + filename);
	}
	
	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line)) {
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (firstLine) {
			firstLine = false;
			if (line == "date | value") {
				continue;
			}
		}
		
		if (line.empty()) {
			continue;
		}
		
		size_t pipePos = line.find(" | ");
		if (pipePos == std::string::npos) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 3));
		
		if (!isValidDate(date)) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		ValueStatus status = validateDecimalValue(valueStr, true);
		if (status == BAD_FORMAT) {
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		if (status == NEGATIVE_VALUE) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (status == TOO_LARGE) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		
		double value;
		try {
			value = stringToDouble(valueStr);
		} catch (const InvalidFormatException& e) {
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue;
		} catch (const InvalidValueException& e) {
			std::cout << "Error: " << e.what() << std::endl;
			continue;
		}

		if (value == 0)
			value = 0; // Normalize a valid textual -0 for display.

		try {
			double rate = getExchangeRate(date);
			double result = value * rate;
			if (result > std::numeric_limits<double>::max() ||
				(value != 0 && rate != 0 && result == 0))
				throw InvalidValueException("Exchange result out of range");
			if (result == 0)
				result = 0;
			std::cout << std::setprecision(std::numeric_limits<double>::digits10)
				<< date << " => " << value << " = " << result << std::endl;
		} catch (const InvalidValueException& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	
	if (!file.eof())
		throw FileException("Could not read input file: " + filename);
	if (firstLine)
		throw InvalidFormatException("Empty input file");
}
