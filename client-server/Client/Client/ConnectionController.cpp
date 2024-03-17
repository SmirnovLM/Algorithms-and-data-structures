#include "ConnectionController.h"

ConnectionController::ConnectionController() {
    std::cout << "/// Client Service ///\n";
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);

    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error\n" << std::endl;
        exit(1);
    }

    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);  
    addr.sin_family = AF_INET;                    

    connection = socket(AF_INET, SOCK_STREAM, NULL);

    if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: Client not connected to service!\n";
        exit(1);
    }
    Sleep(10);
    std::cout << "Connected!\n\n";
}

// �������� ��������
void ConnectionController::Send(const Message message) {
    send(connection, (char*)&message, sizeof(Message), NULL);  // �������� ��������
}

// �������� ������
void ConnectionController::Send(const std::string& message) {
    int message_size = message.length();                       // ������ ������
    send(connection, (char*)&message_size, sizeof(int), NULL); // �������� ������� ������
    send(connection, message.c_str(), message_size, NULL);     // �������� ������
}

// �������������� ������
std::string ConnectionController::RecvString() {
    int msg_size;
    recv(connection, (char*)&msg_size, sizeof(int), NULL); // ����� ������� ������
    
    char* msg = new char[msg_size + 1];
    msg[msg_size] = '\0';
    recv(connection, msg, msg_size, NULL); // ����� ������

    return msg;
}

// �������������� ������ �� ���� � �������
LoginResponse ConnectionController::RecvLoginResponse() {
    LoginResponse resp;
    recv(connection, (char*)&resp, sizeof(LoginResponse), NULL);
    return resp;
}