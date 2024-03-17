#pragma once
#include <iostream>
#include "Patient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataHandler
{
public:
	// �������������� ������� ���� "Patient" � ������ ������ "json"
	static std::string Packing(const Patient& patient);

	// �������������� �� ������ "json" � ������ ���� "Patient" ��� "VIP_Patient"
	static Patient Unpacking(const std::string& str);
};


