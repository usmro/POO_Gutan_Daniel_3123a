#include "Consola.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>
using namespace std;

const string Consola::RESET = "\033[0m";
const string Consola::RED = "\033[31m";
const string Consola::GREEN = "\033[32m";
const string Consola::YELLOW = "\033[33m";
const string Consola::BLUE = "\033[34m";
const string Consola::MAGENTA = "\033[35m";
const string Consola::CYAN = "\033[36m";
const string Consola::WHITE = "\033[37m";
const string Consola::BOLD = "\033[1m";

void Consola::setColor(int color) {
    (void)color;
}

void Consola::resetColor() {
    cout << RESET;
}

void Consola::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

void Consola::printHeader(const string& subtitle) {
    cout << BOLD << CYAN;
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║              🏥  MANAGEMENT SPITAL C++  🏥              ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << RESET;
    cout << YELLOW << "  " << subtitle << RESET << "\n\n";
}

void Consola::printTitle(const string& text) {
    cout << "\n" << BOLD << CYAN;
    cout << "┌──────────────────────────────────────────────────────────┐\n";
    cout << "│ " << left << setw(56) << text << " │\n";
    cout << "└──────────────────────────────────────────────────────────┘\n";
    cout << RESET;
}

void Consola::printMenuBox(const string& title, const vector<pair<int, string>>& items) {
    printHeader(title);
    cout << BOLD << YELLOW;
    cout << "┌──────────────────────────────────────────────────────────┐\n";
    cout << "│ " << left << setw(56) << "MENIU PRINCIPAL" << " │\n";
    cout << "├──────────────────────────────────────────────────────────┤\n";
    cout << RESET;

    for (const auto& item : items) {
        string label = "[" + to_string(item.first) + "] " + item.second;
        cout << "│ " << GREEN << "▶ " << RESET << left << setw(54) << label << " │\n";
    }

    cout << BOLD << YELLOW;
    cout << "└──────────────────────────────────────────────────────────┘\n";
    cout << RESET;
}

void Consola::printStatusBar(int pacienti, int medici, int asistenti, int programari, int facturi) {
    cout << CYAN;
    cout << "────────────────────────────────────────────────────────────\n";
    cout << " 📊 Pacienți: " << pacienti
         << " | 👨‍⚕️ Medici: " << medici
         << " | 👩‍⚕️ Asistenți: " << asistenti
         << " | 📅 Programări: " << programari
         << " | 💰 Facturi: " << facturi << "\n";
    cout << "────────────────────────────────────────────────────────────\n" << RESET;
}

void Consola::printSuccess(const string& text) {
    cout << GREEN << BOLD << "  ✓ " << RESET << GREEN << text << RESET << endl;
}

void Consola::printError(const string& text) {
    cout << RED << BOLD << "  ✗ " << RESET << RED << text << RESET << endl;
}

void Consola::printInfo(const string& text) {
    cout << BLUE << "  ℹ " << RESET << text << endl;
}

void Consola::printWarning(const string& text) {
    cout << YELLOW << "  ⚠ " << RESET << text << endl;
}

void Consola::printSeparator() {
    cout << CYAN << "  ────────────────────────────────────────────────────────" << RESET << endl;
}

void Consola::pauza() {
    cout << "\n" << YELLOW << "  Apasă ENTER pentru a continua..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Consola::citesteOptiune(int min, int max) {
    int opt;
    while (true) {
        cout << BOLD << CYAN << "  Alege opțiunea [" << min << "-" << max << "]: " << RESET;
        cin >> opt;
        if (cin.fail() || opt < min || opt > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Opțiune invalidă! Încearcă din nou.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opt;
        }
    }
}

string Consola::citesteText(const string& prompt) {
    string text;
    cout << CYAN << "  " << prompt << ": " << RESET;
    getline(cin, text);
    while (text.empty()) {
        printWarning("Valoarea nu poate fi goală.");
        cout << CYAN << "  " << prompt << ": " << RESET;
        getline(cin, text);
    }
    return text;
}

int Consola::citesteNumar(const string& prompt) {
    int numar;
    while (true) {
        cout << CYAN << "  " << prompt << ": " << RESET;
        cin >> numar;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numar;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Trebuie introdus un număr întreg valid.");
    }
}

double Consola::citesteDouble(const string& prompt) {
    double val;
    while (true) {
        cout << CYAN << "  " << prompt << ": " << RESET;
        cin >> val;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Trebuie introdus un număr real valid.");
    }
}
