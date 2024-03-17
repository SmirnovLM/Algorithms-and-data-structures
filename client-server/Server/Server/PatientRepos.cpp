#include "PatientRepos.h"


PatientRepos::PatientRepos()
{
	VIP_Patient p1 = VIP_Patient("name1", "surname1", "patromymic1", State::REGULAR, 10000);
	Patient p2 = Patient("name2", "surname2", "patromymic2", State::CRITICAL);
	Patient p3 = Patient("name3", "surname3", "patromymic3", State::REGULAR);
	VIP_Patient p4 = VIP_Patient("name4", "surname4", "patromymic4", State::REGULAR, 30000);
	AddPatient(p1);
	AddPatient(p2);
	AddPatient(p3);
	AddPatient(p4);
}

void PatientRepos::AddPatient(Patient& patient)
{
	if (!queue_Patients.PriorityPush(patient)) 
		throw std::overflow_error("Queue is Full");
}

Patient PatientRepos::GetPatient()
{
    if (!queue_Patients.IsEmpty())
		return queue_Patients.Pop();  
	else
		throw std::out_of_range("Queue is Empty");
}

