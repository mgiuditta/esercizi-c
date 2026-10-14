/*
 * es01 — Somma di un pezzo di vettore con un puntatore  (Base)
 *
 * Testo: implementa somma(p, n), che somma gli n interi che partono
 * dall'indirizzo p, scorrendoli con un PUNTATORE (niente indice i, niente p[i]).
 * Il main (gia' scritto) la usa tre volte: sul vettore intero, sulla prima
 * meta' e sulla seconda meta' (come nell'esempio del prof con p = v + n/2).
 *
 * Input:  n, poi n interi.     Esempio: 5  1 2 3 4 5
 * Output: totale: 15 / prima meta': 3 / seconda meta': 12
 *
 * Come testarlo: make test T=09 E=es01
 */
#include <stdio.h>

#define MAX 100

int somma(const int *p, int n)
{
    /* TODO: dichiara un puntatore q, fallo partire da p e fallo avanzare
       finche' e' prima di p + n, accumulando *q. Niente indici! */
    (void)p;   /* queste due righe evitano l'avviso "parametro non usato": */
    (void)n;   /* cancellale quando scrivi la tua soluzione */
    return 0;
}

int main(void)
{
    int v[MAX];
    int n, i;
    int *p;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    printf("totale: %d\n", somma(v, n));
    printf("prima meta': %d\n", somma(v, n / 2));

    p = v + n / 2;   /* p punta a meta' vettore */
    printf("seconda meta': %d\n", somma(p, n - n / 2));
    return 0;
}
