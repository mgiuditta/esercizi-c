/* =====================================================================
 * es05 — Cosa stampa? Macro contro funzioni  ·  Intermedio
 * NON eseguirlo subito. Per ogni macro, scrivi a mano il testo che il
 * preprocessore produce (sostituzione testuale!), poi calcolalo.
 * Scrivi le 8 righe previste, poi lancia il test e confronta con
 * tests/es05_macro_cosa_stampa.out (o con la soluzione nel README).
 * Per vedere l'espansione vera:  cc -E es05_macro_cosa_stampa.c | tail -30
 * Come testarlo: make test T=08 E=es05
 * ===================================================================== */
#include <stdio.h>

#define MOLTIPLICA(a, b) a * b
#define MUL(a, b) ((a) * (b))
#define QUADRATO(x) x * x
#define QUAD_OK(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int massimo(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int a = 4, b = 3, c = 1;
    int i, j = 4, m;

    printf("1) %d\n", MOLTIPLICA(a - c, b));
    printf("2) %d\n", MUL(a - c, b));
    printf("3) %d\n", QUADRATO(a + 1));
    printf("4) %d\n", 100 / QUADRATO(2));
    printf("5) %d\n", 100 / QUAD_OK(2));

    i = 2;
    m = MAX(i++, j);
    printf("6) m=%d i=%d\n", m, i);

    i = 7;
    m = MAX(i++, j);
    printf("7) m=%d i=%d\n", m, i);

    i = 7;
    m = massimo(i++, j);
    printf("8) m=%d i=%d\n", m, i);
    return 0;
}
