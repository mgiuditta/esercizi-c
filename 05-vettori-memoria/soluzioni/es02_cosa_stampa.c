/*
 * es02 — Cosa stampa?  (SOLUZIONE: stesso codice dello starter, con commenti)
 *
 * Non devi scrivere codice: leggi il programma, scrivi nel README
 * la tua previsione riga per riga (A, B, C, ...), poi esegui il test.
 * Ipotesi: sizeof(int) = 4 (vero su macOS arm64 e Linux x86-64).
 *
 * Come testarlo: make test T=05 E=es02
 */
#include <stdio.h>

#define N 5
#define R 2
#define C 3

int main(void)
{
    int v[N] = {4, 8, 15};               /* le celle non scritte valgono 0 */
    int m[R][C] = {{1, 2, 3}, {4, 5, 6}};
    int i = 0, j, s = 0, cont = 0;

    /* A: sizeof di un vettore = numero elementi * sizeof(int) */
    printf("A: %zu %zu\n", sizeof(v), sizeof(v) / sizeof(v[0]));

    /* B: v[3] non è stato inizializzato esplicitamente; N - 3 vale 2 */
    printf("B: %d %d\n", v[3], v[N - 3]);

    /* C: il ciclo del prof con i++ DENTRO le quadre */
    while (i < N)
        s = s + v[i++];
    printf("C: %d %d\n", s, i);

    /* D: un elemento di vettore può stare a sinistra di = */
    v[1] = v[0] + v[2];
    v[v[0] - 4] = 7;
    printf("D: %d %d %d\n", v[0], v[1], v[2]);

    /* E: sizeof di una matrice e di una sua riga */
    printf("E: %zu %zu\n", sizeof(m), sizeof(m[0]) / sizeof(m[0][0]));

    /* F: una "diagonale" particolare */
    s = 0;
    for (i = 0; i < R; i++)
        s = s + m[i][C - 1 - i];
    printf("F: %d\n", s);

    /* G: conteggio con doppio ciclo */
    for (i = 0; i < R; i++)
        for (j = 0; j < C; j++)
            if (m[i][j] % 2 == 0)
                cont++;
    printf("G: %d\n", cont);

    return 0;
}
