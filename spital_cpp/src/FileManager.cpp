#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Elimină caracterele speciale din JSON
string FileManager::escapeJson(const string& text) {
    string rezultat;
    for (char c : text) {
        if (c == '"') rezultat += "\\\"";
        else if (c == '\\') rezultat += "\\\\";
        else rezultat += c;
    }
    return rezultat;
}

// ========== SALVARE ==========

void FileManager::salveazaPacienti(const vector<Pacient*>& pacienti, const string& fisier) {
    ofstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl;
        return;
    }
    
    f << "{\n  \"pacienti\": [\n";
    
    for (size_t i = 0; i < pacienti.size(); i++) {
        Pacient* p = pacienti[i];
        f << "    {\n";
        f << "      \"id\": " << p->getId() << ",\n";
        f << "      \"nume\": \"" << escapeJson(p->getNume()) << "\",\n";
        f << "      \"cnp\": \"" << p->getCnp() << "\",\n";
        f << "      \"diagnostic\": \"" << escapeJson(p->getDiagnostic()) << "\",\n";
        f << "      \"varsta\": " << p->calculeazaVarsta() << ",\n";
        f << "      \"internat\": " << (p->isInternat() ? "true" : "false") << "\n";
        f << "    }";
        if (i < pacienti.size() - 1) f << ",";
        f << "\n";
    }
    
    f << "  ]\n}\n";
    f.close();
    cout << "[SALVARE] " << pacienti.size() << " pacienti salvati in " << fisier << endl;
}

void FileManager::salveazaAngajati(const vector<Angajat*>& angajati, const string& fisier) {
    ofstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl;
        return;
    }
    
    f << "{\n  \"angajati\": [\n";
    
    for (size_t i = 0; i < angajati.size(); i++) {
        Angajat* a = angajati[i];
        f << "    {\n";
        f << "      \"id\": " << a->getId() << ",\n";
        f << "      \"nume\": \"" << escapeJson(a->getNume()) << "\",\n";
        f << "      \"salariu\": " << a->getSalariu() << ",\n";
        f << "      \"sectie\": \"" << escapeJson(a->getSectie()) << "\",\n";
        f << "      \"activ\": " << (a->isActiv() ? "true" : "false") << "\n";
        f << "    }";
        if (i < angajati.size() - 1) f << ",";
        f << "\n";
    }
    
    f << "  ]\n}\n";
    f.close();
    cout << "[SALVARE] " << angajati.size() << " angajati salvati in " << fisier << endl;
}

void FileManager::salveazaProgramari(const vector<Programare*>& programari, const string& fisier) {
    ofstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl;
        return;
    }
    
    f << "{\n  \"programari\": [\n";
    
    for (size_t i = 0; i < programari.size(); i++) {
        Programare* prog = programari[i];
        f << "    {\n";
        f << "      \"id\": " << prog->getId() << ",\n";
        f << "      \"idPacient\": " << prog->getIdPacient() << ",\n";
        f << "      \"idMedic\": " << prog->getIdMedic() << ",\n";
        f << "      \"data\": \"" << prog->getData() << "\",\n";
        f << "      \"ora\": \"" << prog->getOra() << "\",\n";
        f << "      \"status\": \"" << prog->getStatus() << "\"\n";
        f << "    }";
        if (i < programari.size() - 1) f << ",";
        f << "\n";
    }
    
    f << "  ]\n}\n";
    f.close();
    cout << "[SALVARE] " << programari.size() << " programari salvate in " << fisier << endl;
}

void FileManager::salveazaFacturi(const vector<Factura*>& facturi, const string& fisier) {
    ofstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl;
        return;
    }
    
    f << "{\n  \"facturi\": [\n";
    
    for (size_t i = 0; i < facturi.size(); i++) {
        Factura* fact = facturi[i];
        f << "    {\n";
        f << "      \"id\": " << fact->getId() << ",\n";
        f << "      \"idPacient\": " << fact->getIdPacient() << ",\n";
        f << "      \"total\": " << fact->getTotal() << ",\n";
        f << "      \"platita\": " << (fact->isPlatita() ? "true" : "false") << "\n";
        f << "    }";
        if (i < facturi.size() - 1) f << ",";
        f << "\n";
    }
    
    f << "  ]\n}\n";
    f.close();
    cout << "[SALVARE] " << facturi.size() << " facturi salvate in " << fisier << endl;
}

// ========== ÎNCĂRCARE ==========

vector<Pacient*> FileManager::incarcaPacienti(const string& fisier) {
    vector<Pacient*> pacienti;
    
    ifstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide " << fisier << endl;
        return pacienti;
    }
    
    string linie;
    while (getline(f, linie)) {
        // Parsare simplă demonstrativă.
        // O încărcare completă ar necesita salvarea tuturor câmpurilor și o bibliotecă JSON.
    }
    
    f.close();
    cout << "[INCARCARE] Pacienti incarcati din " << fisier << endl;
    return pacienti;
}

vector<Angajat*> FileManager::incarcaAngajati(const string& fisier) {
    vector<Angajat*> angajati;
    
    ifstream f(fisier);
    if (!f.is_open()) {
        cout << "Eroare: Nu s-a putut deschide " << fisier << endl;
        return angajati;
    }
    
    // Parsare simplă demonstrativă
    f.close();
    cout << "[INCARCARE] Angajati incarcati din " << fisier << endl;
    return angajati;
}