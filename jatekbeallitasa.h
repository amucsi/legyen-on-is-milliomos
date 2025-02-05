#ifndef JATEKBEALLITASA_H_INCLUDED
#define JATEKBEALLITASA_H_INCLUDED

#include "switchek.h"
#include "kerdesfuggvenyek.h"
#include "fajlkezeles.h"

//a dinamikus kategoriak tomb letrehozasahoz hasznos struktura
typedef struct Kategoria {
    char kategoria[16];
} Kategoria;

void kerdestombletrehozas(Kerdes *bemenetkerdestomb, int meret, Kerdes *kimenetkerdestomb, char *kizartkategoria);

char *kategoriakizaras(Kategoria *kategoriak, int kategoriakszama);

int nehezsegvalasztas(int *nehezsegtombokmerete);

int gondolkodasiidofuggveny();

void jatekbeallitasa(Kerdes **nehezsegszerintikerdesek, int *nehezsegtombokmerete, Kategoria *kategoriak, int kategoriakszama);

#endif // JATEKBEALLITASA_H_INCLUDED
