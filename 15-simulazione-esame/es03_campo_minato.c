/*
 * es03 — Campo minato: matrici, puntatori e funzioni  (Tipo esame)
 *
 * Input: R C (righe e colonne, da 1 a 10), poi R righe di C caratteri:
 * '*' = mina, '.' = cella libera.
 * Output: la griglia in cui ogni cella libera e' sostituita dal numero di
 * mine nelle (fino a) 8 celle vicine, il numero totale di mine e la cella
 * libera "piu' pericolosa" (piu' mine vicine; a parita' la prima in ordine
 * di riga e poi di colonna).
 *
 * Completa:
 *   - conta_vicine: mine attorno a (i, j). Leggi le celle con la notazione
 *     a puntatori della E-tivity:  *(*(m + r) + c)  al posto di m[r][c].
 *     Attento ai bordi: non leggere mai fuori dalla griglia.
 *   - calcola: riempie num[i][j] (-1 per le mine) e ritorna il numero di mine.
 *   - piu_pericolosa: ritorna il massimo (o -1 se ci sono solo mine) e
 *     mette riga e colonna in *pi e *pj. Usa il puntatore a riga p gia'
 *     dichiarato: (*p)[j] e' l'elemento j della riga puntata, p++ passa alla riga dopo.
 *
 * Come testarlo: make test T=15 E=es03
 */
#include <stdio.h>
#include <string.h>

#define MAXR 10
#define MAXC 10

int conta_vicine(char m[][MAXC], int righe, int colonne, int i, int j)
{
    /* TODO: due cicli r = i-1..i+1, c = j-1..j+1; salta le celle fuori
       dalla griglia e la cella (i, j) stessa */
    (void)m; (void)righe; (void)colonne; (void)i; (void)j;
    return 0;
}

int calcola(char m[][MAXC], int num[][MAXC], int righe, int colonne)
{
    /* TODO */
    (void)m; (void)num; (void)righe; (void)colonne;
    return 0;
}

int piu_pericolosa(int num[][MAXC], int righe, int colonne, int *pi, int *pj)
{
    int (*p)[MAXC];     /* puntatore a un vettore di MAXC int, cioe' a una RIGA */

    /* TODO: for (p = num, i = 0; i < righe; p++, i++) ... */
    (void)num; (void)righe; (void)colonne; (void)pi; (void)pj;
    p = NULL;
    (void)p;
    return -1;
}

int main(void)
{
    char m[MAXR][MAXC];
    int num[MAXR][MAXC] = {{0}};
    char riga[MAXC + 1];          /* +1 per il terminatore '\0' */
    int righe, colonne, i, j, mine, max, ri = 0, rj = 0;

    if (scanf("%d %d", &righe, &colonne) != 2 ||
        righe < 1 || righe > MAXR || colonne < 1 || colonne > MAXC) {
        printf("dimensioni non valide\n");
        return 1;
    }
    for (i = 0; i < righe; i++) {
        if (scanf("%10s", riga) != 1 || (int) strlen(riga) != colonne) {
            printf("riga %d non valida\n", i);
            return 1;
        }
        for (j = 0; j < colonne; j++)
            m[i][j] = riga[j];
    }

    mine = calcola(m, num, righe, colonne);
    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            if (num[i][j] < 0)
                putchar('*');
            else
                putchar('0' + num[i][j]);   /* cifra -> carattere: '0' + 3 = '3' */
        }
        putchar('\n');
    }
    printf("mine: %d\n", mine);

    max = piu_pericolosa(num, righe, colonne, &ri, &rj);
    if (max < 0)
        printf("nessuna cella libera\n");
    else
        printf("piu' pericolosa: riga %d colonna %d (%d mine vicine)\n", ri, rj, max);
    return 0;
}
