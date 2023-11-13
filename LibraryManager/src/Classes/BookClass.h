#pragma once
#include <string>

class Book {

public:

	std::string title;
	std::string shortDescr;
	std::string author;

	Book(std::string, std::string, std::string, short = 1);

	void setTitle(std::string&);
	void setAuthor(std::string&);
	void setDescr(std::string&);
	void setId(std::size_t&);
	void setRating(short&);
	short getRating();
	size_t getId();

	bool operator ==(const Book& other);

	void printInfo();

private:
	size_t id;
	short rating;


};