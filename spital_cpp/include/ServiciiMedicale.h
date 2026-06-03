#pragma once
#include <string>
using namespace std;

// Clasă abstractă de bază
class ServiciuMedical {
public:
    virtual double calculeazaCost() const = 0;
    virtual string getDescriere() const = 0;
    virtual ~ServiciuMedical() {}
};

// Consultație
class Consultatie : public ServiciuMedical {
private:
    string specialitate;
    double tarifBaza;

public:
    Consultatie(const string& specialitate = "Generala", double tarifBaza = 200);
    double calculeazaCost() const override;
    string getDescriere() const override;
    double getTarifBaza() const;
};

// Analize
class Analize : public ServiciuMedical {
private:
    string tip;
    double pretLaborator;

public:
    Analize(const string& tip = "Sange", double pretLaborator = 100);
    double calculeazaCost() const override;
    string getDescriere() const override;
    double getPretLaborator() const;
};

// Intervenție chirurgicală
class Interventie : public ServiciuMedical {
private:
    string complexitate;
    double costAnestezie;
    double costMateriale;
    double tarifBaza;

public:
    Interventie(const string& complexitate = "minora", 
                double costAnestezie = 300, 
                double costMateriale = 200,
                double tarifBaza = 1000);
    double calculeazaCost() const override;
    string getDescriere() const override;
};

// Spitalizare
class Spitalizare : public ServiciuMedical {
private:
    int nrZile;
    double tarifPeZi;

public:
    Spitalizare(int nrZile, double tarifPeZi = 300);
    double calculeazaCost() const override;
    string getDescriere() const override;
    int getNrZile() const;
};