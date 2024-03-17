#include <iostream>
#include <vector>
#include "TTable.h"
#include "TDatValue.h"
#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TWordStruct.h"
#include "TSortTable.h"
#include "FileReader.h"
#include <fstream>
#include "THashTable.h"
#include "TArrayHashTable.h"
#include "TListHashTable.h"
//#include <Windows.h>

enum class Table {
	SCANTABLE,
	SORTTABLE,
	ARRAYHASHTABLE,
	LISTHASHTABLE
};

int main() {
	std::vector<std::string> v;
	std::string filename1;
	std::string word;
	filename1 = "..\\Table.txt";
	std::ifstream file(filename1);
	if (!file.is_open())
		return -1;
	while (!file.eof()) {
		file >> word;
		v.push_back(word);
	}
	file.close();

	//SetConsoleOutputCP(1251);
	//SetConsoleCP(1251);
	Table tt = Table::ARRAYHASHTABLE;
	switch (tt)
	{
	case Table::SCANTABLE: std::cout << "ScanTable:\n";
		break;
	case Table::SORTTABLE: std::cout << "SortTable:\n";
		break;
	case Table::ARRAYHASHTABLE: std::cout << "ArrayHashTable\n";
		break;
	case Table::LISTHASHTABLE: std::cout << "ListHashTable\n";
		break;
	}

	//TTable* t = new TScanTable(100000); // "attract"
	//TTable* t = new TSortTable(100000);
	//TTable* t = new TListHashTable(100000);
	TTable* t = new TArrayHashTable(100000); // "disrespectfully"

	clock_t begin;

	std::string filename;
	filename = "..\\test.txt";
	FileReader fr(filename);

	begin = clock();
	fr.FileRead(t);
	std::cout << "1) Creating" << ", Time: " << (double)(clock() - begin) / (double)CLOCKS_PER_SEC << "\n\n";

	begin = clock();
	for (size_t i = 0; i < 55999; i++) {
		t->FindRecord(v[i]);
	}
	//std::cout << t->FindRecord("Macked") << std::endl;
	std::cout << "2) Finding" << ", Time: " << (double)(clock() - begin) / (double)CLOCKS_PER_SEC << "\n\n";

	begin = clock();
	t->DeleteRecord("Macked");
	std::cout << "3) Delete" << ", Time: " << (double)(clock() - begin) / (double)CLOCKS_PER_SEC << "\n\n";

	begin = clock();
	std::cout << t->InsertRecord("seeeen", new TWordStruct(1, 6, WORDTYPE::WORD, LANGUAGE::FRENCH, ZAGL::NO)) << std::endl;
	std::cout << "4) Insert" << ", Time: " << (double)(clock() - begin) / (double)CLOCKS_PER_SEC << "\n\n";

	//begin = clock();
	//std::cout << *t;
	//std::cout << "\n";
	//std::cout << "Printing" << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";

	std::cout << "Count of Data: " << t->GetDataCount() << "\n";
	//		std::cout << "Sorts Methoods:\n";
	//		TSortTable sort1, sort2, sort3, sort4, sort5 = TSortTable(1000000);
	//		sort1.SetSortMeth(SortMeth::BubbleSort);
	//		begin = clock();
	//		sort1 = *t;
	//		std::cout << sort1.GetStringSortMeth() << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";
	//		sort2.SetSortMeth(SortMeth::InsertSort);
	//		begin = clock();
	//		sort2 = *t;
	//		std::cout << sort2.GetStringSortMeth() << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";
	//		sort3.SetSortMeth(SortMeth::MergeSort);
	//		begin = clock();
	//		sort3 = *t;
	//		std::cout << sort3.GetStringSortMeth() << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";
	//		sort4.SetSortMeth(SortMeth::QuickSort);
	//		begin = clock();
	//		sort4 = *t;
	//		std::cout << sort4.GetStringSortMeth() << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";
	//		sort5.SetSortMeth(SortMeth::FreeChoice);
	//		begin = clock();
	//		sort5 = *t;
	//		std::cout << sort5.GetStringSortMeth() << ", Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "\n";

	return 0;
}

