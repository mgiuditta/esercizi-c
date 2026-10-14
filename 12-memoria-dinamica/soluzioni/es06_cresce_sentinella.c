/*
 * Esercizio 06 — Un vettore che cresce con realloc fino alla sentinella  (Intermedio)
 *
 * Si leggono interi finche' arriva 0 (la "sentinella", cioe' il valore
 * che segnala la fine) oppure finisce l'input. Non sappiamo quanti saranno:
 * il vettore parte con capacita' 2 e, quando e' pieno, RADDOPPIA con realloc.
 *
 * Completa aggiungi(&v, &n, &cap, x):
 *   - se n == cap, raddoppia la capacita' con realloc (in modo SICURO,
 *     usando un puntatore temporaneo) e aggiorna *pv e *cap;
 *   - mette x in fondo e incrementa *n.
 *   Ritorna 1 se ha fatto una realloc, 0 se no, -1 se la realloc fallisce
 *   (in quel caso il vecchio vettore deve restare valido).
 *
 * Come testarlo: make test T=12 E=es06
 */
#include <stdio.h>
#include <stdlib.h>

int aggiungi(int **pv, int *n, int *cap, int x)
{
    int fatta = 0;

    if (*n == *cap) {
        int nuova = *cap * 2;
        /* MAI scrivere *pv = realloc(*pv, ...): se realloc fallisce restituisce
           NULL e perderemmo l'unico indirizzo del vecchio blocco (memory leak). */
        int *tmp = (int *) realloc(*pv, nuova * sizeof(int));
        if (tmp == NULL)
            return -1;      /* *pv e' ancora valido: il chiamante puo' liberarlo */
        *pv = tmp;          /* il blocco puo' essersi SPOSTATO: aggiorniamo il puntatore del chiamante */
        *cap = nuova;
        fatta = 1;
    }
    (*pv)[*n] = x;          /* (*pv) e' il vettore, [*n] la prima casella libera */
    (*n)++;
    return fatta;
}

int main(void)
{
    int *v;
    int n = 0, cap = 2, x, i, r, riallocazioni = 0;

    v = (int *) malloc(cap * sizeof(int));
    if (v == NULL)
        return 1;

    while (scanf("%d", &x) == 1 && x != 0) {
        r = aggiungi(&v, &n, &cap, x);
        if (r < 0) {
            printf("memoria esaurita\n");
            free(v);
            return 1;
        }
        riallocazioni += r;
    }

    if (n == 0) {
        printf("nessun numero\n");
    } else {
        printf("letti %d numeri, capacita' %d, riallocazioni %d\n", n, cap, riallocazioni);
        printf("al contrario:");
        for (i = n - 1; i >= 0; i--)
            printf(" %d", v[i]);
        printf("\n");
    }
    free(v);
    return 0;
}
