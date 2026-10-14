/* =====================================================================
 * es03 — Fattoriale iterativo  ·  Base
 * Completa fattoriale(n): restituisce n! = 1 * 2 * ... * n, con 0! = 1,
 * usando un ciclo (niente ricorsione: la vedrai nel blocco 4).
 * Il tipo di ritorno è long long perché 20! ha 19 cifre.
 * Il main (già scritto) accetta solo n tra 0 e 20.
 * Input: n. Output: n! = risultato
 * Come testarlo: make test T=07 E=es03
 * ===================================================================== */
#include <stdio.h>

long long fattoriale(int n);

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("input non valido\n");
        return 1;
    }
    if (n < 0 || n > 20) {
        printf("n fuori intervallo (0..20)\n");
        return 0;
    }
    printf("%d! = %lld\n", n, fattoriale(n));
    return 0;
}

long long fattoriale(int n) {
    /* TODO: prodotto 1 * 2 * ... * n in una variabile long long */
    (void)n;   /* cancella questa riga */
    return 0;
}
