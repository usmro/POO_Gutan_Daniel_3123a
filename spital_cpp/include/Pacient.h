#pragma once
#include <string>
#include <vector>
using namespace std;

class Pacient {
private:
    // Date personale
    int id;
    string nume;
    string prenume;
    string cnp;
    string dataNasterii;
    string telefon;
    string email;
    string adresa;
    string grupaSanguina;  // A, B, AB, O
    string rh;             // Pozitiv, Negativ
    
    // Date medicale
    string diagnostic;
    vector<string> boliCronice;
    vector<string> alergii;
    vector<string> medicatieCurenta;
    
    // Date spitalizare
    bool internat;
    string dataInternarii;
    string dataExternarii;
    string sectie;
    int numarSalon;
    int idMedicCurant;  // 0 = fără medic asignat

public:
    // Constructor simplificat
    Pacient(int id, string nume, string prenume, string cnp, 
            string dataNasterii, string telefon);
    
    // Constructor complet
    Pacient(int id, string nume, string prenume, string cnp,
            string dataNasterii, string telefon, string email,
            string adresa, string grupaSanguina, string rh);
    
    // Getters
    int getId();
    string getNume();
    string getCnp();
    string getDataNasterii();
    string getTelefon();
    string getDiagnostic();
    string getGrupaSanguina();
    bool isInternat();
    string getDataInternarii();
    string getSectie();
    int getIdMedicCurant();
    
    // Setters
    void setDiagnostic(string diagnosticNou);
    void setTelefon(string telefonNou);
    void setEmail(string emailNou);
    void setAdresa(string adresaNou);
    
    // Metode medicale
    void adaugaBoalaCronica(string boala);
    void adaugaAlergie(string alergie);
    void adaugaMedicatie(string medicament);
    void afiseazaBoliCronice();
    void afiseazaAlergii();
    
    // Metode spitalizare
    void interneaza(string sectie, int salon, string data);
    void externeaza(string data);
    void asigneazaMedic(int idMedic);
    
    // Utilitare
    int calculeazaVarsta();
    void afisare();
    void afisareCompleta();
};