/*
 * es07 — Il puntatore al massimo e l'ordinamento per selezione  (Tipo esame)  — SOLUZIONE
 *
 * Testo:
 *  1) trova_max(v, n) restituisce un PUNTATORE all'elemento massimo dei primi
 *     n elementi (a parita', il primo che incontri).
 *  2) scambia(x, y) scambia due interi tramite i loro indirizzi.
 *  3) ordina(v, n) ordina in modo crescente cosi': cerca il massimo tra i
 *     primi n e lo scambia con l'ultimo; poi ripete sui primi n-1; ecc.
 *     (ordinamento per selezione, usando trova_max sui "sottovettori").
 * Il main stampa il massimo e il suo indice (differenza tra puntatori),
 * poi il vettore ordinato.
 *
 * Come testarlo: make sol T=09 E=es07
 */
#include <stdio.h>

#define MAX 100

int *trova_max(int *v, int n)
{
    int *pmax = v;        /* candidato: il primo elemento (n >= 1) */
    int *p;

    for (p = v + 1; p < v + n; p++)
        if (*p > *pmax)   /* > stretto: a parita' tengo il primo trovato */
            pmax = p;     /* ricordo DOVE sta il massimo, non solo quanto vale */
    return pmax;          /* indirizzo dentro il vettore del chiamante: e' valido
                             anche dopo il return, perche' il vettore vive nel main */
}

void scambia(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void ordina(int *v, int n)
{
    int k;
    /* k = quanti elementi sono ancora "da sistemare" (i primi k).
     * Ad ogni giro il massimo dei primi k va in fondo, in v[k-1],
     * e da li' non si muove piu'. */
    for (k = n; k > 1; k--) {
        int *pm = trova_max(v, k);  /* massimo del sottovettore v[0..k-1] */
        scambia(pm, v + k - 1);     /* v + k - 1 = indirizzo dell'ultimo dei k */
    }
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
    /* pm - v = di quanti ELEMENTI pm sta dopo l'inizio = indice */
    printf("massimo: %d (indice %d)\n", *pm, (int)(pm - v));

    ordina(v, n);
    printf("ordinato:");
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
    return 0;
}
