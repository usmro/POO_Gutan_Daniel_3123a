#pragma once
#include <string>
#include <fstream>
#include "Consola.h"
using namespace std;

class Logger {
private:
    static Logger* instanta;
    ofstream fisier;
    
    Logger();
    string getCurrentTime();

public:
    static Logger* getInstanta();
    void log(const string& mesaj);
    void logOperatiune(const string& tip, const string& detalii);
    void inchide();
    ~Logger();
};