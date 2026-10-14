/*
 * es06 — Cosa stampa? Puntatori, static, ricorsione e macro  (Tipo esame)
 *
 * Questo programma e' GIA' COMPLETO. L'esercizio e' nel README:
 * senza eseguirlo, scrivi su carta le 22 righe che stampa (da A a L, piu' le righe di giu e su).
 * Poi lancia il test: se passa, il programma e' corretto (lo e' sempre);
 * confronta il TUO foglio con il file tests/es06_cosa_stampa.out.
 *
 * Nota: sizeof di un vettore di char conta i byte, e un char occupa sempre 1 byte.
 *
 * Come testarlo: make test T=15 E=es06
 */
#include <stdio.h>

#define DOPPIO(x) x + x                       /* senza parentesi: attenzione! */
#define QUADRATO(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int prossimo(void)
{
    static int c = 0;
    return ++c;
}

int giu(int n, int *acc)
{
    static int profondita = 0;
    int r;

    profondita++;
    printf("giu(%d) profondita=%d\n", n, profondita);
    if (n <= 0) {
        r = *acc;
    } else {
        *acc += n;
        r = giu(n - 2, acc) + 1;
    }
    profondita--;
    printf("su(%d) r=%d\n", n, r);
    return r;
}

void sposta(int **pp, int k)
{
    *pp += k;
}

int main(void)
{
    int v[] = {10, 20, 30, 40, 50};
    int *p = v, *q = &v[4];
    int i = 3, j = 4, m, acc = 0;
    char s[] = "esame";
    char *c = s;

    printf("A: %d\n", 3 * DOPPIO(2));
    printf("B: %d\n", QUADRATO(1 + 2));
    m = MAX(i++, j);
    printf("C: m=%d i=%d\n", m, i);
    m = MAX(i++, j - 1);
    printf("D: m=%d i=%d\n", m, i);

    printf("E: %d %d\n", *p + 1, *(p + 1));
    sposta(&p, 2);
    printf("F: %d %d\n", *p, (int)(q - p));
    *p++ = 99;
    printf("G: %d %d %d\n", v[2], *p, p[-1]);

    printf("H: %c %c %s\n", *c, *(c + 2), c + 3);
    c[0] = 'E';
    printf("I: %s %d\n", s, (int) sizeof s);

    prossimo();
    prossimo();
    printf("J: %d\n", prossimo());

    m = giu(5, &acc);
    printf("K: m=%d acc=%d\n", m, acc);
    m = giu(0, &acc);
    printf("L: m=%d\n", m);
    return 0;
}
