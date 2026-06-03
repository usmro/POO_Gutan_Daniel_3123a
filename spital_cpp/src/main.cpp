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


// Colectii globale
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
    Consola::printMenuBox("SISTEM GESTIUNE SPITAL", {
        {1, " Gestiune pacienti"},
        {2, " Gestiune personal medical"},
        {3, " Programari"},
        {4, " Facturi"},
        {5, " Salvare / incarcare date"},
        {6, " Statistici"},
        {0, " Iesire"}
    });
    Consola::printStatusBar((int)pacienti.size(), (int)medici.size(), (int)asistenti.size(),
                            (int)programari.size(), (int)facturi.size());
}

// ========== PACIENTI ==========
void meniuPacienti() {
    Consola::clearScreen();
    Consola::printMenuBox("GESTIUNE PACIENTI", {
        {1, "Adauga pacient nou"},
        {2, "Vezi toti pacientii"},
        {3, "Interneaza pacient"},
        {4, "Externeaza pacient"},
        {5, "Cauta pacient dupa ID"},
        {0, "Inapoi"}
    });
}

void adaugaPacient() {
    Consola::printTitle("ADAUGA PACIENT NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string cnp = Consola::citesteText("CNP");
    string dataNasterii = Consola::citesteText("Data nasterii (YYYY-MM-DD)");
    string telefon = Consola::citesteText("Telefon");
    
    Pacient* p = new Pacient(nextIdPacient++, nume, prenume, cnp, dataNasterii, telefon);
    pacienti.push_back(p);
    Consola::printSuccess("Pacient adaugat cu ID: " + to_string(p->getId()));
}

void veziPacienti() {
    Consola::printTitle("LISTA PACIENTI (" + to_string(pacienti.size()) + ")");
    Consola::printSeparator();
    if (pacienti.empty()) {
        Consola::printInfo("Nu exista pacienti inregistrati.");
    } else {
        for (auto p : pacienti) {
            cout << "  ";
            p->afisare();
        }
    }
    Consola::printSeparator();
}

void interneazaPacient() {
    Consola::printTitle("INTERNEAZA PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            string sectie = Consola::citesteText("Sectie");
            int salon = Consola::citesteNumar("Salon");
            string data = Consola::citesteText("Data internarii");
            p->interneaza(sectie, salon, data);
            return;
        }
    }
    Consola::printError("Pacientul cu ID " + to_string(id) + " nu a fost gasit!");
}

void externeazaPacient() {
    Consola::printTitle("EXTERNEAZA PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            string data = Consola::citesteText("Data externarii");
            p->externeaza(data);
            return;
        }
    }
    Consola::printError("Pacientul nu a fost gasit!");
}

void cautaPacient() {
    Consola::printTitle("CAUTA PACIENT");
    int id = Consola::citesteNumar("ID pacient");
    for (auto p : pacienti) {
        if (p->getId() == id) {
            p->afisareCompleta();
            return;
        }
    }
    Consola::printError("Pacientul nu a fost gasit!");
}

void gestiunePacienti() {
    int opt;
    do {
        opt = Consola::meniuInteractv("GESTIUNE PACIENTI", {
            {1, "Adauga pacient nou"},
            {2, "Vezi toti pacientii"},
            {3, "Interneaza pacient"},
            {4, "Externeaza pacient"},
            {5, "Cauta pacient dupa ID"},
            {0, "Inapoi"}
        });
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
    Consola::printMenuBox("GESTIUNE PERSONAL MEDICAL", {
        {1, "Adauga medic nou"},
        {2, "Adauga asistent nou"},
        {3, "Vezi toti medicii"},
        {4, "Vezi toti asistentii"},
        {5, "Vezi tot personalul"},
        {6, "Schimba parola medic"},
        {0, "Inapoi"}
    });
}

void adaugaMedic() {
    Consola::printTitle("ADAUGA MEDIC NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string specializare = Consola::citesteText("Specializare");
    string numarParafa = Consola::citesteText("Numar parafa");
    string sectie = Consola::citesteText("Sectie");
    string parola = Consola::citesteText("Parola pentru login medic");
    
    Medic* m = new Medic(nextIdAngajat++, nume, prenume, "0000000000000", "1980-01-01",
                         "0700000000", nume + "@spital.ro", "Str. Spitalului",
                         "2020-01-01", 8000, "RO00", "Medic", "Norma intreaga",
                         sectie, specializare, numarParafa, "Dr.",
                         "Luni-Vineri 8-14", "", 200, false, parola);
    medici.push_back(m);
    angajati.push_back(m);
    Consola::printSuccess("Medic adaugat cu ID: " + to_string(m->getId()));
    Consola::printInfo("Medicul se poate loga cu ID-ul " + to_string(m->getId()) + " si parola introdusa.");
}

void adaugaAsistent() {
    Consola::printTitle("ADAUGA ASISTENT NOU");
    string nume = Consola::citesteText("Nume");
    string prenume = Consola::citesteText("Prenume");
    string sectie = Consola::citesteText("Sectie");
    
    Asistent* a = new Asistent(nextIdAngajat++, nume, prenume, "0000000000000", "1990-01-01",
                               "0700000000", nume + "@spital.ro", "Str. Spitalului",
                               "2022-01-01", 4000, "RO00", "Asistent", "Norma intreaga",
                               sectie, "Medical");
    asistenti.push_back(a);
    angajati.push_back(a);
    Consola::printSuccess("Asistent adaugat cu ID: " + to_string(a->getId()));
}

void schimbaParolaMedic();

void gestiunePersonal() {
    int opt;
    do {
        opt = Consola::meniuInteractv("GESTIUNE PERSONAL MEDICAL", {
            {1, "Adauga medic nou"},
            {2, "Adauga asistent nou"},
            {3, "Vezi toti medicii"},
            {4, "Vezi toti asistentii"},
            {5, "Vezi tot personalul"},
            {6, "Schimba parola medic"},
            {0, "Inapoi"}
        });
        switch (opt) {
            case 1: adaugaMedic(); break;
            case 2: adaugaAsistent(); break;
            case 3:
                Consola::printTitle("MEDICI (" + to_string(medici.size()) + ")");
                for (auto m : medici) { cout << "  "; m->afisare(); }
                break;
            case 4:
                Consola::printTitle("ASISTENTI (" + to_string(asistenti.size()) + ")");
                for (auto a : asistenti) { cout << "  "; a->afisare(); }
                break;
            case 5:
                Consola::printTitle("TOT PERSONALUL (" + to_string(angajati.size()) + ")");
                for (auto a : angajati) { cout << "  "; a->afisare(); }
                break;
            case 6:
                schimbaParolaMedic();
                break;
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== PROGRAMARI ==========
void meniuProgramari() {
    Consola::clearScreen();
    Consola::printMenuBox("PROGRAMARI", {
        {1, "Programare noua"},
        {2, "Vezi toate programarile"},
        {3, "Confirma programare"},
        {4, "Anuleaza programare"},
        {0, "Inapoi"}
    });
}

void adaugaProgramare() {
    Consola::printTitle("PROGRAMARE NOUA");
    int idPacient = Consola::citesteNumar("ID Pacient");
    int idMedic = Consola::citesteNumar("ID Medic");
    string data = Consola::citesteText("Data (YYYY-MM-DD)");
    string ora = Consola::citesteText("Ora (HH:MM)");
    string motiv = Consola::citesteText("Motiv");
    
    try {
        Programare* prog = new Programare(nextIdProgramare++, idPacient, idMedic, data, ora, motiv);
        prog->valideaza();
        programari.push_back(prog);
        Consola::printSuccess("Programare creata cu ID: " + to_string(prog->getId()));
    } catch (ProgramareInvalidaException& e) {
        Consola::printError(e.what());
    }
}

void gestiuneProgramari() {
    int opt;
    do {
        opt = Consola::meniuInteractv("PROGRAMARI", {
            {1, "Programare noua"},
            {2, "Vezi toate programarile"},
            {3, "Confirma programare"},
            {4, "Anuleaza programare"},
            {0, "Inapoi"}
        });
        switch (opt) {
            case 1: adaugaProgramare(); break;
            case 2:
                Consola::printTitle("PROGRAMARI (" + to_string(programari.size()) + ")");
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
    Consola::printMenuBox("FACTURI", {
        {1, "Emite factura noua"},
        {2, "Vezi toate facturile"},
        {3, "Plateste factura"},
        {0, "Inapoi"}
    });
}

void emiteFactura() {
    Consola::printTitle("EMITE FACTURA");
    int idPacient = Consola::citesteNumar("ID Pacient");
    Factura* f = new Factura(idPacient);
    
    Consola::printInfo("Adauga servicii (scrie 'stop' pentru a termina)");
    string serviciu;
    double cost;
    int nr = 1;
    while (true) {
        serviciu = Consola::citesteText("Serviciul " + to_string(nr));
        if (serviciu == "stop" || serviciu == "0") break;
        cost = Consola::citesteDouble("Cost");
        f->adaugaServiciu(serviciu, cost);
        nr++;
    }
    
    facturi.push_back(f);
    Consola::printSuccess("Factura emisa! Total: " + to_string(f->getTotal()) + " lei");
    f->afisare();
}

void gestiuneFacturi() {
    int opt;
    do {
        opt = Consola::meniuInteractv("FACTURI", {
            {1, "Emite factura noua"},
            {2, "Vezi toate facturile"},
            {3, "Plateste factura"},
            {0, "Inapoi"}
        });
        switch (opt) {
            case 1: emiteFactura(); break;
            case 2:
                Consola::printTitle("FACTURI (" + to_string(facturi.size()) + ")");
                for (auto f : facturi) f->afisare();
                break;
            case 3: {
                int id = Consola::citesteNumar("ID Factura");
                string metoda = Consola::citesteText("Metoda plata");
                for (auto f : facturi)
                    if (f->getId() == id) { f->plateste(metoda); break; }
                break;
            }
        }
        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

// ========== SALVARE / INCARCARE ==========
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
    Consola::printTitle("INCARCARE DATE");

    // Curatam datele deja existente in memorie, apoi incarcam din fisiere.
    curatareDate();

    pacienti = FileManager::incarcaPacienti("date/pacienti.json");
    angajati = FileManager::incarcaAngajati("date/angajati.json");

    medici.clear();
    asistenti.clear();
    nextIdPacient = 1;
    nextIdAngajat = 1;

    for (auto p : pacienti) {
        if (p->getId() >= nextIdPacient) nextIdPacient = p->getId() + 1;
    }

    for (auto a : angajati) {
        if (a->getId() >= nextIdAngajat) nextIdAngajat = a->getId() + 1;
        if (auto m = dynamic_cast<Medic*>(a)) medici.push_back(m);
        else if (auto as = dynamic_cast<Asistent*>(a)) asistenti.push_back(as);
    }

    Consola::printInfo("Pacienti incarcati: " + to_string(pacienti.size()));
    Consola::printInfo("Medici incarcati: " + to_string(medici.size()));
    Consola::printInfo("Asistenti incarcati: " + to_string(asistenti.size()));
}

// ========== STATISTICI ==========
void statistici() {
    Consola::clearScreen();
    Consola::printTitle("STATISTICI SPITAL");
    Consola::printSeparator();
    cout << "   Pacienti       : " << pacienti.size() << endl;
    cout << "   Medici        : " << medici.size() << endl;
    cout << "   Asistenti     : " << asistenti.size() << endl;
    cout << "   Programari     : " << programari.size() << endl;
    cout << "   Facturi        : " << Factura::getContor() << endl;
    double total = 0;
    for (auto f : facturi) total += f->getTotal();
    cout << "  💵 Total facturat : " << total << " lei" << endl;
    Consola::printSeparator();
}


// ========== AUTENTIFICARE / ROLURI ==========
enum class RolUtilizator {
    NEAUTENTIFICAT,
    ADMINISTRATOR,
    MEDIC,
    PACIENT
};

struct SesiuneUtilizator {
    RolUtilizator rol = RolUtilizator::NEAUTENTIFICAT;
    int id = 0;
    string numeAfisat = "";
};

Pacient* gasestePacientDupaId(int id) {
    for (auto p : pacienti) {
        if (p->getId() == id) return p;
    }
    return nullptr;
}

Medic* gasesteMedicDupaId(int id) {
    for (auto m : medici) {
        if (m->getId() == id) return m;
    }
    return nullptr;
}

void schimbaParolaMedic() {
    Consola::printTitle("SCHIMBA PAROLA MEDIC");
    if (medici.empty()) {
        Consola::printWarning("Nu exista medici inregistrati.");
        return;
    }

    int id = Consola::citesteNumar("ID medic");
    Medic* medic = gasesteMedicDupaId(id);
    if (!medic) {
        Consola::printError("Medicul cu ID-ul introdus nu exista.");
        return;
    }

    string parolaNoua = Consola::citesteText("Parola noua");
    medic->setParola(parolaNoua);
    Consola::printSuccess("Parola medicului a fost actualizata.");
}

void afiseazaProgramariPacient(int idPacient) {
    Consola::printTitle("PROGRAMARILE MELE");
    bool gasit = false;
    for (auto prog : programari) {
        if (prog->getIdPacient() == idPacient) {
            cout << "  ";
            prog->afisare();
            gasit = true;
        }
    }
    if (!gasit) Consola::printInfo("Nu exista programari pentru acest pacient.");
}

void afiseazaProgramariMedic(int idMedic) {
    Consola::printTitle("PROGRAMARI MEDIC");
    bool gasit = false;
    for (auto prog : programari) {
        if (prog->getIdMedic() == idMedic) {
            cout << "  ";
            prog->afisare();
            gasit = true;
        }
    }
    if (!gasit) Consola::printInfo("Nu exista programari pentru acest medic.");
}

void afiseazaFacturiPacient(int idPacient) {
    Consola::printTitle("FACTURILE MELE");
    bool gasit = false;
    for (auto f : facturi) {
        if (f->getIdPacient() == idPacient) {
            f->afisare();
            gasit = true;
        }
    }
    if (!gasit) Consola::printInfo("Nu exista facturi pentru acest pacient.");
}

void adaugaProgramarePentruPacient(int idPacient) {
    Consola::printTitle("CERERE PROGRAMARE PACIENT");
    if (medici.empty()) {
        Consola::printWarning("Nu exista medici in sistem. Contactati administratorul.");
        return;
    }

    Consola::printInfo("Medici disponibili:");
    for (auto m : medici) {
        cout << "  ID " << m->getId() << " - ";
        m->afisare();
    }

    int idMedic = Consola::citesteNumar("ID Medic");
    if (!gasesteMedicDupaId(idMedic)) {
        Consola::printError("Medicul ales nu exista.");
        return;
    }

    string data = Consola::citesteText("Data (YYYY-MM-DD)");
    string ora = Consola::citesteText("Ora (HH:MM)");
    string motiv = Consola::citesteText("Motiv");

    try {
        Programare* prog = new Programare(nextIdProgramare++, idPacient, idMedic, data, ora, motiv);
        prog->valideaza();
        programari.push_back(prog);
        Consola::printSuccess("Programarea a fost inregistrata cu ID: " + to_string(prog->getId()));
    } catch (ProgramareInvalidaException& e) {
        Consola::printError(e.what());
    }
}

SesiuneUtilizator autentificare() {
    while (true) {
        int opt = Consola::meniuInteractv("AUTENTIFICARE", {
            {1, "Login administrator"},
            {2, "Login medic"},
            {3, "Login pacient"},
            {0, "Iesire"}
        });

        if (opt == 0) {
            return {};
        }

        if (opt == 1) {
            string user = Consola::citesteText("Utilizator");
            string parola = Consola::citesteText("Parola");

            if (user == "admin" && parola == "admin") {
                Logger::getInstanta()->log("Login administrator");
                return {RolUtilizator::ADMINISTRATOR, 0, "Administrator"};
            }

            Consola::printError("Date de autentificare gresite. User: admin | Parola: admin");
            Consola::pauza();
        }

        if (opt == 2) {
            if (medici.empty()) {
                Consola::printWarning("Nu exista medici salvati in sistem. Intra ca administrator si adauga un medic.");
                Consola::pauza();
                continue;
            }

            int id = Consola::citesteNumar("ID medic");
            string parola = Consola::citesteText("Parola medic");

            Medic* medic = gasesteMedicDupaId(id);
            if (medic && medic->getParola() == parola) {
                Logger::getInstanta()->log("Login medic ID " + to_string(id));
                return {RolUtilizator::MEDIC, id, medic->getNume()};
            }

            Consola::printError("ID sau parola gresita pentru medic.");
            Consola::pauza();
        }

        if (opt == 3) {
            if (pacienti.empty()) {
                Consola::printWarning("Nu exista pacienti salvati in sistem.");
                Consola::pauza();
                continue;
            }

            int id = Consola::citesteNumar("ID pacient");
            string cnp = Consola::citesteText("CNP pacient");

            Pacient* pacient = gasestePacientDupaId(id);
            if (pacient && pacient->getCnp() == cnp) {
                Logger::getInstanta()->log("Login pacient ID " + to_string(id));
                return {RolUtilizator::PACIENT, id, pacient->getNume()};
            }

            Consola::printError("ID sau CNP gresit pentru pacient.");
            Consola::pauza();
        }
    }
}

void ruleazaAdministrator() {
    int opt;
    do {
        opt = Consola::meniuInteractv("ADMINISTRATOR - SISTEM GESTIUNE SPITAL", {
            {1, "Gestiune pacienti"},
            {2, "Gestiune personal medical"},
            {3, "Programari"},
            {4, "Facturi"},
            {5, "Salvare / incarcare date"},
            {6, "Statistici"},
            {0, "Logout"}
        });

        Consola::printStatusBar((int)pacienti.size(), (int)medici.size(), (int)asistenti.size(),
                                (int)programari.size(), (int)facturi.size());

        switch (opt) {
            case 1: gestiunePacienti(); break;
            case 2: gestiunePersonal(); break;
            case 3: gestiuneProgramari(); break;
            case 4: gestiuneFacturi(); break;
            case 5: {
                int sopt = Consola::meniuInteractv("SALVARE / INCARCARE", {
                    {1, "Salvare date"},
                    {2, "Incarcare date"},
                    {0, "Inapoi"}
                });
                if (sopt == 1) salvareDate();
                else if (sopt == 2) incarcareDate();
                break;
            }
            case 6: statistici(); break;
        }

        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

void ruleazaMedic(int idMedic) {
    Medic* medic = gasesteMedicDupaId(idMedic);
    string titlu = medic ? ("MEDIC - " + medic->getNume()) : "MEDIC";

    int opt;
    do {
        opt = Consola::meniuInteractv(titlu, {
            {1, "Vezi datele mele"},
            {2, "Vezi lista pacientilor"},
            {3, "Vezi programarile mele"},
            {4, "Confirma programare"},
            {5, "Anuleaza programare"},
            {6, "Statistici"},
            {0, "Logout"}
        });

        switch (opt) {
            case 1:
                if (medic) medic->afisareDetaliata();
                else Consola::printError("Medicul nu mai exista in sistem.");
                break;
            case 2:
                veziPacienti();
                break;
            case 3:
                afiseazaProgramariMedic(idMedic);
                break;
            case 4: {
                int id = Consola::citesteNumar("ID Programare");
                bool gasit = false;
                for (auto prog : programari) {
                    if (prog->getId() == id && prog->getIdMedic() == idMedic) {
                        prog->confirma();
                        Consola::printSuccess("Programare confirmata.");
                        gasit = true;
                        break;
                    }
                }
                if (!gasit) Consola::printError("Programarea nu exista sau nu apartine acestui medic.");
                break;
            }
            case 5: {
                int id = Consola::citesteNumar("ID Programare");
                string motiv = Consola::citesteText("Motiv anulare");
                bool gasit = false;
                for (auto prog : programari) {
                    if (prog->getId() == id && prog->getIdMedic() == idMedic) {
                        prog->anuleaza(motiv);
                        Consola::printSuccess("Programare anulata.");
                        gasit = true;
                        break;
                    }
                }
                if (!gasit) Consola::printError("Programarea nu exista sau nu apartine acestui medic.");
                break;
            }
            case 6:
                statistici();
                break;
        }

        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}

void ruleazaPacient(int idPacient) {
    Pacient* pacient = gasestePacientDupaId(idPacient);
    string titlu = pacient ? ("PACIENT - " + pacient->getNume()) : "PACIENT";

    int opt;
    do {
        opt = Consola::meniuInteractv(titlu, {
            {1, "Vezi datele mele"},
            {2, "Vezi programarile mele"},
            {3, "Creeaza programare"},
            {4, "Vezi facturile mele"},
            {0, "Logout"}
        });

        switch (opt) {
            case 1:
                pacient = gasestePacientDupaId(idPacient);
                if (pacient) pacient->afisareCompleta();
                else Consola::printError("Pacientul nu mai exista in sistem.");
                break;
            case 2:
                afiseazaProgramariPacient(idPacient);
                break;
            case 3:
                adaugaProgramarePentruPacient(idPacient);
                break;
            case 4:
                afiseazaFacturiPacient(idPacient);
                break;
        }

        if (opt != 0) Consola::pauza();
    } while (opt != 0);
}


// ========== MAIN ==========
int main() {
    Logger::getInstanta()->log("Aplicatia a pornit");

    // Incarcare automata la pornire, daca exista fisierele salvate anterior.
    if (std::filesystem::exists("date/pacienti.json") || std::filesystem::exists("date/angajati.json")) {
        pacienti = FileManager::incarcaPacienti("date/pacienti.json");
        angajati = FileManager::incarcaAngajati("date/angajati.json");
        for (auto p : pacienti) {
            if (p->getId() >= nextIdPacient) nextIdPacient = p->getId() + 1;
        }
        for (auto a : angajati) {
            if (a->getId() >= nextIdAngajat) nextIdAngajat = a->getId() + 1;
            if (auto m = dynamic_cast<Medic*>(a)) medici.push_back(m);
            else if (auto as = dynamic_cast<Asistent*>(a)) asistenti.push_back(as);
        }
    }

    while (true) {
        SesiuneUtilizator sesiune = autentificare();

        if (sesiune.rol == RolUtilizator::NEAUTENTIFICAT) {
            break;
        }

        Consola::printSuccess("Autentificare reusita: " + sesiune.numeAfisat);
        Consola::pauza();

        if (sesiune.rol == RolUtilizator::ADMINISTRATOR) {
            ruleazaAdministrator();
        } else if (sesiune.rol == RolUtilizator::MEDIC) {
            ruleazaMedic(sesiune.id);
        } else if (sesiune.rol == RolUtilizator::PACIENT) {
            ruleazaPacient(sesiune.id);
        }

        salvareDate();
    }

    salvareDate();
    curatareDate();
    Logger::getInstanta()->inchide();
    return 0;
}
