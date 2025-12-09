#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iomanip>

class BitcoinExchange {
private:
	std::map<std::string, double> _exchangeRates;
	
	// Private helper functions
	bool isValidDate(const std::string& date) const;
	bool isValidValue(double value) const;
	std::string trim(const std::string& str) const;
	double stringToDouble(const std::string& str) const;
	bool isLeapYear(int year) const;
	bool validateDateFormat(const std::string& date) const;

public:
	// Orthodox Canonical Form
	BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange(void);
	
	// Main functionality
	void loadDatabase(const std::string& filename);
	void processInput(const std::string& filename);
	double getExchangeRate(const std::string& date) const;
	
	// Exception classes
	class FileException : public std::exception {
	private:
		std::string _message;
	public:
		FileException(const std::string& message) : _message(message) {}
		virtual ~FileException() throw() {}
		virtual const char* what() const throw() { return _message.c_str(); }
	};
	
	class InvalidFormatException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidFormatException(const std::string& message) : _message(message) {}
		virtual ~InvalidFormatException() throw() {}
		virtual const char* what() const throw() { return _message.c_str(); }
	};
	
	class InvalidValueException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidValueException(const std::string& message) : _message(message) {}
		virtual ~InvalidValueException() throw() {}
		virtual const char* what() const throw() { return _message.c_str(); }
	};
};

#endif




