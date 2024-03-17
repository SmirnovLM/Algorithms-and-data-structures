#pragma once
#include "TDatValue.h"
#include <iostream>

//typedef std::string TKey;
using TKey = std::string;
                          
class TTabRecord: public TDatValue
{
protected:
	TKey key;         // ���� ������
	PTDatValue value; // ��������� �� �������� ������

	void Print(std::ostream& out) const override {
		out << key << " " << *value;
	}

	// ���������� �������� �����
	void SetKey(const TKey& _key) { 
		key = _key; 
	} 

	// ���������� ��������� �� ������
	void SetValue(PTDatValue _value) { 
		value = _value; 
	}

public:
	TTabRecord(const TKey& _key = "", PTDatValue _value = nullptr) : 
		key(_key), value(_value) {}

	// �������� �������� �����
	TKey GetKey() { 
		return key; 
	}

	// �������� ��������� �� ������
	PTDatValue GetValue() { 
		return value;
	}

	// �������� ������������
	TTabRecord& operator=(const TTabRecord& tr) {
		key = tr.key;
		value = tr.value;
		return *this;
	}

	// ��������� " = "
	bool operator==(const TTabRecord& tr) const {
		return key == tr.key;
	}

	// ��������� " < "
	bool operator<(const TTabRecord& tr) const {
		return key < tr.key;
	}

	// ��������� " > "
	bool operator>(const TTabRecord& tr) const {
		return key > tr.key;
	}

	PTDatValue GetCopy() override {
		return new TTabRecord(key, value);
	}

	// ������������� ������ ��� ��������� ����� ������:
	friend class TArrayTable;
	friend class TScanTable;
};

typedef TTabRecord* PTTabRecord; // using PTTabRecord = TTabRecord*;

