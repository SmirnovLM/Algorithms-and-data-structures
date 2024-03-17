#pragma once
#include "TTabRecord.h"
#include "TDatCom.h"
#define TAB_OK 0       // ��� ������  
#define TAB_EMPTY -101
#define TAB_FULL -102
#define TAB_NO_RECORD -103
#define TAB_REC_DOUBLE -104
#define TAB_NO_MEMBER -105

// ����������� ������� �����, ���������� ������������ ������� �������
class TTable: public TDatCom
{
protected:
	size_t dataCount;  // ���������� ������� � �������
	size_t efficiency; // ���������� ������������� ���������� ��������

public:
	TTable(size_t _dataCount = 0, size_t _efficiency = 0) :
		dataCount(_dataCount), efficiency(_efficiency) {}

	~TTable() {} // ���� ������ �������, ��� �����?

	// �������������� ������:
	size_t GetDataCount() const { return dataCount; }
	size_t GetEfficiency() const { return efficiency; }
	bool IsEmpty() const { return dataCount == 0; }
	virtual bool IsFull() const = 0;

	// ������ ������� � �������:
	virtual TKey GetKey() const = 0;         // �������� �������� ����� ������� ������
	virtual PTDatValue GetValue() const = 0; // �������� ��������� �� �������� ������� ������

	// ������ ��������� �������:
	virtual PTDatValue FindRecord(const TKey key) = 0;                     // ����� ������ �� �������� �����
	virtual bool InsertRecord(const TKey key, const PTDatValue value) = 0; // ������� ������ � �������
	virtual void DeleteRecord(const TKey key) = 0;                         // �������� �����
	
	// ��������� (��������):
	virtual int Reset() = 0;            // ���������� ������� ������� �� ������ ������
	virtual int IsTabEnded() const = 0; // �������� ���������� �������
	virtual int GoNext() = 0;           // ����������� ������� ������� �� ��������� ������
	// (=1 ����� ���������� ��� ��������� ������ �������)

	friend std::ostream& operator<<(std::ostream& out, TTable& table) {
		for (table.Reset(); !table.IsTabEnded(); table.GoNext()) {
			out << "KEY: " << table.GetKey();
			for (int i = 0; i < 25 - table.GetKey().length(); i++) out << " ";

			out << "VALUE: " << *table.GetValue();
			out	<< std::endl;
		}
		return out;
	}
};

