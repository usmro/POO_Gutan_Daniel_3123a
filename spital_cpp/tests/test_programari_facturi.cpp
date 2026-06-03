#include <cassert>
#include <cmath>
#include <iostream>
#include "Programare.h"
#include "Factura.h"
#include "ServiciiMedicale.h"

void testProgramareValida() {
    Programare p(1, 1, 1, "2026-06-03", "10:30", "Consultatie", 30, 200);
    p.valideaza();
    assert(p.getStatus() == "In asteptare");
    p.confirma();
    assert(p.getStatus() == "Confirmata");
}

void testProgramareInvalida() {
    bool exceptiePrinsa = false;
    try {
        Programare p(1, 1, 1, "2026-06-03", "22:00", "Consultatie");
        p.valideaza();
    } catch (const ProgramareInvalidaException&) {
        exceptiePrinsa = true;
    }
    assert(exceptiePrinsa);
}

void testSuprapunereProgramari() {
    Programare a(1, 1, 7, "2026-06-03", "10:00", "Consultatie", 60, 200);
    Programare b(2, 2, 7, "2026-06-03", "10:30", "Control", 30, 150);
    Programare c(3, 3, 8, "2026-06-03", "10:30", "Control", 30, 150);
    assert(a.seSuprapuneCu(b));
    assert(!a.seSuprapuneCu(c));
}

void testCalculFactura() {
    Factura f(1);
    Consultatie consultatie("Cardiologie", 200);
    Analize analize("Sange", 100);
    f.adaugaServiciu(consultatie);
    f.adaugaServiciu(analize);
    assert(f.getNumarServicii() == 2);
    assert(f.getTotal() > 0);
}

int main() {
    testProgramareValida();
    testProgramareInvalida();
    testSuprapunereProgramari();
    testCalculFactura();
    std::cout << "Toate testele au trecut cu succes!\n";
    return 0;
}
