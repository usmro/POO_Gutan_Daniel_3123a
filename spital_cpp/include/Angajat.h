#pragma once
#include <string>
using namespace std;

class Angajat {
protected:
    // Date personale
    int id;
    string nume;
    string prenume;
    string cnp;
    string dataNasterii;
    string telefon;
    string email;
    string adresa;
    
    // Date angajare
    string dataAngajarii;
    double salariu;
    string iban;
    string functie;          // Ex: "Asistent", "Brancardier", "Manager"
    string tipContract;      // "Norma intreaga", "Part-time 4h", "Part-time 6h"
    string sectie;           // Ex: "Cardiologie", "UPU", "Administrativ"
    bool esteActiv;          // true = lucrează, false = a plecat

public:
    Angajat(int id, string nume, string prenume, string cnp,
            string dataNasterii, string telefon, string email,
            string adresa, string dataAngajarii, double salariu,
            string iban, string functie, string tipContract,
            string sectie);
    
    // Getters
    int getId();
    string getNume();
    double getSalariu();
    string getSectie();
    string getFunctie();
    bool isActiv();
    
    // Setters
    void setSalariu(double salariuNou);
    void setTelefon(string telefonNou);
    void setEmail(string emailNou);
    void setSectie(string sectieNoua);
    void dezactiveaza();     // Marchează angajatul ca inactiv
    void activeaza();        // Reactivează angajatul
    
    // Metode virtuale pentru POLIMORFISM
    virtual double calculBonus();
    virtual void afisare();
    
    // Utilitare
    int calculeazaVechime();
    int calculeazaVarsta();
    void afisareCompleta();
    
    virtual ~Angajat() {}
};