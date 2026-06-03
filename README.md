# Hospital Management System

Aplicație de gestiune a activităților unui spital, dezvoltată în C++17 în cadrul disciplinei Programare Orientată pe Obiecte. Sistemul permite administrarea pacienților, personalului medical, programărilor și facturilor, oferind în același timp persistența datelor și mecanisme de validare pentru operațiile importante.

---

# Cuprins

* Prezentare generală
* Funcționalități implementate
* Tehnologii utilizate
* Organizarea proiectului
* Structura aplicației
* Compilare și rulare
* Utilizare
* Persistența datelor
* Concepte OOP utilizate
* Funcționalități suplimentare
* Testare
* Autor

---

# Prezentare generală

Hospital Management System este o aplicație de consolă destinată gestionării informațiilor din cadrul unui spital.

Sistemul permite:

* administrarea pacienților;
* administrarea medicilor și asistenților;
* gestionarea programărilor medicale;
* emiterea și calcularea facturilor;
* salvarea și încărcarea informațiilor între sesiuni;
* monitorizarea operațiilor importante prin mecanisme de logging.

Proiectul urmărește aplicarea principiilor Programării Orientate pe Obiecte într-un scenariu apropiat de un sistem real de evidență medicală.

---

# Funcționalități implementate

## Gestionare pacienți

* Adăugare pacient nou
* Vizualizare pacienți existenți
* Actualizare informații
* Asocierea diagnosticului

## Gestionare personal medical

* Administrare medici
* Administrare asistenți medicali
* Evidență specializări și funcții

## Programări

* Crearea unei programări
* Verificarea datelor introduse
* Tratarea programărilor invalide prin excepții personalizate
* Vizualizarea programărilor existente

## Facturare

* Generarea facturilor pentru servicii medicale
* Calculul costului folosind polimorfism
* Emiterea și evidența facturilor

## Monitorizare și jurnalizare

* Înregistrarea internărilor
* Înregistrarea emiterii facturilor
* Salvarea operațiilor importante în fișiere de log

## Salvare date

* Persistență JSON
* Încărcarea datelor la pornirea aplicației
* Salvarea modificărilor efectuate de utilizator

---

# Tehnologii utilizate

* C++17
* STL (vector, string, map, unordered_map, smart pointers)
* Programare Orientată pe Obiecte
* JSON pentru persistența datelor
* Makefile pentru compilare
* ANSI Escape Codes pentru interfața în consolă

---

# Organizarea proiectului

```text
SPITAL_CPP/
│
├── src/                 # Fișiere sursă
├── include/             # Fișiere header
├── tests/               # Teste unitare
├── docs/                # Documentație
│
├── Makefile
├── README.md
│
└── date/
    ├── pacienti.json
    ├── medici.json
    ├── programari.json
    └── facturi.json
```

---

# Structura aplicației

## Pacient

Clasa responsabilă pentru gestionarea informațiilor despre pacienți:

* nume;
* vârstă;
* diagnostic;
* istoric medical.

## Angajat

Clasă de bază pentru personalul medical.

Conține informații comune:

* nume;
* identificator;
* salariu.

### Medic

Derivă din clasa Angajat.

Gestionează:

* specializarea;
* consultațiile;
* serviciile medicale oferite.

### Asistent

Derivă din clasa Angajat.

Gestionează:

* atribuțiile specifice;
* suportul acordat pacienților.

## Programare

Reprezintă o consultație programată între pacient și medic.

Include:

* data programării;
* ora;
* medicul responsabil;
* pacientul asociat.

## Factura

Gestionează costurile serviciilor medicale și emiterea documentelor de plată.

---

# Compilare și rulare

## Cerințe

* g++ cu suport pentru C++17
* make

## Compilare

```bash
make
```

## Rulare

Linux:

```bash
./spital
```

Windows:

```bash
spital.exe
```

## Rulare teste

```bash
make test
```

---

# Utilizare

La pornire este afișat meniul principal al aplicației.

Opțiunile disponibile permit:

| Opțiune | Descriere                   |
| ------- | --------------------------- |
| 1       | Gestionare pacienți         |
| 2       | Gestionare personal medical |
| 3       | Gestionare programări       |
| 4       | Gestionare facturi          |
| 5       | Salvare date                |
| 6       | Statistici                  |
| 0       | Ieșire                      |

Utilizatorul poate naviga prin meniuri și efectua operațiile necesare direct din consolă.

---

# Persistența datelor

Datele aplicației sunt salvate în fișiere JSON.

Avantajele acestei abordări:

* datele rămân disponibile între sesiuni;
* format ușor de extins;
* fișiere ușor de inspectat și modificat.

La pornirea aplicației, informațiile salvate anterior sunt încărcate automat.

---

# Concepte OOP utilizate

## Încapsulare

Datele interne ale claselor sunt protejate și accesate prin metode publice.

## Moștenire

```text
Angajat
├── Medic
└── Asistent
```

## Polimorfism

Calculul costurilor serviciilor medicale este realizat prin metode virtuale redefinite.

## Abstracție

Fiecare clasă expune doar operațiile relevante utilizatorului.

## Gestionarea resurselor

Utilizarea structurilor STL și a mecanismelor moderne C++ pentru administrarea datelor.

---

# Funcționalități suplimentare

Pe lângă cerințele obligatorii au fost implementate:

* Persistență JSON
* Pattern Factory pentru generarea facturilor
* Logging pentru operațiile critice
* Interfață de consolă îmbunătățită
* Validarea datelor introduse de utilizator

---

# Testare

Proiectul include teste pentru:

* validarea programărilor;
* calculul facturilor;
* verificarea funcționalităților esențiale ale sistemului.

Testele pot fi rulate independent prin:

```bash
make test
```

---

# Autor

**Dany Gutan**

Proiect realizat pentru disciplina **Programare Orientată pe Obiecte**, având ca scop aplicarea conceptelor OOP într-un sistem de gestiune medicală.
