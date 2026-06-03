# Documentație proiect - Sistem gestiune spital

Proiectul gestionează pacienți, personal medical, programări și facturi. Aplicația folosește programare orientată pe obiecte, moștenire, polimorfism, excepții personalizate, logging și persistență JSON.

## Clase principale
- `Pacient`
- `Angajat`, cu derivatele `Medic` și `Asistent`
- `Programare`
- `Factura`
- `ServiciuMedical`, cu derivate pentru consultații, analize, intervenții și spitalizare

## Funcționalități
- adăugare și afișare pacienți;
- internare și externare pacient;
- adăugare personal medical;
- creare, confirmare și anulare programări;
- emitere și plată facturi;
- salvare date în format JSON;
- logging pentru operațiuni importante.
