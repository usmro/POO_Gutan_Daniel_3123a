#pragma once
#include <string>
using namespace std;

class Consola {
public:
    static void setColor(int color);
    static void resetColor();
    static void printTitle(const string& text);
    static void printSuccess(const string& text);
    static void printError(const string& text);
    static void printInfo(const string& text);
    static void printSeparator();
    static void clearScreen();
    static int citesteOptiune(int min, int max);
    static string citesteText(const string& prompt);
    static int citesteNumar(const string& prompt);
    static double citesteDouble(const string& prompt);
    static void pauza();
};