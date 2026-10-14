/*
 * es03 — file 3 di 3: main.c
 * Output atteso con input 10 -3 7 -20 5:
 *   mossa 1: +10 -> totale 10
 *   mossa 2: -3 -> totale 7
 *   mossa 3: +7 -> totale 14
 *   mossa 4: -20 -> totale 0
 *   mossa 5: +5 -> totale 5
 *   fine partita, totale azzerato: 0
 */
#include <stdio.h>
#include "punteggio.h"

int main(void)
{
    int p, mossa = 0;
    int finto = 0;   /* TODO 3: quando hai fatto il TODO 1, cancella questa variabile e
                        usa al suo posto punteggio_totale (nelle due printf e nell'azzeramento) */

    while (scanf("%d", &p) == 1) {
        mossa++;
        aggiungi_punti(p);
        printf("mossa %d: %+d -> totale %d\n", mossa, p, finto);
    }
    finto = 0;
    printf("fine partita, totale azzerato: %d\n", finto);
    return 0;
}
