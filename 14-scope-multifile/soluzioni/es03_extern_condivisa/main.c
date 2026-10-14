/*
 * main.c — usa il modulo "punteggio"  (SOLUZIONE di es03)
 */
#include <stdio.h>
#include "punteggio.h"       /* virgolette: cerca prima nella cartella del progetto */

int main(void)
{
    int p, mossa = 0;

    while (scanf("%d", &p) == 1) {
        mossa++;
        aggiungi_punti(p);
        /* leggo DIRETTAMENTE la variabile definita in punteggio.c: è possibile
           perché punteggio.h la dichiara con extern */
        printf("mossa %d: %+d -> totale %d\n", mossa, p, punteggio_totale);
    }
    punteggio_totale = 0;    /* main può anche SCRIVERLA: la variabile è condivisa davvero */
    printf("fine partita, totale azzerato: %d\n", punteggio_totale);
    return 0;
}
