/* =====================================================================
 * es03 — Fattoriale iterativo  ·  Base  ·  SOLUZIONE
 * Scrivi fattoriale(n) = 1 * 2 * ... * n (con 0! = 1) usando un ciclo.
 * Il risultato è un long long perché cresce in fretta (20! ha 19 cifre).
 * Come testarlo: make sol T=07 E=es03
 * ===================================================================== */
#include <stdio.h>

long long fattoriale(int n);   /* prototipo: restituisce un long long */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("input non valido\n");
        return 1;
    }
    /* 21! supera il massimo di un long long (circa 9.2 * 10^18):
     * il calcolo andrebbe in overflow (comportamento indefinito per
     * gli interi con segno). Quindi accetto solo 0..20. */
    if (n < 0 || n > 20) {
        printf("n fuori intervallo (0..20)\n");
        return 0;
    }
    /* %lld è il segnaposto di printf per i long long */
    printf("%d! = %lld\n", n, fattoriale(n));
    return 0;
}

long long fattoriale(int n) {
    long long f = 1;   /* 0! = 1 e 1! = 1: il ciclo sotto non gira */
    int i;
    for (i = 2; i <= n; i++)
        f = f * i;     /* i viene convertito a long long prima del prodotto */
    return f;
}
