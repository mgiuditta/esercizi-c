/* =====================================================================
 * es01 — Massimo di due e di tre numeri  ·  Base
 * Completa max2(a, b), che restituisce il maggiore tra a e b, e
 * max3(a, b, c), che restituisce il maggiore dei tre USANDO max2
 * (senza riscrivere i confronti).
 * Input: tre interi. Output:
 *   max2(a, b) = ...
 *   max3(a, b, c) = ...
 * Come testarlo: make test T=07 E=es01
 * ===================================================================== */
#include <stdio.h>

/* prototipi: dicono al compilatore che queste funzioni esistono */
int max2(int a, int b);
int max3(int a, int b, int c);

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("input non valido\n");
        return 1;
    }
    printf("max2(%d, %d) = %d\n", a, b, max2(a, b));
    printf("max3(%d, %d, %d) = %d\n", a, b, c, max3(a, b, c));
    return 0;
}

int max2(int a, int b) {
    /* TODO: restituisci il maggiore tra a e b */
    (void)a; (void)b;   /* zittisce l'avviso "parametro non usato": cancella questa riga */
    return 0;
}

int max3(int a, int b, int c) {
    /* TODO: restituisci il maggiore dei tre chiamando max2 (due volte) */
    (void)a; (void)b; (void)c;   /* cancella questa riga */
    return 0;
}
