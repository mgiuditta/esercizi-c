/*
 * 01 — es01: MCD con goto  (Base)
 *
 * Testo: completa la funzione mcd_goto traducendo "pari pari" in C lo
 * pseudocodice del prof (E-tivity 2.1), usando goto ed etichette:
 *
 *     1  read x
 *     2  read y
 *     3  r = x mod y
 *     4  if r = 0 then goto 8
 *     5  x = y
 *     6  y = r
 *     7  goto 3
 *     8  write y
 *
 * Le righe 1, 2 e 8 (lettura e stampa) sono gia' nel main.
 * Tu scrivi le righe 3-7 dentro mcd_goto. Si assume x > 0 e y > 0.
 *
 * Come testarlo: make test T=01 E=es01
 */
#include <stdio.h>

int mcd_goto(int x, int y)
{
    int r = 0;

    /* TODO: metti un'etichetta "modulo:" davanti al calcolo del resto
       e un'etichetta "risultato:" davanti al return finale.
       Poi traduci le righe 3-7 con if e goto. */
    (void)x;
    (void)r;

    return y; /* TODO: valore provvisorio (giusto solo per caso) */
}

int main(void)
{
    int x = 0;
    int y = 0;

    if (scanf("%d %d", &x, &y) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    printf("MCD(%d, %d) = %d\n", x, y, mcd_goto(x, y));
    return 0;
}
