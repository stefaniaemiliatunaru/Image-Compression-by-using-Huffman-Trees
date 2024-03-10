#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* definire structura arbore cuaternar cu cei 4 fii */
typedef struct nod {
    unsigned char info;
    unsigned char red, green, blue;
    struct nod *fiu1, *fiu2, *fiu3, *fiu4;
} TNod, *TArb;

/* definire coada */
typedef struct celula {
    TArb info;
    struct celula* urm;
} TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;
} TCoada;
