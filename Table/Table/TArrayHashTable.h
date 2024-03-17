#pragma once
#include "THashTable.h"
class TArrayHashTable: public THashTable
{
protected:
	PTTabRecord* pData; // память для записей в таблице
	size_t tabSize;     // макс. возм. к-во записей
	size_t freePos;     // свободная позиция (первая свободная строка, обнаруженная при поиске)
	size_t currentPos;  // текущфя позиция (строка памяти при завершении поиска)
	PTTabRecord pMark;  // маркер для индикации строк с удаленными записями
	int hashStep;       // шаг вторичного перемешивания

	int GetNextPosition(size_t position) {
		// ???
		return (position + hashStep) % tabSize;
	}

public:
	explicit TArrayHashTable(size_t size = 50, int step = 7): tabSize(size), hashStep(step)
	{
		pData = new PTTabRecord[size];
		for (int i = 0; i < size; i++) {
			pData[i] = nullptr;
		}
		pMark = new TTabRecord("", nullptr);
		currentPos = 0;
		freePos = -1;
	}

	virtual ~TArrayHashTable() 
	{
		for (int i = 0; i < tabSize; i++) {
			if (pData[i] != nullptr && pData[i] != pMark)
			{
				delete pData[i];
			}
		}
		delete[] pData;
		delete pMark;
	}

	virtual bool IsFull() const override {
		return dataCount >= tabSize;
	}

	virtual PTDatValue FindRecord(TKey key) override 
	{
		SetRetCode(TAB_OK);
		PTDatValue tmp = nullptr;
		freePos = -1;
		efficiency = 0;
		currentPos = HashFunc(key) % tabSize;

		for (int i = 0; i < tabSize; i++) {
			efficiency++;
			if (pData[currentPos] == nullptr) break;
			else if (pData[currentPos] == pMark) {
				if (freePos == -1) freePos = currentPos;
			}
			else if (pData[currentPos]->GetKey() == key) {
				tmp = pData[currentPos]->GetValue();
				break;
			}
			// ???
			currentPos = GetNextPosition(currentPos);
		}

		if (tmp == nullptr) 
			SetRetCode(TAB_NO_RECORD);
		else
			SetRetCode(TAB_OK);

		return tmp;
	}

	virtual bool InsertRecord(TKey key, PTDatValue val) override {
		if (IsFull()) {
			SetRetCode(TAB_FULL);
		}
		else {
			PTDatValue tmp = FindRecord(key);
			if (tmp != nullptr) 
				SetRetCode(TAB_REC_DOUBLE);
			else {
				SetRetCode(TAB_OK);
				if (freePos != -1) 
					currentPos = freePos;
				pData[currentPos] = new TTabRecord(key, val);
				dataCount++;
				return true;
			}
		}
		return false;
		/*if (IsFull()) {
			SetRetCode(TAB_FULL);
		}
		else {
			PTDatValue tmp = FindRecord(key);
			if (GetRetCode() == TAB_NO_RECORD) {
				if (freePos != -1) {
					currentPos = freePos;
				}
				pData[currentPos] = new TTabRecord(key, val);
				dataCount++;
				return true;
			}
			else {
				SetRetCode(TAB_REC_DOUBLE);
			}
		}
		return false;*/
		/*currentPos = HashFunc(key) % tabSize;
		for (int i = 0; i < tabSize; i++) {
			efficiency++;
			if (pData[currentPos] != nullptr && pData[currentPos]->GetKey() == key)
				return false;
			else if (pData[currentPos] == nullptr) {
				pData[currentPos] = new TTabRecord(key, val);
				dataCount++;
			}
			currentPos = GetNextPosition(currentPos);
		}
		SetRetCode(TAB_FULL);
		return true;*/
	}

	virtual void DeleteRecord(TKey key) override {
		PTDatValue tmp = FindRecord(key);
		if (tmp == nullptr) {
			SetRetCode(TAB_NO_RECORD);
		}
		else {
			SetRetCode(TAB_OK);
			delete pData[currentPos];
			pData[currentPos] = pMark;
			dataCount--;
		}
	}

	virtual int Reset() override {
		/*currentPos = 0;
		while (currentPos < tabSize) {
			if (pData[currentPos] != nullptr && pData[currentPos] != pMark)
				break;
			else
				currentPos++;
		}
		return IsTabEnded();*/
		currentPos = 0;
		while (currentPos < tabSize) {
			if (pData[currentPos] != nullptr && pData[currentPos] != pMark) break;
			currentPos++;

		}
		return IsTabEnded();
	}

	virtual int IsTabEnded() const override {
		return currentPos >= tabSize;
	}

	virtual int GoNext() override {
		//if (!IsTabEnded()) {
		//	// ???
		//	while (currentPos < tabSize) {
		//		if (pData[currentPos] != nullptr && pData[currentPos] != pMark) break;
		//	}
		//}
		//return IsTabEnded();
		while (!IsTabEnded()) {
			currentPos++;
			if (pData[currentPos] != nullptr && pData[currentPos] != pMark) break;
		}
		return IsTabEnded();
	}

	virtual TKey GetKey() const override {
		if (currentPos >= 0 && currentPos < tabSize) return pData[currentPos]->GetKey();

		return "";
	}

	virtual PTDatValue GetValue() const override {
		if (currentPos >= 0 && currentPos < tabSize) return pData[currentPos]->GetValue();

		return nullptr;
	}
};

