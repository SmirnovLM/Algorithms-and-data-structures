#pragma once
#include "TTable.h"
#define SIZE 100000
;
#define InitialFNV 2166136261U;
#define FNVMultiple 16777619;

//typedef unsigned long long ull;

class THashTable : public TTable
{
protected:
	virtual unsigned long long HashFunc(const TKey& key) {
		//Хеш ф-ия генерирует индекс для ключа!!!
		/*unsigned long long hv = 0;
		int keySize = key.size();
		for (int i = 0; i < keySize; i++) {
			hv = (hv << 3) + key[i];
		}
		return hv;*/

		/*int seed = 131;
		unsigned long long hv = 0;
		for (int i = 0; i < key.size(); i++) {
			hv = (hv * seed) + key[i];
		}
		return hv % SIZE;*/

		unsigned long long sum = 0;
		for (int k = 0; k < key.size(); k++)
			sum = sum + int(key[k]);
		return sum % SIZE; ///////////

		/*unsigned long long hv = InitialFNV;
		for (size_t i = 0; i < key.size(); i++) {
			hv = hv ^ (key[i]);
			hv = hv * FNVMultiple;
		}
		return hv;*/

		/*return 0;*/
	}
	
public:
	THashTable() : TTable() {}
};

