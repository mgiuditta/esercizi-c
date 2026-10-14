/*
 * Esercizio 01 — Un vettore la cui dimensione si decide durante l'esecuzione  (Base)
 *
 * Completa leggi_vettore(n): alloca con malloc un vettore di n interi,
 * controlla che l'allocazione sia riuscita, legge n interi con scanf e
 * restituisce il puntatore. Se l'allocazione fallisce o l'input finisce
 * prima, restituisce NULL (liberando cio' che aveva allocato).
 * Poi, nel main, libera la memoria con free.
 *
 * Input: n, poi n interi.
 * Output: la media (2 decimali) e i valori strettamente sopra la media.
 *
 * Come testarlo: make test T=12 E=es01
 */
#include <stdio.h>
#include <stdlib.h>   /* malloc, free: senza questo include il compilatore protesta */

int *leggi_vettore(int n)
{
    /* TODO:
       1. alloca con malloc lo spazio per n interi (usa sizeof)
       2. se malloc restituisce NULL, ritorna NULL
       3. leggi n interi con scanf; se una lettura fallisce, free e ritorna NULL
       4. ritorna il puntatore al vettore */
    (void)n;
    return NULL;
}

double media(const int *v, int n)
{
    long somma = 0;
    int i;
    for (i = 0; i < n; i++)
        somma += v[i];
    return (double)somma / n;
}

int main(void)
{
    int n, i;
    int *v;
    double m;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("nessun valore\n");
        return 0;
    }

    v = leggi_vettore(n);
    if (v == NULL) {
        printf("errore: allocazione o input non valido\n");
        return 1;
    }

    m = media(v, n);
    printf("media: %.2f\n", m);
    printf("sopra la media:");
    for (i = 0; i < n; i++)
        if (v[i] > m)
            printf(" %d", v[i]);
    printf("\n");

    /* TODO: libera la memoria allocata da leggi_vettore e metti v a NULL */
    return 0;
}
