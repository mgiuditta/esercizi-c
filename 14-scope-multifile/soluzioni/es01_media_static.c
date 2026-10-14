/*
 * es01 — Media "che ricorda" con variabili static locali  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.4 (static locale: "il valore resta inalterato tra le varie
 * chiamate"), Appunti Unità 4 par. 4.6 (funzione contatore con static int c = 0).
 */
#include <stdio.h>

/* Riceve UN valore alla volta e restituisce la media di TUTTI i valori ricevuti finora.
 * Chi chiama non deve passare né la somma né il conteggio: la funzione li ricorda da sola. */
double media_corrente(int x)
{
    static int conteggio = 0;   /* inizializzata UNA volta sola, prima che il programma parta */
    static long somma = 0;      /* static: NON sta nel record di attivazione sullo stack,
                                   ma nel segmento dati, come le globali: sopravvive al return */

    conteggio++;                /* alla 1ª chiamata diventa 1, alla 2ª diventa 2, ... */
    somma += x;
    return (double)somma / conteggio;   /* cast a double: altrimenti divisione intera (5/2 = 2) */
}

int main(void)
{
    int x;

    while (scanf("%d", &x) == 1)
        printf("valore %d -> media %.2f\n", x, media_corrente(x));
    return 0;
}
