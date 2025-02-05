#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "debugmalloc.h"
#include "kerdesfuggvenyek.h"

int kerdesfuggveny(Kerdes jelenlegikerdes, int gondolkodasiido, int penz, int *penzptr, bool *segitsegek) {
    clock_t elerhetoido = clock() + gondolkodasiido;
    char valasz;
    printf("%s\n(A) %s\n(B) %s\n(C) %s\n(D) %s\n\n> ", jelenlegikerdes.kerdes, jelenlegikerdes.A, jelenlegikerdes.B, jelenlegikerdes.C, jelenlegikerdes.D);

    do {
        if (kbhit()) {
        valasz = getch();
        printf("%c\n", valasz);
        switch (valasz) {

            case 'A':
            case 'a':
                if (jelenlegikerdes.helyesvalasz == 'A' || jelenlegikerdes.helyesvalasz == 'a') {
                    *penzptr += 10;
                    return helyesvalaszswitch(penz+10, penzptr, segitsegek);
                }

                else {
                    return 0;
                }

            case 'B':
            case 'b':
                if (jelenlegikerdes.helyesvalasz == 'B' || jelenlegikerdes.helyesvalasz == 'b') {
                    *penzptr += 10;
                    return helyesvalaszswitch(penz+10, penzptr, segitsegek);
                }

                else {
                    return 0;
                }

            case 'C':
            case 'c':
                if (jelenlegikerdes.helyesvalasz == 'C' || jelenlegikerdes.helyesvalasz == 'c') {
                    *penzptr += 10;
                    return helyesvalaszswitch(penz+10, penzptr, segitsegek);
                }

                else {
                    return 0;
                }

            case 'D':
            case 'd':
                if (jelenlegikerdes.helyesvalasz == 'D' || jelenlegikerdes.helyesvalasz == 'd') {
                    *penzptr += 10;
                    return helyesvalaszswitch(penz+10, penzptr, segitsegek);
                }

                else {
                    return 0;
                }

            case 'f':
            case 'F':
                if (segitsegek[0]) {
                    printf("Felhasznaltad a felezes segitsegedet!\n");
                    felezes(jelenlegikerdes.helyesvalasz);
                    segitsegek[0] = false;
                    break;
                }

                else {
                    printf("Mar felhasznaltad ezt a segitseget!\n\n> ");
                    break;
                }

            case 'k':
            case 'K':
                if(segitsegek[1]) {
                    printf("A kozonseg segitseget kerted!\nA kozonseg szerint a helyes valasz: %c\n\n> ", jelenlegikerdes.helyesvalasz);
                    segitsegek[1] = false;
                    break;
                }

                else {
                    printf("Mar felhasznaltad ezt a segitseget!\n\n> ");
                    break;
                }


            default:
                printf("Ismeretlen input!\n\n> ");
                break;
        }
        }
    } while (elerhetoido > clock());
    return lejartidoswitch(); //ha letelik az ido, megall a while loop es meghivjuk a lejartidoswitchet
}

void felezes(char helyesvalasz) { //felezes segitseg fuggvenye
    char betuk[] = {'A','B','C','D'};
    char masikbetu = helyesvalasz;
    int random;
    while (masikbetu == helyesvalasz) {
        srand(time(NULL));
        random = (rand() % (3 - 0 + 1)) + 0;
        masikbetu = betuk[random];
    }
    if (masikbetu < helyesvalasz) //abc sorrendben printelje ki oket
        printf("A ket lehetseges valaszlehetoseg: %c vagy %c\n\n> ", masikbetu, helyesvalasz);
    else
        printf("A ket lehetseges valaszlehetoseg: %c vagy %c\n\n> ", helyesvalasz, masikbetu);
}
