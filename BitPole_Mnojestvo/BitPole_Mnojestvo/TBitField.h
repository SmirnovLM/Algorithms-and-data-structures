#pragma once
#include <iostream>

typedef unsigned int TELEM; // ������� unsigned int -> TELEM (32 ����)

class TBitField
{
private:
	// �������� �����
	TELEM* pMem; // ������ ��� ������������� �������� ����
	int MemLen;  // �-�� ��-��� ���� ��� ������������� �������� ����
	int BitLen;  // ����� �������� ���� - ���� ���. ���

	// ������� ����� pMem, � ������� ���������� ������ �������� ������� (100 - 4)
	int GetMemIndex(const int n) const;
	// ����������� ��������� �����
	TELEM GetMemMask(const int n) const;

public:
	// ����� ���������� ��� � ���������
	TBitField(int memLen);
	TBitField(const TBitField& bf);
	~TBitField();

	// ������ � �����
	int GetLength() const;         // ������� ���������� ��������� �����
	void SetBit(const int n);      // ��������� ����������� ���� � ������� (����������)
	void ClrBit(const int n);      // ������� �������� ����������� ����
	int GetBit(const int n) const; // ������� �������� �������������� ����

	// ���������� ���������� ���������
	int operator ==(const TBitField& bf) const;
	int operator !=(const TBitField& bf) const;

	// �������� ������������
	TBitField& operator =(const TBitField& bf);

	// ���������� |
	TBitField& operator |(const TBitField& bf) const;

	// ���������� &
	TBitField& operator &(const TBitField& bf);

	// ��������� ~
	TBitField& operator ~() const;

	// COUT, CIN
	friend std::istream& operator >>(std::istream& in, TBitField& a);
	friend std::ostream& operator <<(std::ostream& out, const TBitField& a);
};

