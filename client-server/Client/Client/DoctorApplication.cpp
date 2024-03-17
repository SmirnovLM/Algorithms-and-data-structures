#include "DoctorApplication.h"

DoctorApplication::DoctorApplication() : online(false) {
    Working();
}

void DoctorApplication::Working() {
    while (true) {
        if (!online) {
            Login();
        }
        else {
            std::cout << "\nChoose The Action:\n";
            std::cout << "1 - Get Patient from Queue;\n";
            std::cout << "2 - Logout from Account;\n";

            int action;
            std::cin >> action; // Действие = 1 или 2
            std::cout << std::endl;

            switch (action)
            {
                case 1: {
                    GetPatient();
                } break;

                case 2: {
                    Logout();
                } break;

                default: {
                    std::cout << "Error: There is no suitable action!\n";
                    break;
                }
            }
        }
        Sleep(10);
    }
}

void DoctorApplication::Login() {
    LoginResponse loginResponse;
    do {
        connectionController.Send(Message::LOGIN);

        std::cout << "LOGIN:\n";
        std::string login;
        std::getline(std::cin, login);
        connectionController.Send(login);

        std::cout << "PASSWORD:\n";
        std::string password;
        std::getline(std::cin, password);
        if (password == "") password = " ";
        connectionController.Send(password);

        loginResponse = connectionController.RecvLoginResponse();
        if (loginResponse == LoginResponse::WRONG) {
            std::cout << "LOGIN or PASSWORD isn't corrected!\n";
        }
    } while (loginResponse != LoginResponse::RIGHT);
    std::cout << "\nYou logged in Account!\n";

    online = true;
}

void DoctorApplication::GetPatient() {
    connectionController.Send(Message::GETPATIENT);

    std::string jsonPatient = connectionController.RecvString();
    try {
        Patient patient = DataHandler::Unpacking(jsonPatient);
        std::cout << "\tPATIENT:\n";
        std::cout << "\tNAME: " << patient.GetName() << std::endl;
        std::cout << "\tSURNAME: " << patient.GetSurName() << std::endl;
        std::cout << "\tPATRONYMIC: " << patient.GetPatronymic() << std::endl;
        std::cout << "\tSTATE: " <<
            (patient.GetStateOfPatient() == State::REGULAR ? "Regular\n" :
            (patient.GetStateOfPatient() == State::MEDIUM ? "Medium\n" : "Critical\n"));
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error) {
        std::cout << jsonPatient << std::endl;
    }
}

void DoctorApplication::Logout() {
    //connectionController.Send(Message::LOGOUT);
    online = false;
    std::cout << "You logout from Account!\n\n";
}




