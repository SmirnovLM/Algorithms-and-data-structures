#pragma once
#include <iostream>

// ����������� ����� ��������-��������
class TDatValue
{
protected:
	virtual void Print(std::ostream& out) const = 0;

public:
	TDatValue() = default; 

	virtual TDatValue* GetCopy() = 0; // �������� �����

	friend std::ostream& operator<<(std::ostream& out, TDatValue& dv) {
		//? TDatValue == nullpointer;
	    dv.Print(out);
		return out;
	}
};

typedef TDatValue* PTDatValue; // TDatValue* = PTDatValue

