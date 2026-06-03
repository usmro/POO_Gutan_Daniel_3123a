#include "Medic.h"
#include <iostream>
#include <algorithm>
using namespace std;

Medic::Medic(int id, string nume, string prenume, string cnp,
             string dataNasterii, string telefon, string email,
             string adresa, string dataAngajarii, double salariu,
             string iban, string functie, string tipContract,
             string sectie, string specializare, string numarParafa,
             string titluAcademic, string programLucru,
             string telefonServiciu, double tarifConsultatie,
             bool areGarzi)
    : Angajat(id, nume, prenume, cnp, dataNasterii, telefon, email,
              adresa, dataAngajarii, salariu, iban, functie, tipContract, sectie) {
    this->specializare = specializare;
    this->numarParafa = numarParafa;
    this->titluAcademic = titluAcademic;
    this->programLucru = programLucru;
    this->telefonServiciu = telefonServiciu;
    this->tarifConsultatie = tarifConsultatie;
    this->areGarzi = areGarzi;
}

// Getters
string Medic::getSpecializare() { return specializare; }
string Medic::getNumarParafa() { return numarParafa; }
string Medic::getTitluAcademic() { return titluAcademic; }
string Medic::getProgramLucru() { return programLucru; }
double Medic::getTarifConsultatie() { return tarifConsultatie; }
int Medic::getNrPacienti() { return pacientiIDs.size(); }
bool Medic::getAreGarzi() { return areGarzi; }
vector<int> Medic::getPacientiIDs() { return pacientiIDs; }

// Setters
void Medic::setProgramLucru(string program) { programLucru = program; }
void Medic::setTelefonServiciu(string telefon) { telefonServiciu = telefon; }
void Medic::setTarifConsultatie(double tarif) { tarifConsultatie = tarif; }
void Medic::setGarzi(bool faceGarzi) { areGarzi = faceGarzi; }

// Limbi straine
void Medic::adaugaLimba(string limba) {
    limbiStraine.push_back(limba);
}

void Medic::afiseazaLimbi() {
    if (limbiStraine.empty()) {
        cout << "  Limbi straine: -" << endl;
    } else {
        cout << "  Limbi straine: ";
        for (size_t i = 0; i < limbiStraine.size(); i++) {
            cout << limbiStraine[i];
            if (i < limbiStraine.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Gestiune pacienți
void Medic::adaugaPacient(int idPacient) {
    if (!arePacient(idPacient)) {
        pacientiIDs.push_back(idPacient);
    }
}

void Medic::stergePacient(int idPacient) {
    auto it = find(pacientiIDs.begin(), pacientiIDs.end(), idPacient);
    if (it != pacientiIDs.end()) {
        pacientiIDs.erase(it);
    }
}

bool Medic::arePacient(int idPacient) {
    return find(pacientiIDs.begin(), pacientiIDs.end(), idPacient) != pacientiIDs.end();
}

// POLIMORFISM
double Medic::calculBonus() {
    if (!esteActiv) return 0;
    double bonus = salariu * 0.15;
    if (areGarzi) bonus += 500;
    bonus += pacientiIDs.size() * 30;
    if (titluAcademic == "Conf. Dr.") bonus *= 1.1;
    if (titluAcademic == "Prof. Dr.") bonus *= 1.2;
    return bonus;
}

void Medic::afisare() {
    cout << "[MEDIC] " << titluAcademic << " " << nume << " " << prenume
         << " | Specializare: " << specializare
         << " | Parafa: " << numarParafa
         << " | Pacienti: " << pacientiIDs.size()
         << " | Tarif: " << tarifConsultatie << " lei"
         << " | Garzi: " << (areGarzi ? "DA" : "NU")
         << " | Bonus: " << calculBonus() << " lei" << endl;
}

void Medic::afisareDetaliata() {
    cout << "\n========== FISA MEDIC ==========" << endl;
    cout << "ID: " << id << " | " << titluAcademic << " " << nume << " " << prenume << endl;
    cout << "Specializare: " << specializare << endl;
    cout << "Parafa: " << numarParafa << endl;
    cout << "Sectie: " << sectie << endl;
    cout << "Program: " << programLucru << endl;
    cout << "Telefon serviciu: " << telefonServiciu << endl;
    cout << "Telefon personal: " << telefon << endl;
    cout << "Email: " << email << endl;
    cout << "Tarif consultatie: " << tarifConsultatie << " lei" << endl;
    cout << "Garzi: " << (areGarzi ? "DA" : "NU") << endl;
    cout << "Nr. pacienti alocati: " << pacientiIDs.size() << endl;
    afiseazaLimbi();
    cout << "Salariu: " << salariu << " lei" << endl;
    cout << "Bonus: " << calculBonus() << " lei" << endl;
    cout << "Vechime: " << calculeazaVechime() << " ani" << endl;
    cout << "Status: " << (esteActiv ? "ACTIV" : "INACTIV") << endl;
    cout << "==================================" << endl;
}