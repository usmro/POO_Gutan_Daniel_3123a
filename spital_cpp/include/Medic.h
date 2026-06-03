#pragma once
#include "Angajat.h"
#include <string>
#include <vector>
using namespace std;

class Medic : public Angajat {
private:
    string specializare;
    string numarParafa;
    string titluAcademic;        // "Dr.", "Conf. Dr.", "Prof. Dr."
    string programLucru;         // "Luni-Vineri 8-14"
    string telefonServiciu;      // separat de telefonul personal
    vector<string> limbiStraine; // "Romana", "Engleza", "Franceza"
    double tarifConsultatie;     // costul unei consultatii
    vector<int> pacientiIDs;     // ID-urile pacientilor alocati
    bool areGarzi;
    string parola;             // parola pentru autentificarea medicului

public:
    Medic(int id, string nume, string prenume, string cnp,
          string dataNasterii, string telefon, string email,
          string adresa, string dataAngajarii, double salariu,
          string iban, string functie, string tipContract,
          string sectie, string specializare, string numarParafa,
          string titluAcademic = "Dr.",
          string programLucru = "Luni-Vineri 8-14",
          string telefonServiciu = "",
          double tarifConsultatie = 200,
          bool areGarzi = false,
          string parola = "medic123");
    
    // Getters
    string getSpecializare();
    string getNumarParafa();
    string getTitluAcademic();
    string getProgramLucru();
    double getTarifConsultatie();
    int getNrPacienti();
    bool getAreGarzi();
    string getParola();
    vector<int> getPacientiIDs();
    
    // Setters
    void setProgramLucru(string program);
    void setTelefonServiciu(string telefon);
    void setTarifConsultatie(double tarif);
    void setGarzi(bool faceGarzi);
    void setParola(string parolaNoua);
    
    // Limbi straine
    void adaugaLimba(string limba);
    void afiseazaLimbi();
    
    // Gestiune pacienti
    void adaugaPacient(int idPacient);
    void stergePacient(int idPacient);
    bool arePacient(int idPacient);
    
    // POLIMORFISM
    double calculBonus() override;
    void afisare() override;
    void afisareDetaliata();
};