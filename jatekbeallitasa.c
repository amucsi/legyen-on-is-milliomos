#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#include "debugmalloc.h"
#include "jatekbeallitasa.h"
#include "switchek.h"
#include "kerdesfuggvenyek.h"
#include "fajlkezeles.h"

void kerdestombletrehozas(Kerdes *bemenetkerdestomb, int meret, Kerdes *kimenetkerdestomb, char *kizartkategoria) {
    srand(time(NULL));
    int randomszam = (rand() % (meret-1 - 0 + 1)) + 0;
    int count = 0;
    while (count < 15) {
        bool kesz = false;
        for (int i = 0; i < 15; i++) { //megnezi van-e azonos kerdes
            if (strcmp(kimenetkerdestomb[i].kerdes, bemenetkerdestomb[randomszam].kerdes) == 0) {
                randomszam = (rand() % (meret-1 - 0 + 1)) + 0;
                kesz = true;
                break;
            }
        }
        if (kesz) continue;
        if (strcmp(bemenetkerdestomb[randomszam].kategoria, kizartkategoria) == 0) { //megnezi nincs-e kizarva
            randomszam = (rand() % (meret-1 - 0 + 1)) + 0;
            continue;
        }
        kimenetkerdestomb[count] = bemenetkerdestomb[randomszam];
        count++;
        randomszam = (rand() % (meret-1 - 0 + 1)) + 0;
    }
}

char *kategoriakizaras(Kategoria *kategoriak, int kategoriakszama) {
    printf("Szeretnel kizarni kerdes kategoriat?\n\n(1) Igen\n(2) Nem\n\n> ");
    char kizartkategoria[16];
    do {
        char kategoriavalasz;
        scanf(" %c", &kategoriavalasz);
        switch (kategoriavalasz) {
            case '1':
                printf("Valassz egyet!\n");
                for (int i = 0; i < kategoriakszama; i++) {
                    printf("%s\n", kategoriak[i].kategoria); printf("\n> "); }
                while(scanf("%s", kizartkategoria)) {
                    for (int i = 0; i < kategoriakszama; i++) {
                        if (strcmp(kizartkategoria, kategoriak[i].kategoria) == 0) {
                            printf("Elfogadva!\n\n");
                            return kategoriak[i].kategoria;
                        }
                    }
                    printf("Ismeretlen kategoria!\n\n> ");
                }
            case '2':
                return "xxxxxxxxxxxxxxx";
            default:
                printf("Ismeretlen input!\n\n> ");
                break;
        }
    } while (true);
}

int nehezsegvalasztas(int *nehezsegtombokmerete) {
    int valasztottnehezseg;
    printf("Valassz nehezsegi szintet! (1-15)\n\n> ");
    while(scanf("%d", &valasztottnehezseg)) {
        if ((valasztottnehezseg < 1) || (valasztottnehezseg > 15)) {
            printf("Ismeretlen input!\n\n> ");
            continue;
        }
        if (nehezsegtombokmerete[valasztottnehezseg-1] < 15) {
            printf("Ebbol a nehezsegbol nincs eleg kerdes! Kerlek valassz ujat!\n\n> ");
            continue;
        }
        break;
    }
    return valasztottnehezseg;
}

//gondolkdoasi ido bekerdezeseert felelos fuggveny
int gondolkodasiidofuggveny() {
    printf("Szeretnel gondolkodasi idot beallitani?\n\n(1) Igen\n(2) Nem\n\n> ");
    char valasz;
    int gondolkodasiido;
    do {
        scanf(" %c", &valasz);
        switch(valasz) {
            case '1':
                printf("Add meg masodpercben!\n\n> ");
                scanf("%d", &gondolkodasiido);
                printf("Az altalad beallitott gondolkodasi ido: %d masodperc\n\n", gondolkodasiido);
                return gondolkodasiido*1000;  //masodpercce alakitas
            case '2':
                gondolkodasiido = 3600 * 1000; //default 1 ora
                return gondolkodasiido;
            default:
                printf("Ismeretlen input!\n\n");
                break;
        }
    } while (true);
}

void jatekbeallitasa(Kerdes **nehezsegszerintikerdesek, int *nehezsegtombokmerete, Kategoria *kategoriak, int kategoriakszama) {
    system("cls");
    char jatekosnev[10+1]; //alapertekek
    int penz = 0;
    bool segitsegek[2] = {true, true};

    printf("Mi a neved? (Maximum 10 karakter hosszu lehet)\n\n> ");
    scanf(" %100[0-9a-zA-Z ]", jatekosnev);
    while ((strlen(jatekosnev) > 10) | ((strchr(jatekosnev, ' ')) != NULL)) {
        if (strlen(jatekosnev) > 10)
            printf("Tul hosszu! Roviditsd le!\n\n");
        if (strchr(jatekosnev, ' '))    //ha nem null pointert kap akkor hibauzenet
            printf("Nem lehet benne szokoz! Ird le nelkule!\n\n");
        printf("> ");
        scanf(" %100[0-9a-zA-Z ]", jatekosnev);
    }
    printf("Nev elfogadva: %s\n\n", jatekosnev);

    int valasztottnehezseg = nehezsegvalasztas(nehezsegtombokmerete); //nehezsegi szint bekerdezese

    char *kizartkategoria = kategoriakizaras(kategoriak, kategoriakszama); //kategoria kizarasa

    Kerdes generaltkerdesek[15];
    kerdestombletrehozas(nehezsegszerintikerdesek[valasztottnehezseg-1], nehezsegtombokmerete[valasztottnehezseg-1], generaltkerdesek, kizartkategoria); //friss kerdestomb letrehozasa

    int gondolkodasiido = gondolkodasiidofuggveny(); //gondolkodasi ido bekerdezese

    printf("Kezdodjek a jatek!\n"); //jatek inditasa
    for (int i = 3; i > 0; i--) {
        printf("%d...\n", i);
        Sleep(1);
    }
    system("cls");
    clock_t kezdes = clock(), vegzes; //ido szamolasanak megkezdese
    double ido;
    Dicso jatekos;
    strcpy(jatekos.nev, jatekosnev);

    for (int i = 0; i < 15; i++) { //fo jatekciklus
        printf("%d. Kerdes  (F) Felezes segitseg, (K) Kozonseg segitseg\n", i+1);
        int returnedkerdes = kerdesfuggveny(generaltkerdesek[i], gondolkodasiido, penz, &penz, segitsegek);
        vegzes = clock();
        ido = (double) (vegzes-kezdes) / CLOCKS_PER_SEC;    //a clock orajelekben szamol, ezert el kell osztani a clocks per seccel, hogy masodperc legyen
        jatekos.nyertpenz = penz;
        jatekos.jatekido = ido;
        if(returnedkerdes == 0)  { //helytelen valasz eseten
            jatekos.helyeskerdesek = i;
            statisztika(penz, ido);
            printf("Helytelen valasz! A jateknak vege. Nyeremenyed: 0MFt\n");
            printf("Ennyi kerdest valaszoltal meg: %d. Ennyi ideig jatszottal: %.0f masodperc.\n\n", i, ido);
            rosszvalaszswitch();
            return;
        }
        // if (returnedkerdes == 1) alapertek, megy tovabb a ciklus
        //kulonleges eset, ha kilep a jatekos
        if (returnedkerdes == 2) {
                jatekos.helyeskerdesek = i+1;
                dicsoseglista(jatekos);
                statisztika(penz, ido);
                printf("Elsetaltal ezzel az osszeggel: %dMFt\n", penz);
                printf("Ennyi kerdest valaszoltal meg: %d. Ennyi ideig jatszottal: %.0f masodperc.\n\n", i+1, ido);
                return;
        }

        if (returnedkerdes == 3) {
            jatekos.helyeskerdesek = i;
            statisztika(penz, ido);
            printf("Ennyi kerdest valaszoltal meg: %d. Ennyi ideig jatszottal: %.0f masodperc.\n\n", i, ido);
            return;
        }
    }
    //alapertekek ha mind a 15 kerdes helyes
    jatekos.helyeskerdesek = 15;
    printf("%s\n", jatekos.nev);
    dicsoseglista(jatekos);
    statisztika(penz, ido);
    printf("Gratulalunk, megnyerted a jatekot");
}
