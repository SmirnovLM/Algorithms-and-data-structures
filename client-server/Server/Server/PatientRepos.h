#pragma once
#include <iostream>
#include "Queue.h"
#include "Patient.h"
#include <vector>


// ������ ���������� ���������

class PatientRepos
{
private:
	Queue<Patient> queue_Patients;        // ������� ���������
public:
	PatientRepos();
	void AddPatient(Patient& patient); // �������� �������� � �������
	Patient GetPatient();              // ����� �������� � �������
};

