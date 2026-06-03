#include <iostream>
#include <vector>
#include <filesystem>
#include "Pacient.h"
#include "Angajat.h"
#include "Medic.h"
#include "Asistent.h"
#include "Programare.h"
#include "Factura.h"
#include "ServiciiMedicale.h"
#include "FacturaFactory.h"
#include "FileManager.h"
#include "Logger.h"
#include "Consola.h"
using namespace std;


// Colecții globale
vector<Pacient*> pacienti;
vector<Angajat*> angajati;
vector<Medic*> medici;
vector<Asistent*> asistenti;
vector<Programare*> programari;
vector<Factura*> facturi;

int nextIdPacient = 1;
int nextIdAngajat = 1;
int nextIdProgramare = 1;

void curatareDate() {
    for (auto p : pacienti) delete p;

    // Medicii si asistentii sunt detinuti prin vectorul angajati.
    // Nu ii stergem si din vectorii medici/asistenti, altfel apare double free.
    for (auto a : angajati) delete a;

    for (auto prog : programari) delete prog;
    for (auto f : facturi) delete f;

    pacienti.clear();
    angajati.clear();
    medici.clear();
    asistenti.clear();
    programari.clear();
    facturi.clear();
}

// ========== MENIU PRINCIPAL ==========
void meniuPrincipal() {
    Consola::clearScreen();
    Consola::printTitle("SISTEM GESTIUNE SPITAL");
    cout << "  ║                                            ║" << endl;
    cout << "  ║  1. 👤 Gestiune Pacienți                   ║" << endl;
    cout << "  ║  2. 👨‍⚕️  Gestiune Personal Medical           ║" << endl;
    cout << "  ║  3. 📅 Programări                          ║" << endl;
    cout << "  ║  4. 💰 Facturi                             ║" << endl;
    cout << "  ║  5. 💾 Salvare / Încărcare date            ║" << endl;
    cout << "  ║  6. 📊 Statistici                          ║" << endl;
    cout << "  ║  0. 🚪 Ieșire                              ║" << endl;
    cout << "  ║                                            ║" << endl;
    Consola::printSeparator();
}

// ========== PACIENȚI ==========
void meniuPacienti() {
    Consola::clearScreen();
    Consola::printTitle("GESTIUNE PACIENȚI");
    cout << "  1. Adaugă pacient nou" << endl;
    cout << "  2. Vezi toți pacienții" << endl;
    cout << "  3. Internează pacient" << endl;
    cout << "  4. Externează pacient" << endl;
    cout << "  5. Caută pacient după ID" << endl;
    cout << "  0. Înapoi" << endl;
    Consola::printSeparator();
}

void adaugaPacient() {
    Consola::printTitle("ADAUGĂ PACIENT NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string cnp = Consola::citesteText("CNP");
    string dataNasterii = Consola::citesteText("Data nașterii (YYYY-MM-DD)");
    string telefon = Consola::citesteText("Telefon");
    
    Pacient* p = new Pacient(nextIdPacient++, nume, prenume, cnp, dataNasterii, telefon);
    pacienti.push_back(p);
    Consola::printSuccess("Pacient adăugat cu ID: " + to_string(p->getId()));
}

void veziPacienti() {
    Consola::printTitle("LISTA PACIENȚI (" + to_string(pacienti.size()) + ")");
    Consola::printSeparator();
    if (pacienti.empty()) {
        Consola::printInfo("Nu există pacienți înregistrați.");
    } else {
        for (auto p : pacienti) {
            cout << "  ";
            p->afisare();
        }
    }
    Consola::printSeparator();
}

void interneazaPacient() {
    Consola::printTitle("INTERNEAZĂ PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            string sectie = Consola::citesteText("Secție");
            int salon = Consola::citesteNumar("Salon");
            string data = Consola::citesteText("Data internării");
            p->interneaza(sectie, salon, data);
            return;
        }
    }
    Consola::printError("Pacientul cu ID " + to_string(id) + " nu a fost găsit!");
}

void externeazaPacient() {
    Consola::printTitle("EXTERNEAZĂ PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            string data = Consola::citesteText("Data externării");
            p->externeaza(data);
            return;
        }
    }
    Consola::printError("Pacientul nu a fost găsit!");
}

void cautaPacient() {
    Consola::printTitle("CAUTĂ PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            p->afisareCompleta();
            return;
        }
    }
    Consola::printError("Pacientul nu a fost găsit!");
}

void gestiunePacienti() {
    int opt;
    do {
        meniuPacienti();
        opt = Consola::citesteOptiune(0, 5);
        switch (opt) {
            case 1: adaugaPacient(); break;
            case 2: veziPacienti(); break;
            case 3: interneazaPacient(); break;
            case 4: externeazaPacient(); break;
            case 5: cautaPacient(); break;
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== PERSONAL MEDICAL ==========
void meniuPersonal() {
    Consola::clearScreen();
    Consola::printTitle("GESTIUNE PERSONAL MEDICAL");
    cout << "  1. Adaugă medic nou" << endl;
    cout << "  2. Adaugă asistent nou" << endl;
    cout << "  3. Vezi toți medicii" << endl;
    cout << "  4. Vezi toți asistenții" << endl;
    cout << "  5. Vezi tot personalul" << endl;
    cout << "  0. Înapoi" << endl;
    Consola::printSeparator();
}

void adaugaMedic() {
    Consola::printTitle("ADAUGĂ MEDIC NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string specializare = Consola::citesteText("Specializare");
    string numarParafa = Consola::citesteText("Număr parafă");
    string sectie = Consola::citesteText("Secție");
    
    Medic* m = new Medic(nextIdAngajat++, nume, prenume, "0000000000000", "1980-01-01",
                         "0700000000", nume + "@spital.ro", "Str. Spitalului",
                         "2020-01-01", 8000, "RO00", "Medic", "Norma intreaga",
                         sectie, specializare, numarParafa);
    medici.push_back(m);
    angajati.push_back(m);
    Consola::printSuccess("Medic adăugat cu ID: " + to_string(m->getId()));
}

void adaugaAsistent() {
    Consola::printTitle("ADAUGĂ ASISTENT NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string sectie = Consola::citesteText("Secție");
    
    Asistent* a = new Asistent(nextIdAngajat++, nume, prenume, "0000000000000", "1990-01-01",
                               "0700000000", nume + "@spital.ro", "Str. Spitalului",
                               "2022-01-01", 4000, "RO00", "Asistent", "Norma intreaga",
                               sectie, "Medical");
    asistenti.push_back(a);
    angajati.push_back(a);
    Consola::printSuccess("Asistent adăugat cu ID: " + to_string(a->getId()));
}

void gestiunePersonal() {
    int opt;
    do {
        meniuPersonal();
        opt = Consola::citesteOptiune(0, 5);
        switch (opt) {
            case 1: adaugaMedic(); break;
            case 2: adaugaAsistent(); break;
            case 3:
                Consola::printTitle("MEDICI (" + to_string(medici.size()) + ")");
                for (auto m : medici) { cout << "  "; m->afisare(); }
                break;
            case 4:
                Consola::printTitle("ASISTENȚI (" + to_string(asistenti.size()) + ")");
                for (auto a : asistenti) { cout << "  "; a->afisare(); }
                break;
            case 5:
                Consola::printTitle("TOT PERSONALUL (" + to_string(angajati.size()) + ")");
                for (auto a : angajati) { cout << "  "; a->afisare(); }
                break;
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== PROGRAMĂRI ==========
void meniuProgramari() {
    Consola::clearScreen();
    Consola::printTitle("PROGRAMĂRI");
    cout << "  1. Programare nouă" << endl;
    cout << "  2. Vezi toate programările" << endl;
    cout << "  3. Confirmă programare" << endl;
    cout << "  4. Anulează programare" << endl;
    cout << "  0. Înapoi" << endl;
    Consola::printSeparator();
}

void adaugaProgramare() {
    Consola::printTitle("PROGRAMARE NOUĂ");
    int idPacient = Consola::citesteNumar("ID Pacient");
    int idMedic = Consola::citesteNumar("ID Medic");
    string data = Consola::citesteText("Data (YYYY-MM-DD)");
    string ora = Consola::citesteText("Ora (HH:MM)");
    string motiv = Consola::citesteText("Motiv");
    
    try {
        Programare* prog = new Programare(nextIdProgramare++, idPacient, idMedic, data, ora, motiv);
        prog->valideaza();
        programari.push_back(prog);
        Consola::printSuccess("Programare creată cu ID: " + to_string(prog->getId()));
    } catch (ProgramareInvalidaException& e) {
        Consola::printError(e.what());
    }
}

void gestiuneProgramari() {
    int opt;
    do {
        meniuProgramari();
        opt = Consola::citesteOptiune(0, 4);
        switch (opt) {
            case 1: adaugaProgramare(); break;
            case 2:
                Consola::printTitle("PROGRAMĂRI (" + to_string(programari.size()) + ")");
                for (auto prog : programari) { cout << "  "; prog->afisare(); }
                break;
            case 3: {
                int id = Consola::citesteNumar("ID Programare");
                for (auto prog : programari)
                    if (prog->getId() == id) { prog->confirma(); break; }
                break;
            }
            case 4: {
                int id = Consola::citesteNumar("ID Programare");
                string motiv = Consola::citesteText("Motiv anulare");
                for (auto prog : programari)
                    if (prog->getId() == id) { prog->anuleaza(motiv); break; }
                break;
            }
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== FACTURI ==========
void meniuFacturi() {
    Consola::clearScreen();
    Consola::printTitle("FACTURI");
    cout << "  1. Emite factură nouă" << endl;
    cout << "  2. Vezi toate facturile" << endl;
    cout << "  3. Plătește factură" << endl;
    cout << "  0. Înapoi" << endl;
    Consola::printSeparator();
}

void emiteFactura() {
    Consola::printTitle("EMITE FACTURĂ");
    int idPacient = Consola::citesteNumar("ID Pacient");
    Factura* f = new Factura(idPacient);
    
    Consola::printInfo("Adaugă servicii (scrie 'stop' pentru a termina)");
    string serviciu;
    double cost;
    int nr = 1;
    while (true) {
        cout << "  Serviciul " << nr << ": ";
        cin >> serviciu;
        if (serviciu == "stop" || serviciu == "0") break;
        cost = Consola::citesteDouble("Cost");
        f->adaugaServiciu(serviciu, cost);
        nr++;
    }
    
    facturi.push_back(f);
    Consola::printSuccess("Factură emisă! Total: " + to_string(f->getTotal()) + " lei");
    f->afisare();
}

void gestiuneFacturi() {
    int opt;
    do {
        meniuFacturi();
        opt = Consola::citesteOptiune(0, 3);
        switch (opt) {
            case 1: emiteFactura(); break;
            case 2:
                Consola::printTitle("FACTURI (" + to_string(facturi.size()) + ")");
                for (auto f : facturi) f->afisare();
                break;
            case 3: {
                int id = Consola::citesteNumar("ID Factură");
                string metoda = Consola::citesteText("Metodă plată");
                for (auto f : facturi)
                    if (f->getId() == id) { f->plateste(metoda); break; }
                break;
            }
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== SALVARE / ÎNCĂRCARE ==========
void salvareDate() {
    Consola::printTitle("SALVARE DATE");
    std::filesystem::create_directories("date");
    FileManager::salveazaPacienti(pacienti, "date/pacienti.json");
    FileManager::salveazaAngajati(angajati, "date/angajati.json");
    FileManager::salveazaProgramari(programari, "date/programari.json");
    FileManager::salveazaFacturi(facturi, "date/facturi.json");
    Consola::printSuccess("Toate datele au fost salvate!");
}

void incarcareDate() {
    Consola::printTitle("ÎNCĂRCARE DATE");
    auto p = FileManager::incarcaPacienti("date/pacienti.json");
    Consola::printInfo("Pacienți încărcați: " + to_string(p.size()));
}

// ========== STATISTICI ==========
void statistici() {
    Consola::clearScreen();
    Consola::printTitle("STATISTICI SPITAL");
    Consola::printSeparator();
    cout << "  👤 Pacienți       : " << pacienti.size() << endl;
    cout << "  👨‍⚕️ Medici        : " << medici.size() << endl;
    cout << "  👩‍⚕️ Asistenți     : " << asistenti.size() << endl;
    cout << "  📅 Programări     : " << programari.size() << endl;
    cout << "  💰 Facturi        : " << Factura::getContor() << endl;
    double total = 0;
    for (auto f : facturi) total += f->getTotal();
    cout << "  💵 Total facturat : " << total << " lei" << endl;
    Consola::printSeparator();
}

// ========== MAIN ==========
int main() {
    Logger::getInstanta()->log("Aplicația a pornit");
    
    int opt;
    do {
        meniuPrincipal();
        opt = Consola::citesteOptiune(0, 6);
        switch (opt) {
            case 1: gestiunePacienti(); break;
            case 2: gestiunePersonal(); break;
            case 3: gestiuneProgramari(); break;
            case 4: gestiuneFacturi(); break;
            case 5: {
                Consola::clearScreen();
                Consola::printTitle("SALVARE / ÎNCĂRCARE");
                cout << "  1. Salvare date" << endl;
                cout << "  2. Încărcare date" << endl;
                int sopt = Consola::citesteOptiune(1, 2);
                if (sopt == 1) salvareDate();
                else incarcareDate();
                break;
            }
            case 6: statistici(); break;
            case 0: Consola::printSuccess("La revedere!"); break;
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
    
    curatareDate();
    Logger::getInstanta()->inchide();
    return 0;
}