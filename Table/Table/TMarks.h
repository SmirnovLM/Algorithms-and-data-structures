#pragma once
#define SIZE 5
#include "TDatValue.h"

class TMarks : public TDatValue
{
private:
	int _marks[SIZE];

public:
	TMarks(int m1, int m2, int m3, int m4, int m5) {
		_marks[0] = m1;
		_marks[1] = m2;
		_marks[2] = m3;
		_marks[3] = m4;
		_marks[4] = m5;
		
	}
	void Print(std::ostream& out) const override {
		for (int i = 0; i < SIZE; i++) {
			out << _marks[i] << "\t";
		}

	}
	TDatValue* GetCopy() override {
		return new TMarks(_marks[0], _marks[1], _marks[2], _marks[3], _marks[4]);
	}
};

