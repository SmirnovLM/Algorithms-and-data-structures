#pragma once
#include <iostream>
#include "Queue.h"
#include "Patient.h"
#include <vector>


// Логика добавление пациентов

class PatientRepos
{
private:
	Queue<Patient> queue_Patients;        // Очередь Пациентов
public:
	PatientRepos();
	void AddPatient(Patient& patient); // Добавить Пациента в Очередь
	Patient GetPatient();              // Взять Пациента с Очереди
};

