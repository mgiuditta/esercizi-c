/*
 * es07 — Il puntatore al massimo e l'ordinamento per selezione  (Tipo esame)
 *
 * Testo:
 *  1) trova_max(v, n) restituisce un PUNTATORE all'elemento massimo dei primi
 *     n elementi (a parita', il primo che incontri). n >= 1.
 *  2) scambia(x, y) scambia due interi tramite i loro indirizzi.
 *  3) ordina(v, n) ordina in modo crescente cosi': cerca il massimo tra i
 *     primi n e lo scambia con l'ultimo; poi ripete sui primi n-1; ecc.
 *     (ordinamento per selezione, usando trova_max sui "sottovettori").
 * Il main (gia' scritto) stampa il massimo e il suo indice (differenza tra
 * puntatori), poi il vettore ordinato.
 *
 * Input:  n, poi n interi.     Esempio: 6  4 7 1 9 3 9
 * Output: massimo: 9 (indice 3)
 *         ordinato: 1 3 4 7 9 9
 *
 * Come testarlo: make test T=09 E=es07
 */
#include <stdio.h>

#define MAX 100

int *trova_max(int *v, int n)
{
    /* TODO: parti con pmax = v, scorri con un puntatore da v + 1 a v + n
       (escluso) e aggiorna pmax quando trovi un valore STRETTAMENTE maggiore. */
    (void)n;   /* cancella questa riga */
    return v;  /* provvisorio */
}

void scambia(int *x, int *y)
{
    /* TODO */
    (void)x; (void)y;   /* cancella questa riga */
}

void ordina(int *v, int n)
{
    /* TODO: per k che va da n giu' fino a 2:
       prendi il puntatore al massimo dei primi k e scambialo con v + k - 1 */
    (void)v; (void)n;   /* cancella questa riga */
}

int main(void)
{
    int v[MAX];
    int n, i;
    int *pm;

    if (scanf("%d", &n) != 1 || n > MAX)
        return 1;
    if (n < 1) {
        printf("vettore vuoto\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    pm = trova_max(v, n);
    printf("massimo: %d (indice %d)\n", *pm, (int)(pm - v));

    ordina(v, n);
    printf("ordinato:");
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
    return 0;
}
