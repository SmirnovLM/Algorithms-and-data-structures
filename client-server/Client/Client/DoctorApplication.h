#pragma once
#include "ConnectionController.h"

class DoctorApplication
{
private:
    ConnectionController connectionController;
    bool online;

    void Working();    // Работа Приложения

    void GetPatient(); // Запрос на Получение Пациента
    void Logout();     // Запрос на Выход из Системы
    void Login();      // Запрос на Вход в Систему

public:
    DoctorApplication();
};

