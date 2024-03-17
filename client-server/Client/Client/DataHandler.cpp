#include "DataHandler.h"

// Преобразование объекта типа "Patient" в формат Строки "json"
std::string DataHandler::Packing(const Patient& patient)
{
	json jsonString{};

	jsonString["name"] = patient.GetName();
	jsonString["surname"] = patient.GetSurName();
	jsonString["patronymic"] = patient.GetPatronymic();
	jsonString["state"] = patient.GetStateOfPatient();

	return jsonString.dump();
}

// Преобразование из Строки "json" в объект типа "Patient" или "VIP_Patient"
Patient DataHandler::Unpacking(const std::string& str)
{
	json jsonString = json::parse(str);
	return Patient
	(
		jsonString["name"].get<std::string>(),
		jsonString["surname"].get<std::string>(),
		jsonString["patronymic"].get<std::string>(),
		jsonString["state"].get<State>()
	);
}