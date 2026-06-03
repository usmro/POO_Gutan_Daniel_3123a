# Documentatie proiect - Sistem gestiune spital

Proiectul gestioneaza pacienti, personal medical, programari si facturi. Aplicatia foloseste programare orientata pe obiecte, mostenire, polimorfism, exceptii personalizate, logging si persistenta JSON.

## Clase principale
- `Pacient`
- `Angajat`, cu derivatele `Medic` si `Asistent`
- `Programare`
- `Factura`
- `ServiciuMedical`, cu derivate pentru consultatii, analize, interventii si spitalizare

## Functionalitati
- adaugare si afisare pacienti;
- internare si externare pacient;
- adaugare personal medical;
- creare, confirmare si anulare programari;
- emitere si plata facturi;
- salvare date in format JSON;
- logging pentru operatiuni importante.
