#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>

bool isValidInput(const std::string& input) {
	return !input.empty();
}

bool getInput(const std::string& prompt, std::string& input) {
	std::cout << prompt;
	if (!std::getline(std::cin, input)) {
		std::cout << std::endl;
		return false;
	}
	return true;
}

bool getField(const std::string& prompt, std::string& input) {
	do {
		if (!getInput(prompt, input))
			return false;
	} while (!isValidInput(input));
	return true;
}

int stringToInt(const std::string& str) {
	int result = 0;
	if (str.empty() || str.length() > 9)
		return -1;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9')
			return -1;
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

bool createContact(Contact& contact) {
	std::string input;

	if (!getField("Enter first name: ", input))
		return false;
	contact.setFirstName(input);
	if (!getField("Enter last name: ", input))
		return false;
	contact.setLastName(input);
	if (!getField("Enter nickname: ", input))
		return false;
	contact.setNickname(input);
	if (!getField("Enter phone number: ", input))
		return false;
	contact.setPhoneNumber(input);
	if (!getField("Enter darkest secret: ", input))
		return false;
	contact.setDarkestSecret(input);
	return true;
}

int main() {
	PhoneBook phoneBook;
	std::string command;
	
	std::cout << "Welcome to the PhoneBook!" << std::endl;
	std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
	
	while (true) {
		if (!getInput("Enter command: ", command))
			break;
		
		if (command == "ADD") {
			Contact newContact;
			if (!createContact(newContact))
				break;
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
			if (!getInput("Enter index of contact to display: ", indexStr))
				break;
			
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