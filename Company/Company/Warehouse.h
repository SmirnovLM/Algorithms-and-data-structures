#pragma once
#include <iostream>
#include <iomanip>
#include "ElectronicEquipment.h"

#define SIZE 100
#define SizeWarehouseOfLaptops 10
#define SizeWarehouseOfTables 30
#define SizeWarehouseOfSmartphones 60

#define IndexStartForLaptops 0
#define IndexStartForTablets 10
#define IndexStartForSmartphones 40

class Warehouse
{
protected:
	PElectronicEquipment* pData;
	size_t size;
	size_t cur1;
	size_t cur2;
	size_t cur3;

public:
	Warehouse(size_t _size = SIZE): 
		size(_size), 
		cur1(IndexStartForLaptops), 
		cur2(IndexStartForTablets), 
		cur3(IndexStartForSmartphones) 
	{
		pData = new PElectronicEquipment[_size];
		for (size_t i = 0; i < size; i++) {
			pData[i] = nullptr;
		}
	}

	virtual ~Warehouse() {
		for (int i = 0; i < size; i++) {
			delete pData[i];
		}
		delete[] pData;
	}

	size_t GetSizeOfSmartphones() const {
		size_t k = 0;
		for (size_t i = SizeWarehouseOfTables; i < SizeWarehouseOfSmartphones; i++) {
			if (pData[i] == nullptr)
				continue;
			else
				k++;
		}
		return k;
	}
	size_t GetSizeOfTablets() const {
		size_t k = 0;
		for (size_t i = SizeWarehouseOfLaptops; i < SizeWarehouseOfTables; i++) {
			if (pData[i] == nullptr)
				continue;
			else
				k++;
		}
		return k;
	}
	size_t GetSizeOfLaptops() const {
		size_t k = 0;
		for (size_t i = 0; i < SizeWarehouseOfLaptops; i++) {
			if (pData[i] == nullptr)
				continue;
			else
				k++;
		}
		return k;
	}

	PElectronicEquipment operator[](size_t index) {
		return pData[index];
	}

	void Insert(PElectronicEquipment s) {

		Laptop tmp1;
		Tablet tmp2;
		Smartphone tmp3;

		if (dynamic_cast<Laptop*>(s) != nullptr) { 
			pData[cur1++] = s;
		}
		if (dynamic_cast<Tablet*>(s) != nullptr) {
			pData[cur2++] = s;
		}
		if (dynamic_cast<Smartphone*>(s) != nullptr) {
			pData[cur3++] = s;
		}
	}

	void Delete(size_t l, size_t t, size_t s) {
		while (l > 0) {
			l--;
			delete pData[--cur1];
			pData[cur1] = nullptr;
		}
		
		while (t > 0) {
			t--;
			delete pData[--cur2];
			pData[cur2] = nullptr;
		}

		while (s > 0) {
			s--;
			delete pData[--cur3];
			pData[cur3] = nullptr;
		}
	}

    void PrintLaptops(std::ostream& out) {
		out << "Laptops:\n";
		out << "---------------------------------------------------------------------------------\n";
		out << "| " << std::setw(20) << std::left << "Name";
		out << "| " << std::setw(15) << std::left << "Price (RUR)";
		out << "| " << std::setw(10) << std::left << "RAM (GB)";
		out << "| " << std::setw(10) << std::left << "SDD (GB)";
		out << "| " << std::setw(15) << std::left << "Weight (Gram)" << "|\n";
		out << "---------------------------------------------------------------------------------\n";

		for (size_t i = IndexStartForLaptops; i < IndexStartForTablets; i++)
		{
			if ((*this)[i] == nullptr)
				continue;
			else
				out << *((*this)[i]) << "\n";
		}
		out << "---------------------------------------------------------------------------------\n\n";
	}

	void PrintTablets(std::ostream& out) {
		out << "Tablets:\n";
		out << "---------------------------------------------------------------------------------\n";
		out << "| " << std::setw(20) << std::left << "Name";
		out << "| " << std::setw(15) << std::left << "Price (RUR)";
		out << "| " << std::setw(10) << std::left << "RAM (GB)";
		out << "| " << std::setw(10) << std::left << "SDD (GB)";
		out << "| " << std::setw(15) << std::left << "Weight (Gram)" << "|\n";
		out << "---------------------------------------------------------------------------------\n";

		for (size_t i = IndexStartForTablets; i < IndexStartForSmartphones; i++)
		{
			if ((*this)[i] == nullptr)
				continue;
			else
				out << *((*this)[i]) << "\n";
		}
		out << "---------------------------------------------------------------------------------\n\n";
	}

	void PrintSmartphones(std::ostream& out) {
		out << "Smartphones:\n";
		out << "---------------------------------------------------------------------------------\n";
		out << "| " << std::setw(20) << std::left << "Name";
		out << "| " << std::setw(15) << std::left << "Price (RUR)";
		out << "| " << std::setw(10) << std::left << "RAM (GB)";
		out << "| " << std::setw(10) << std::left << "SDD (GB)";
		out << "| " << std::setw(15) << std::left << "Weight (Gram)" << "|\n";
		out << "---------------------------------------------------------------------------------\n";

		for (size_t i = IndexStartForSmartphones; i < SIZE; i++)
		{
			if ((*this)[i] == nullptr)
				continue;
			else
				out << *((*this)[i]) << "\n";
		}
		out << "---------------------------------------------------------------------------------\n\n";
	}

	friend std::ostream& operator<<(std::ostream& out, Warehouse& w) {
		w.PrintLaptops(out);
		w.PrintTablets(out);
		w.PrintSmartphones(out);
		return out;
	}
};

