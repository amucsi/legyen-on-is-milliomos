#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"
#include "fajlkezeles.h"

void statisztika(int penz, double ido) { //statisztika fajlt kezelo függveny
    FILE *statisztikafajl = fopen("statisztika.txt", "r");
    int jatekokszama = 0, atlagospenz, atlagosido;

    //ha nem letezik a fajl, akkor letrehozza
    if (statisztikafajl == NULL) {
        statisztikafajl = fopen("statisztika.txt", "w");
        jatekokszama = 1;
        atlagospenz = penz;
        atlagosido = ido;
    }

    else { //ha letezik beolvassa az eddigi adatokat
        char sor[100];
        fgets(sor, 100, statisztikafajl);
        sscanf(sor,"%*s %*s %d", &jatekokszama);
        fgets(sor, 100, statisztikafajl);
        sscanf(sor, "%*s %*s %d", &atlagospenz);
        fgets(sor, 100, statisztikafajl);
        sscanf(sor, "%*s %*s %d", &atlagosido);

        jatekokszama++;
        atlagospenz = (atlagospenz*(jatekokszama-1)+penz)/jatekokszama;
        atlagosido = (atlagosido*(jatekokszama-1)+ido)/jatekokszama;

        fclose(statisztikafajl);
        statisztikafajl = fopen("statisztika.txt", "w");
    }

    fprintf(statisztikafajl, "Jatekok szama %d\nAtlagos penz %d\nAtlagos ido %d\n", jatekokszama, atlagospenz, atlagosido);
    fclose(statisztikafajl);
}

void kiiras_statisztika() { //a statisztika megjelenitese
    system("cls");
    FILE *statisztika = fopen("statisztika.txt", "r");
    if (statisztika == NULL)
        printf("Nincs megjelenitheto statisztika!\n\n");
    else {
        int betu;
        while ((betu = getc(statisztika)) != EOF)
            putchar(betu);
        printf("\n");
    }
    fclose(statisztika);
}

void dicsoseglista(Dicso jatekos) { //a dicsoseglista fajlt kezelo fuggveny
    FILE *dicsosegfajl = fopen("dicsoseglista.txt", "r");
    Dicso dicsoseglista[10];

    //ha nem letezik a fajl, akkor letrehozza, a dicsoseglista pedig ures lesz
    if (dicsosegfajl == NULL) {
        dicsosegfajl = fopen("dicsoseglista.txt", "w");
        Dicso nulla = {"", 0, 0, 0};
        for (int i = 0; i < 10; i++)
            dicsoseglista[i] = nulla;
    }
    //beolvassa az eddigi dicsoseglistat fajlbol, utana kiuriti a fajlt
    else {
        char sor[100];
        for(int i = 0; i < 10; i++) {
            fgets(sor, 100, dicsosegfajl);
            sscanf(sor, "%d %s %d %d", &dicsoseglista[i].helyeskerdesek, dicsoseglista[i].nev, &dicsoseglista[i].nyertpenz, &dicsoseglista[i].jatekido);
        }
        fclose(dicsosegfajl);
        dicsosegfajl = fopen("dicsoseglista.txt", "w");
    }

    //helyes kerdesek szama szerint rendezi sorba
    for (int i = 0; i < 10; i++) {
        if (dicsoseglista[i].helyeskerdesek < jatekos.helyeskerdesek) {
            for (int j = 9; j > i; j++) {
                dicsoseglista[i] = dicsoseglista[i-1];
            }
            dicsoseglista[i] = jatekos;
            break;
        }
    }

    for (int i = 0; i < 10; i++) {
        fprintf(dicsosegfajl, "      %2d           %10s       %4d          %3d\n", dicsoseglista[i].helyeskerdesek, dicsoseglista[i].nev, dicsoseglista[i].nyertpenz, dicsoseglista[i].jatekido);
    }
    fprintf(dicsosegfajl, " Helyes kerdesek    Jatekosnev    Nyert penz    Jatekido\n");
    fclose(dicsosegfajl);
}

void kiiras_dicsoseglista() { //dicsoseglista megjelenitese
    system("cls");
    FILE *dicsoseglista = fopen("dicsoseglista.txt", "r");
    if (dicsoseglista == NULL)
        printf("Nincs megjelenitheto dicsoseglista!\n\n");
    else {
        int betu;
        while ((betu = getc(dicsoseglista)) != EOF)
            putchar(betu);
        printf("\n");
    }
    fclose(dicsoseglista);
}
