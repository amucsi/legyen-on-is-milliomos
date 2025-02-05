// LEGYEN ON IS MILLIOMOS Mucsi Attila Gábor HEZNU6, utolso modositas: 2022.11.26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#include "debugmalloc.h"
#include "jatekbeallitasa.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
    #ifdef _WIN32      //karakterkodolas
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    debugmalloc_max_block_size(10000000); //a debugmalloc kovetelese

    FILE *kerdesbank; //a kerdesbank fajl letrehozasa
    kerdesbank = fopen("csvxd.csv", "r");
    if (kerdesbank == NULL) {
        perror("Kerdesbank sikertelen megnyitasa");
        return 0;
    }

    int nehezsegtombokmerete[15] = {0}; //az azonos nehezsegu kerdesek merete
    int db = 0; //osszes kerdes darabszama
    Kerdes *kerdesek = NULL;
    Kerdes ujkerdes;

    int kategoriakszama = 0;
    Kategoria *kategoriak = NULL;
    Kategoria ujkategoria;

    char sor[500];
    while (fgets(sor, 500, kerdesbank) != 0) { //fajl vegeig olvas
        char charnehezseg[3];
        sscanf(sor,"%2[^;];%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%1[^;];%s", charnehezseg, ujkerdes.kerdes, ujkerdes.A, ujkerdes.B, ujkerdes.C, ujkerdes.D, &ujkerdes.helyesvalasz, ujkerdes.kategoria);
        ujkerdes.nehezseg = atoi(charnehezseg); //ha egybol integerkent olvasnam be akkor a szam ascii kodja lenne, ezert kell az ideiglenes charnehezseg valtozo
        Kerdes *ujtomb = (Kerdes*) malloc(sizeof(Kerdes) * (db+1));
        for (int i = 0; i < db; i++)
            ujtomb[i] = kerdesek[i];
        free(kerdesek);
        kerdesek = ujtomb;
        kerdesek[db] = ujkerdes;
        db++;
        nehezsegtombokmerete[ujkerdes.nehezseg-1]++;

        strcpy(ujkategoria.kategoria, ujkerdes.kategoria);
        bool kesz = false; //megnezzuk van-e ugyanolyan, ha igen akkor continue
        for (int i = 0; i < kategoriakszama; i++) {
            if (strcmp(ujkategoria.kategoria, kategoriak[i].kategoria) == 0) {
                kesz = true;
                break;
            }
        }
        if (kesz) continue;

        Kategoria *ujkategoriak = (Kategoria*) malloc(sizeof(Kategoria) * (kategoriakszama+1));
        for (int i = 0; i < kategoriakszama; i++)
            ujkategoriak[i] = kategoriak[i];
        free(kategoriak);
        kategoriak = ujkategoriak;
        kategoriak[kategoriakszama] = ujkategoria;
        kategoriakszama++;
    }

    //ketdimenzios, dinamikus kerdestomb letrehozasa
    Kerdes **nehezsegszerintikerdesek = (Kerdes**) malloc(15 * sizeof(Kerdes*));
    for (int i = 0; i < 15; i++)
        nehezsegszerintikerdesek[i] = (Kerdes*) malloc(nehezsegtombokmerete[i] * sizeof(Kerdes));

    int count[15] = {0}; //ideiglenes szamlalo
    for (int i = 0; i < db; i++) { //nehezseg szerinti szetvalogatas
        nehezsegszerintikerdesek[kerdesek[i].nehezseg-1][count[kerdesek[i].nehezseg-1]] = kerdesek[i];
        count[kerdesek[i].nehezseg-1]++;
    }

    //a program fo switche
    printf ("Legyen On Is Milliomos jatek\n\n");
    char valasz;
    do {
        valasz = Fomenu();
        switch (valasz) {
            case '1':
                jatekbeallitasa(nehezsegszerintikerdesek, nehezsegtombokmerete, kategoriak, kategoriakszama);
                break;

            case '2':
                kiiras_dicsoseglista();
                break;

            case '3':
                kiiras_statisztika();
                break;
            case '4':
                printf("Kileptel a jatekbol. Szia!\n\n");
                break;
        }
    } while (valasz != '4');

    //a dinamikus tombok felszabaditasa
    for (int i = 0; i < 15; i++)
        free(nehezsegszerintikerdesek[i]);
    free(kerdesek);
    free(nehezsegszerintikerdesek);
    free(kategoriak);
    return 0;
}
