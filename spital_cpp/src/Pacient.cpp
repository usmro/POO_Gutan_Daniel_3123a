#include "Pacient.h"
#include "Logger.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor simplificat
Pacient::Pacient(int id, string nume, string prenume, string cnp,
                 string dataNasterii, string telefon) {
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->dataNasterii = dataNasterii;
    this->telefon = telefon;
    this->email = "";
    this->adresa = "";
    this->grupaSanguina = "Necunoscuta";
    this->rh = "";
    this->diagnostic = "Fara diagnostic";
    this->internat = false;
    this->dataInternarii = "";
    this->dataExternarii = "";
    this->sectie = "";
    this->numarSalon = 0;
    this->idMedicCurant = 0;
}

// Constructor complet
Pacient::Pacient(int id, string nume, string prenume, string cnp,
                 string dataNasterii, string telefon, string email,
                 string adresa, string grupaSanguina, string rh) {
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->dataNasterii = dataNasterii;
    this->telefon = telefon;
    this->email = email;
    this->adresa = adresa;
    this->grupaSanguina = grupaSanguina;
    this->rh = rh;
    this->diagnostic = "Fara diagnostic";
    this->internat = false;
    this->dataInternarii = "";
    this->dataExternarii = "";
    this->sectie = "";
    this->numarSalon = 0;
    this->idMedicCurant = 0;
}

// Getters
int Pacient::getId() { return id; }
string Pacient::getNume() { return nume + " " + prenume; }
string Pacient::getCnp() { return cnp; }
string Pacient::getDataNasterii() { return dataNasterii; }
string Pacient::getTelefon() { return telefon; }
string Pacient::getDiagnostic() { return diagnostic; }
string Pacient::getGrupaSanguina() { return grupaSanguina + " " + rh; }
bool Pacient::isInternat() { return internat; }
string Pacient::getDataInternarii() { return dataInternarii; }
string Pacient::getSectie() { return sectie; }
int Pacient::getIdMedicCurant() { return idMedicCurant; }

// Setters
void Pacient::setDiagnostic(string diagnosticNou) {
    diagnostic = diagnosticNou;
}

void Pacient::setTelefon(string telefonNou) {
    telefon = telefonNou;
}

void Pacient::setEmail(string emailNou) {
    email = emailNou;
}

void Pacient::setAdresa(string adresaNou) {
    adresa = adresaNou;
}

// Metode medicale
void Pacient::adaugaBoalaCronica(string boala) {
    boliCronice.push_back(boala);
}

void Pacient::adaugaAlergie(string alergie) {
    alergii.push_back(alergie);
}

void Pacient::adaugaMedicatie(string medicament) {
    medicatieCurenta.push_back(medicament);
}

void Pacient::afiseazaBoliCronice() {
    if (boliCronice.empty()) {
        cout << "  Nu are boli cronice inregistrate." << endl;
    } else {
        cout << "  Boli cronice: ";
        for (size_t i = 0; i < boliCronice.size(); i++) {
            cout << boliCronice[i];
            if (i < boliCronice.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

void Pacient::afiseazaAlergii() {
    if (alergii.empty()) {
        cout << "  Nu are alergii inregistrate." << endl;
    } else {
        cout << "  Alergii: ";
        for (size_t i = 0; i < alergii.size(); i++) {
            cout << alergii[i];
            if (i < alergii.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Metode spitalizare
void Pacient::interneaza(string sectie, int salon, string data) {
    internat = true;
    this->sectie = sectie;
    this->numarSalon = salon;
    this->dataInternarii = data;
    this->dataExternarii = "";
    cout << "Pacientul " << nume << " " << prenume << " a fost internat." << endl;
    cout << "  Sectie: " << sectie << " | Salon: " << salon << " | Data: " << data << endl;
    Logger::getInstanta()->logOperatiune("INTERNARE", 
    "Pacientul " + nume + " " + prenume + " (ID:" + to_string(id) + 
    ") internat in sectia " + sectie + ", salon " + to_string(numarSalon) + 
    ", data: " + data);
}

void Pacient::externeaza(string data) {
    internat = false;
    this->dataExternarii = data;
    cout << "Pacientul " << nume << " " << prenume << " a fost externat la data de " << data << endl;
}

void Pacient::asigneazaMedic(int idMedic) {
    this->idMedicCurant = idMedic;
    cout << "Medicul cu ID " << idMedic << " a fost asignat pacientului " << nume << " " << prenume << endl;
}

// Utilitare
int Pacient::calculeazaVarsta() {
    int anNastere = stoi(dataNasterii.substr(0, 4));
    return 2026 - anNastere;
}

void Pacient::afisare() {
    cout << "ID: " << id << " | " << nume << " " << prenume
         << " | CNP: " << cnp
         << " | Varsta: " << calculeazaVarsta() << " ani"
         << " | Diagnostic: " << diagnostic
         << " | Internat: " << (internat ? "DA" : "NU");
    if (internat) {
        cout << " | Sectie: " << sectie << " | Salon: " << numarSalon;
    }
    cout << endl;
}

void Pacient::afisareCompleta() {
    cout << "\n========== FISA PACIENT ==========" << endl;
    cout << "ID: " << id << endl;
    cout << "Nume: " << nume << " " << prenume << endl;
    cout << "CNP: " << cnp << endl;
    cout << "Data nasterii: " << dataNasterii << " (" << calculeazaVarsta() << " ani)" << endl;
    cout << "Telefon: " << telefon << endl;
    cout << "Email: " << email << endl;
    cout << "Adresa: " << adresa << endl;
    cout << "Grupa sanguina: " << grupaSanguina << " " << rh << endl;
    cout << "\n--- DATE MEDICALE ---" << endl;
    cout << "Diagnostic: " << diagnostic << endl;
    afiseazaBoliCronice();
    afiseazaAlergii();
    cout << "\n--- SPITALIZARE ---" << endl;
    cout << "Internat: " << (internat ? "DA" : "NU") << endl;
    if (internat) {
        cout << "Data internarii: " << dataInternarii << endl;
        cout << "Sectie: " << sectie << " | Salon: " << numarSalon << endl;
        cout << "Medic curant ID: " << idMedicCurant << endl;
    }
    if (!dataExternarii.empty()) {
        cout << "Data externarii: " << dataExternarii << endl;
    }
    cout << "==================================" << endl;
}