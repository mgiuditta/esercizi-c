/*
 * es07 — Vettore ricorsivo: somma, massimo e ricerca binaria tracciata  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.2 (iterazione per strutture statiche, ricorsione come
 * alternativa), Appunti Unità 4 par. 2.10; variante degli esercizi 4 e 9 di LEZ 20.
 */
#include <stdio.h>

#define MAX 100

/* Somma dei primi n elementi: l'ultimo elemento + la somma dei primi n-1. */
int somma(int v[], int n)
{
    if (n == 0)                         /* caso base: vettore vuoto, somma 0 */
        return 0;
    return v[n - 1] + somma(v, n - 1);  /* il "pezzo" di vettore si accorcia di 1 */
}

/* Massimo dei primi n elementi (n >= 1). */
int massimo(int v[], int n)
{
    int m;

    if (n == 1)                         /* caso base: un solo elemento, è lui il massimo */
        return v[0];
    m = massimo(v, n - 1);              /* massimo dei primi n-1 */
    return v[n - 1] > m ? v[n - 1] : m; /* confronto con l'ultimo */
}

/* Ricerca binaria ricorsiva in v[sx..dx] (v ORDINATO in modo crescente).
 * Stampa l'intervallo visitato a ogni chiamata, così si vede il problema che si dimezza. */
int cerca(int v[], int sx, int dx, int x)
{
    int med;

    if (sx > dx)                        /* caso base 1: intervallo vuoto -> non c'è */
        return -1;
    printf("[%d,%d] ", sx, dx);
    med = (sx + dx) / 2;                /* elemento centrale */
    if (v[med] == x)                    /* caso base 2: trovato */
        return med;
    if (x < v[med])                     /* x può stare solo nella metà sinistra */
        return cerca(v, sx, med - 1, x);
    return cerca(v, med + 1, dx, x);    /* altrimenti nella metà destra */
}

int main(void)
{
    int v[MAX], n, i, x, pos;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    printf("somma = %d\n", somma(v, n));
    printf("massimo = %d\n", massimo(v, n));

    while (scanf("%d", &x) == 1) {
        printf("cerco %d: ", x);
        pos = cerca(v, 0, n - 1, x);
        if (pos >= 0)
            printf("-> trovato in posizione %d\n", pos);
        else
            printf("-> non presente\n");
    }
    return 0;
}
