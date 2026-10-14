/*
 * es05 — Trova e correggi l'errore: temperature della settimana  ·  Intermedio
 *
 * Il programma legge esattamente N temperature (numeri interi),
 * stampa la somma, la media e le variazioni da un giorno al successivo.
 * Esempio: 12 15 13 13 18  ->  somma: 71 / media: 14.20 / variazioni: +3 -2 +0 +5
 *
 * Il codice qui sotto COMPILA, ma contiene DUE errori. Senza AddressSanitizer
 * potrebbe perfino sembrare funzionare (o stampare numeri strani).
 * Con il test (che usa AddressSanitizer) il programma va in CRASH.
 * Trova gli errori, correggili cambiando il meno possibile, e rilancia il test.
 *
 * Come testarlo: make test T=05 E=es05
 */
#include <stdio.h>

#define N 5

int main(void)
{
    int t[N];
    int d[N - 1];
    int i, somma = 0;

    for (i = 0; i < N; i++)
        if (scanf("%d", &t[i]) != 1) {
            printf("servono %d numeri\n", N);
            return 1;
        }

    for (i = 0; i <= N; i++)
        somma += t[i];
    printf("somma: %d\n", somma);
    printf("media: %.2f\n", (double)somma / N);

    for (i = 0; i < N; i++)
        d[i] = t[i + 1] - t[i];

    printf("variazioni:");
    for (i = 0; i < N - 1; i++)
        printf(" %+d", d[i]);
    printf("\n");
    return 0;
}
