#include "Angajat.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <chrono>
using namespace std;

Angajat::Angajat(int id, string nume, string prenume, string cnp,
                 string dataNasterii, string telefon, string email,
                 string adresa, string dataAngajarii, double salariu,
                 string iban, string functie, string tipContract,
                 string sectie) {
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->dataNasterii = dataNasterii;
    this->telefon = telefon;
    this->email = email;
    this->adresa = adresa;
    this->dataAngajarii = dataAngajarii;
    this->salariu = salariu;
    this->iban = iban;
    this->functie = functie;
    this->tipContract = tipContract;
    this->sectie = sectie;
    this->esteActiv = true;
}

int Angajat::getId() { return id; }
string Angajat::getNume() { return nume + " " + prenume; }
double Angajat::getSalariu() { return salariu; }
string Angajat::getSectie() { return sectie; }
string Angajat::getFunctie() { return functie; }
bool Angajat::isActiv() { return esteActiv; }

void Angajat::setSalariu(double salariuNou) {
    if (salariuNou < 0) throw invalid_argument("Salariu negativ!");
    salariu = salariuNou;
}

void Angajat::setTelefon(string telefonNou) { telefon = telefonNou; }
void Angajat::setEmail(string emailNou) { email = emailNou; }
void Angajat::setSectie(string sectieNoua) { sectie = sectieNoua; }

void Angajat::dezactiveaza() { esteActiv = false; }
void Angajat::activeaza() { esteActiv = true; }

double Angajat::calculBonus() {
    if (!esteActiv) return 0;
    if (tipContract == "Part-time 4h") return salariu * 0.03;
    if (tipContract == "Part-time 6h") return salariu * 0.04;
    return salariu * 0.05;
}

int Angajat::calculeazaVechime() {
    int an = stoi(dataAngajarii.substr(0, 4));
    return 2026 - an;
}

int Angajat::calculeazaVarsta() {
    int an = stoi(dataNasterii.substr(0, 4));
    return 2026 - an;
}

void Angajat::afisare() {
    cout << "ID: " << id << " | " << nume << " " << prenume
         << " | " << functie << " | " << sectie
         << " | Salariu: " << salariu << " lei"
         << " | Activ: " << (esteActiv ? "DA" : "NU") << endl;
}

void Angajat::afisareCompleta() {
    cout << "\n===== DATE ANGAJAT =====" << endl;
    cout << "ID: " << id << endl;
    cout << "Nume: " << nume << " " << prenume << endl;
    cout << "Functie: " << functie << endl;
    cout << "Sectie: " << sectie << endl;
    cout << "Salariu: " << salariu << " lei" << endl;
    cout << "Vechime: " << calculeazaVechime() << " ani" << endl;
    cout << "Status: " << (esteActiv ? "ACTIV" : "INACTIV") << endl;
    cout << "========================" << endl;
}