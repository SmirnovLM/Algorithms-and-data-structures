#pragma once
#include "ConnectionController.h"

class DoctorApplication
{
private:
    ConnectionController connectionController;
    bool online;

    void Working();    // ������ ����������

    void GetPatient(); // ������ �� ��������� ��������
    void Logout();     // ������ �� ����� �� �������
    void Login();      // ������ �� ���� � �������

public:
    DoctorApplication();
};

