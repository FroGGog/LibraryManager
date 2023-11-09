#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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

	bool operator ==(const Book& other) {
		if (this->title == other.title && this->author == other.author) {			
			return true;
		}
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

	Book add_fList(unsigned& id) {
		return allBooks[id-1];
	}


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

	void f_bookByAuthorTitle(std::string& author, std::string& title) {
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
		else if (action == "f_author") {
			std::cout << "Write books author : ";
			std::string tempAuthor{};
			std::string tempTitle{ " " };
			std::cin >> tempAuthor;
			f_bookByAuthorTitle(tempAuthor, tempTitle);
		}
		else if (action == "f_title") {
			std::cout << "Write books title : ";
			std::string tempAuthor{ " " };
			std::string tempTitle{};
			std::cin >> tempTitle;
			f_bookByAuthorTitle(tempAuthor, tempTitle);
		}
		else if (action == "exit") {
			return;
		}
	}

private:
	unsigned library_size = allBooks.size();
};

class User {

public:

	Library* c_mainLibrary{};

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
		for (auto book : favoriteBooks) {
			book.printInfo();
		}
	}

	bool checkBookInFav(Book mainBook) {
		for (auto book : favoriteBooks) {
			if (mainBook == book) {
				return true;
			}
		}
		return false;
	}

	void f_BookListManager() {
		short userChoice{};
		unsigned id{};
		std::cout << "Your favorites list menu.\n[1]Add book by id\n[2]Remove book by id\n[3]Print info about book from your list\n";
		std::cin >> userChoice;
		switch (userChoice) {
			case 1:
				system("cls");
				std::cout << "Write books index to add : ";
				if (c_mainLibrary->getAndCheckValidId(id)) {
					if (checkBookInFav(c_mainLibrary->add_fList(id))) {
						std::cout << "Book already in list!\n";
						return;
					}
					else {
						std::cout << "Book added \n";
						favoriteBooks.push_back(c_mainLibrary->add_fList(id));
						return;
					}
					
				}
				else {
					return;
				}
			case 2:
				system("cls");
				std::cout << "Write books index to remove : ";
				if (c_mainLibrary->getAndCheckValidId(id)) {
					auto iterator = favoriteBooks.begin() + id - 1;
					favoriteBooks.erase(iterator);
					std::cout << "Book deleted!\n";
					return;
				}
			
		}
		return;
	}

	//enum class userOptions : short {FindById = 1, FindByAuthor, FindByTitle, ShowFavoriteList, ChangeFavoriteList, AddNewBookToLibrary};

	void printMainMenu() {
		std::cout << "Here is user options menu. You can do this with your persmission:\n[1] Print all library books\n";
		std::cout << "[2] Find book by id\n[3] Find book by author\n[4] Find book by title\n[5] Show your favorite books\n[6] Edit favorite books list\n";
		std::cout << "[7] Suggest new library book to add\n[8] Exit\n";
	}

	std::string userChoice(bool& inUserPanel) {
		unsigned userNum{};
		std::cout << "Enter number from 1 to 8 : ";
		std::cin >> userNum;

		std::cout << '\n';
		switch (userNum)
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
	}
private:
	std::vector<Book> favoriteBooks{};
	//unsigned vectorSize = std::size(favoriteBooks);
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