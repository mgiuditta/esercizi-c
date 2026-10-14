/*
 * Esercizio 02 — Somma delle diagonali con l'aritmetica dei puntatori  (Base)
 *
 * Completa le due funzioni usando SOLO l'aritmetica dei puntatori,
 * cioe' la forma *(*(m + i) + j) vista nella E-tivity MatriciePuntatori.
 * Vietato scrivere m[i][j] dentro le funzioni.
 *
 * Input: n (1..10), poi n*n interi riga per riga.
 * Output: "principale = S1" e "secondaria = S2".
 *
 * Come testarlo: make test T=11 E=es02
 */
#include <stdio.h>

#define N 10 /* numero MASSIMO di colonne: serve al compilatore (vedi README) */

/* Somma degli elementi m[0][0], m[1][1], ..., m[n-1][n-1]. */
int somma_principale(int (*m)[N], int n)
{
    /* TODO: somma gli elementi della diagonale principale
             usando *(*(m + i) + ...) */
    (void)m; (void)n; /* toglie l'avviso "parametro non usato": cancellalo */
    return 0;
}

/* Somma degli elementi m[0][n-1], m[1][n-2], ..., m[n-1][0]. */
int somma_secondaria(int (*m)[N], int n)
{
    /* TODO: somma gli elementi della diagonale secondaria
             (riga i, colonna n - 1 - i) con l'aritmetica dei puntatori */
    (void)m; (void)n; /* toglie l'avviso "parametro non usato": cancellalo */
    return 0;
}

int main(void)
{
    int mat[N][N];
    int n, i, j;

    if (scanf("%d", &n) != 1 || n < 1 || n > N) {
        printf("dimensione non valida\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (scanf("%d", &mat[i][j]) != 1) {
                printf("input incompleto\n");
                return 1;
            }

    /* mat "decade" a int (*)[N]: puntatore alla prima riga */
    printf("principale = %d\n", somma_principale(mat, n));
    printf("secondaria = %d\n", somma_secondaria(mat, n));
    return 0;
}
