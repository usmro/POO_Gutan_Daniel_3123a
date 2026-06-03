#include "Consola.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;


namespace {
#ifdef _WIN32
void activeazaAnsiWindows() {
    // Nu includem windows.h pentru a evita conflictul std::byte/byte in MinGW.
    // Culorile ANSI functioneaza in terminalele moderne; meniul cu sageti foloseste conio.h.
}
#endif

int citesteTasta() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 224 || ch == 0) {
        int ext = _getch();
        if (ext == 72) return 1001; // sageata sus
        if (ext == 80) return 1002; // sageata jos
        return 0;
    }
    if (ch == 13) return 1003; // Enter
    if (ch == 27) return 1004; // Esc
    return ch;
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    int result = ch;
    if (ch == 27) {
        char seq[2] = {0, 0};
        if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
            if (seq[0] == '[' && seq[1] == 'A') result = 1001;
            else if (seq[0] == '[' && seq[1] == 'B') result = 1002;
            else result = 1004;
        } else {
            result = 1004;
        }
    } else if (ch == '\n' || ch == '\r') {
        result = 1003;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return result;
#endif
}
}

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
    cout << "+==========================================================+\n";
    cout << "|                MANAGEMENT SPITAL C++                |\n";
    cout << "+==========================================================+\n";
    cout << RESET;
    cout << YELLOW << "  " << subtitle << RESET << "\n\n";
}

void Consola::printTitle(const string& text) {
    cout << "\n" << BOLD << CYAN;
    cout << "+----------------------------------------------------------+\n";
    cout << "| " << left << setw(56) << text << " |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << RESET;
}

void Consola::printMenuBox(const string& title, const vector<pair<int, string>>& items) {
    printHeader(title);
    cout << BOLD << YELLOW;
    cout << "+----------------------------------------------------------+\n";
    cout << "| " << left << setw(56) << "MENIU PRINCIPAL" << " |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << RESET;

    for (const auto& item : items) {
        string label = "[" + to_string(item.first) + "] " + item.second;
        cout << "| " << GREEN << "> " << RESET << left << setw(54) << label << " |\n";
    }

    cout << BOLD << YELLOW;
    cout << "+----------------------------------------------------------+\n";
    cout << RESET;
}

void Consola::printStatusBar(int pacienti, int medici, int asistenti, int programari, int facturi) {
    cout << CYAN;
    cout << "------------------------------------------------------------\n";
    cout << "  Pacienti: " << pacienti
         << " |  Medici: " << medici
         << " |  Asistenti: " << asistenti
         << " |  Programari: " << programari
         << " |  Facturi: " << facturi << "\n";
    cout << "------------------------------------------------------------\n" << RESET;
}

void Consola::printSuccess(const string& text) {
    cout << GREEN << BOLD << "  [OK] " << RESET << GREEN << text << RESET << endl;
}

void Consola::printError(const string& text) {
    cout << RED << BOLD << "  [X] " << RESET << RED << text << RESET << endl;
}

void Consola::printInfo(const string& text) {
    cout << BLUE << "  [i] " << RESET << text << endl;
}

void Consola::printWarning(const string& text) {
    cout << YELLOW << "  [!] " << RESET << text << endl;
}

void Consola::printSeparator() {
    cout << CYAN << "  --------------------------------------------------------" << RESET << endl;
}

void Consola::pauza() {
    cout << "\n" << YELLOW << "  Apasa ENTER pentru a continua..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Consola::citesteOptiune(int min, int max) {
    int opt;
    while (true) {
        cout << BOLD << CYAN << "  Alege optiunea [" << min << "-" << max << "]: " << RESET;
        cin >> opt;
        if (cin.fail() || opt < min || opt > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Optiune invalida! Incearca din nou.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opt;
        }
    }
}


int Consola::meniuInteractv(const string& title, const vector<pair<int, string>>& items) {
#ifdef _WIN32
    activeazaAnsiWindows();
#endif
    if (items.empty()) return -1;

    int selectat = 0;
    while (true) {
        clearScreen();
        printHeader(title);

        cout << BOLD << YELLOW;
        cout << "+----------------------------------------------------------+\n";
        cout << "| " << left << setw(56) << "MENIU - navigare cu sagetile" << " |\n";
        cout << "+----------------------------------------------------------+\n";
        cout << RESET;

        for (int i = 0; i < (int)items.size(); ++i) {
            string label = items[i].second;
            if (i == selectat) {
                cout << "| " << BOLD << CYAN << "> " << RESET << BOLD << "\033[7m"
                     << left << setw(52) << label << RESET << " |\n";
            } else {
                cout << "|   " << left << setw(52) << label << " |\n";
            }
        }

        cout << BOLD << YELLOW;
        cout << "+----------------------------------------------------------+\n";
        cout << RESET;
        cout << CYAN << "  UP/DOWN navigare   ENTER selectare   ESC inapoi/iesire" << RESET << "\n";

        int tasta = citesteTasta();
        if (tasta == 1001) {
            selectat--;
            if (selectat < 0) selectat = (int)items.size() - 1;
        } else if (tasta == 1002) {
            selectat++;
            if (selectat >= (int)items.size()) selectat = 0;
        } else if (tasta == 1003) {
            return items[selectat].first;
        } else if (tasta == 1004) {
            for (const auto& item : items) {
                if (item.first == 0) return 0;
            }
            return -1;
        }
    }
}

string Consola::citesteText(const string& prompt) {
    string text;
    cout << CYAN << "  " << prompt << ": " << RESET;
    getline(cin, text);
    while (text.empty()) {
        printWarning("Valoarea nu poate fi goala.");
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
        printError("Trebuie introdus un numar intreg valid.");
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
        printError("Trebuie introdus un numar real valid.");
    }
}
