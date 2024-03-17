#pragma once
#include <iostream>
#include <fstream>
#include "TTable.h"
#include "TScanTable.h"
#include "TWordStruct.h"

class FileReader
{
protected:
	std::string filename;

protected:
	void ChangeWord(std::string& str) {
		if (str == "")
			return;
		if (str[0] == '*')
			return;
		if (str[0] == '.' && str[str.length() - 1] == '.')
			return;
		if (str.size() == 1)
			return;
		if (str == "——")
			return;
		// Обрезка лишних знаков в начале слова
		if ( str[0] == '-' || str[0] == '“' || str[0] == '‘' || str[0] == '(' )
			str = str.substr(1, str.length() - 1);

		// Обрезка лишних знаков в конце слова
		auto c = str[str.length() - 1];
		/*while (c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':' || c == '”' || c == '’' || c == ')' || c == '™')
		{
			str = str.substr(0, str.length() - 1);
			c = str[str.length() - 1];
		}*/
		while ( !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) ) {
			str = str.substr(0, str.length() - 1);
			if (str.size() == 0)
				return;
			c = str[str.length() - 1];
		}
	}

	void Finding(TTable& t, std::string str) {
		if (t.FindRecord(str) == nullptr) {
			std::cout << "\'" << str << "\'" << " " << "is not in table!\n";
		}
		else {
			std::cout << "\'" << str << "\'" << " " << "is on table\n";
		}
	}

public:
	FileReader(std::string name) : filename(name) {}

	bool FileRead(TTable* table) 
	{
		std::ifstream file(filename);

		TWordStruct* tws;

		if (!file.is_open()) 
			return false;
		
		else {
			std::string word = ""; // Слово 
			int length = 0;        // Количество Букв в Слове (длина)
			WORDTYPE wordType;     // Тип Слова
			LANGUAGE language;     // Язык Слова
			ZAGL zagl;             // Первая - Заглавная?

			while (!file.eof()) 
			{
				file >> word;
				if (word == "")
					break;

				ChangeWord(word); // Изменение слова - отсечение лишних знаков
				if (table->FindRecord(word) == nullptr) 
				{
					// Получение Информации о Считанном Слове:
					if (word[0] >= '0' && word[0] <= '9') {
						wordType = WORDTYPE::NUMBER;
						language = LANGUAGE::NON;
						zagl = ZAGL::NON;
					}
					else if (word[0] >= 'a' && word[0] <= 'z') {
						wordType = WORDTYPE::WORD;
						language = LANGUAGE::FRENCH;
						zagl = ZAGL::NO;
					}
					else if (word[0] >= 'A' && word[0] <= 'Z') {
						wordType = WORDTYPE::WORD;
						language = LANGUAGE::FRENCH;
						zagl = ZAGL::YES;
					}
					/*else if (word[0] >= 'А' && word[0] <= 'Я') {
						wordType = WORDTYPE::WORD;
						language = LANGUAGE::RUSSIA;
						zagl = ZAGL::YES;
					}
					else if (word[0] >= 'а' && word[0] <= 'я') {
						wordType = WORDTYPE::WORD;
						language = LANGUAGE::RUSSIA;
						zagl = ZAGL::NO;
					}*/
					else {
						wordType = WORDTYPE::SYMBOL;
						language = LANGUAGE::NON;
						zagl = ZAGL::NON;
					}
					table->InsertRecord(word, new TWordStruct(1, word.length(), wordType, language, zagl));
					word = "";
				}
				else {
					((TWordStruct*)table->FindRecord(word))->Plus();
					word = "";
				}
			}
			file.close();
		}
		return true;
	}
};

