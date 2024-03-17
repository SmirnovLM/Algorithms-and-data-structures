#pragma once

#include <iostream>
#include "AccountsRepos.h"
#include "PatientRepos.h"
#include "DataHandler.h"
#include <winsock2.h>
#include <vector>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

class ConnectionListener
{
private:
    static SOCKET connections[10];
    static AccountsRepos accountsRepos;
    static PatientRepos repository;
    static int counter;

    SOCKET sListen;
    SOCKADDR_IN addr;
    int sizeOfAddr;
    
    // ���������
    enum class Message {
        LOGIN,       // ��������� � ����� � �������
        GETPATIENT,  // �������� ��������
        LOGOUT       // ��������� � ������ �� �������
    };

    // ����� �� ���� � �������
    enum class LoginResponse {
        WRONG,        // ������������
        RIGHT,        // ����������
        ALREADYENTER
    };

    static void ClientHandler(int index);
    void Listen();

    static void Login(int index);
    static void Logout(int index);
    static void GetPatient(int index);
       
public:
    ConnectionListener();
};

