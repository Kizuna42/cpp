#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook() : contactCount(0), nextIndex(0) {
}

PhoneBook::~PhoneBook() {
}

void PhoneBook::addContact(const Contact& contact) {
	contacts[nextIndex] = contact;
	nextIndex = (nextIndex + 1) % 8;
	if (contactCount < 8)
		contactCount++;
}

std::string truncateString(const std::string& str) {
	if (str.length() > 10) {
		return str.substr(0, 9) + ".";
	}
	return str;
}

void PhoneBook::displayContacts() const {
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	
	for (int i = 0; i < contactCount; i++) {
		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10) << truncateString(contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10) << truncateString(contacts[i].getLastName()) << "|";
		std::cout << std::setw(10) << truncateString(contacts[i].getNickname()) << std::endl;
	}
}

void PhoneBook::displayContact(int index) const {
	if (index < 0 || index >= contactCount) {
		std::cout << "Invalid index" << std::endl;
		return;
	}
	
	const Contact& contact = contacts[index];
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}

int PhoneBook::getContactCount() const {
	return contactCount;
}