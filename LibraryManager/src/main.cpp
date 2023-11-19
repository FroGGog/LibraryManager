#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Classes/BookClass.h"
#include "Classes/LibraryClass.h"
#include "Classes/UserClass.h"
#include "UserDataBase.h"


std::string adminAccess() {
	std::string username{};
	std::string password{};
	std::cout << "Enter your username and password(split in two lines)(or keep empty for guest enter)\n";
	std::cout << "*Guest users can't save their favorite lists*\n";
	std::cout << "Or type !r to register\n";
	std::getline(std::cin, username);
	if (username == "!r") {
		return "reg";
	}
	std::getline(std::cin, password);
	std::cout << '\n';
	if (username == "admin" && password == "admin") {
		std::cout << "Access granted!\n";
		return "admin";
	}
	else {
		return "user";
	}
}

std::string adminPanel(bool& inAdminPanel) {
	std::cout << "Admin menu.\n";
	std::cout << "Choose option:\n[1]Add book\n[2]Remove book\n[3]Edit book\n[4]Find book by id\n[5]Print all books list\n[6]Exit\n";
	short userChoice{};
	std::cin >> userChoice;
	std::cout << '\n';
	switch (userChoice) {
		case 1:
			return "add";
			break;
		case 2:
			return "remove";
			break;
		case 3:
			return "edit";
			break;
		case 4:
			return "f_id";
			break;
		case 5:
			return "booklist";
			break;
		case 6:
			inAdminPanel = false;
			break;
		default:
			std::cout << "No such command\n";
			break;
	}
	return "exit";
}



int main() {

	bool inAdminPanel{ false };
	bool inUserPanel{ false };

	Book testBook{"All quiet on the Western front", "A novel by Erich Maria Remarque", "Erich Maria Remarque", 10};
	Book testBook2{ "Return", "A novel by Erich Maria Remarque 2", "Erich Maria Remarque", 8 };
	Book testBook3{ "Aboba", "love", "Danek" };

	Library mainLibrary{};

	DataBase mainDataBase{};

	User mainUser{mainLibrary};

	mainLibrary.addBook(testBook);
	mainLibrary.addBook(testBook2);
	mainLibrary.addBook(testBook3);

	std::string admin = adminAccess();
	if (admin == "admin") {
		inAdminPanel = true;
		while (inAdminPanel) {
			std::string adminAction{};
			adminAction = adminPanel(inAdminPanel);

			mainLibrary.libraryManager(adminAction);
		}
	}
	else if(admin == "user") {
		inUserPanel = true;
		while (inUserPanel) {
			unsigned userNum{};
			std::string userAction{};
			mainUser.printMainMenu();
			userAction = mainUser.userChoice(inUserPanel);
			mainLibrary.libraryManager(userAction);
		}
	}
	else {

		mainDataBase.regNewUser();
		mainDataBase.SaveUserInfo();

	}
	
	return 0;
}