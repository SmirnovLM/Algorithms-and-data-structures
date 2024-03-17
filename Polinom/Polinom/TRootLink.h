#pragma once
#include "TDatValue.h"

class TRootLink;
typedef TRootLink* PTRootLink;
typedef TDatValue* PTDatValue;

class TRootLink {
protected:
	PTRootLink pNext;
public:
	TRootLink(PTRootLink pN = nullptr) { pNext = pN; }

	PTRootLink GetNext() { return pNext; }

	void SetNextLink(PTRootLink newNextLink) {
		pNext = newNextLink;
	}

	void InsertNextLink(PTRootLink newNextLink) {
		PTRootLink tmp = pNext;
		pNext = newNextLink;
		if (newNextLink != nullptr)
			newNextLink->pNext = tmp;
	}

	virtual void SetDataValue(PTDatValue pVal) = 0;
	virtual PTDatValue GetDatValue() = 0;

	friend class TDatList;
};
