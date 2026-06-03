#include "ServiciiMedicale.h"
#include <sstream>
#include <iomanip>
using namespace std;

// ========== CONSULTATIE ==========
Consultatie::Consultatie(const string& specialitate, double tarifBaza) 
    : specialitate(specialitate), tarifBaza(tarifBaza) {
    if (specialitate == "Cardiologie") this->tarifBaza = 250;
    else if (specialitate == "Neurologie") this->tarifBaza = 300;
    else if (specialitate == "Pediatrie") this->tarifBaza = 180;
    else if (specialitate == "Dermatologie") this->tarifBaza = 160;
    else if (specialitate == "Oftalmologie") this->tarifBaza = 170;
    else this->tarifBaza = tarifBaza;
}

double Consultatie::calculeazaCost() const {
    if (specialitate != "Generala") {
        return tarifBaza * 1.10;
    }
    return tarifBaza;
}

string Consultatie::getDescriere() const {
    stringstream ss;
    ss << "Consultatie " << specialitate;
    return ss.str();
}

double Consultatie::getTarifBaza() const { return tarifBaza; }


// ========== ANALIZE ==========
Analize::Analize(const string& tip, double pretLaborator)
    : tip(tip), pretLaborator(pretLaborator) {
    if (tip == "Sange complet") this->pretLaborator = 150;
    else if (tip == "Urina") this->pretLaborator = 80;
    else if (tip == "RMN") this->pretLaborator = 800;
    else if (tip == "CT") this->pretLaborator = 600;
    else if (tip == "Radiografie") this->pretLaborator = 120;
    else if (tip == "EKG") this->pretLaborator = 130;
    else if (tip == "Ecografie") this->pretLaborator = 200;
    else this->pretLaborator = pretLaborator;
}

double Analize::calculeazaCost() const {
    return pretLaborator * 1.15;
}

string Analize::getDescriere() const {
    stringstream ss;
    ss << "Analize " << tip;
    return ss.str();
}

double Analize::getPretLaborator() const { return pretLaborator; }


// ========== INTERVENTIE CHIRURGICALA ==========
Interventie::Interventie(const string& complexitate, 
                         double costAnestezie, 
                         double costMateriale,
                         double tarifBaza)
    : complexitate(complexitate), 
      costAnestezie(costAnestezie), 
      costMateriale(costMateriale),
      tarifBaza(tarifBaza) {
    if (complexitate == "majora") {
        this->tarifBaza = 5000;
        this->costAnestezie = 800;
        this->costMateriale = 1000;
    } else if (complexitate == "medie") {
        this->tarifBaza = 2500;
        this->costAnestezie = 500;
        this->costMateriale = 500;
    }
}

double Interventie::calculeazaCost() const {
    double cost = tarifBaza + costAnestezie + costMateriale;
    if (complexitate == "majora") cost *= 1.05;
    else if (complexitate == "medie") cost *= 1.03;
    return cost;
}

string Interventie::getDescriere() const {
    stringstream ss;
    ss << "Interventie chirurgicala " << complexitate;
    return ss.str();
}


// ========== SPITALIZARE ==========
Spitalizare::Spitalizare(int nrZile, double tarifPeZi)
    : nrZile(nrZile), tarifPeZi(tarifPeZi) {}

double Spitalizare::calculeazaCost() const {
    double cost = nrZile * tarifPeZi;
    if (nrZile >= 14) cost *= 0.80;
    else if (nrZile >= 7) cost *= 0.90;
    return cost;
}

string Spitalizare::getDescriere() const {
    stringstream ss;
    ss << "Spitalizare " << nrZile << " zile x " << fixed << setprecision(0) 
       << tarifPeZi << " lei/zi";
    if (nrZile >= 14) ss << " (reducere 20%)";
    else if (nrZile >= 7) ss << " (reducere 10%)";
    return ss.str();
}

int Spitalizare::getNrZile() const { return nrZile; }