#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Classes/BookClass.h"
#include "Classes/LibraryClass.h"


/*
TODO
1. Create data base for saving users information

*/




class User {

public:

	Library* c_mainLibrary{nullptr};

	//constructor that creates pointer to main books library
	User(Library& mainLibrary) {
		c_mainLibrary = &mainLibrary;
	}

	~User() {
		c_mainLibrary = nullptr;
	}

	// add user saved list, saved users in file with some info about tham, exmpl userFavoriteBooks{index, index, index}
	//but if some books was deleted you must update user favorite indexes

	void printUserF_List() {
		if (std::size(favoriteBooks) == 0) {
			std::cout << "Your favorites list is empty!\n\n";
			return;
		}
		for (auto& book : favoriteBooks) {
			std::cout << book.getId() << ". " << book.title << "\n";
		}
	}

	//checks if book is already in favorites list
	bool checkBookInFav(Book mainBook) {
		for (auto& book : favoriteBooks) {
			if (mainBook == book) {
				return true;
			}
		}
		return false;
	}

	void f_listIndexUpdate(unsigned& index) {
		size_t tempId{};
		for (auto iterator{ favoriteBooks.begin() + index }; iterator < favoriteBooks.end(); iterator++) {
			tempId = iterator->getId() - 1;
			iterator->setId(tempId);
		}
	}

	//main function that manages actions with books favorites list
	void f_BookListManager() {
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

	bool checkUserIsDigit(std::string& userNum) {
		for (unsigned i{}; i < userNum.length(); i++) {
			if (!isdigit(userNum[i])) {
				return false;
			}
		}
		return true;

	}

	void printMainMenu() {
		std::cout << "Here is user options menu. You can do this with your persmission:\n[1] Print all library books\n";
		std::cout << "[2] Find book by id\n[3] Find book by author\n[4] Find book by title\n[5] Show your favorite books\n[6] Edit favorite books list\n";
		std::cout << "[7] Suggest new library book to add\n[8] Exit\n";
	}

	std::string userChoice(bool& inUserPanel) {
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
private:
	std::vector<Book> favoriteBooks{};
	size_t f_size = favoriteBooks.size();
};



bool adminAccess() {
	std::string username{};
	std::string password{};
	std::cout << "Enter your username and password(split in to lines)(or keep empty for guest enter) :\n";
	std::cin >> username;
	std::cin >> password;
	std::cout << '\n';
	if (username == "admin" && password == "admin") {
		std::cout << "Access granted!\n";
		return true;
	}
	else {
		return false;
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

	bool admin{ false };
	bool inAdminPanel{ false };
	bool inUserPanel{ true };

	Book testBook{"All quiet on the Western front", "A novel by Erich Maria Remarque", "Erich Maria Remarque", 10};
	Book testBook2{ "Return", "A novel by Erich Maria Remarque 2", "Erich Maria Remarque", 8 };
	Book testBook3{ "Aboba", "love", "Danek" };

	Library mainLibrary{};

	User mainUser{mainLibrary};

	mainLibrary.addBook(testBook);
	mainLibrary.addBook(testBook2);
	mainLibrary.addBook(testBook3);

 	//admin = adminAccess();
	admin = false;
	if (admin) {
		inAdminPanel = true;
		while (inAdminPanel) {
			std::string adminAction{};
			//adminAction = adminPanel(inAdminPanel);

			mainLibrary.libraryManager(adminAction);
		}
	}
	while (inUserPanel) {
		unsigned userNum{};
		std::string userAction{};
		mainUser.printMainMenu();
		userAction = mainUser.userChoice(inUserPanel);
		mainLibrary.libraryManager(userAction);
	}


	return 0;
}