#include "Factura.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <stdexcept>
using namespace std;

int Factura::contor = 0;

Factura::Factura(int idPacient) {
    contor++;
    id = contor;
    this->idPacient = idPacient;
    dataEmitere = getCurrentDate();
    dataScadenta = getDataScadentaDate();
    platita = false;
    metodaPlata = "";
}

string Factura::getCurrentDate() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M");
    return ss.str();
}

string Factura::getDataScadentaDate() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    time += 30 * 24 * 3600;
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d");
    return ss.str();
}

int Factura::getId() { return id; }
int Factura::getIdPacient() { return idPacient; }
double Factura::getTotal() {
    double total = 0;
    for (const auto& s : servicii) total += s.second;
    return total;
}
bool Factura::isPlatita() { return platita; }
string Factura::getDataEmitere() { return dataEmitere; }
string Factura::getDataScadenta() { return dataScadenta; }
int Factura::getNumarServicii() { return servicii.size(); }

void Factura::adaugaServiciu(const string& descriere, double cost) {
    if (cost < 0) throw invalid_argument("Cost negativ!");
    if (platita) throw runtime_error("Factura deja platita!");
    servicii.push_back({descriere, cost});
}

void Factura::adaugaServiciu(const ServiciuMedical& serviciu) {
    adaugaServiciu(serviciu.getDescriere(), serviciu.calculeazaCost());
}

void Factura::plateste(const string& metoda) {
    if (platita) throw runtime_error("Deja platita!");
    platita = true;
    metodaPlata = metoda;
    cout << "Factura #" << id << " platita (" << metoda << ")." << endl;
    Logger::getInstanta()->logOperatiune("FACTURA", 
    "Factura #" + to_string(id) + " platita pentru pacientul " + 
    to_string(idPacient) + ". Suma: " + to_string(getTotal()) + 
    " lei. Metoda: " + metoda);
}

string Factura::getDetaliiPlata() {
    stringstream ss;
    ss << "Factura #" << id << " | Pacient: " << idPacient
       << " | Total: " << getTotal() << " lei | "
       << (platita ? "PLATITA" : "NEPLATITA");
    if (platita) ss << " (" << metodaPlata << ")";
    return ss.str();
}

void Factura::afisare() {
    cout << "\n==================================================" << endl;
    cout << "                   FACTURA #" << id << endl;
    cout << "==================================================" << endl;
    cout << "Pacient ID: " << idPacient << endl;
    cout << "Data emitere: " << dataEmitere << endl;
    cout << "Data scadenta: " << dataScadenta << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "SERVICII MEDICALE:" << endl;
    int nr = 1;
    for (const auto& s : servicii) {
        cout << "  " << nr << ". " << s.first;
        cout << string(40 - s.first.length(), '.');
        cout << s.second << " lei" << endl;
        nr++;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "TOTAL: " << getTotal() << " lei" << endl;
    cout << "Status: " << (platita ? "PLATITA" : "NEPLATITA");
    if (platita) cout << " - " << metodaPlata;
    cout << endl;
    cout << "==================================================" << endl;
}