/* =====================================================================
 * es07 — Cosa stampa? Chiamate annidate, locali omonime e stack
 * Tipo esame  ·  SOLUZIONE (il codice è identico allo starter:
 * l'esercizio è PREVEDERE l'output, la spiegazione è nel README)
 * Come testarlo: make sol T=07 E=es07
 * ===================================================================== */
#include <stdio.h>

int x = 1;            /* GLOBALE: sta nel segmento dati, vive per tutto il programma */

int g(int x);         /* prototipi */
int f(int y);

int main(void) {
    int y = 3;        /* locale di main: sta nel record di attivazione di main */
    int r;

    printf("main: x=%d y=%d\n", x, y);       /* x qui è la globale */
    r = f(y);                                /* passo una COPIA di y (3) */
    printf("main: x=%d y=%d r=%d\n", x, y, r);

    {                 /* blocco interno: una nuova x locale fa ombra alla globale */
        int x = 100;
        printf("blocco: x=%d\n", x);
    }                 /* qui la x = 100 smette di esistere */

    r = g(x);         /* fuori dal blocco x è di nuovo la globale (1) */
    printf("fine: x=%d r=%d\n", x, r);
    return 0;
}

int f(int y) {        /* y è il parametro formale: una copia, NON la y di main */
    int x = y + 2;    /* locale di f: fa ombra alla x globale */
    printf("f prima: x=%d y=%d\n", x, y);
    y = g(x);         /* cambio la MIA copia di y, non quella di main */
    printf("f dopo: x=%d y=%d\n", x, y);
    return x + y;
}

int g(int x) {        /* il parametro x fa ombra alla globale */
    int y = x * 10;
    x = x + 1;        /* modifica solo la copia dentro g */
    printf("g: x=%d y=%d\n", x, y);
    return y + x;
}
