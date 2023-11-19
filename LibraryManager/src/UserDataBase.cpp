#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "Classes/UserClass.h"
#include "UserDataBase.h"


bool DataBase::checkValidUserName(std::string& userName) {
	return true;
}

void DataBase::regNewUser() {

	std::cout << "Please print your username and password next. Split in two lines :\n";
	std::getline(std::cin, DataBase::currentUserName);
	if (checkValidUserName(DataBase::currentUserName)) {
		std::getline(std::cin, DataBase::currentUserPass);
	};
	std::cout << "You have been registered!\n";
}

void DataBase::SaveUserInfo() {
	std::string info{DataBase::currentUserName + ' ' + DataBase::currentUserPass};
	std::fstream fs;

	fs.open("DataBase.txt", std::ios::app);

	if (fs.is_open()) {

		fs << info << '\n';
	}

	fs.close();

}








