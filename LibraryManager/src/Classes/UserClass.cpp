#include <iostream>
#include "BookClass.h"
#include "LibraryClass.h"
#include "UserClass.h"

//constructor that creates pointer to main books library
User::User(Library& mainLibrary) {
	c_mainLibrary = &mainLibrary;
}

User::~User() {
	c_mainLibrary = nullptr;
}

// add user saved list, saved users in file with some info about tham, exmpl userFavoriteBooks{index, index, index}
//but if some books was deleted you must update user favorite indexes

void User::printUserF_List() {
	if (std::size(favoriteBooks) == 0) {
		std::cout << "Your favorites list is empty!\n\n";
		return;
	}
	for (auto& book : favoriteBooks) {
		std::cout << book.getId() << ". " << book.title << "\n";
	}
}

//checks if book is already in favorites list
bool User::checkBookInFav(Book mainBook) {
	for (auto& book : favoriteBooks) {
		if (mainBook == book) {
			return true;
		}
	}
	return false;
}

void User::f_listIndexUpdate(unsigned& index) {
	size_t tempId{};
	for (auto iterator{ favoriteBooks.begin() + index }; iterator < favoriteBooks.end(); iterator++) {
		tempId = iterator->getId() - 1;
		iterator->setId(tempId);
	}
}

//main function that manages actions with books favorites list
void User::f_BookListManager() {
	f_size = favoriteBooks.size();
	short userChoice{};
	unsigned id{};
	std::cout << "Your favorites list menu.\n[1]Add book by id\n[2]Remove book by id\n[3]Print info about book from your list\n";
	std::cin >> userChoice;
	switch (userChoice) {
	case 1:
		system("cls");
		std::cout << "Write books index to add : ";
		if (c_mainLibrary->getAndCheckValidId(id, c_mainLibrary->allBooks.size())) {
			if (checkBookInFav(c_mainLibrary->add_fList(id))) {
				std::cout << "Book already in list!\n";
				return;
			}
			else {
				std::cout << "Book added \n";
				Book tempBook = c_mainLibrary->add_fList(id);
				size_t newIndex = f_size + 1;
				tempBook.setId(newIndex);
				favoriteBooks.push_back(tempBook);
				return;
			}
		}
		else {
			return;
		}
	case 2:
		system("cls");
		std::cout << "Write books index to remove : ";
		//change this, it must check if id valid for f_BooksList
		if (c_mainLibrary->getAndCheckValidId(id, c_mainLibrary->allBooks.size())) {
			f_listIndexUpdate(id);
			auto iterator = favoriteBooks.begin() + id - 1;
			favoriteBooks.erase(iterator);
			std::cout << "Book deleted!\n";
			return;
		}
	case 3:
		system("cls");
		std::cout << "Write books index to show info about";
		if (c_mainLibrary->getAndCheckValidId(id, c_mainLibrary->allBooks.size())) {
			auto iterator = favoriteBooks.begin() + id - 1;
			iterator->printInfo();
			return;
		}

	}
	return;
}

bool User::checkUserIsDigit(std::string& userNum) {
	for (unsigned i{}; i < userNum.length(); i++) {
		if (!isdigit(userNum[i])) {
			return false;
		}
	}
	return true;

}

void User::printMainMenu() {
	std::cout << "Here is user options menu. You can do this with your persmission:\n[1] Print all library books\n";
	std::cout << "[2] Find book by id\n[3] Find book by author\n[4] Find book by title\n[5] Show your favorite books\n[6] Edit favorite books list\n";
	std::cout << "[7] Suggest new library book to add\n[8] Exit\n";
}

std::string User::userChoice(bool& inUserPanel) {
	std::string userNum{};
	std::cout << "Enter number from 1 to 8 : ";
	std::cin >> userNum;
	if (!checkUserIsDigit(userNum)) {
		return "None";
	}

	std::cout << '\n';
	//converts string into int
	switch (int userNum2 = std::stoi(userNum))
	{
	case 1:
		system("cls");
		return "booklist";
	case 2:
		system("cls");
		return "f_id";
	case 3:
		system("cls");
		return "f_author";
	case 4:
		system("cls");
		return "f_title";
	case 5:
		system("cls");
		printUserF_List();
		return "None";
	case 6:
		system("cls");
		f_BookListManager();
		return "None";
	case 8:
		inUserPanel = false;
		return "exit";
	default:
		break;
	}
	return "None";
}