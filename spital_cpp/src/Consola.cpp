#include "Consola.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

void Consola::setColor(int color) {
    (void)color;
    // Funcționalitate dezactivată pentru compatibilitate
}

void Consola::resetColor() {
    // Funcționalitate dezactivată pentru compatibilitate
}

void Consola::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Consola::printTitle(const string& text) {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════╗" << endl;
    cout << "  ║  🏥 " << text << endl;
    cout << "  ╚══════════════════════════════════════════╝" << endl;
}

void Consola::printSuccess(const string& text) {
    cout << "  ✅ " << text << endl;
}

void Consola::printError(const string& text) {
    cout << "  ❌ " << text << endl;
}

void Consola::printInfo(const string& text) {
    cout << "  ℹ️  " << text << endl;
}

void Consola::printSeparator() {
    cout << "  ────────────────────────────────────────────" << endl;
}

void Consola::pauza() {
    cout << "\n  Apasă Enter pentru a continua...";
    cin.ignore();
    cin.get();
}

int Consola::citesteOptiune(int min, int max) {
    int opt;
    while (true) {
        cout << "  Alege [" << min << "-" << max << "]: ";
        cin >> opt;
        if (cin.fail() || opt < min || opt > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Opțiune invalidă!");
        } else {
            cin.ignore();
            return opt;
        }
    }
}

string Consola::citesteText(const string& prompt) {
    string text;
    cout << "  " << prompt << ": ";
    cin >> text;
    return text;
}

int Consola::citesteNumar(const string& prompt) {
    int numar;
    cout << "  " << prompt << ": ";
    cin >> numar;
    return numar;
}

double Consola::citesteDouble(const string& prompt) {
    double val;
    cout << "  " << prompt << ": ";
    cin >> val;
    return val;
}