/*
 * es01 — Somma, media, massimo e minimo di un vettore  ·  Base
 *
 * Input:  n (da 1 a N_MAX), poi n numeri interi.
 * Output: somma, media (2 decimali), massimo e minimo.
 * Completa le tre funzioni somma, massimo, minimo. Il main è già pronto.
 *
 * Come testarlo: make test T=05 E=es01
 */
#include <stdio.h>

#define N_MAX 100

/* Restituisce la somma di v[0] + v[1] + ... + v[n-1]. */
int somma(int v[], int n)
{
    /* TODO: scorri il vettore con un for e accumula la somma */
    (void)v; (void)n;   /* serve solo a zittire i warning: toglilo quando scrivi il codice */
    return 0;
}

/* Restituisce il valore più grande tra v[0] .. v[n-1]. */
int massimo(int v[], int n)
{
    /* TODO: attenzione al valore di partenza (pensa a un vettore di soli negativi) */
    (void)v; (void)n;
    return 0;
}

/* Restituisce il valore più piccolo tra v[0] .. v[n-1]. */
int minimo(int v[], int n)
{
    /* TODO */
    (void)v; (void)n;
    return 0;
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

    printf("somma: %d\n", somma(v, n));
    printf("media: %.2f\n", (double)somma(v, n) / n);
    printf("massimo: %d\n", massimo(v, n));
    printf("minimo: %d\n", minimo(v, n));
    return 0;
}
