﻿#include <iostream>
#include <string>
#include <vector>


//main book class
class Book {

public:
	std::string title{};
	std::string shortDescr{};
	std::string author{};
	//constructor
	Book(std::string title, std::string shortDescr = "None", std::string author = "None", short rating = 1) {
		this->title = title;
		this->shortDescr = shortDescr;
		this->author = author;
		this->rating = rating;
	}

	void setTitle(std::string& title) {
		this->title = title;
	}
	void setAuthor(std::string& author) {
		this->author = author;
	}
	void setDescr(std::string& descr) {
		this->shortDescr = descr;
	}
	void setId(unsigned& id) {
		this->id = id;
	}
	void setRating(short& rating) {
		if (rating > 10 || rating < 1) {
			std::cout << "Invalid value (must be from 1 to 10)\n";
			return;
		}
		this->rating = rating;
	}
	short getRating() {
		return rating;
	}
	unsigned getId() {
		return id;
	}
	void printInfo() {

		auto lambdaFunc = [](short& rating) {
			for (short stars{ 0 }; stars < rating; stars++) {
				std::wcout <<  "* ";
			}
			std::cout << "\n\n";
		};
		std::cout << "\nBook : \'" + this->title + "\'.\nAuthor : " + this->author + "\nShort description : " + this->shortDescr + "\nRating : "; 
		lambdaFunc(rating);
	}

private:
	unsigned id{};
	short rating{};
};

class Library {

public:
	//vector for all books
	std::vector<Book> allBooks{};

	void addBook() {
		std::string tempAuthor{};
		std::string tempDescr{};
		std::string tempTitle{};
		short tempRating{};
		std::cout << "\nWrite book's title :";
		std::cin.ignore();
		std::getline(std::cin, tempTitle);
		std::cout << "\nWrite book's author :";
		std::getline(std::cin, tempAuthor);
		std::cout << "\nWrite short book description :";
		std::getline(std::cin, tempDescr);
		Book tempBook{ tempTitle, tempDescr, tempTitle };
		std::cout << "\nChoose rating : ";
		std::cin >> tempRating;
		tempBook.setRating(tempRating);
		library_size++;
		tempBook.setId(library_size);
		allBooks.push_back(tempBook);
	}
	void addBook(Book& book) {
		library_size++;
		book.setId(library_size);
		allBooks.push_back(book);
	}
	void removeBook(unsigned& id) {
		auto iterator = allBooks.begin() + id - 1;
		std::cout << "Are you want to delete " << "\'" << iterator->title << "\'" << " from books list?(y/n)";
		char answer{};
		std::cin >> answer;
		if (answer == 'y') {
			updateIndex(iterator->getId());
			allBooks.erase(iterator);
			std::cout << "book removed! \n\n";
			library_size--;
		}
		else {
			return;
		}
	}

	//function to update books indexes when any book removed
	void updateIndex(unsigned removedBookId) {
		for (auto& book : allBooks) {
			unsigned tempId = book.getId();
			if (tempId > removedBookId) {
				tempId--;
				book.setId(tempId);
			}
		}
	}

	void editBook(unsigned& id) {
		auto iterator = allBooks.begin() + id - 1;
		std::string tempString{};
		short tempRating{};
		std::cout << "Edit title(keep empty to leave the old:\n";
		std::cin.ignore();
		std::getline(std::cin, tempString);
		if (!tempString.empty()) {
			iterator->setTitle(tempString);
		}
		std::cout << "\nEdit author :\n";
		std::getline(std::cin, tempString);
		if (!tempString.empty()) {
			iterator->setAuthor(tempString);
		}
		std::cout << "\nEdit description :\n";
		std::getline(std::cin, tempString);
		if (!tempString.empty()) {
			iterator->setDescr(tempString);
		}
		std::cout << "\nEdit rating :\n";
		std::cin >>tempRating;
		if (iterator->getRating() != tempRating) {
			iterator->setRating(tempRating);
		}
		
	}

	void f_bookById(unsigned& id) {
		auto iterator = allBooks.begin() + id - 1;
		iterator->printInfo();
	}

	void printBooksList() {
		
		std::cout << "Here are list of all library books: \n";
		for (auto book : allBooks) {
			std::cout << book.getId() << ". " + book.title+'\n';
		}
		std::cout << "\n\n";
	}

	bool getAndCheckValidId(unsigned& id) {
		std::cin >> id;
		if (id > library_size) {
			std::cout << "Index out of range\n";
			return false;
		}
		return true;
	}

	void libraryManager(std::string& action) {
		if (action == "add") {
			addBook();
		}
		else if (action == "booklist") {
			printBooksList();
		}
		else if (action == "remove") {
			std::cout << "Write book index to remove : ";
			unsigned id{};
			if (getAndCheckValidId(id)) {
				removeBook(id);
			}
			return;
		}
		else if (action == "edit") {
			std::cout << "Write book index to edit : ";
			unsigned id{};
			if (getAndCheckValidId(id)) {
				editBook(id);
			}
			return;
		}
		else if (action == "f_id") {
			std::cout << "Write book index to print info : ";
			unsigned id{};
			if (getAndCheckValidId(id)) {
				f_bookById(id);
			}
			return;
		}
	}

private:
	unsigned library_size = allBooks.size();
};

class User {

	// add user saved list, saved users in file with some info about tham, exmpl userFavoriteBooks{index, index, index}
	//but if some books was deleted you must update user favorite indexes

	enum class userOptions{FindById = 1, FindByAuthor, FindByTitle, ShowFavoriteList, ChangeFavoriteList, AddNewBookToLibrary};

	void printMainMenu() {

	}


	void mainMenu() {
		system("cls");
		std::cout << "It's library, there you can search for added books, or or offer to add your own\n";

	}


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

	Book testBook{"All quiet on the Western front", "A novel by Erich Maria Remarque", "Erich Maria Remarque", 5};
	Book testBook2{ "Return", "A novel by Erich Maria Remarque 2", "Erich Maria Remarque" };

	Library mainLibrary{};

	User mainUser{};

	mainLibrary.addBook(testBook);
	mainLibrary.addBook(testBook2);

 	//admin = adminAccess();
	admin = true;
	if (admin) {
		inAdminPanel = true;
		while (inAdminPanel) {
			std::string adminAction{};
			//adminAction = adminPanel(inAdminPanel);

			mainLibrary.libraryManager(adminAction);
		}
		
	}


	return 0;
}