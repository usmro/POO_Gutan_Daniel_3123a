#pragma once
#include <string>
#include <vector>
#include "Pacient.h"
#include "Angajat.h"
#include "Medic.h"
#include "Asistent.h"
#include "Programare.h"
#include "Factura.h"
using namespace std;

class FileManager {
public:
    // Salvare date
    static void salveazaPacienti(const vector<Pacient*>& pacienti, const string& fisier);
    static void salveazaAngajati(const vector<Angajat*>& angajati, const string& fisier);
    static void salveazaProgramari(const vector<Programare*>& programari, const string& fisier);
    static void salveazaFacturi(const vector<Factura*>& facturi, const string& fisier);
    
    // Încărcare date
    static vector<Pacient*> incarcaPacienti(const string& fisier);
    static vector<Angajat*> incarcaAngajati(const string& fisier);
    
    // Helper
    static string escapeJson(const string& text);
};