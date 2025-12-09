#include "BitcoinExchange.hpp"

// Constructors
BitcoinExchange::BitcoinExchange(void) {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates) {
}

// Assignment operator
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_exchangeRates = other._exchangeRates;
	}
	return *this;
}

// Destructor
BitcoinExchange::~BitcoinExchange(void) {
}

// Helper functions
std::string BitcoinExchange::trim(const std::string& str) const {
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

double BitcoinExchange::stringToDouble(const std::string& str) const {
	std::istringstream iss(str);
	double value;
	iss >> value;
	if (iss.fail() || !iss.eof()) {
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
	
	// Check if year, month, day are digits
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(date[i])) {
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
	
	if (year < 1900 || year > 2100) {
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

bool BitcoinExchange::isValidValue(double value) const {
	return value >= 0 && value <= 1000;
}

// Main functionality
void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw FileException("Could not open database file: " + filename);
	}
	
	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line)) {
		if (firstLine) {
			firstLine = false;
			if (line == "date,exchange_rate") {
				continue;  // Skip header
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
	// Find the exact date or the closest previous date
	std::map<std::string, double>::const_iterator it = _exchangeRates.find(date);
	
	if (it != _exchangeRates.end()) {
		return it->second;
	}
	
	// Find the closest date before the given date
	it = _exchangeRates.lower_bound(date);
	if (it == _exchangeRates.begin()) {
		throw InvalidValueException("No exchange rate available for date: " + date);
	}
	
	--it;  // Get the previous date
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
		if (firstLine) {
			firstLine = false;
			if (line == "date | value") {
				continue;  // Skip header
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
		
		// Validate date
		if (!isValidDate(date)) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		
		// Validate and parse value
		double value;
		try {
			value = stringToDouble(valueStr);
		} catch (const InvalidFormatException& e) {
			std::cout << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		
		// Check value range
		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		
		// Get exchange rate and calculate result
		try {
			double rate = getExchangeRate(date);
			double result = value * rate;
			// Remove trailing zeros and unnecessary decimal points
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(10) << result;
			std::string resultStr = oss.str();
			// Remove trailing zeros
			resultStr.erase(resultStr.find_last_not_of('0') + 1, std::string::npos);
			if (resultStr[resultStr.length() - 1] == '.') {
				resultStr.erase(resultStr.length() - 1);
			}
			std::cout << date << " => " << value << " = " << resultStr << std::endl;
		} catch (const InvalidValueException& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	
	file.close();
}





