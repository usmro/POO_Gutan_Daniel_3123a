#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

Logger* Logger::instanta = nullptr;

string Logger::getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Logger::Logger() {
    fisier.open("date/operatiuni.log", ios::app);
    if (fisier.is_open()) {
        fisier << "\n===== SISTEM PORNIT: " << getCurrentTime() << " =====\n";
    }
}

Logger* Logger::getInstanta() {
    if (instanta == nullptr) {
        instanta = new Logger();
    }
    return instanta;
}

void Logger::log(const string& mesaj) {
    string timestamp = getCurrentTime();
    if (fisier.is_open()) {
        fisier << "[" << timestamp << "] " << mesaj << endl;
    }
    cout << "[LOG] " << mesaj << endl;
}

void Logger::logOperatiune(const string& tip, const string& detalii) {
    string mesaj = "[" + tip + "] " + detalii;
    log(mesaj);
}

void Logger::inchide() {
    if (fisier.is_open()) {
        fisier << "===== SISTEM OPrit: " << getCurrentTime() << " =====\n";
        fisier.close();
    }
}

Logger::~Logger() {
    inchide();
}