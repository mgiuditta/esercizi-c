/*
 * es02 — Cosa stampa?
 *
 * Non devi scrivere codice: leggi il programma e, SENZA eseguirlo,
 * scrivi la tua previsione delle righe A..G (sul README o su un foglio).
 * Poi esegui il test: se passa, il programma stampa esattamente
 * quello che c'è in tests/es02_cosa_stampa.out. Confronta con la tua previsione.
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
    int v[N] = {4, 8, 15};
    int m[R][C] = {{1, 2, 3}, {4, 5, 6}};
    int i = 0, j, s = 0, cont = 0;

    printf("A: %zu %zu\n", sizeof(v), sizeof(v) / sizeof(v[0]));

    printf("B: %d %d\n", v[3], v[N - 3]);

    while (i < N)
        s = s + v[i++];
    printf("C: %d %d\n", s, i);

    v[1] = v[0] + v[2];
    v[v[0] - 4] = 7;
    printf("D: %d %d %d\n", v[0], v[1], v[2]);

    printf("E: %zu %zu\n", sizeof(m), sizeof(m[0]) / sizeof(m[0][0]));

    s = 0;
    for (i = 0; i < R; i++)
        s = s + m[i][C - 1 - i];
    printf("F: %d\n", s);

    for (i = 0; i < R; i++)
        for (j = 0; j < C; j++)
            if (m[i][j] % 2 == 0)
                cont++;
    printf("G: %d\n", cont);

    /* La tua previsione:
     * A:
     * B:
     * C:
     * D:
     * E:
     * F:
     * G:
     */
    return 0;
}
