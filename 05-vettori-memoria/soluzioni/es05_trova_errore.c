/*
 * es05 — Trova e correggi l'errore: temperature della settimana  (SOLUZIONE)
 *
 * Il programma legge esattamente N temperature (numeri interi),
 * stampa la somma, la media e le variazioni da un giorno al successivo.
 *
 * Come testarlo: make sol T=05 E=es05
 */
#include <stdio.h>

#define N 5

int main(void)
{
    int t[N];        /* N temperature: indici validi 0 .. N-1           */
    int d[N - 1];    /* N-1 variazioni: indici validi 0 .. N-2           */
    int i, somma = 0;

    for (i = 0; i < N; i++)
        if (scanf("%d", &t[i]) != 1) {
            printf("servono %d numeri\n", N);
            return 1;
        }

    /* CORREZIONE 1: era "i <= N". Con <= il ciclo fa un giro in più
     * e legge t[N], cella che NON appartiene al vettore. Il C non se ne
     * accorge e somma la "spazzatura" che trova lì; AddressSanitizer
     * invece ferma il programma con "stack-buffer-overflow". */
    for (i = 0; i < N; i++)
        somma += t[i];
    printf("somma: %d\n", somma);
    printf("media: %.2f\n", (double)somma / N);

    /* CORREZIONE 2: era "i < N". Le variazioni sono N-1 (tra 5 giorni
     * ci sono 4 "passaggi"). Con i < N, all'ultimo giro (i = N-1)
     * scriveremmo d[N-1] (fuori da d) e leggeremmo t[N] (fuori da t). */
    for (i = 0; i < N - 1; i++)
        d[i] = t[i + 1] - t[i];

    printf("variazioni:");
    for (i = 0; i < N - 1; i++)
        printf(" %+d", d[i]);     /* %+d stampa sempre il segno: +3, -2 */
    printf("\n");
    return 0;
}
