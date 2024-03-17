#pragma once
#include <iostream>
#include <vector>
#include "Warehouse.h"
#include <map>


enum class StampsByLaptops {
	Honor,
	Lenovo,
	Acer,
	Asus,
	Apple
};
enum class StampsByTablets {
	AppleIPad,
	Samsung,
	Huawei,
	Lenovo,
};
enum class StampsByPhone {
	Samsung,
	Honor,
	Oppo,
	IPhone,
	Xiaomi
};




class Company
{
protected:
	Warehouse* address;
	std::vector<std::string> StampsByPhones;
	std::vector<std::string> StampsByTablets;
	std::vector<std::string> StampsByLaptops;

public:
	Company() {
		address = new Warehouse();
		
	}

	void Fill() {

	}
};

