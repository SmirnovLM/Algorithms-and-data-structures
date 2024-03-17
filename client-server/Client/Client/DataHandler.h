#pragma once
#include <iostream>
#include "Patient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataHandler
{
public:
	// Преобразование объекта типа "Patient" в формат Строки "json"
	static std::string Packing(const Patient& patient);

	// Преобразование из Строки "json" в объект типа "Patient" или "VIP_Patient"
	static Patient Unpacking(const std::string& str);
};


