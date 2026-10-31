/*
 * 01 — es10: triangoli numerici validati, versione con goto — SOLUZIONE
 *
 * Ogni ciclo di es09 diventa una coppia di etichette:
 *   do { corpo } while (c);   ->  inizio: corpo; if (c) goto inizio;
 *   while (c) { corpo }       ->  inizio: if (!c) goto fine; corpo; goto inizio; fine:
 */
#include <stdio.h>

int main(void)
{
    int righe = 0;
    int max = 0;
    int stampati = 0;
    int i = 1;
    int j;

leggi_righe:                          /* do while: corpo prima, test dopo */
    if (scanf("%d", &righe) != 1) {
        goto input_non_valido;
    }
    if (righe <= 0) {
        goto leggi_righe;
    }

leggi_max:
    if (scanf("%d", &max) != 1) {
        goto input_non_valido;
    }
    if (max <= 0) {
        goto leggi_max;
    }

riga:                                 /* while esterno: test prima del corpo */
    if (i > righe) {
        goto fine;
    }
    j = 1;
colonna:                              /* while interno */
    if (j > i) {
        goto fine_riga;
    }
    if (j > 1) {
        printf(" ");
    }
    printf("%d", j);
    stampati = stampati + 1;
    j = j + 1;
    if (stampati == max) {            /* uscita anticipata: salto all'etichetta finale */
        printf("\n");
        goto fine;
    }
    goto colonna;
fine_riga:
    printf("\n");
    i = i + 1;
    goto riga;

fine:
    return 0;

input_non_valido:
    printf("Input non valido\n");
    return 1;
}
