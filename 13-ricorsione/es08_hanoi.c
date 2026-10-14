/*
 * es08 — Torre di Hanoi con numero del disco e conteggio delle mosse  ·  Tipo esame
 * Ispirato a: Appunti Unità 4, par. 2.12 (funzione hanoi(n, s, d, a) e muoviDisco).
 *
 * Input: numero di dischi n (1..10). Paletti numerati 1, 2, 3: sposta tutto da 1 a 3.
 * Ogni mossa va stampata così:   mossa K: disco D da S a T
 * (il disco 1 è il più piccolo). Alla fine:
 *   Totale mosse: M (2^n - 1 = ...)
 * Le mosse si contano con un PUNTATORE al contatore del main.
 *
 * Come testarlo: make test T=13 E=es08
 */
#include <stdio.h>

void muoviDisco(int disco, int s, int d, int *mosse)
{
    /* TODO: incrementa il contatore puntato da mosse e stampa la mossa */
    (void)disco;
    (void)s;
    (void)d;
    (void)mosse;
}

void hanoi(int n, int s, int d, int a, int *mosse)
{
    /* TODO: caso base n == 1; altrimenti i tre passi degli appunti */
    (void)n;
    (void)s;
    (void)d;
    (void)a;
    (void)mosse;
}

int potenza(int i, int n)
{
    /* TODO: copia la tua potenza ricorsiva di es01 */
    (void)i;
    (void)n;
    return 0;
}

int main(void)
{
    int n, mosse = 0;

    if (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        printf("Numero di dischi non valido (1..10)\n");
        return 0;
    }
    hanoi(n, 1, 3, 2, &mosse);
    printf("Totale mosse: %d (2^%d - 1 = %d)\n", mosse, n, potenza(2, n) - 1);
    return 0;
}
