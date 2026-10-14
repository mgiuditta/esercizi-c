/* =====================================================================
 * es07 — Cosa stampa? Chiamate annidate, locali omonime e stack
 * Tipo esame
 * NON eseguirlo subito. Leggi il codice, disegna lo stack a ogni
 * chiamata e scrivi su un foglio le 8 righe che secondo te stampa.
 * Poi lancia il test: il test confronta l'output vero con quello atteso
 * (tests/es07_stack_cosa_stampa.out). Apri quel file, o la soluzione
 * nel README, e confronta con la tua previsione.
 * Come testarlo: make test T=07 E=es07
 * ===================================================================== */
#include <stdio.h>

int x = 1;

int g(int x);
int f(int y);

int main(void) {
    int y = 3;
    int r;

    printf("main: x=%d y=%d\n", x, y);
    r = f(y);
    printf("main: x=%d y=%d r=%d\n", x, y, r);

    {
        int x = 100;
        printf("blocco: x=%d\n", x);
    }

    r = g(x);
    printf("fine: x=%d r=%d\n", x, r);
    return 0;
}

int f(int y) {
    int x = y + 2;
    printf("f prima: x=%d y=%d\n", x, y);
    y = g(x);
    printf("f dopo: x=%d y=%d\n", x, y);
    return x + y;
}

int g(int x) {
    int y = x * 10;
    x = x + 1;
    printf("g: x=%d y=%d\n", x, y);
    return y + x;
}
