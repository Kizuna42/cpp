#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

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

BitcoinExchange::FileException::FileException(const std::string& message) : _message(message) {
}

BitcoinExchange::FileException::~FileException() throw() {
}

const char* BitcoinExchange::FileException::what() const throw() {
	return _message.c_str();
}

BitcoinExchange::InvalidFormatException::InvalidFormatException(const std::string& message) : _message(message) {
}

BitcoinExchange::InvalidFormatException::~InvalidFormatException() throw() {
}

const char* BitcoinExchange::InvalidFormatException::what() const throw() {
	return _message.c_str();
}

BitcoinExchange::InvalidValueException::InvalidValueException(const std::string& message) : _message(message) {
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
	std::istringstream iss(str);
	double value;
	iss >> value;
	if (iss.fail() || !iss.eof() || value != value ||
		value == std::numeric_limits<double>::infinity() ||
		value == -std::numeric_limits<double>::infinity()) {
		throw InvalidFormatException("Invalid number format");
	}
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
		
		try {
			double rate = stringToDouble(rateStr);
			if (rate < 0) {
				throw InvalidValueException("Negative exchange rate in database: " + rateStr);
			}
			_exchangeRates[date] = rate;
		} catch (const InvalidFormatException& e) {
			throw InvalidFormatException("Invalid exchange rate format: " + rateStr);
		}
	}
	
	file.close();
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
		
		double value;
		try {
			value = stringToDouble(valueStr);
		} catch (const InvalidFormatException& e) {
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		
		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		
		try {
			double rate = getExchangeRate(date);
			double result = value * rate;
			std::cout << std::setprecision(std::numeric_limits<double>::digits10)
				<< date << " => " << value << " = " << result << std::endl;
		} catch (const InvalidValueException& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	
	file.close();
}
