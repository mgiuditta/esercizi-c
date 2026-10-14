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
    int *v;
    int i;

    /* n * sizeof(int) byte: sizeof rende il codice indipendente dal sistema.
       Il cast (int *) non e' obbligatorio in C, ma il prof lo scrive sempre. */
    v = (int *) malloc(n * sizeof(int));
    if (v == NULL)          /* la memoria potrebbe non bastare: si controlla SEMPRE */
        return NULL;

    for (i = 0; i < n; i++) {
        if (scanf("%d", &v[i]) != 1) {   /* v[i] e' identico a *(v + i) */
            free(v);        /* prima di arrenderci restituiamo la memoria */
            return NULL;
        }
    }
    return v;   /* il blocco vive nello heap: resta valido anche dopo il return */
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

    free(v);      /* ogni malloc deve avere la sua free */
    v = NULL;     /* buona pratica: v non punta piu' a memoria valida */
    return 0;
}
