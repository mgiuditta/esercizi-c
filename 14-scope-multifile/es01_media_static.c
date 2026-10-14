/*
 * es01 — Media "che ricorda" con variabili static locali  ·  Base
 * Ispirato a: Trascrizione 4.4 (static locale), Appunti Unità 4 par. 4.6 (contatore con static).
 *
 * Completa media_corrente(x): riceve UN valore alla volta e restituisce la media di
 * TUTTI i valori ricevuti finora. Il main non le passa né la somma né il conteggio:
 * la funzione deve ricordarseli da sola, con due variabili locali static.
 *   input 10 20 30  ->  medie 10.00, 15.00, 20.00
 *
 * Come testarlo: make test T=14 E=es01
 */
#include <stdio.h>

double media_corrente(int x)
{
    /* TODO: dichiara qui due variabili static (conteggio e somma), aggiornale
       e restituisci la media come double */
    (void)x;
    return 0.0;
}

int main(void)
{
    int x;

    while (scanf("%d", &x) == 1)
        printf("valore %d -> media %.2f\n", x, media_corrente(x));
    return 0;
}
