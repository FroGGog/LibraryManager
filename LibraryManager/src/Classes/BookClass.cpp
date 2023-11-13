#include <iostream>
#include <string>
#include "BookClass.h"

//main book class
Book::Book(std::string title, std::string shortDescr = "None", std::string author = "None", short rating) {
	this->title = title;
	this->shortDescr = shortDescr;
	this->author = author;
	this->rating = rating;
}
void Book::setTitle(std::string& title) {
	this->title = title;
}
void Book::setAuthor(std::string& author) {
	this->author = author;
}
void Book::setDescr(std::string& descr) {
	this->shortDescr = descr;
}
void Book::setId(size_t& id) {
	this->id = id;
}
void Book::setRating(short& rating) {
	if (rating > 10 || rating < 1) {
		std::cout << "Invalid value (must be from 1 to 10)\n";
		return;
	}
	this->rating = rating;
}
short Book::getRating() {
	return rating;
}
size_t Book::getId() {
	return id;
}

	//== operator for cheking if one book is equal to another by title and author
bool Book::operator ==(const Book& other) {
	if (this->title == other.title && this->author == other.author) {
		return true;
	}
	else {
		return false;
	}
}

void Book::printInfo() {

	auto lambdaFunc = [](short& rating) {
		for (short stars{ 0 }; stars < rating; stars++) {
			std::wcout << "* ";
		}
		std::cout << "\n\n";
		};
	std::cout << "\nBook : \'" + this->title + "\'.\nAuthor : " + this->author + "\nShort description : " + this->shortDescr + "\nRating : ";
		lambdaFunc(rating);
}
