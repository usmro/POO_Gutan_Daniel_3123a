#pragma once
#include "Factura.h"
#include "ServiciiMedicale.h"
#include <string>
#include <vector>
using namespace std;

class FacturaFactory {
public:
    // Creează factură pentru o simplă consultație
    static Factura creazaFacturaConsultatie(int idPacient, const string& specialitate);
    
    // Creează factură pentru mai multe analize
    static Factura creazaFacturaAnalize(int idPacient, const vector<string>& tipuriAnalize);
    
    // Creează factură pentru internare (cu/fără intervenție)
    static Factura creazaFacturaInternare(int idPacient, int nrZile, 
                                          const string& sectie, bool cuInterventie = false);
    
    // Creează factură de urgență (pachet complet predefinit)
    static Factura creazaFacturaUrgenta(int idPacient);
};