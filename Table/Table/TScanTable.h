#pragma once
#define SIZE 50
#include "TArrayTable.h"

class TScanTable: public TArrayTable
{
public:
	TScanTable(size_t size = SIZE) : TArrayTable(size) {}

	virtual PTDatValue FindRecord(TKey key) {
		int i;
		SetRetCode(TAB_OK);
		for (i = 0; i < dataCount; i++) {
			if (pData[i]->GetKey() == key) {
				break;
			}
		}
		efficiency = i + 1;
		if (i < dataCount) {
			curPos = i;
			return pData[curPos]->value;
		}

		SetRetCode(TAB_NO_RECORD);
		return nullptr;
	}

	virtual bool InsertRecord(TKey key, PTDatValue value) {
		if (IsFull()) {
			SetRetCode(TAB_FULL);
			return false;
		}

		pData[dataCount] = new TTabRecord(key, value);
		dataCount++;
		SetRetCode(TAB_OK);
		return true;
	}

	virtual void DeleteRecord(TKey key) {
		PTDatValue tmp = FindRecord(key);
		if (FindRecord(key) == nullptr)
			SetRetCode(TAB_NO_RECORD);
		else {
			SetRetCode(TAB_OK);
			/*this->pData[this->curPos] = this->pData[this->dataCount - 1];
			this->pData[--this->dataCount] = nullptr;*/
			for (int i = curPos; i < dataCount - 1; i++) {
				pData[i] = pData[i + 1];
			}
			pData[--dataCount] = nullptr;
		}
	}
};

