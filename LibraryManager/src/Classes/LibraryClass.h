#pragma once
#include <vector>
#include "BookClass.h"

class Library {

public:
	std::vector<Book> allBooks{};

	Book add_fList(unsigned&);

	void addBook();
	void addBook(Book&);
	void removeBook(unsigned&);
	void updateIndex(unsigned);
	void editBook(unsigned&);
	void f_bookById(unsigned&);
	void f_bookByAOrT(std::string&, std::string&);
	void printBooksList();
	bool getAndCheckValidId(unsigned&, size_t);
	void libraryManager(std::string&);

private:
	size_t library_size{0};

};