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
    
    // Сообщение
    enum class Message {
        LOGIN,       // Сообщение о входе в систему
        GETPATIENT,  // Получить Пациента
        LOGOUT       // Сообщение о выходе из системы
    };

    // Ответ на вход в систему
    enum class LoginResponse {
        WRONG,        // неправильный
        RIGHT,        // правильный
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

