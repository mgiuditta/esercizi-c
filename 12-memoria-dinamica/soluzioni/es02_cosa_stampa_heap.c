/*
 * Esercizio 02 — Cosa stampa? calloc, sizeof, realloc e NULL  (Base)
 *
 * Questo file e' GIA' completo. L'esercizio e' nel README:
 * prevedi l'output di ogni riga (A-H), POI esegui il test.
 * Assumiamo sizeof(int) = 4, sizeof(double) = 8, sizeof(int *) = 8
 * (macOS arm64 e Linux x86-64).
 *
 * Come testarlo: make test T=12 E=es02
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {   /* la struct degli appunti, par. 1.4 */
    int a;
    double b;
} esempio;

int main(void)
{
    int v[10];
    int *p, *tmp, *q;
    int i;

    p = (int *) calloc(10, sizeof(int));
    if (p == NULL)
        return 1;

    /* A: sizeof di un vettore e sizeof di un puntatore */
    printf("A: %d %d\n", (int)sizeof(v), (int)sizeof(p));

    /* B: che cosa c'e' in un blocco appena creato con calloc? */
    printf("B: %d %d\n", p[0], p[9]);

    for (i = 0; i < 10; i++)
        p[i] = i * i;

    /* C: aritmetica dei puntatori su memoria dinamica */
    q = p + 3;
    printf("C: %d %d\n", *q, (int)(q - p));

    /* D: la stessa distanza, ma misurata in byte */
    printf("D: %d\n", (int)((char *)q - (char *)p));

    /* E: realloc ingrandisce il blocco: i vecchi valori restano? */
    tmp = (int *) realloc(p, 20 * sizeof(int));
    if (tmp == NULL) {
        free(p);
        return 1;
    }
    p = tmp;
    q = NULL;   /* q puntava al VECCHIO blocco: dopo realloc non si usa piu' */
    printf("E: %d %d\n", p[3], p[9]);

    /* F: NULL usato in una condizione */
    printf("F: %d %d\n", q == NULL, !q);

    /* G: dopo free + NULL */
    free(p);
    p = NULL;
    printf("G: %d\n", p ? 1 : 0);

    /* H: quanto e' grande la struct? */
    printf("H: %d %d\n", (int)(sizeof(int) + sizeof(double)), (int)sizeof(esempio));

    return 0;
}
