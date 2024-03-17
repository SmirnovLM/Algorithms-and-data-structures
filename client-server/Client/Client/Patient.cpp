#include "Patient.h"

Patient::Patient() : _patientState(State::UNDEFINED) {}

// Обычный Пациент
Patient::Patient
(
	const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	State patientState
) :
	_name(name),
	_surname(surname),
	_patronymic(patronymic),
	_patientState(patientState)
{}

std::string Patient::GetName() const { return _name; }
std::string Patient::GetSurName() const { return _surname; }
std::string Patient::GetPatronymic() const { return _patronymic; }
State Patient::GetStateOfPatient() const { return _patientState; }

bool Patient::operator>(const Patient& patient) const
{
	if (this->GetStateOfPatient() >= patient.GetStateOfPatient())
		return true;
	else
		return false;
}




// Vip Пациент
VIP_Patient::VIP_Patient() : Patient() {}
VIP_Patient::VIP_Patient
(
	const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	State patientState,
	size_t money
) :
	Patient(name, surname, patronymic, patientState),
	_money(money)
{}

size_t VIP_Patient::GetCountOfMoney() const { return _money; }

bool VIP_Patient::operator>(const VIP_Patient& patient) const {
	if (this->GetStateOfPatient() == State::CRITICAL && patient.GetStateOfPatient() != State::CRITICAL)
		return true;
	if (this->GetCountOfMoney() > patient.GetCountOfMoney() && patient.GetStateOfPatient() != State::CRITICAL)
		return true;
	if (this->GetStateOfPatient() == State::CRITICAL &&
		patient.GetStateOfPatient() == State::CRITICAL &&
		this->GetCountOfMoney() > patient.GetCountOfMoney())
		return true;
	if (this->GetStateOfPatient() != State::CRITICAL &&
		patient.GetStateOfPatient() != State::CRITICAL &&
		this->GetCountOfMoney() > patient.GetCountOfMoney())
		return true;
	return false;
}

bool VIP_Patient::operator>(const Patient& patient) const
{
	if (patient.GetStateOfPatient() == State::CRITICAL && this->GetStateOfPatient() != State::CRITICAL)
		return false;
	else
		return true;
}

bool Patient::operator>(const VIP_Patient& patient) const
{
	if (this->GetStateOfPatient() == State::CRITICAL && patient.GetStateOfPatient() != State::CRITICAL)
		return true;
	else
		return false;
}
