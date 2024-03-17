#pragma once
#include "TTable.h"
#define TabMaxSize 50

enum class Position {
	FIRST, 
	CURRENT, 
	LAST
};

// Абстрактный класс для таблиц с непрерывной памятью служит для управления структурой хранения
class TArrayTable : public TTable
{
protected:
	PTTabRecord* pData; // Память для записей таблицы
	size_t size;        // Макс. возм. колич. записей в таблице
	size_t curPos;      // Номер текущей записи, начиная c <0>

public:

	TArrayTable(size_t _size = TabMaxSize): size(_size), curPos(0) {
		pData = new PTTabRecord[size];
		for (int i = 0; i < size; i++) {
			pData[i] = nullptr;
		}
	}

	virtual ~TArrayTable() {
		for (int i = 0; i < size; i++) {
			delete pData[i];
		}
		delete[] pData;
	}

	size_t GetSize() const { 
		return size; 
	}

	//Информационные Методы
	virtual bool IsFull() const override {
		return dataCount >= size;
	}
	int GetTabSize() const {
		int k = 0;
		for (size_t i = 0; i < this->size; i++)
			this->pData[i] == nullptr ? k : k++;
		return k;
	}

	// Методы Доступа к Записям 

	virtual TKey GetKey() const {
		return GetKey(Position::CURRENT);
	}
	virtual TKey GetKey(Position position) const {
		int localPosition = -1;
		if (!IsEmpty()) 
		{
			switch (position) 
			{
				case Position::FIRST:
					localPosition = 0;
					break;
				case Position::LAST: 
					localPosition = dataCount - 1;
					break;
				default:
					localPosition = curPos;
					break;
			}
		}
		return (localPosition == -1 ? std::string("") : pData[localPosition]->GetKey());
	}
	
	virtual PTDatValue GetValue() const {
		return GetValue(Position::CURRENT);
	}
	virtual PTDatValue GetValue(Position position) const {
		int localPosition = -1;
		if (!IsEmpty())
		{
			switch (position)
			{
			case Position::FIRST:
				localPosition = 0;
				break;
			case Position::LAST:
				localPosition = dataCount - 1;
				break;
			default:
				localPosition = curPos;
				break;
			}
		}
		
		return (localPosition == -1 ? nullptr : pData[localPosition]->GetValue());
	}
	

	virtual int Reset(void) {
		curPos = 0;
		return IsTabEnded();
	}
	virtual int IsTabEnded(void) const {
		return curPos >= dataCount;
	}
	virtual int GoNext(void) {
		if (!IsTabEnded()) {
			curPos++;
		}
		return IsTabEnded();
	}

	virtual int SetCurrentPos(int pos) {
		if (pos < 0 || pos > dataCount)
			curPos = 0;
		else
			curPos = pos;
		return IsTabEnded();
	}

	int GetCurrentPos(void) const {
		return curPos;
	}
	friend class TSortTable;
};

