#include "TMonom.h"

TMonom::TMonom(double _coef, std::vector<int> _degress) 
{
	coef = _coef;
	degress = _degress;
}

TDatValue* TMonom::GetCopy() 
{
	return new TMonom(this->coef, this->degress);
}

double TMonom::GetCoef(void) const
{
	return coef;
}

std::vector<int> TMonom::GetDegress(void) const
{
	return degress;
}

TMonom& TMonom::operator=(const TMonom& tmp)
{
	this->coef = tmp.coef;
	this->degress = tmp.degress;
	return *this;
}

bool TMonom::operator==(const TMonom& tmp) const
{
	return (this->coef == tmp.coef && degress == tmp.degress);
}

bool TMonom::operator<(const TMonom& tmp) const
{
	return false;
}
