#ifndef FAJLKEZELES_H_INCLUDED
#define FAJLKEZELES_H_INCLUDED

//dicsoseglistahoz tartozo struktura
typedef struct Dicso {
    char nev[10+1];
    int helyeskerdesek;
    int nyertpenz;
    int jatekido;
} Dicso;

void statisztika(int penz, double ido);

void kiiras_statisztika();

void dicsoseglista(Dicso jatekos);

void kiiras_dicsoseglista();

#endif // FAJLKEZELES_H_INCLUDED
