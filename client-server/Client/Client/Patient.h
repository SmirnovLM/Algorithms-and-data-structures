#pragma once
#include <iostream>

// Медицинские Статусы Пациента
enum class State {
	UNDEFINED, // Неопределенный (0)
	REGULAR,   // Обычный        (1)
	MEDIUM,    // Средний        (2)
	CRITICAL   // Критический    (3)
};
class VIP_Patient;
class Patient
{
protected:
	std::string _name;       // Имя Пациента
	std::string _surname;    // Фамилия Пациента
	std::string _patronymic; // Отчество Пациента
	State _patientState;     // Медицинский Статус Пациента

public:
	Patient();
	Patient
	(
		const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		State patientState
	);

	std::string GetName() const;       // Получить Имя Пациента
	std::string GetSurName() const;    // Получить Фамилию Пациента
	std::string GetPatronymic() const; // Получить Отчество Пациента
	State GetStateOfPatient() const;   // Получить Медецинский Статус Пациента

	bool operator>(const Patient& patient) const;    
	bool operator>(const VIP_Patient& patient) const;
	virtual ~Patient() {}
};


class VIP_Patient : public Patient
{
private:
	size_t _money; // Деньги Пациента

public:
	VIP_Patient();
	VIP_Patient
	(
		const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		State patientState,
		size_t money = 1000
	);

	size_t GetCountOfMoney() const; // Получить Количество Денежных Средств Пациента
	bool operator> (const VIP_Patient& patient) const;
	bool operator> (const Patient& patient) const;
};
