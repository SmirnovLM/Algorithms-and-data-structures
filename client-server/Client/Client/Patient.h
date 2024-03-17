#pragma once
#include <iostream>

// ����������� ������� ��������
enum class State {
	UNDEFINED, // �������������� (0)
	REGULAR,   // �������        (1)
	MEDIUM,    // �������        (2)
	CRITICAL   // �����������    (3)
};
class VIP_Patient;
class Patient
{
protected:
	std::string _name;       // ��� ��������
	std::string _surname;    // ������� ��������
	std::string _patronymic; // �������� ��������
	State _patientState;     // ����������� ������ ��������

public:
	Patient();
	Patient
	(
		const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		State patientState
	);

	std::string GetName() const;       // �������� ��� ��������
	std::string GetSurName() const;    // �������� ������� ��������
	std::string GetPatronymic() const; // �������� �������� ��������
	State GetStateOfPatient() const;   // �������� ����������� ������ ��������

	bool operator>(const Patient& patient) const;    
	bool operator>(const VIP_Patient& patient) const;
	virtual ~Patient() {}
};


class VIP_Patient : public Patient
{
private:
	size_t _money; // ������ ��������

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

	size_t GetCountOfMoney() const; // �������� ���������� �������� ������� ��������
	bool operator> (const VIP_Patient& patient) const;
	bool operator> (const Patient& patient) const;
};
