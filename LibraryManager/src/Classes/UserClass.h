#pragma once
#include "LibraryClass.h"

class User {

public:
	Library* c_mainLibrary{nullptr};

	User(Library&);
	~User();

	void printUserF_List();
	bool checkBookInFav(Book);
	void f_listIndexUpdate(unsigned&);
	void f_BookListManager();
	bool checkUserIsDigit(std::string&);
	void printMainMenu();
	std::string userChoice(bool&);

private:
	std::vector<Book> favoriteBooks{};
	size_t f_size = favoriteBooks.size();

	std::string userName{};
	std::string password{};


};