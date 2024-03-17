#include "ConnectionListener.h"
#include <iostream>
#include "Queue.h"

/*
class B;
class A {
private:
    int a;
public:
    A() {};
    A(int _a) : a(_a) {};
    int geta() const { return a; }
    bool operator>(const A& aa) const {
        if (this->a > aa.geta()) return true;
        else return false;
    }
    bool operator>(const B& bb) const;
    virtual ~A() {}
};

class B : public A {
private:
    int b;
public:
    B() {}
    B(int _a, int _b) : b(_b), A(_a) {};
    int getb() { return b; }

    bool operator>(A& aa) {
        if (this->geta() > aa.geta()) return true;
        else return false;
    }
    bool operator>(B& bb) {
        if (this->geta() > bb.geta()) return true;
        else return false;
    }
};

bool A::operator>(const B& bb) const {
    if (this->a > bb.geta()) return true;
    else return false;
}

void op(A& aa) {
    B* b = dynamic_cast<B*>(&aa);
    if (b != nullptr) std::cout << "B";
    if (b == nullptr) std::cout << "A";
}
*/


PatientRepos ConnectionListener::repository;
AccountsRepos ConnectionListener::accountsRepos;

/*
std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> ConnectionListener::BaseOfAccounts;
oyoyoyoy
*/
//std::vector<std::pair<std::string, std::string>> ConnectionListener::BaseOfAccounts;

SOCKET ConnectionListener::connections[10];
int ConnectionListener::counter = 0;

int main(int argc, char* argv[]) 
{   
    ConnectionListener server;
}
