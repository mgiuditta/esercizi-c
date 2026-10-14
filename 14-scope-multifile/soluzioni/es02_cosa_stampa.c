/*
 * es02 — Cosa stampa? static locale, static globale, variabili che si nascondono
 * Ispirato a: Trascrizione 4.4 (static locale e globale), Trascrizione 3.1 (globale n
 * modificata da una funzione), Appunti Unità 4 par. 4.6-4.7.
 *
 * Questo file È GIÀ COMPLETO. L'esercizio è nel README:
 * prevedi l'output SENZA eseguire, poi lancia  make test T=14 E=es02
 */
#include <stdio.h>

int x = 100;                 /* globale: visibile in tutto il file (e da altri file con extern) */
static int chiamate_g = 0;   /* globale static: visibile SOLO in questo file */

void f(void)
{
    int a = 0;               /* automatica: ricreata (e rimessa a 0) a ogni chiamata */
    static int s = 0;        /* static: inizializzata una volta sola, poi ricorda */
    a++;
    s++;
    chiamate_g++;
    printf("f: a=%d s=%d\n", a, s);
}

void stampa_x(void)
{
    printf("stampa_x: x=%d\n", x);
}

void scendi(int n)
{
    static int livello = 0;  /* UNA sola variabile, condivisa da TUTTE le chiamate ricorsive */
    livello++;
    printf("scendi(%d): livello=%d\n", n, livello);
    if (n > 0)
        scendi(n - 1);
}

int main(void)
{
    int x = 1;               /* locale del main: NASCONDE la globale x dentro il main */

    f();
    f();
    f();
    printf("main: x=%d\n", x);
    {
        int x = 2;           /* blocco interno: nasconde a sua volta la x del main */
        printf("blocco: x=%d\n", x);
    }
    printf("main: x=%d\n", x);
    stampa_x();
    scendi(2);
    scendi(1);
    printf("chiamate_g=%d\n", chiamate_g);
    return 0;
}
