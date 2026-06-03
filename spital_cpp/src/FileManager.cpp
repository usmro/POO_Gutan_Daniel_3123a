#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <filesystem>
using namespace std;

static string jsonString(const string& block, const string& key, const string& def = "") {
    regex r("\\\"" + key + "\\\"\\s*:\\s*\\\"([^\\\"]*)\\\"");
    smatch m;
    if (regex_search(block, m, r)) return m[1].str();
    return def;
}

static int jsonInt(const string& block, const string& key, int def = 0) {
    regex r("\\\"" + key + "\\\"\\s*:\\s*(-?[0-9]+)");
    smatch m;
    if (regex_search(block, m, r)) return stoi(m[1].str());
    return def;
}

static double jsonDouble(const string& block, const string& key, double def = 0.0) {
    regex r("\\\"" + key + "\\\"\\s*:\\s*(-?[0-9]+(?:\\.[0-9]+)?)");
    smatch m;
    if (regex_search(block, m, r)) return stod(m[1].str());
    return def;
}

static bool jsonBool(const string& block, const string& key, bool def = false) {
    regex r("\\\"" + key + "\\\"\\s*:\\s*(true|false)");
    smatch m;
    if (regex_search(block, m, r)) return m[1].str() == "true";
    return def;
}

static vector<string> objectBlocks(const string& text) {
    vector<string> blocks;
    int depth = 0;
    size_t start = string::npos;
    bool inString = false;
    bool escaped = false;

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        if (inString) {
            if (escaped) escaped = false;
            else if (c == '\\') escaped = true;
            else if (c == '"') inString = false;
            continue;
        }
        if (c == '"') { inString = true; continue; }
        if (c == '{') {
            if (depth == 1) start = i;
            depth++;
        } else if (c == '}') {
            depth--;
            if (depth == 1 && start != string::npos) {
                blocks.push_back(text.substr(start, i - start + 1));
                start = string::npos;
            }
        }
    }
    return blocks;
}

static pair<string,string> splitFullName(const string& full) {
    size_t pos = full.find(' ');
    if (pos == string::npos) return {full, ""};
    return {full.substr(0, pos), full.substr(pos + 1)};
}

string FileManager::escapeJson(const string& text) {
    string rezultat;
    for (char c : text) {
        if (c == '"') rezultat += "\\\"";
        else if (c == '\\') rezultat += "\\\\";
        else rezultat += c;
    }
    return rezultat;
}

void FileManager::salveazaPacienti(const vector<Pacient*>& pacienti, const string& fisier) {
    filesystem::create_directories(filesystem::path(fisier).parent_path());
    ofstream f(fisier);
    if (!f.is_open()) { cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl; return; }

    f << "{\n  \"pacienti\": [\n";
    for (size_t i = 0; i < pacienti.size(); i++) {
        Pacient* p = pacienti[i];
        f << "    {\n";
        f << "      \"id\": " << p->getId() << ",\n";
        f << "      \"numeFamilie\": \"" << escapeJson(p->getNumeFamilie()) << "\",\n";
        f << "      \"prenume\": \"" << escapeJson(p->getPrenume()) << "\",\n";
        f << "      \"nume\": \"" << escapeJson(p->getNume()) << "\",\n";
        f << "      \"cnp\": \"" << escapeJson(p->getCnp()) << "\",\n";
        f << "      \"dataNasterii\": \"" << escapeJson(p->getDataNasterii()) << "\",\n";
        f << "      \"telefon\": \"" << escapeJson(p->getTelefon()) << "\",\n";
        f << "      \"diagnostic\": \"" << escapeJson(p->getDiagnostic()) << "\",\n";
        f << "      \"internat\": " << (p->isInternat() ? "true" : "false") << ",\n";
        f << "      \"sectie\": \"" << escapeJson(p->getSectie()) << "\",\n";
        f << "      \"numarSalon\": " << p->getNumarSalon() << ",\n";
        f << "      \"dataInternarii\": \"" << escapeJson(p->getDataInternarii()) << "\"\n";
        f << "    }" << (i < pacienti.size() - 1 ? "," : "") << "\n";
    }
    f << "  ]\n}\n";
    cout << "[SALVARE] " << pacienti.size() << " pacienti salvati in " << fisier << endl;
}

void FileManager::salveazaAngajati(const vector<Angajat*>& angajati, const string& fisier) {
    filesystem::create_directories(filesystem::path(fisier).parent_path());
    ofstream f(fisier);
    if (!f.is_open()) { cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl; return; }

    f << "{\n  \"angajati\": [\n";
    for (size_t i = 0; i < angajati.size(); i++) {
        Angajat* a = angajati[i];
        Medic* m = dynamic_cast<Medic*>(a);
        Asistent* as = dynamic_cast<Asistent*>(a);
        string tip = m ? "Medic" : (as ? "Asistent" : "Angajat");

        f << "    {\n";
        f << "      \"tip\": \"" << tip << "\",\n";
        f << "      \"id\": " << a->getId() << ",\n";
        f << "      \"numeFamilie\": \"" << escapeJson(a->getNumeFamilie()) << "\",\n";
        f << "      \"prenume\": \"" << escapeJson(a->getPrenume()) << "\",\n";
        f << "      \"cnp\": \"" << escapeJson(a->getCnp()) << "\",\n";
        f << "      \"dataNasterii\": \"" << escapeJson(a->getDataNasterii()) << "\",\n";
        f << "      \"telefon\": \"" << escapeJson(a->getTelefon()) << "\",\n";
        f << "      \"email\": \"" << escapeJson(a->getEmail()) << "\",\n";
        f << "      \"adresa\": \"" << escapeJson(a->getAdresa()) << "\",\n";
        f << "      \"dataAngajarii\": \"" << escapeJson(a->getDataAngajarii()) << "\",\n";
        f << "      \"salariu\": " << a->getSalariu() << ",\n";
        f << "      \"iban\": \"" << escapeJson(a->getIban()) << "\",\n";
        f << "      \"functie\": \"" << escapeJson(a->getFunctie()) << "\",\n";
        f << "      \"tipContract\": \"" << escapeJson(a->getTipContract()) << "\",\n";
        f << "      \"sectie\": \"" << escapeJson(a->getSectie()) << "\",\n";
        if (m) {
            f << "      \"specializare\": \"" << escapeJson(m->getSpecializare()) << "\",\n";
            f << "      \"numarParafa\": \"" << escapeJson(m->getNumarParafa()) << "\",\n";
            f << "      \"tarifConsultatie\": " << m->getTarifConsultatie() << ",\n";
            f << "      \"parola\": \"" << escapeJson(m->getParola()) << "\"\n";
        } else if (as) {
            f << "      \"gradProfesional\": \"" << escapeJson(as->getGradProfesional()) << "\",\n";
            f << "      \"tipAsistent\": \"" << escapeJson(as->getTipAsistent()) << "\"\n";
        } else {
            f << "      \"detalii\": \"\"\n";
        }
        f << "    }" << (i < angajati.size() - 1 ? "," : "") << "\n";
    }
    f << "  ]\n}\n";
    cout << "[SALVARE] " << angajati.size() << " angajati salvati in " << fisier << endl;
}

void FileManager::salveazaProgramari(const vector<Programare*>& programari, const string& fisier) {
    filesystem::create_directories(filesystem::path(fisier).parent_path());
    ofstream f(fisier);
    if (!f.is_open()) { cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl; return; }
    f << "{\n  \"programari\": [\n";
    for (size_t i = 0; i < programari.size(); i++) {
        Programare* prog = programari[i];
        f << "    {\n";
        f << "      \"id\": " << prog->getId() << ",\n";
        f << "      \"idPacient\": " << prog->getIdPacient() << ",\n";
        f << "      \"idMedic\": " << prog->getIdMedic() << ",\n";
        f << "      \"data\": \"" << escapeJson(prog->getData()) << "\",\n";
        f << "      \"ora\": \"" << escapeJson(prog->getOra()) << "\",\n";
        f << "      \"motiv\": \"" << escapeJson(prog->getMotiv()) << "\",\n";
        f << "      \"status\": \"" << escapeJson(prog->getStatus()) << "\"\n";
        f << "    }" << (i < programari.size() - 1 ? "," : "") << "\n";
    }
    f << "  ]\n}\n";
    cout << "[SALVARE] " << programari.size() << " programari salvate in " << fisier << endl;
}

void FileManager::salveazaFacturi(const vector<Factura*>& facturi, const string& fisier) {
    filesystem::create_directories(filesystem::path(fisier).parent_path());
    ofstream f(fisier);
    if (!f.is_open()) { cout << "Eroare: Nu s-a putut deschide fisierul " << fisier << endl; return; }
    f << "{\n  \"facturi\": [\n";
    for (size_t i = 0; i < facturi.size(); i++) {
        Factura* fact = facturi[i];
        f << "    {\n";
        f << "      \"id\": " << fact->getId() << ",\n";
        f << "      \"idPacient\": " << fact->getIdPacient() << ",\n";
        f << "      \"total\": " << fact->getTotal() << ",\n";
        f << "      \"platita\": " << (fact->isPlatita() ? "true" : "false") << "\n";
        f << "    }" << (i < facturi.size() - 1 ? "," : "") << "\n";
    }
    f << "  ]\n}\n";
    cout << "[SALVARE] " << facturi.size() << " facturi salvate in " << fisier << endl;
}

vector<Pacient*> FileManager::incarcaPacienti(const string& fisier) {
    vector<Pacient*> pacienti;
    ifstream f(fisier);
    if (!f.is_open()) { cout << "Info: Nu exista inca " << fisier << endl; return pacienti; }
    string text((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    for (const string& b : objectBlocks(text)) {
        int id = jsonInt(b, "id");
        string nume = jsonString(b, "numeFamilie");
        string prenume = jsonString(b, "prenume");
        if (nume.empty()) {
            auto parts = splitFullName(jsonString(b, "nume"));
            nume = parts.first; prenume = parts.second;
        }
        Pacient* p = new Pacient(id, nume, prenume, jsonString(b, "cnp"),
                                 jsonString(b, "dataNasterii", "2000-01-01"),
                                 jsonString(b, "telefon"));
        string diagnostic = jsonString(b, "diagnostic");
        if (!diagnostic.empty()) p->setDiagnostic(diagnostic);
        if (jsonBool(b, "internat")) {
            p->interneaza(jsonString(b, "sectie", "Necunoscuta"), jsonInt(b, "numarSalon", 0), jsonString(b, "dataInternarii", ""));
        }
        pacienti.push_back(p);
    }
    cout << "[INCARCARE] " << pacienti.size() << " pacienti incarcati din " << fisier << endl;
    return pacienti;
}

vector<Angajat*> FileManager::incarcaAngajati(const string& fisier) {
    vector<Angajat*> angajati;
    ifstream f(fisier);
    if (!f.is_open()) { cout << "Info: Nu exista inca " << fisier << endl; return angajati; }
    string text((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    for (const string& b : objectBlocks(text)) {
        string tip = jsonString(b, "tip");
        int id = jsonInt(b, "id");
        string nume = jsonString(b, "numeFamilie");
        string prenume = jsonString(b, "prenume");
        if (nume.empty()) {
            auto parts = splitFullName(jsonString(b, "nume"));
            nume = parts.first; prenume = parts.second;
        }
        if (tip == "Medic") {
            auto* m = new Medic(id, nume, prenume, jsonString(b, "cnp", "0000000000000"),
                                jsonString(b, "dataNasterii", "1980-01-01"), jsonString(b, "telefon", "0700000000"),
                                jsonString(b, "email", nume + "@spital.ro"), jsonString(b, "adresa", "Str. Spitalului"),
                                jsonString(b, "dataAngajarii", "2020-01-01"), jsonDouble(b, "salariu", 8000),
                                jsonString(b, "iban", "RO00"), jsonString(b, "functie", "Medic"),
                                jsonString(b, "tipContract", "Norma intreaga"), jsonString(b, "sectie"),
                                jsonString(b, "specializare"), jsonString(b, "numarParafa"), "Dr.",
                                "Luni-Vineri 8-14", "", jsonDouble(b, "tarifConsultatie", 200), false,
                                jsonString(b, "parola", "medic123"));
            angajati.push_back(m);
        } else if (tip == "Asistent") {
            auto* a = new Asistent(id, nume, prenume, jsonString(b, "cnp", "0000000000000"),
                                   jsonString(b, "dataNasterii", "1990-01-01"), jsonString(b, "telefon", "0700000000"),
                                   jsonString(b, "email", nume + "@spital.ro"), jsonString(b, "adresa", "Str. Spitalului"),
                                   jsonString(b, "dataAngajarii", "2022-01-01"), jsonDouble(b, "salariu", 4000),
                                   jsonString(b, "iban", "RO00"), jsonString(b, "functie", "Asistent"),
                                   jsonString(b, "tipContract", "Norma intreaga"), jsonString(b, "sectie"),
                                   jsonString(b, "gradProfesional", "Medical"), jsonString(b, "tipAsistent", "Generalist"));
            angajati.push_back(a);
        }
    }
    cout << "[INCARCARE] " << angajati.size() << " angajati incarcati din " << fisier << endl;
    return angajati;
}
