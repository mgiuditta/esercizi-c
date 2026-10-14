/*
 * es06 — Ordinamento per selezione (selection sort), passo per passo  (SOLUZIONE)
 *
 * Input:  n (da 1 a N_MAX), poi n interi.
 * Output: il vettore dopo ogni "passata" dell'algoritmo, poi il risultato.
 *
 * Come testarlo: make sol T=05 E=es06
 */
#include <stdio.h>

#define N_MAX 100

void stampa(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}

/* Selection sort, idea in una frase: alla passata p cerchiamo il
 * MINIMO tra le celle p .. n-1 e lo portiamo in posizione p.
 * Dopo la passata p, le celle 0 .. p sono già ordinate e non si
 * toccano più (come quando metti in fila delle carte scegliendo ogni
 * volta la più piccola tra quelle rimaste). */
void ordina(int v[], int n)
{
    int p, i, pos_min, tmp;
    /* Bastano n-1 passate: quando restano n-1 celle sistemate,
     * l'ultima è per forza la più grande ed è già al suo posto. */
    for (p = 0; p < n - 1; p++) {
        pos_min = p;                       /* ricordiamo la POSIZIONE, non il valore:
                                              ci serve per lo scambio */
        for (i = p + 1; i < n; i++)
            if (v[i] < v[pos_min])
                pos_min = i;
        /* scambio v[p] <-> v[pos_min] con variabile d'appoggio */
        tmp = v[p];
        v[p] = v[pos_min];
        v[pos_min] = tmp;

        printf("passata %d:", p + 1);
        stampa(v, n);
    }
}

int main(void)
{
    int v[N_MAX];
    int n, i;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    ordina(v, n);
    printf("ordinato:");
    stampa(v, n);
    return 0;
}
