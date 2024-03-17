#pragma once
#define SIZE 50
#include "TScanTable.h"
#include <algorithm>

enum class SortMeth {
	BubbleSort,
	QuickSort,
	MergeSort,
	InsertSort,
	FreeChoice
};

class TSortTable : public TScanTable
{
protected:
	SortMeth sortMeth; // Сортировочный метод
	// *& - ссылка на указатель, чтобы напрямую работать с указателем, переданным через параметр в метод.

	// Вызов Сортировочного метода
	void SortData() {
		efficiency = 0;
		switch (sortMeth)
		{
		case SortMeth::BubbleSort:
			BubbleSort(pData, GetDataCount());
			break;

		case SortMeth::InsertSort:
			InsertSort(pData, GetDataCount());
			break;

		case SortMeth::QuickSort:
			QuickSort(pData, GetDataCount());
			break;

		case SortMeth::MergeSort:
			MergeSort(pData, GetDataCount());
			break;

		default:
			FreeChoice(pData, GetDataCount());
			break;
		}
	}

	// 1) Buble Sort
	void BubbleSort(PTTabRecord* data, int size) {
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - i - 1; j++)
			{
				if (data[j]->GetKey() > data[j + 1]->GetKey())
				{
					this->efficiency++;
					PTTabRecord tmp = data[j];
					data[j] = data[j + 1];
					data[j + 1] = tmp;
				}
			}
		}
	}

	// 2) Insert Sort
	void InsertSort(PTTabRecord* data, int size) {
		PTTabRecord curElem;
		this->efficiency = this->dataCount;
		for (int i = 1; i < size; i++)
		{
			for (int j = i; j > 0 && data[j - 1] > data[j]; j--)
			{
				std::swap(data[j - 1], data[j]);
				this->efficiency++;
			}
		}
	}

	// 3) Merge Sort
	void MergeSort(PTTabRecord* data, int size) {
		PTTabRecord* pBuf = new PTTabRecord[size];
		std::copy(data, data + size, pBuf);
		MergeData(data, pBuf, 0, size - 1);
		for (int i = 0; i < size; i++) {
			delete pBuf[i];
		}
		delete[] pBuf;
	}
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int left, int right /*int n1, int n2*/) {
		if (left == right) return;
		int mid = left + right >> 1;

		MergeData(pData, pBuf, left, mid);      // Левая часть
		MergeData(pData, pBuf, mid + 1, right); // Правая часть

		MergeSorter(pData, pBuf, left, mid, right); // Объединение 2х отсортированных частей
	}
	void MergeSorter(PTTabRecord*& pData, PTTabRecord *&pBuf, int left, int mid, int right /*int size*/) 
	{
		int k = left, i = left, j = mid + 1;
		while (i <= mid && j <= right) 
		{
			if (pData[i] <= pData[j]) 
				pBuf[k++] = pData[i++];
			else 
				pBuf[k++] = pData[j++];
		}

		efficiency += mid - i;
		std::copy(pData + i, pData + mid + 1, pBuf + k);

		efficiency += right - left;
		std::copy(pBuf + left, pBuf + right + 1, pData + left);
	}

	// 4) Quick Sort
	void QuickSort(PTTabRecord* data, int size) { 
		QuickSplit(data, 0, size - 1);
	}
	void QuickSplit(PTTabRecord* data, int start, int end) {
		int startInd = start;
		int endInd = end;

		PTTabRecord pivot = data[(start + end) >> 1];
		while (start < end) {
			while (data[start] < pivot) start++;
			while (data[end] > pivot) end--;

			if (start < end) {
				efficiency++;
				std::swap(data[start], data[end]);
				start++;
				end--;
			}
		}

		if (endInd - startInd < 2) return;
		QuickSplit(data, startInd, end);
		QuickSplit(data, start, endInd);
	}

	// Free Choice Sort
	void FreeChoice(PTTabRecord* data, int size) {
		std::sort(data, data + size);
	}

public:
	TSortTable(int size = SIZE) : TScanTable(size) {}
	TSortTable(const TScanTable& st) {
		*this = st;
	}

	// operator =
	TSortTable& operator=(const TScanTable& st) {
		if (pData != nullptr) {
			for (int i = 0; i < dataCount; i++) {
				delete pData[i];
			}
			delete[] pData;
			pData = nullptr;
		}

		size = st.GetSize();
		dataCount = st.GetDataCount();
		pData = new PTTabRecord[size];

		for (int i = 0; i < dataCount; i++) {
			pData[i] = (PTTabRecord)st.pData[i]->GetCopy();
		}

		SortData();
		curPos = 0;
		return *this;
	}

	SortMeth GetSortMeth() {
		return sortMeth;
	}
	void SetSortMeth(SortMeth _sortmeth) {
		sortMeth = _sortmeth;
	}

	std::string GetStringSortMeth() {
		switch (sortMeth)
		{
		case SortMeth::BubbleSort:
			return "BubbleSort"; break;
		case SortMeth::InsertSort:
			return "InsertSort"; break;
		case SortMeth::MergeSort:
			return "MergeSort"; break;
		case SortMeth::QuickSort:
			return "QuickSort"; break;
		default:
			return "FreeChoise"; break;
		}
	}

	virtual PTDatValue FindRecord(TKey key) override {
		int first = 0; 
		int last = dataCount - 1;
		int mid;
		efficiency = 0;
		SetRetCode(TAB_OK);

		while (first < last) {
			efficiency++;
			mid = (first + last) >> 1;

			if (pData[mid]->GetKey() == key) {
				first = mid + 1;
				last = mid;
			}
			if (pData[mid]->GetKey() > key) 
				last = mid - 1;
			else
				first = mid + 1;
		}
		if (last < 0 || pData[last]->GetKey() < key) { // mid < 0 ?
			last++;
		}
		curPos = last;
		if (last < dataCount && (pData[last]->GetKey() == key)) {
			SetRetCode(TAB_OK);
			return pData[last]->GetValue();
		}
		SetRetCode(TAB_NO_RECORD);
		return nullptr;
	}

	virtual bool InsertRecord(TKey key, PTDatValue pVal) override {
		if (IsFull()) {
			SetRetCode(TAB_FULL);
			return false;
		}
		else {
			PTDatValue tmp = FindRecord(key);
			if (RetCode == TAB_OK) {
				SetRetCode(TAB_REC_DOUBLE);
			}
			else {
				RetCode = TAB_OK;
				for (int i = dataCount; i > curPos; i--) {
					pData[i] = pData[i - 1];
				}
				pData[curPos] = new TTabRecord(key, pVal);
				dataCount++;
			}
		}
		return true;
	}

	virtual void DeleteRecord(TKey key) override {
		FindRecord(key);
		if (RetCode == TAB_OK) {
			SetRetCode(TAB_OK);
			for (int i = curPos; i < dataCount - 1; i++) {
				pData[i] = pData[i + 1];
			}
			pData[--dataCount] = nullptr;
		}
		// проблема с утечкой памяти
	}
};

