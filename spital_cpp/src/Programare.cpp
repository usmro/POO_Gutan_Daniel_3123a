#include "Programare.h"
#include <iostream>
#include <sstream>
using namespace std;

Programare::Programare(int id, int idPacient, int idMedic,
                       string data, string ora, string motiv,
                       int durataMinute, double cost) {
    this->id = id;
    this->idPacient = idPacient;
    this->idMedic = idMedic;
    this->data = data;
    this->ora = ora;
    this->motiv = motiv;
    this->durataMinute = durataMinute;
    this->cost = cost;
    this->status = "In asteptare";
    this->observatii = "";
}

// Getters
int Programare::getId() { return id; }
int Programare::getIdPacient() { return idPacient; }
int Programare::getIdMedic() { return idMedic; }
string Programare::getData() { return data; }
string Programare::getOra() { return ora; }
string Programare::getMotiv() { return motiv; }
int Programare::getDurataMinute() { return durataMinute; }
string Programare::getStatus() { return status; }
double Programare::getCost() { return cost; }

// Setters
void Programare::setCost(double costNou) {
    if (costNou < 0) {
        throw ProgramareInvalidaException("Costul nu poate fi negativ!");
    }
    cost = costNou;
}

void Programare::setDurata(int minute) {
    if (minute <= 0) {
        throw ProgramareInvalidaException("Durata trebuie sa fie pozitiva!");
    }
    durataMinute = minute;
}

// Metode status
void Programare::confirma() {
    if (status == "Anulata") {
        throw ProgramareInvalidaException("Nu se poate confirma o programare anulata!");
    }
    status = "Confirmata";
    cout << "Programarea #" << id << " a fost confirmata." << endl;
}

void Programare::anuleaza(string motivAnulare) {
    if (status == "Anulata") {
        throw ProgramareInvalidaException("Programarea este deja anulata!");
    }
    if (status == "Prezentat") {
        throw ProgramareInvalidaException("Nu se poate anula o programare la care pacientul s-a prezentat!");
    }
    status = "Anulata";
    observatii = "ANULATA: " + motivAnulare;
    cout << "Programarea #" << id << " a fost anulata: " << motivAnulare << endl;
}

void Programare::marcheazaPrezentat() {
    if (status == "Anulata") {
        throw ProgramareInvalidaException("Programarea este anulata!");
    }
    status = "Prezentat";
    cout << "Pacientul s-a prezentat la programarea #" << id << endl;
}

void Programare::marcheazaAbsent() {
    if (status == "Anulata") {
        throw ProgramareInvalidaException("Programarea este anulata!");
    }
    status = "Absent";
    cout << "Pacientul NU s-a prezentat la programarea #" << id << endl;
}

// Metode noi
void Programare::reprogrameaza(string dataNoua, string oraNoua) {
    if (status == "Prezentat") {
        throw ProgramareInvalidaException("Nu se poate reprograma o programare deja efectuata!");
    }
    
    string dataVeche = data;
    string oraVeche = ora;
    
    data = dataNoua;
    ora = oraNoua;
    status = "In asteptare";
    observatii = "Reprogramata din " + dataVeche + " " + oraVeche;
    
    valideaza();  // Verificam noile date
    
    cout << "Programarea #" << id << " a fost reprogramata pe " 
         << data << " la ora " << ora << endl;
}

bool Programare::seSuprapuneCu(const Programare& alta) {
    // Verifica daca sunt la acelasi medic
    if (this->idMedic != alta.idMedic) return false;
    
    // Verifica daca sunt in aceeasi zi
    if (this->data != alta.data) return false;
    
    // Calculeaza minutele de inceput si sfarsit pentru ambele programari
    int ora1 = stoi(this->ora.substr(0, 2));
    int min1 = stoi(this->ora.substr(3, 2));
    int start1 = ora1 * 60 + min1;
    int end1 = start1 + this->durataMinute;
    
    int ora2 = stoi(alta.ora.substr(0, 2));
    int min2 = stoi(alta.ora.substr(3, 2));
    int start2 = ora2 * 60 + min2;
    int end2 = start2 + alta.durataMinute;
    
    // Verifica suprapunerea
    return (start1 < end2 && start2 < end1);
}

string Programare::getDetaliiFactura() {
    stringstream ss;
    ss << "Programare #" << id 
       << " | Data: " << data << " " << ora
       << " | Motiv: " << motiv
       << " | Durata: " << durataMinute << " min"
       << " | Cost: " << cost << " lei"
       << " | Status: " << status;
    return ss.str();
}

// Validare
void Programare::valideaza() {
    if (idPacient <= 0) {
        throw ProgramareInvalidaException("ID pacient invalid!");
    }
    if (idMedic <= 0) {
        throw ProgramareInvalidaException("ID medic invalid!");
    }
    if (data.empty()) {
        throw ProgramareInvalidaException("Data este obligatorie!");
    }
    if (ora.empty()) {
        throw ProgramareInvalidaException("Ora este obligatorie!");
    }
    
    int oraInt = stoi(ora.substr(0, 2));
    int minInt = stoi(ora.substr(3, 2));
    
    if (oraInt < 8 || oraInt > 20) {
        throw ProgramareInvalidaException("Programarile se fac doar intre 8:00 si 20:00!");
    }
    if (minInt < 0 || minInt > 59) {
        throw ProgramareInvalidaException("Minutele trebuie sa fie intre 0 si 59!");
    }
}

void Programare::adaugaObservatii(string obs) {
    observatii = obs;
}

void Programare::afisare() {
    cout << "Programare #" << id 
         << " | Pacient ID: " << idPacient
         << " | Medic ID: " << idMedic
         << " | Data: " << data
         << " | Ora: " << ora
         << " | Durata: " << durataMinute << " min"
         << " | Motiv: " << motiv
         << " | Cost: " << cost << " lei"
         << " | Status: " << status << endl;
    if (!observatii.empty()) {
        cout << "  Observatii: " << observatii << endl;
    }
}