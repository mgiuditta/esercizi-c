/*
 * es07 — Vettore ricorsivo: somma, massimo e ricerca binaria tracciata  ·  Tipo esame
 * Ispirato a: Trascrizione 4.2 e Appunti Unità 4 par. 2.10 (iterazione e ricorsione).
 *
 * Input: n (1..100), poi n interi ORDINATI in modo crescente, poi un numero qualsiasi
 * di valori da cercare. Implementa SENZA cicli:
 *   somma(v, n)          somma dei primi n elementi
 *   massimo(v, n)        massimo dei primi n elementi (n >= 1)
 *   cerca(v, sx, dx, x)  ricerca binaria in v[sx..dx]: stampa "[sx,dx] " a ogni chiamata
 *                        su un intervallo NON vuoto; restituisce la posizione o -1.
 * Esempio: v = 1 3 4 7 9 11 15 20, cerco 8 -> "[0,7] [4,7] [4,4] -> non presente"
 *
 * Come testarlo: make test T=13 E=es07
 */
#include <stdio.h>

#define MAX 100

int somma(int v[], int n)
{
    /* TODO */
    (void)v;
    (void)n;
    return 0;
}

int massimo(int v[], int n)
{
    /* TODO */
    (void)v;
    (void)n;
    return 0;
}

int cerca(int v[], int sx, int dx, int x)
{
    /* TODO: caso base intervallo vuoto (sx > dx) -> -1; poi stampa "[sx,dx] ",
       calcola il centro e decidi se hai trovato o in quale metà richiamarti */
    (void)v;
    (void)sx;
    (void)dx;
    (void)x;
    return -1;
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
