#pragma once
#include "TDatValue.h"
#include <vector>

// �����: 
class TMonom : public TDatValue {
protected:
	double coef;              // �����������
	std::vector<int> degress; // ������ ��������

public:
	TMonom(double _coef, std::vector<int> _degress);
	virtual TDatValue* GetCopy();

	double GetCoef(void) const;
	std::vector<int> GetDegress(void) const;

	TMonom& operator=(const TMonom& tmp);

	bool operator==(const TMonom& tmp) const;
	bool operator<(const TMonom& tmp) const; // ���������������� �������

	friend class TPolinom;
};
