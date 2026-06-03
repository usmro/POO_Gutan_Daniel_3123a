#  Sistem de Management al unui Spital - C++

Aplicatie de consola pentru gestionarea pacientilor, medicilor, asistentilor, programarilor si facturilor intr-un spital.

## Functionalitati

- Gestionare pacienti: adaugare, afisare, cautare, internare, externare
- Gestionare personal medical: medici si asistenti
- Gestionare programari: creare, confirmare, anulare
- Gestionare facturi: emitere, afisare, plata
- Calcul polimorfic pentru servicii medicale
- Logging pentru operatiuni critice
- Salvare date in format JSON
- Teste unitare simple pentru programari si facturi
- Interfata in consola cu meniuri stilizate

## Structura proiect

```text
spital_cpp/
+-- include/        # headere C++
+-- src/            # implementari C++
+-- tests/          # teste unitare
+-- docs/           # documentatie
+-- Makefile        # build automat
+-- README.md
```

## Compilare si rulare

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

## Cerinte acoperite

- Clase obligatorii: `Pacient`, `Medic`, `Programare`, `Factura`
- Mostenire: `Angajat -> Medic`, `Angajat -> Asistent`
- Polimorfism: `ServiciuMedical` + clase derivate
- Exceptii personalizate: `ProgramareInvalidaException`
- Logging: internari si facturi
- Teste unitare: programari si calcul factura
- Persistenta JSON
- Pattern Factory pentru facturi

## Autor

Dany Gutan
