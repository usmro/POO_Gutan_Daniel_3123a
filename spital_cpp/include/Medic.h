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
    double tarifConsultatie;     // costul unei consultații
    vector<int> pacientiIDs;     // ID-urile pacienților alocați
    bool areGarzi;

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
          bool areGarzi = false);
    
    // Getters
    string getSpecializare();
    string getNumarParafa();
    string getTitluAcademic();
    string getProgramLucru();
    double getTarifConsultatie();
    int getNrPacienti();
    bool getAreGarzi();
    vector<int> getPacientiIDs();
    
    // Setters
    void setProgramLucru(string program);
    void setTelefonServiciu(string telefon);
    void setTarifConsultatie(double tarif);
    void setGarzi(bool faceGarzi);
    
    // Limbi straine
    void adaugaLimba(string limba);
    void afiseazaLimbi();
    
    // Gestiune pacienți
    void adaugaPacient(int idPacient);
    void stergePacient(int idPacient);
    bool arePacient(int idPacient);
    
    // POLIMORFISM
    double calculBonus() override;
    void afisare() override;
    void afisareDetaliata();
};