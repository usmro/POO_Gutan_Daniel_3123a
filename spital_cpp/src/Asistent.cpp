#include "Asistent.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Asistent::Asistent(int id, string nume, string prenume, string cnp,
                   string dataNasterii, string telefon, string email,
                   string adresa, string dataAngajarii, double salariu,
                   string iban, string functie, string tipContract,
                   string sectie, string gradProfesional,
                   string tipAsistent, int oreSuplimentare,
                   bool areTureNoapte, int nrTureNoapteEfectuate,
                   bool areAvizLiberaPractica)
    : Angajat(id, nume, prenume, cnp, dataNasterii, telefon, email,
              adresa, dataAngajarii, salariu, iban, functie, tipContract, sectie) {
    this->gradProfesional = gradProfesional;
    this->tipAsistent = tipAsistent;
    this->oreSuplimentare = oreSuplimentare;
    this->areTureNoapte = areTureNoapte;
    this->nrTureNoapteEfectuate = nrTureNoapteEfectuate;
    this->areAvizLiberaPractica = areAvizLiberaPractica;
}

string Asistent::getGradProfesional() { return gradProfesional; }
string Asistent::getTipAsistent() { return tipAsistent; }
int Asistent::getOreSuplimentare() { return oreSuplimentare; }
bool Asistent::getAreTureNoapte() { return areTureNoapte; }
int Asistent::getNrTureNoapteEfectuate() { return nrTureNoapteEfectuate; }
bool Asistent::getAreAvizLiberaPractica() { return areAvizLiberaPractica; }

void Asistent::setOreSuplimentare(int ore) {
    if (ore < 0) throw invalid_argument("Ore negative!");
    oreSuplimentare = ore;
}

void Asistent::setTureNoapte(bool are) { areTureNoapte = are; }

void Asistent::setAvizLiberaPractica(bool are) {
    areAvizLiberaPractica = are;
    if (are) cout << "Aviz ACTIVAT." << endl;
    else cout << "Aviz DEZACTIVAT!" << endl;
}

void Asistent::adaugaOreSuplimentare(int ore) {
    if (ore < 0) throw invalid_argument("Ore negative!");
    oreSuplimentare += ore;
    cout << "+" << ore << " ore. Total: " << oreSuplimentare << endl;
}

void Asistent::incrementareTureNoapte() {
    nrTureNoapteEfectuate++;
    cout << "Tura noapte. Total: " << nrTureNoapteEfectuate << endl;
}

void Asistent::reseteazaPontaj() {
    oreSuplimentare = 0;
    nrTureNoapteEfectuate = 0;
    cout << "Pontaj resetat." << endl;
}

bool Asistent::poateLucra() { return areAvizLiberaPractica && esteActiv; }

void Asistent::afisareAviz() {
    cout << "Aviz: " << (areAvizLiberaPractica ? "VALABIL" : "LIPSA") << endl;
}

double Asistent::calculBonus() {
    if (!esteActiv || !areAvizLiberaPractica) return 0;
    double bonus = salariu * 0.10 + oreSuplimentare * 20 + nrTureNoapteEfectuate * 50;
    if (gradProfesional == "Principal") bonus *= 1.2;
    return bonus;
}

void Asistent::afisare() {
    cout << "[ASISTENT] ID: " << id << " | " << nume << " " << prenume
         << " | Grad: " << gradProfesional << " | Tip: " << tipAsistent
         << " | Sectie: " << sectie << " | Ore supl: " << oreSuplimentare
         << " | Ture noapte: " << nrTureNoapteEfectuate
         << " | Aviz: " << (areAvizLiberaPractica ? "OK" : "LIPSA")
         << " | Bonus: " << calculBonus() << " lei"
         << " | Activ: " << (esteActiv ? "DA" : "NU") << endl;
}