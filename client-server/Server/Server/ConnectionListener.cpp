#include "ConnectionListener.h"

ConnectionListener::ConnectionListener() 
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) { 
		std::cout << "ERROR\n";
		exit(1);
	}

	sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	Listen();
}

void ConnectionListener::Listen()
{
	listen(sListen, SOMAXCONN);
	std::cout << "Server is working\n";
	SOCKET newConnections;

	for (int i = 0; i < 10; i++) {
		newConnections = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);
		if (newConnections == 0) {
			std::cout << "ERROR\n";
		}
		else {
			std::cout << "Client " << i << " connected\n";
			connections[i] = newConnections;
			counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
}

void ConnectionListener::ClientHandler(int index)
{
	std::string patient;
	Message message;
	
	while (true) {
		int a = recv(connections[index], (char*)&message, sizeof(Message), NULL);
		if (a == -1) {
			/*for (int i = 0; i < BaseOfAccounts.size(); i++) {
				if (BaseOfAccounts[i].second == connections[index])
					BaseOfAccounts[i].second = 0;
			}*/
			//auto iterator = std::find(doctors.begin(), doctors.end(), socket); // Указатель на Сокет в Векторе
			//doctors.erase(iterator);
			std::cout << "Client " << index << " disconnected\n";
			break;
		}
		switch (message)
		{
			case Message::LOGIN: 
			{
				Login(index);
			} 
			break;

			case Message::LOGOUT: 
			{
				Logout(index);
			} 
			break;

			case Message::GETPATIENT: 
			{
				GetPatient(index);
			} 
			break; 
		} 
	}
}

void ConnectionListener::Login(int index)
{
	int msg_size = -1;

	recv(connections[index], (char*)&msg_size, sizeof(int), NULL);
	char* login = new char[msg_size + 1];
	login[msg_size] = '\0';
	recv(connections[index], login, msg_size, NULL);

	recv(connections[index], (char*)&msg_size, sizeof(int), NULL);
	char* password = new char[msg_size + 1];
	password[msg_size] = '\0';
	recv(connections[index], password, msg_size, NULL);

	LoginResponse loginResponse;
	if (accountsRepos.Checking(login, password)) {
		loginResponse = LoginResponse::RIGHT;
	}
	
	else
		loginResponse = LoginResponse::WRONG;

	send(connections[index], (char*)&loginResponse, sizeof(LoginResponse), NULL);
}

void ConnectionListener::Logout(int index)
{
	//connections[index] = 0;
	//closesocket(connections[index]);
}

void ConnectionListener::GetPatient(int index)
{
	std::string patient;
	try {
		patient = DataHandler::Packing(repository.GetPatient());
	} 
	catch (std::out_of_range) {
		patient = "Queue is empty!\n";
	}

	int patient_size = patient.size();
	send(connections[index], (char*)&patient_size, sizeof(int), NULL);
	send(connections[index], patient.c_str(), patient_size, NULL);
}




