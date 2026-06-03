#include "FacturaFactory.h"
#include <iostream>
using namespace std;

Factura FacturaFactory::creazaFacturaConsultatie(int idPacient, const string& specialitate) {
    cout << "[FACTORY] Creare factura consultatie " << specialitate << "..." << endl;
    
    Factura f(idPacient);
    Consultatie consult(specialitate);
    f.adaugaServiciu(consult);
    
    cout << "[FACTORY] Factura #" << f.getId() << " creata. Total: " << f.getTotal() << " lei" << endl;
    return f;
}

Factura FacturaFactory::creazaFacturaAnalize(int idPacient, const vector<string>& tipuriAnalize) {
    cout << "[FACTORY] Creare factura pentru " << tipuriAnalize.size() << " analize..." << endl;
    
    Factura f(idPacient);
    for (const string& tip : tipuriAnalize) {
        Analize analiza(tip);
        f.adaugaServiciu(analiza);
    }
    
    cout << "[FACTORY] Factura #" << f.getId() << " creata. Total: " << f.getTotal() << " lei" << endl;
    return f;
}

Factura FacturaFactory::creazaFacturaInternare(int idPacient, int nrZile, 
                                                const string& sectie, bool cuInterventie) {
    cout << "[FACTORY] Creare factura internare " << nrZile << " zile, sectia " << sectie << "..." << endl;
    
    Factura f(idPacient);
    
    Spitalizare spitalizare(nrZile);
    f.adaugaServiciu(spitalizare);
    
    Consultatie consult("Generala");
    f.adaugaServiciu(consult);
    
    if (cuInterventie) {
        Interventie operatie("medie");
        f.adaugaServiciu(operatie);
    }
    
    cout << "[FACTORY] Factura #" << f.getId() << " creata. Total: " << f.getTotal() << " lei" << endl;
    return f;
}

Factura FacturaFactory::creazaFacturaUrgenta(int idPacient) {
    cout << "[FACTORY] Creare factura URGENTA..." << endl;
    
    Factura f(idPacient);
    
    Consultatie consult("Generala");
    f.adaugaServiciu(consult);
    
    Analize sange("Sange complet");
    Analize radiografie("Radiografie");
    f.adaugaServiciu(sange);
    f.adaugaServiciu(radiografie);
    
    Spitalizare spitalizare(1);
    f.adaugaServiciu(spitalizare);
    
    cout << "[FACTORY] Factura #" << f.getId() << " creata. Total: " << f.getTotal() << " lei" << endl;
    return f;
}