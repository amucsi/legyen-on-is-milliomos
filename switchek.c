#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "debugmalloc.h"
#include "switchek.h"

char Fomenu () {
    char valasz;
    bool kesz = false;
    do {
        printf ("FOMENU\n\n");
        printf ("(1) Uj jatek inditasa\n(2) Dicsoseglista\n(3) Statisztika\n(4) Kilepes\n\n> ");
        scanf (" %c", &valasz);
        printf("\n");
        switch (valasz) {
            case '1': kesz = true; break;
            case '2': kesz = true; break;
            case '3': kesz = true; break;
            case '4': kesz = true; break;
            default : printf("Ismeretlen input!\n\n> "); break;
        }
   } while (!kesz);
   return valasz;
}

//helyes valasz megadasa eseten megjeleno menu
int helyesvalaszswitch(int penz, int *penzptr, bool *segitsegek) {
    printf("Helyes valasz!\nJelenlegi penzosszeged: %d\n\n", penz);
    do {
        printf("Mi legyen?\n(1) Kovetkezo kerdes\n(2) Felezes segitseg vasarlasa (50MFt)\n(3) Kozonseg segitseg vasarlasa (50MFt)\n(4) Kilepes a jatekbol a nyeremenyt megtartva\n\n> ");
        char valasz;
        scanf(" %c", &valasz);
        switch(valasz) {
            case '1':
                printf("Jojjon a kovetkezo kerdes!\n\n");
                for (int i = 3; i > 0; i--) {
                    printf("%d...\n", i);
                    sleep(1);
                }
                system("cls");
                return 1;
            case '2':
                if (segitsegek[0])
                    printf("Meg nem hasznaltad fel a felezes segitsegedet!\n\n> ");

                else if (*penzptr < 50)
                    printf("Nincs eleg penzed!\n\n> ");

                else {
                    printf("Megvasaroltad a felezes segitseget!\n\n> ");
                    segitsegek[0] = true;
                    *penzptr -= 50;
                }

                break;

            case '3':
                if (segitsegek[1])
                    printf("Meg nem hasznaltad fel a kozonseg segitsegedet!\n\n> ");

                else if (*penzptr < 50)
                    printf("Nincs eleg penzed!\n\n> ");

                else {
                    printf("Megvasaroltad a kozonseg segitseget!\n\n> ");
                    segitsegek[1] = true;
                    *penzptr -= 50;
                }

                break;

            case '4':
                return 2;
            default:
                printf("Helytelen input!\n\n");
                break;
        }
    } while (true);
}

//rossz valasz megadasa eseten megjeleno menu
void rosszvalaszswitch() {

    do {
        printf("Mi legyen?\n(1) Fomenu\n\n> ");
        char valasz;
        scanf(" %c", &valasz);

        switch(valasz) {

            case '1':
                system("cls");
                return;
            default:
                printf("Helytelen input!\n\n");
                break;
        }
    } while (true);
}

//az ido lejarta eseten megjeleno switch
int lejartidoswitch() {
    printf("Lejart az idod! A jateknak vege. Nyeremenyed: 0MFt\n\n");
    do {
        printf("Mi legyen?\n(1) Fomenu\n\n> ");
        char valasz;
        scanf(" %c", &valasz);

        switch(valasz) {

            case '1':
                system("cls");
                return 3;
            default:
                printf("Helytelen input!\n\n");
                break;
        }
    } while (true);
}
