#pragma once
#include "THashTable.h"
#include <list>
class TListHashTable: public THashTable
{
protected:
	size_t tabSize;
	size_t currentList;
	PTTabRecord currentElem;
	std::list<PTTabRecord>* pList;
	std::list<PTTabRecord>::iterator iter;

public:
	TListHashTable(size_t size): tabSize(size), currentList(0), currentElem(0) {
		pList = new std::list<PTTabRecord>[size];
		for (int i = 0; i < size; i++) {
			pList[i] = std::list<PTTabRecord>();
		}
		iter = pList[currentList].begin();
	}
	virtual ~TListHashTable() {
		delete[] pList;
	}

	virtual bool IsFull() const override {
		return pList == nullptr;
	}

	virtual PTDatValue FindRecord(TKey key) override 
	{
		PTDatValue pVal = nullptr;
		currentList = HashFunc(key) % tabSize;
		efficiency = 0;
		
		auto iterator = pList[currentList].begin();
		for ( ; iterator != pList[currentList].end(); ++iterator) {
			efficiency++;
			if ((*iterator)->GetKey() == key)
			{
				pVal = (*iterator)->GetValue();
				currentElem = *iterator;
				//iter = iterator;
				break;
			}
		}
		if (pVal == nullptr) 
			SetRetCode(TAB_NO_RECORD);
		else 
			SetRetCode(TAB_OK);
		return pVal;
	}
	virtual bool InsertRecord(TKey key, PTDatValue val) override {
		if (IsFull()) 
			SetRetCode(TAB_FULL);
		else {
			PTDatValue pVal = FindRecord(key);
			if (pVal != nullptr)
				SetRetCode(TAB_REC_DOUBLE);
			else {
				SetRetCode(TAB_OK);
				dataCount++;
				pList[currentList].push_front(new TTabRecord(key, val));
				return true;
			}
		}
		return false;
	}

	virtual void DeleteRecord(TKey key) override {
		auto tmp = FindRecord(key);
		if (tmp == nullptr) 
			SetRetCode(TAB_NO_RECORD);
		else {
			SetRetCode(TAB_OK);
			dataCount--;
			pList[currentList].remove(currentElem);
		}
	}

	virtual int Reset() override {
		currentList = 0;
		while (pList[currentList].empty() and !IsTabEnded()) currentList++;
		iter = pList[currentList].begin();
		return IsTabEnded();
		/*currentList = 0;
		while (currentList != tabSize) {
			if (pList[currentList] != std::list<PTTabRecord>()) {
				iter = pList[currentList].begin();
				break;
			}
			currentList++;
		}
		return IsTabEnded();*/
	}

	virtual int IsTabEnded() const override {
		return currentList >= tabSize;
	}

	bool IsListEnded() const {
		auto tmp = iter;
		return ++tmp == pList[currentList].end(); // lValue and rValue
	}

	virtual int GoNext() override {
		if (!IsListEnded()) {
			iter++;
		}
		else if (!IsTabEnded()) {
			while (pList[++currentList].empty() and !IsTabEnded());
			iter = pList[currentList].begin();
		}
		//return IsFull();
		return IsTabEnded();
	}

	virtual TKey GetKey() const override {
		return (*iter)->GetKey();
	}

	virtual PTDatValue GetValue() const override {
		return (*iter)->GetValue();
	}
};

