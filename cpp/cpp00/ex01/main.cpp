#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>

std::string getInput(const std::string& prompt) {
	std::string input;
	std::cout << prompt;
	std::getline(std::cin, input);
	return input;
}

bool isValidInput(const std::string& input) {
	return !input.empty();
}

int stringToInt(const std::string& str) {
	int result = 0;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9')
			return -1;
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

Contact createContact() {
	Contact contact;
	std::string input;
	
	do {
		input = getInput("Enter first name: ");
	} while (!isValidInput(input));
	contact.setFirstName(input);
	
	do {
		input = getInput("Enter last name: ");
	} while (!isValidInput(input));
	contact.setLastName(input);
	
	do {
		input = getInput("Enter nickname: ");
	} while (!isValidInput(input));
	contact.setNickname(input);
	
	do {
		input = getInput("Enter phone number: ");
	} while (!isValidInput(input));
	contact.setPhoneNumber(input);
	
	do {
		input = getInput("Enter darkest secret: ");
	} while (!isValidInput(input));
	contact.setDarkestSecret(input);
	
	return contact;
}

int main() {
	PhoneBook phoneBook;
	std::string command;
	
	std::cout << "Welcome to the PhoneBook!" << std::endl;
	std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
	
	while (true) {
		std::cout << "Enter command: ";
		std::getline(std::cin, command);
		
		if (command == "ADD") {
			Contact newContact = createContact();
			phoneBook.addContact(newContact);
			std::cout << "Contact added successfully!" << std::endl;
		}
		else if (command == "SEARCH") {
			if (phoneBook.getContactCount() == 0) {
				std::cout << "No contacts available." << std::endl;
				continue;
			}
			
			phoneBook.displayContacts();
			
			std::string indexStr;
			std::cout << "Enter index of contact to display: ";
			std::getline(std::cin, indexStr);
			
			int index = stringToInt(indexStr);
			if (index == -1) {
				std::cout << "Invalid index" << std::endl;
			} else {
				phoneBook.displayContact(index);
			}
		}
		else if (command == "EXIT") {
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else {
			std::cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << std::endl;
		}
	}
	
	return 0;
}