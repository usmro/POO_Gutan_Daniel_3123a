#pragma once
#include "Factura.h"
#include "ServiciiMedicale.h"
#include <string>
#include <vector>
using namespace std;

class FacturaFactory {
public:
    // Creeaza factura pentru o simpla consultatie
    static Factura creazaFacturaConsultatie(int idPacient, const string& specialitate);
    
    // Creeaza factura pentru mai multe analize
    static Factura creazaFacturaAnalize(int idPacient, const vector<string>& tipuriAnalize);
    
    // Creeaza factura pentru internare (cu/fara interventie)
    static Factura creazaFacturaInternare(int idPacient, int nrZile, 
                                          const string& sectie, bool cuInterventie = false);
    
    // Creeaza factura de urgenta (pachet complet predefinit)
    static Factura creazaFacturaUrgenta(int idPacient);
};