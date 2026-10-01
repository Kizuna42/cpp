#include "BitcoinExchange.hpp"

#include <iostream>

int main(int argc, char** argv) {
	if (argc != 4)
		return 1;
	BitcoinExchange exchange;
	exchange.loadDatabase(argv[1]);
	BitcoinExchange copied(exchange);
	BitcoinExchange assigned;
	assigned = copied;
	if (copied.getExchangeRate("2011-01-02") != 2 ||
		assigned.getExchangeRate("2011-01-02") != 2)
		return 1;
	try {
		exchange.loadDatabase(argv[2]);
		return 1;
	} catch (const std::exception&) {
		// A failed reload must preserve the complete previous database.
		if (exchange.getExchangeRate("2011-01-02") != 2)
			return 1;
	}
	exchange.loadDatabase(argv[3]);
	if (exchange.getExchangeRate("2011-01-02") != 7 ||
		copied.getExchangeRate("2011-01-02") != 2)
		return 1;
	try {
		exchange.getExchangeRate("2010-01-01");
		return 1;
	} catch (const BitcoinExchange::InvalidValueException&) {
	}
	std::cout << "PASS database copy, assignment, atomic reload\n";
	return 0;
}
