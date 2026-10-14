/*
 * es03 — Ricerca lineare e conteggio delle occorrenze  ·  Base
 *
 * Input:  n (da 1 a N_MAX), poi n interi, poi il valore x da cercare.
 * Output: "posizione: P" dove P è l'indice della PRIMA cella che contiene x
 *         (-1 se x non c'è), e "occorrenze: K" = quante celle contengono x.
 * Completa cerca e conta. Il main è già pronto.
 *
 * Come testarlo: make test T=05 E=es03
 */
#include <stdio.h>

#define N_MAX 100

/* Restituisce l'indice della prima cella uguale a x, oppure -1. */
int cerca(int v[], int n, int x)
{
    /* TODO */
    (void)v; (void)n; (void)x;
    return -1;
}

/* Restituisce quante celle di v sono uguali a x. */
int conta(int v[], int n, int x)
{
    /* TODO */
    (void)v; (void)n; (void)x;
    return 0;
}

int main(void)
{
    int v[N_MAX];
    int n, i, x;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &x);

    printf("posizione: %d\n", cerca(v, n, x));
    printf("occorrenze: %d\n", conta(v, n, x));
    return 0;
}
