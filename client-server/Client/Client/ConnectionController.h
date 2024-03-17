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

// Ответ на вход в систему
enum class LoginResponse {
    WRONG,        // Неправильный
    RIGHT,        // Правильный
    ALREADYENTER
};

class ConnectionController
{
private:
    SOCKET connection;
    SOCKADDR_IN addr;

public:
    ConnectionController();

    void Send(const Message mes);      // Отправка Действия
    void Send(const std::string& mes); // Отправка Строки

    std::string RecvString();          // Восстановление Строки
    LoginResponse RecvLoginResponse(); // Восстановление Ответа на вход в систему
};

