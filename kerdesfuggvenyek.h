#ifndef KERDESFUGGVENYEK_H_INCLUDED
#define KERDESFUGGVENYEK_H_INCLUDED

#include "switchek.h"

//kerdes struktura
typedef struct Kerdes {
    int nehezseg;
    char kerdes[101];
    char A[31];
    char B[31];
    char C[31];
    char D[31];
    char helyesvalasz;
    char kategoria[16];
} Kerdes;

int kerdesfuggveny(Kerdes jelenlegikerdes, int gondolkodasiido, int penz, int *penzptr, bool *segitsegek);

void felezes(char helyesvalasz);

#endif // KERDESFUGGVENYEK_H_INCLUDED

