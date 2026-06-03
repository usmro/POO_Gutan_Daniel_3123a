#pragma once
#include <string>
#include "Exceptii.h"
using namespace std;

class Programare {
private:
    int id;
    int idPacient;
    int idMedic;
    string data;              // "2026-05-20"
    string ora;               // "10:30"
    string motiv;             // "Consultatie", "Control", "Urgenta"
    int durataMinute;         // durata estimata in minute (default 30)
    string status;            // "In asteptare", "Confirmata", "Anulata", "Prezentat", "Absent"
    double cost;              // costul programarii
    string observatii;

public:
    Programare(int id, int idPacient, int idMedic,
               string data, string ora, string motiv = "Consultatie",
               int durataMinute = 30, double cost = 0);
    
    // Getters
    int getId();
    int getIdPacient();
    int getIdMedic();
    string getData();
    string getOra();
    string getMotiv();
    int getDurataMinute();
    string getStatus();
    double getCost();
    
    // Setters
    void setCost(double costNou);
    void setDurata(int minute);
    
    // Metode status
    void confirma();
    void anuleaza(string motivAnulare);
    void marcheazaPrezentat();
    void marcheazaAbsent();
    
    // Metode noi
    void reprogrameaza(string dataNoua, string oraNoua);
    bool seSuprapuneCu(const Programare& alta);
    string getDetaliiFactura();
    
    // Validare si afisare
    void valideaza();
    void adaugaObservatii(string obs);
    void afisare();
};