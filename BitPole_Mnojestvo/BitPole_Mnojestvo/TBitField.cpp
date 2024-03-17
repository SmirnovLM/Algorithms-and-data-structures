#include "TBitField.h"

int TBitField::GetMemIndex(const int n) const
{
	return n >> 5; // (n / 32) = (n / 2^5)
}

TELEM TBitField::GetMemMask(const int n) const
{
	return 1 << (n & 31); // n % 32 = n & 31
	// 31 =     011 111
	// n = 63 = 111 111
	//          011 111
	// 1 << 2:  0001 -> 0100  
}

// throw - выкидывает появление ошибки
TBitField::TBitField (int len): BitLen(len) 
{
	if (BitLen < 1) throw BitLen;
	if (BitLen < 32) MemLen = (len + 31) >> 5; // Деление "/" на 32 = 2^5
	else MemLen = ((len - 1) >> 5) + 1;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
	else
		throw "ERROR";
}

TBitField::TBitField(const TBitField& bf) 
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	else
		throw "ERROR";
}

TBitField::~TBitField() 
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetLength() const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n >= BitLen || n < 0)
		throw ("ERROR: n = " + n);
	else
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n >= BitLen || n < 0)
		throw ("ERROR: n = " + n);
	else
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n >= BitLen || n < 0) 
		throw ("ERROR: n = " + n);
	if (n > -1 || n < BitLen) 
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	return 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen != bf.BitLen)
		return false;
	for (size_t i = 0; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i))
			return false;
	return true;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	// Проверка на самоприсваивание

	if (this->MemLen != bf.MemLen)
	{
		this->MemLen = bf.MemLen;
		if (pMem != nullptr) {
			delete[] pMem;
		}
		this->pMem = new TELEM[MemLen];
	}

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

TBitField& TBitField::operator|(const TBitField& bf) const
{
	int bitlen = BitLen;
	if (bf.BitLen > bitlen) {
		bitlen = bf.BitLen;
	}
	TBitField tbf = TBitField(bitlen);
	for (size_t i = 0; i < MemLen; i++) {
		tbf.pMem[i] = pMem[i];
	}
	for (size_t i = 0; i < bf.MemLen; i++) {
		tbf.pMem[i] |= bf.pMem[i];
	}
	return tbf;
}

TBitField& TBitField::operator&(const TBitField& bf)
{
	int bitlen = BitLen;
	if (bf.BitLen > bitlen) {
		bitlen = bf.BitLen;
	}
	TBitField tbf = TBitField(bitlen);
	for (size_t i = 0; i < MemLen; i++) {
		tbf.pMem[i] = pMem[i];
	}
	for (size_t i = 0; i < bf.MemLen; i++) {
		tbf.pMem[i] &= bf.pMem[i];
	}
	return tbf;
}

TBitField& TBitField::operator~() const
{
	int bitlen = GetLength();
	TBitField tbf(bitlen);
	for (int i = 0; i < MemLen; i++) {
		tbf.pMem[i] = ~pMem[i];
	}
	return tbf;
}

std::istream& operator>>(std::istream& in, TBitField& bf)
{
	int bitlen = bf.GetLength();
	std::cout << "Input the train of the TBitField" << std::endl;
	for (size_t i = 0; i < bitlen; i++) {
		unsigned int k;
		in >> k;
	    bf.SetBit(k);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const TBitField& bf)
{
	int bitlen = bf.GetLength();
	for (size_t i = 0; i < bitlen; i++) {
		out << (bf.GetBit(i) > 0 ? 1 : 0);
	}
	out << std::endl;
	return out;
}
