#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <map>
#include <string>

class BitcoinExchange {
private:
	std::map<std::string, double> _exchangeRates;
	
	bool isValidDate(const std::string& date) const;
	std::string trim(const std::string& str) const;
	double stringToDouble(const std::string& str) const;
	bool isLeapYear(int year) const;
	bool validateDateFormat(const std::string& date) const;

public:
	BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange(void);
	
	void loadDatabase(const std::string& filename);
	void processInput(const std::string& filename);
	double getExchangeRate(const std::string& date) const;
	
	class FileException : public std::exception {
	private:
		std::string _message;
	public:
		FileException(const std::string& message);
		virtual ~FileException() throw();
		virtual const char* what() const throw();
	};
	
	class InvalidFormatException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidFormatException(const std::string& message);
		virtual ~InvalidFormatException() throw();
		virtual const char* what() const throw();
	};
	
	class InvalidValueException : public std::exception {
	private:
		std::string _message;
	public:
		InvalidValueException(const std::string& message);
		virtual ~InvalidValueException() throw();
		virtual const char* what() const throw();
	};
};

#endif
