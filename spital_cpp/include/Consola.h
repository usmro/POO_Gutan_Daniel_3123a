#pragma once
#include <string>
#include <vector>
using namespace std;

class Consola {
public:
    static const string RESET;
    static const string RED;
    static const string GREEN;
    static const string YELLOW;
    static const string BLUE;
    static const string MAGENTA;
    static const string CYAN;
    static const string WHITE;
    static const string BOLD;

    static void setColor(int color);
    static void resetColor();
    static void printTitle(const string& text);
    static void printHeader(const string& subtitle = "SISTEM DE GESTIUNE SPITAL");
    static void printSuccess(const string& text);
    static void printError(const string& text);
    static void printInfo(const string& text);
    static void printWarning(const string& text);
    static void printSeparator();
    static void printMenuBox(const string& title, const vector<pair<int, string>>& items);
    static void printStatusBar(int pacienti, int medici, int asistenti, int programari, int facturi);
    static void clearScreen();
    static int citesteOptiune(int min, int max);
    static string citesteText(const string& prompt);
    static int citesteNumar(const string& prompt);
    static double citesteDouble(const string& prompt);
    static void pauza();
};
