#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 
#include <iostream>
#include <string>
#include "DataHandler.h"

#pragma warning(disable: 4996)


enum class Message {
    LOGIN,
    GETPATIENT,
    LOGOUT,
    ERRORR
};

// ����� �� ���� � �������
enum class LoginResponse {
    WRONG,        // ������������
    RIGHT,        // ����������
    ALREADYENTER
};

class ConnectionController
{
private:
    SOCKET connection;
    SOCKADDR_IN addr;

public:
    ConnectionController();

    void Send(const Message mes);      // �������� ��������
    void Send(const std::string& mes); // �������� ������

    std::string RecvString();          // �������������� ������
    LoginResponse RecvLoginResponse(); // �������������� ������ �� ���� � �������
};

