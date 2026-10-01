#include "BitcoinExchange.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

// data.csv is looked up next to the executable when it is not in the current
// working directory, so ./btc works from the repository root as well.
static std::string resolveDatabasePath(const char* programPath) {
	const std::string name = "data.csv";

	std::ifstream probe(name.c_str());
	if (probe.is_open()) {
		return name;
	}

	std::string path(programPath);
	size_t slash = path.find_last_of('/');
	if (slash == std::string::npos) {
		return name;
	}
	return path.substr(0, slash + 1) + name;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	
	try {
		BitcoinExchange exchange;
		exchange.loadDatabase(resolveDatabasePath(argv[0]));
		exchange.processInput(argv[1]);
	} catch (const BitcoinExchange::FileException&) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
