/*
 * es03 — Campo minato: matrici, puntatori e funzioni  (Tipo esame) — SOLUZIONE
 *
 * Input: R C (righe e colonne, da 1 a 10), poi R righe di C caratteri:
 * '*' = mina, '.' = cella libera.
 * Output: la griglia in cui ogni cella libera e' sostituita dal numero di
 * mine nelle (fino a) 8 celle vicine, il numero totale di mine e la cella
 * libera "piu' pericolosa" (piu' mine vicine; a parita', la prima in ordine
 * di riga e poi di colonna).
 *
 * Come testarlo: make sol T=15 E=es03
 */
#include <stdio.h>
#include <string.h>

#define MAXR 10
#define MAXC 10

/* Mine nelle celle vicine a (i, j). Accesso con la notazione a puntatori della
 * E-tivity "Matrici e puntatori": *(*(m + r) + c) equivale a m[r][c].
 *  - m + r       e' l'indirizzo della RIGA r (tipo: puntatore a un vettore di MAXC char)
 *  - *(m + r)    e' quella riga, che "decade" nell'indirizzo del suo primo char
 *  - ... + c     si sposta di c char dentro la riga; l'ultimo * legge il carattere */
int conta_vicine(char m[][MAXC], int righe, int colonne, int i, int j)
{
    int r, c, conta = 0;

    for (r = i - 1; r <= i + 1; r++)
        for (c = j - 1; c <= j + 1; c++) {
            if (r < 0 || r >= righe || c < 0 || c >= colonne)
                continue;                 /* fuori dalla griglia: NON leggere (sarebbe fuori dal vettore) */
            if (r == i && c == j)
                continue;                 /* la cella stessa non e' una vicina */
            if (*(*(m + r) + c) == '*')
                conta++;
        }
    return conta;
}

/* Riempie num[i][j] con le vicine di ogni cella libera e -1 per le mine.
 * Ritorna il numero totale di mine. */
int calcola(char m[][MAXC], int num[][MAXC], int righe, int colonne)
{
    int i, j, mine = 0;

    for (i = 0; i < righe; i++)
        for (j = 0; j < colonne; j++) {
            if (m[i][j] == '*') {
                num[i][j] = -1;
                mine++;
            } else {
                num[i][j] = conta_vicine(m, righe, colonne, i, j);
            }
        }
    return mine;
}

/* Cerca la cella libera con piu' mine vicine. Due risultati (riga e colonna)
 * escono dai parametri puntatore; il return da' il massimo, oppure -1 se non
 * c'e' nessuna cella libera.
 * p e' un PUNTATORE A RIGA (int (*)[MAXC]): p++ salta un'intera riga. */
int piu_pericolosa(int num[][MAXC], int righe, int colonne, int *pi, int *pj)
{
    int (*p)[MAXC];
    int i, j, max = -1;

    for (p = num, i = 0; i < righe; p++, i++)
        for (j = 0; j < colonne; j++)
            if ((*p)[j] > max) {          /* > e non >=: tengo la PRIMA trovata */
                max = (*p)[j];
                *pi = i;
                *pj = j;
            }
    return max;      /* le mine valgono -1: se ci sono solo mine, max resta -1 */
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
