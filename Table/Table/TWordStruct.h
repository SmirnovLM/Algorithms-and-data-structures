#pragma once
#define SIZE 2
#include "TDatValue.h"

enum class LANGUAGE {
	RUSSIA,
	FRENCH,
	NON
};

enum class WORDTYPE {
	WORD,
	NUMBER,
	SYMBOL
};

enum class ZAGL {
	YES,
	NO,
	NON
};

class TWordStruct : public TDatValue
{
protected:
	int data[SIZE]{};
	WORDTYPE wordType;
	LANGUAGE language;
	ZAGL zagl;

	std::string GetLanguage() const {
		switch (this->language)
		{
			case LANGUAGE::RUSSIA:
				return "Russia";
				break;
			
			case LANGUAGE::FRENCH:
				return "French";
				break;

			default:
				return "Non";
				break;
		}
	}

	std::string GetWordType() const {
		switch (this->wordType)
		{
		case WORDTYPE::WORD :
			return "Word";
			break;

		case WORDTYPE::NUMBER :
			return "Number";
			break;

		default:
			return "Non";
			break;
		}
	}

	std::string GetZagl() const {
		switch (this->zagl)
		{
		case ZAGL::YES:
			return "Yes";
			break;

		case ZAGL::NO:
			return "No";
			break;

		default:
			return "Non";
			break;
		}
	}

public:
	TWordStruct(int count, int length, WORDTYPE wt, LANGUAGE lg, ZAGL zg) : 
		wordType(wt), 
		language(lg), 
		zagl(zg) 
	{
		this->data[0] = count;
		this->data[1] = length;
	}

	void Plus() { this->data[0]++; }

	void Print(std::ostream& out) const override {
		out << "Sum: " << data[0] << ", ";
		out << "Length: " << data[1] << ", ";
		out << "WordType: " << this->GetWordType() << ", ";
		out << "Language: " << this->GetLanguage() << ", ";
		out	<< "Zagl: " << this->GetZagl();
	}

	TDatValue* GetCopy() override {
		return new TWordStruct(data[0], data[1], wordType, language, zagl);
	}
};

