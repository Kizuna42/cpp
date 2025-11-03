#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
	std::cout << "=== CPP09 ex00: Bitcoin Exchange ===" << std::endl;
	
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
		std::cout << "Example: " << argv[0] << " input.txt" << std::endl;
		return 1;
	}
	
	try {
		BitcoinExchange exchange;
		
		// Load the database
		std::cout << "\nLoading exchange rate database..." << std::endl;
		exchange.loadDatabase("data.csv");
		
		// Display sample of database
		std::cout << "\nDatabase loaded successfully:" << std::endl;
		exchange.displayDatabase();
		
		// Process input file
		std::cout << "\nProcessing input file: " << argv[1] << std::endl;
		std::cout << "Results:" << std::endl;
		exchange.processInput(argv[1]);
		
	} catch (const BitcoinExchange::FileException& e) {
		std::cout << "File Error: " << e.what() << std::endl;
		return 1;
	} catch (const BitcoinExchange::InvalidFormatException& e) {
		std::cout << "Format Error: " << e.what() << std::endl;
		return 1;
	} catch (const BitcoinExchange::InvalidValueException& e) {
		std::cout << "Value Error: " << e.what() << std::endl;
		return 1;
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}




