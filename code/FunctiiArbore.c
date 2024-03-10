#include "header.h"
#define uc unsigned char
#define ui unsigned int
#define ull unsigned long long

TArb InitA() {
    TArb aux = (TArb)malloc(sizeof(TNod));
    aux->info = 0;
    aux->red = 0;
    aux->green = 0;
    aux->blue = 0;
    aux->fiu1 = aux->fiu2 = aux->fiu3 = aux->fiu4 = NULL;
    return aux;
    }

TArb ConstrFr(uc x, uc r, uc g, uc b) {
    TArb aux = (TArb)malloc(sizeof(TNod));
    if (!aux) return NULL;
    aux->info = x;
    aux->red = r;
    aux->green = g;
    aux->blue = b;
    aux->fiu1 = aux->fiu2 = aux->fiu3 = aux->fiu4 = NULL;
    return aux;
}

void DistrugeArb(TArb r) {
    if (!r) return;
    DistrugeArb(r->fiu1);
    DistrugeArb(r->fiu2);
    DistrugeArb(r->fiu3);
    DistrugeArb(r->fiu4);
    free(r);
}

void Divizare(uc **R, uc **G, uc **B, ui x, ui y, ui size, ull factor, TArb r) {
    ull aux_red = 0, aux_green = 0, aux_blue = 0, mean = 0;
    ui i = 0, j = 0;
    for (i = x; i < x + size; i++) {
        for (j = y; j < y + size; j++) {
            aux_red = aux_red + R[i][j];
            aux_green = aux_green + G[i][j];
            aux_blue = aux_blue + B[i][j];
        }
    }
    uc red = 0, green = 0, blue = 0;
    red = aux_red / (size * size);
    green = aux_green / (size * size);
    blue = aux_blue / (size * size);
    for (i = x; i < x + size; i++) {
        for (j = y; j < y + size; j++) {
            mean = mean + (red - R[i][j]) * (red - R[i][j]);
            mean = mean + (green - G[i][j]) * (green - G[i][j]);
            mean = mean + (blue - B[i][j]) * (blue - B[i][j]);
        }
    }
    mean  = mean / (3 * size * size);
    if (mean > factor) {
        r->fiu1 = ConstrFr(0, 0, 0, 0);
        Divizare(R, G, B, x, y, size/2, factor, r->fiu1);
        r->fiu2 = ConstrFr(0, 0, 0, 0);
        Divizare(R, G, B, x, y + size/2, size/2, factor, r->fiu2);
        r->fiu3 = ConstrFr(0, 0, 0, 0);
        Divizare(R, G, B, x + size/2, y + size/2, size/2, factor, r->fiu3);
        r->fiu4 = ConstrFr(0, 0, 0, 0);
        Divizare(R, G, B, x + size/2, y, size/2, factor, r->fiu4);
    } else {
        r->red = red;
        r->green = green;
        r->blue = blue;
        r->info = 1;
    }
}

/* functia care numara frunzele din arbore */
int NrFrunze(TArb r) {
    if (r == NULL) return 0;
    int nr_frunze = 0;
    if (r->fiu1 == NULL && r->fiu2 == NULL && r->fiu3 == NULL && r->fiu4 == NULL) nr_frunze++;
    nr_frunze = nr_frunze + NrFrunze(r->fiu1);
    nr_frunze = nr_frunze + NrFrunze(r->fiu2);
    nr_frunze = nr_frunze + NrFrunze(r->fiu3);
    nr_frunze = nr_frunze + NrFrunze(r->fiu4);
    return nr_frunze;
}

/* functia care numara nivelurile din arbore */
int NrNiv(TArb r) {
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    if (!r) return 0;
    n1 = NrNiv(r->fiu1);
    n2 = NrNiv(r->fiu2);
    n3 = NrNiv(r->fiu3);
    n4 = NrNiv(r->fiu4);
    int max = n1;
    if (n2 > max) max = n2;
    if (n3 > max) max = n3;
    if (n4 > max) max = n4;
    return 1 + max;
}

/* functia care afla nivelul primei frunze din arbore */
int NivelMinim(TArb r) {
    if (!r) return 0;
    if (r->fiu1 == NULL && r->fiu2 == NULL && r->fiu3 == NULL && r->fiu4 == NULL) return 1;
    int f1 = NivelMinim(r->fiu1);
    int f2 = NivelMinim(r->fiu2);
    int f3 = NivelMinim(r->fiu3);
    int f4 = NivelMinim(r->fiu4);
    if (f1 == 0) {
        int min = f2;
        if (min > f3) min = f3;
        if (min > f4) min = f4;
        return min + 1;
    }
    if (f2 == 0) {
        int min = f1;
        if (min > f3) min = f3;
        if (min > f4) min = f4; 
        return min + 1;
    }
    if (f3 == 0) {
        int min = f1;
        if (min > f2) min = f2;
        if (min > f4) min = f4;
        return min + 1;
    }
    if (f4 == 0) {
        int min = f1;
        if (min > f2) min = f2;
        if (min > f3) min = f3;
        return min + 1;
    }
    int min = f1;
    if (min > f2) min = f2;
    if (min > f3) min = f3;
    if (min > f4) min = f4;
    return min + 1;
}

/* functia de afisare a arborelui */
void Afisare(TArb r) {
    if (r == NULL) return;
    printf("%d ", r->info);
    printf("%d %d %d\n", r->red, r->green, r->blue);
    Afisare(r->fiu1);
    Afisare(r->fiu2);
    Afisare(r->fiu3);
    Afisare(r->fiu4);
}

/* functia ce afiseaza toate nodurile de pe un anumit nivel */
void AfisareNivel(TArb r, int nivel_crt, int nivel, FILE *fout) {
    if (r == NULL) return;
    if (nivel_crt == nivel) {
        fwrite(&r->info, sizeof(uc), 1, fout);
        if (r->info == 1) {
            fwrite(&r->red, sizeof(uc), 1, fout);
            fwrite(&r->green, sizeof(uc), 1, fout);
            fwrite(&r->blue, sizeof(uc), 1, fout);
        }
    }
    if (r->fiu1) AfisareNivel(r->fiu1, nivel_crt + 1, nivel, fout);
    if (r->fiu2) AfisareNivel(r->fiu2, nivel_crt + 1, nivel, fout);
    if (r->fiu3) AfisareNivel(r->fiu3, nivel_crt + 1, nivel, fout);
    if (r->fiu4) AfisareNivel(r->fiu4, nivel_crt + 1, nivel, fout);
}

/* Functia de adaugare a unui element in coada */
int IntrQ(TCoada *c, TArb x) {
    TLista aux = NULL;
    aux = (TLista)malloc(sizeof(TCelula));
    if (!aux) return 0;
    aux->info = x;
    aux->urm = NULL;
    if (c->sf != NULL) {
        c->sf->urm = aux;
    } else {
        c->inc = aux;
    }
    c->sf = aux;
    return 1;
}

/* Functia de extragere a unui element din coada */
int ExtrQ(TCoada *c, TArb *x) {
    TLista aux = NULL;
    if (c->inc == NULL) return 0;
    aux = c->inc;
    *x = aux->info;
    c->inc = aux->urm;
    if (c->inc == NULL) c->sf = NULL;
    free(aux);
    return 1;
}

/* Functia de distrugere a cozii */
void DistrQ(TCoada **c) {
    TLista p = NULL, aux = NULL;
    p = (*c)->inc;
    while (p) {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*c);
    *c = NULL;
}

/* Functia de initializare coada */
TCoada* InitQ() {
    TCoada *c = (TCoada*)malloc(sizeof(TCoada));
    if (!c) return NULL;
    c->inc = c->sf = NULL;
    return c;
}

/* functia de creare a imaginii pornind de la arborele cuaternar */
void CreareImagine(uc **R, uc **G, uc **B, ui x, ui y, ui size, TArb r) {
        if (r->info == 1) {
            ui i = 0, j = 0;
            for (i = x; i < x + size; i++) {
                for (j = y; j < y + size; j++) {
                    R[i][j] = r->red;
                    G[i][j] = r->green;
                    B[i][j] = r->blue;
                }
            }
        } else {
        CreareImagine(R, G, B, x, y, size/2, r->fiu1);
        CreareImagine(R, G, B, x, y + size/2, size/2, r->fiu2);
        CreareImagine(R, G, B, x + size/2, y + size/2, size/2, r->fiu3);
        CreareImagine(R, G, B, x + size/2, y, size/2, r->fiu4);
        }
}
