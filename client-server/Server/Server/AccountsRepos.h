#pragma once
#include <iostream>
#include "vector"
#include <fstream>
class AccountsRepos
{
private:
	std::vector<std::pair<std::string, std::string>> dataBase;

	std::vector<std::pair<std::string, std::string>> LoadFromFile(std::string filename) 
	{
		std::vector<std::pair<std::string, std::string>> dataBase;

		std::ifstream input(filename);

		if (!input.is_open()) {
			throw "File is not open!\n";
		}

		while (!input.eof()) {
			std::pair<std::string, std::string> pair;
			input >> pair.first;
			input >> pair.second;
			dataBase.push_back(pair);
		}
		return dataBase;
	}
public:
	AccountsRepos(): dataBase(LoadFromFile("..\\BaseOfAccounts.txt")) { }

	bool Checking(std::string login, std::string password) {
		for (int i = 0; i < dataBase.size(); i++) {
			if (login == dataBase[i].first && password == dataBase[i].second)
				return true;
		}
		return false;
	}
};

