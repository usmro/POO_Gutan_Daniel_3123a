#pragma once
#include <exception>
#include <string>
using namespace std;

class ProgramareInvalidaException : public exception {
private:
    string mesaj;
public:
    ProgramareInvalidaException(const string& msg) : mesaj(msg) {}
    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};