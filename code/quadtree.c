#include "header.h"
#define uc unsigned char
#define ui unsigned int

#define UNU 1
#define DOI 2
#define TREI 3
#define PATRU 4
#define OSUTA 100
TArb ConstrFr(uc x, uc r, uc g, uc b);
void DistrugeArb(TArb r);
TArb InitA();
int NrFrunze(TArb r);
int NrNiv(TArb r);
void Divizare(uc ** R, uc ** G, uc ** B, ui x, ui y, ui size, unsigned long long factor, TArb r);
void Afisare(TArb r);
int NivelMinim(TArb r);
void AfisareNivel(TArb r, int nivel_crt, int nivel, FILE * fout);
TArb ConstrArb(uc * v_info, uc * v_red, uc * v_green, uc * v_blue, int * i, int j);
int IntrQ(TCoada * c, TArb x);
int ExtrQ(TCoada * c, TArb * x);
void DistrQ(TCoada ** c);
TCoada * InitQ();
void CreareImagine(uc ** R, uc ** G, uc ** B, ui x, ui y, ui size, TArb r);

int main(int argc, char * argv[]) {
    char cerinta[OSUTA];
    snprintf(cerinta, strlen(argv[UNU])+1, "%s", argv[UNU]);
    int factor = 0;
    FILE *fin = NULL, *fout = NULL;
    if (strcmp(cerinta, "-c1") == 0 || strcmp(cerinta, "-c2") == 0) {
        factor = atoi(argv[DOI]);
        fin = fopen(argv[TREI], "r");
    fout = fopen(argv[PATRU], "wb");
    } else if (strcmp(cerinta, "-d") == 0) {
        fin = fopen(argv[DOI], "r");
        fout = fopen(argv[TREI], "wb");
    }

    if (strcmp(cerinta, "-c1") == 0) {
        char tip_f[OSUTA];
        fscanf(fin, "%s", tip_f);
        ui width = 0, height = 0;
        fscanf(fin, "%u", & width);
        fscanf(fin, "%u", & height);
        ui size = width;
        ui val_max_col = 0;
        fscanf(fin, "%u", & val_max_col);
        char backslash_n = 0;
        fscanf(fin, "%c", & backslash_n);
        uc red = 0, green = 0, blue = 0;
        uc ** matrix_r = NULL, ** matrix_g = NULL, ** matrix_b = NULL;
        int i = 0, j = 0;
        matrix_r = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_r[i] = malloc(size * sizeof(uc));
        }
        matrix_g = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_g[i] = malloc(size * sizeof(uc));
        }
        matrix_b = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_b[i] = malloc(size * sizeof(uc));
        }
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fread( & red, sizeof(uc), 1, fin);
                fread( & green, sizeof(uc), 1, fin);
                fread( & blue, sizeof(uc), 1, fin);
                matrix_r[i][j] = red;
                matrix_g[i][j] = green;
                matrix_b[i][j] = blue;
            }
        }
        TArb quadtree = InitA();
        Divizare(matrix_r, matrix_g, matrix_b, 0, 0, size, factor, quadtree);
        fprintf(fout, "%d\n", NrNiv(quadtree));
        fprintf(fout, "%d\n", NrFrunze(quadtree));
        int nivel = NivelMinim(quadtree);
        ui rez = 1;
        for (i = 0; i < nivel - 1; i++)
            rez = rez * 2;
        rez = size / rez;
        fprintf(fout, "%d\n", rez);
        for (i = 0; i < size; i++)
            free(matrix_r[i]);
        free(matrix_r);
        for (i = 0; i < size; i++)
            free(matrix_g[i]);
        free(matrix_g);
        for (i = 0; i < size; i++)
            free(matrix_b[i]);
        free(matrix_b);
        DistrugeArb(quadtree);
    }

    if (strcmp(cerinta, "-c2") == 0) {
        char tip_f[OSUTA];
        fscanf(fin, "%s", tip_f);
        ui width = 0, height = 0;
        fscanf(fin, "%u", & width);
        fscanf(fin, "%u", & height);
        ui size = width;
        ui val_max_col = 0;
        fscanf(fin, "%u", & val_max_col);
        char backslash_n = 0;
        fscanf(fin, "%c", & backslash_n);
        uc red = 0, green = 0, blue = 0;
        uc ** matrix_r = NULL, ** matrix_g = NULL, ** matrix_b = NULL;
        int i = 0, j = 0;
        matrix_r = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_r[i] = malloc(size * sizeof(uc));
        }
        matrix_g = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_g[i] = malloc(size * sizeof(uc));
        }
        matrix_b = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_b[i] = malloc(size * sizeof(uc));
        }
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fread( & red, sizeof(uc), 1, fin);
                fread( & green, sizeof(uc), 1, fin);
                fread( & blue, sizeof(uc), 1, fin);
                matrix_r[i][j] = red;
                matrix_g[i][j] = green;
                matrix_b[i][j] = blue;
            }
        }
        TArb quadtree = InitA();
        Divizare(matrix_r, matrix_g, matrix_b, 0, 0, size, factor, quadtree);
        fwrite( & size, sizeof(ui), 1, fout);
        int nr_niv = NrNiv(quadtree);
        for (i = 0; i < nr_niv; i++) {
            AfisareNivel(quadtree, 0, i, fout);
        }
        for (i = 0; i < size; i++) {
            free(matrix_r[i]);
        }
        free(matrix_r);
        for (i = 0; i < size; i++) {
            free(matrix_g[i]);
        }
        free(matrix_g);
        for (i = 0; i < size; i++) {
            free(matrix_b[i]);
        }
        free(matrix_b);
        DistrugeArb(quadtree);
    }

    if (strcmp(cerinta, "-d") == 0) {
        ui size = 0;
        fread( & size, sizeof(ui), 1, fin);
        TArb quadtree = NULL;
        TCoada * coada = InitQ();
        uc type = 0;
        fread( & type, sizeof(uc), 1, fin);
        if (type == 0) {
            quadtree = ConstrFr(type, 0, 0, 0);
            IntrQ(coada, quadtree);
        }
        if (type == 1) {
            uc aux_red = 0;
            fread( & aux_red, sizeof(uc), 1, fin);
            uc aux_green = 0;
            fread( & aux_green, sizeof(uc), 1, fin);
            uc aux_blue = 0;
            fread( & aux_blue, sizeof(uc), 1, fin);
            quadtree = ConstrFr(type, aux_red, aux_green, aux_blue);
        }
        TArb aux = NULL;
        while (ExtrQ(coada, & aux)) {
            fread( & type, sizeof(uc), 1, fin);
            aux -> fiu1 = ConstrFr(type, 0, 0, 0);
            if (aux -> fiu1 -> info == 0) {
                IntrQ(coada, aux -> fiu1);
            } else {
                fread( & aux -> fiu1 -> red, sizeof(uc), 1, fin);
                fread( & aux -> fiu1 -> green, sizeof(uc), 1, fin);
                fread( & aux -> fiu1 -> blue, sizeof(uc), 1, fin);
            }
            fread( & type, sizeof(uc), 1, fin);
            aux -> fiu2 = ConstrFr(type, 0, 0, 0);
            if (aux -> fiu2 -> info == 0) {
                IntrQ(coada, aux -> fiu2);
            } else {
                fread( & aux -> fiu2 -> red, sizeof(uc), 1, fin);
                fread( & aux -> fiu2 -> green, sizeof(uc), 1, fin);
                fread( & aux -> fiu2 -> blue, sizeof(uc), 1, fin);
            }
            fread( & type, sizeof(uc), 1, fin);
            aux -> fiu3 = ConstrFr(type, 0, 0, 0);
            if (aux -> fiu3 -> info == 0) {
                IntrQ(coada, aux -> fiu3);
            } else {
                fread( & aux -> fiu3 -> red, sizeof(uc), 1, fin);
                fread( & aux -> fiu3 -> green, sizeof(uc), 1, fin);
                fread( & aux -> fiu3 -> blue, sizeof(uc), 1, fin);
            }
            fread( & type, sizeof(uc), 1, fin);
            aux -> fiu4 = ConstrFr(type, 0, 0, 0);
            if (aux -> fiu4 -> info == 0) {
                IntrQ(coada, aux -> fiu4);
            } else {
                fread( & aux -> fiu4 -> red, sizeof(uc), 1, fin);
                fread( & aux -> fiu4 -> green, sizeof(uc), 1, fin);
                fread( & aux -> fiu4 -> blue, sizeof(uc), 1, fin);
            }
        }
        uc ** matrix_r = NULL, ** matrix_g = NULL, ** matrix_b = NULL;
        int i = 0, j = 0;
        matrix_r = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_r[i] = malloc(size * sizeof(uc));
        }
        matrix_g = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_g[i] = malloc(size * sizeof(uc));
        }
        matrix_b = malloc(size * sizeof(uc * ));
        for (i = 0; i < size; i++) {
            matrix_b[i] = malloc(size * sizeof(uc));
        }
        CreareImagine(matrix_r, matrix_g, matrix_b, 0, 0, size, quadtree);
        fprintf(fout, "P6\n");
        fprintf(fout, "%d %d\n", size, size);
        fprintf(fout, "255\n");
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fwrite( & (matrix_r[i][j]), sizeof(uc), 1, fout);
                fwrite( & (matrix_g[i][j]), sizeof(uc), 1, fout);
                fwrite( & (matrix_b[i][j]), sizeof(uc), 1, fout);
            }
        }
        for (i = 0; i < size; i++) {
            free(matrix_r[i]);
        }
        free(matrix_r);
        for (i = 0; i < size; i++) {
            free(matrix_g[i]);
        }
        free(matrix_g);
        for (i = 0; i < size; i++) {
            free(matrix_b[i]);
        }
        free(matrix_b);
        DistrugeArb(quadtree);
        DistrQ(&coada);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
