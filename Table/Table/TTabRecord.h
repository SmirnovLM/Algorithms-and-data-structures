#pragma once
#include "TDatValue.h"
#include <iostream>

//typedef std::string TKey;
using TKey = std::string;
                          
class TTabRecord: public TDatValue
{
protected:
	TKey key;         // Ключ Записи
	PTDatValue value; // Указатель на Значение Записи

	void Print(std::ostream& out) const override {
		out << key << " " << *value;
	}

	// Установить Значение Ключа
	void SetKey(const TKey& _key) { 
		key = _key; 
	} 

	// Установить Указатель на Данные
	void SetValue(PTDatValue _value) { 
		value = _value; 
	}

public:
	TTabRecord(const TKey& _key = "", PTDatValue _value = nullptr) : 
		key(_key), value(_value) {}

	// Получить Значение Ключа
	TKey GetKey() { 
		return key; 
	}

	// Получить Указатель на Данные
	PTDatValue GetValue() { 
		return value;
	}

	// Оператор Присваивания
	TTabRecord& operator=(const TTabRecord& tr) {
		key = tr.key;
		value = tr.value;
		return *this;
	}

	// Сравнение " = "
	bool operator==(const TTabRecord& tr) const {
		return key == tr.key;
	}

	// Сравнение " < "
	bool operator<(const TTabRecord& tr) const {
		return key < tr.key;
	}

	// Сравнение " > "
	bool operator>(const TTabRecord& tr) const {
		return key > tr.key;
	}

	PTDatValue GetCopy() override {
		return new TTabRecord(key, value);
	}

	// Дружественные классы для различных типов таблиц:
	friend class TArrayTable;
	friend class TScanTable;
};

typedef TTabRecord* PTTabRecord; // using PTTabRecord = TTabRecord*;

