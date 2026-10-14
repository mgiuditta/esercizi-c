/*
 * es04 — Inverti un tratto del vettore "sul posto"  ·  Intermedio
 *
 * Input:  n (da 1 a N_MAX), n interi, poi due indici a e b.
 * Output: il vettore dopo aver invertito SOLO gli elementi da v[a] a v[b]
 *         (estremi compresi), senza usare un secondo vettore.
 *         Se gli indici non sono validi stampa "intervallo non valido".
 * Esempio: 10 20 30 40 50 60 70 con a=1, b=4  ->  10 50 40 30 20 60 70
 *
 * Come testarlo: make test T=05 E=es04
 */
#include <stdio.h>

#define N_MAX 100

/* Inverte v[a], v[a+1], ..., v[b] direttamente dentro v. */
void inverti_tratto(int v[], int a, int b)
{
    /* TODO: due indici che si vengono incontro + scambio con variabile d'appoggio */
    (void)v; (void)a; (void)b;
}

int main(void)
{
    int v[N_MAX];
    int n, i, a, b;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("intervallo non valido\n");
        return 1;
    }

    /* TODO: se a e b non sono indici validi (0 <= a <= b <= n-1)
     *       stampa "intervallo non valido" e termina con return 1. */

    inverti_tratto(v, a, b);

    for (i = 0; i < n; i++)
        printf("%d%s", v[i], i < n - 1 ? " " : "\n");
    return 0;
}
