# 🏥 Sistem de Management al unui Spital - C++

Aplicație de consolă pentru gestionarea pacienților, medicilor, asistenților, programărilor și facturilor într-un spital.

## Funcționalități

- Gestionare pacienți: adăugare, afișare, căutare, internare, externare
- Gestionare personal medical: medici și asistenți
- Gestionare programări: creare, confirmare, anulare
- Gestionare facturi: emitere, afișare, plată
- Calcul polimorfic pentru servicii medicale
- Logging pentru operațiuni critice
- Salvare date în format JSON
- Teste unitare simple pentru programări și facturi
- Interfață în consolă cu meniuri stilizate

## Structură proiect

```text
spital_cpp/
├── include/        # headere C++
├── src/            # implementări C++
├── tests/          # teste unitare
├── docs/           # documentație
├── Makefile        # build automat
└── README.md
```

## Compilare și rulare

```bash
make
./spital
```

Sau manual:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o spital
./spital
```

## Rulare teste

```bash
make test
```

## Cerințe acoperite

- Clase obligatorii: `Pacient`, `Medic`, `Programare`, `Factura`
- Moștenire: `Angajat -> Medic`, `Angajat -> Asistent`
- Polimorfism: `ServiciuMedical` + clase derivate
- Excepții personalizate: `ProgramareInvalidaException`
- Logging: internări și facturi
- Teste unitare: programări și calcul factură
- Persistență JSON
- Pattern Factory pentru facturi

## Autor

Dany Gutan
