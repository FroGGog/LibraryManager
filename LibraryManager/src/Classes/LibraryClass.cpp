#include <iostream>
#include <string>
#include "BookClass.h"
#include "LibraryClass.h"
#include <vector>


//returns book from library vector wich must be added to user f_list
Book Library::add_fList(unsigned& id) {
	return allBooks[id - 1];
}
void Library::addBook() {
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
void Library::addBook(Book& book) {
	library_size++;
	book.setId(library_size);
	allBooks.push_back(book);
}
void Library::removeBook(unsigned& id) {
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
void Library::updateIndex(unsigned removedBookId) {
	for (auto& book : allBooks) {
		size_t tempId = book.getId();
		if (tempId > removedBookId) {
			tempId--;
			book.setId(tempId);
		}
	}
}

void Library::editBook(unsigned& id) {
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
	std::cin >> tempRating;
	if (iterator->getRating() != tempRating) {
		iterator->setRating(tempRating);
	}
}

//searcing book by given id
void Library::f_bookById(unsigned& id) {
	auto iterator = allBooks.begin() + id - 1;
	iterator->printInfo();
}

//seactring book by given title
void Library::f_bookByAOrT(std::string& author, std::string& title) {
	unsigned count{};
	for (auto iterator{ allBooks.begin() }; iterator < allBooks.end(); iterator++) {
		if (iterator->author == author || iterator->title == title) {
			count++;
			std::cout << iterator->getId() << ".  " << iterator->title << " : " << iterator->author << '\n';
		}
	}
	std::cout << "\n\n";
	if (count == 0) {
		std::cout << "No such book in library. \n";
	}
}

//prints all books from library
void Library::printBooksList() {

	std::cout << "Here are list of all library books: \n";
	for (auto& book : allBooks) {
		std::cout << book.getId() << ". " + book.title + '\n';
	}
	std::cout << "\n\n";
}

//checks if user used valid id for some inputs
bool Library::getAndCheckValidId(unsigned& id, size_t lib_size) {
	std::cin >> id;
	if (id > lib_size) {
		std::cout << "Index out of range\n";
		return false;
	}
	return true;
}

//main library manager function that controll what programm should do
void Library::libraryManager(std::string& action) {
	if (action == "add") {
		addBook();
	}
	else if (action == "booklist") {
		printBooksList();
	}
	else if (action == "remove") {
		std::cout << "Write book index to remove : ";
		unsigned id{};
		if (getAndCheckValidId(id, library_size)) {
			removeBook(id);
		}
		return;
		}
	else if (action == "edit") {
		std::cout << "Write book index to edit : ";
		unsigned id{};
		if (getAndCheckValidId(id, library_size)) {
			editBook(id);
		}
		return;
	}
	//find by id
	else if (action == "f_id") {
		std::cout << "Write book index to print info : ";
		unsigned id{};
		if (getAndCheckValidId(id, library_size)) {
			f_bookById(id);
		}
		return;
		}
	//find by author
	else if (action == "f_author") {
		std::cout << "Write books author : ";
		std::string tempAuthor{};
		std::string tempTitle{ " " };
		std::cin >> tempAuthor;
		f_bookByAOrT(tempAuthor, tempTitle);
	}
	//find by title
	else if (action == "f_title") {
		std::cout << "Write books title : ";
		std::string tempAuthor{ " " };
		std::string tempTitle{};
		std::cin >> tempTitle;
		f_bookByAOrT(tempAuthor, tempTitle);
	}
	else if (action == "exit") {
		return;
	}
}