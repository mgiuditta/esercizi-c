/* =====================================================================
 * es01 — Cosa stampa? Una variabile n, cinque scope  ·  Base
 * NON eseguirlo subito. Per ogni printf chiediti: QUALE n è visibile in
 * quel punto (globale, locale, parametro, blocco, for)? Scrivi su un
 * foglio le 10 righe che prevedi, poi lancia il test e confronta con
 * tests/es01_scope_cosa_stampa.out (o con la soluzione nel README).
 * Come testarlo: make test T=08 E=es01
 * ===================================================================== */
#include <stdio.h>

int n = 10;

void stampa_n(void);
void azzera(void);
void incrementa(int n);

int main(void) {
    printf("A: n=%d\n", n);
    azzera();
    stampa_n();
    incrementa(n);
    printf("B: n=%d\n", n);
    {
        int n = 3;
        printf("C: n=%d\n", n);
        stampa_n();
        n++;
    }
    for (int n = 0; n < 2; n++)
        printf("D: n=%d\n", n);
    n = n * 2;
    stampa_n();
    return 0;
}

void stampa_n(void) {
    printf("stampa_n: n=%d\n", n);
}

void azzera(void) {
    int n = 0;
    n++;
    printf("azzera: n=%d\n", n);
}

void incrementa(int n) {
    n = n + 5;
    printf("incrementa: n=%d\n", n);
}
