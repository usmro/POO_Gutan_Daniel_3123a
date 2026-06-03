#pragma once
#include "Angajat.h"
#include <string>
using namespace std;

class Asistent : public Angajat {
private:
    string gradProfesional;
    string tipAsistent;
    int oreSuplimentare;
    bool areTureNoapte;
    int nrTureNoapteEfectuate;
    bool areAvizLiberaPractica;

public:
    Asistent(int id, string nume, string prenume, string cnp,
             string dataNasterii, string telefon, string email,
             string adresa, string dataAngajarii, double salariu,
             string iban, string functie, string tipContract,
             string sectie, string gradProfesional,
             string tipAsistent = "Generalist",
             int oreSuplimentare = 0, bool areTureNoapte = false,
             int nrTureNoapteEfectuate = 0, bool areAvizLiberaPractica = true);
    
    string getGradProfesional();
    string getTipAsistent();
    int getOreSuplimentare();
    bool getAreTureNoapte();
    int getNrTureNoapteEfectuate();
    bool getAreAvizLiberaPractica();
    
    void setOreSuplimentare(int ore);
    void setTureNoapte(bool are);
    void setAvizLiberaPractica(bool are);
    
    void adaugaOreSuplimentare(int ore);
    void incrementareTureNoapte();
    void reseteazaPontaj();
    
    bool poateLucra();
    void afisareAviz();
    
    double calculBonus() override;
    void afisare() override;
};