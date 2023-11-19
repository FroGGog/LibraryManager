#pragma once
#include <string>

class DataBase {

public:
	bool checkValidUserName(std::string&);
	void regNewUser();
	void SaveUserInfo();

private:
	std::string currentUserName{};
	std::string currentUserPass{};


};