#pragma once
#include "TRootLink.h"

class TDatLink;
typedef TDatLink* PTDatLink;

class TDatLink: public TRootLink {
protected:
	PTDatValue pValue;
public:
	TDatLink(PTDatValue _pValue = nullptr, PTRootLink pN = nullptr): TRootLink(pN) {
		pValue = _pValue;
	}
	PTDatValue GetDatValue() {
		return pValue;
	}
	PTDatLink GetNextDatLink() {
		return static_cast<PTDatLink>(pNext);
	}

	friend class TDatList;
};
