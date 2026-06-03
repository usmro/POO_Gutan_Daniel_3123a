#pragma once
#include <string>
#include <vector>
#include <utility>
#include "ServiciiMedicale.h"
using namespace std;

class Factura {
private:
    static int contor;
    int id;
    int idPacient;
    vector<pair<string, double>> servicii;
    string dataEmitere;
    string dataScadenta;
    bool platita;
    string metodaPlata;

public:
    Factura(int idPacient);
    int getId();
    int getIdPacient();
    double getTotal();
    bool isPlatita();
    string getDataEmitere();
    string getDataScadenta();
    int getNumarServicii();
    void adaugaServiciu(const string& descriere, double cost);
    void adaugaServiciu(const ServiciuMedical& serviciu);
    void plateste(const string& metoda = "Cash");
    string getDetaliiPlata();
    void afisare();
    static int getContor() { return contor; }

private:
    string getCurrentDate();
    string getDataScadentaDate();
};