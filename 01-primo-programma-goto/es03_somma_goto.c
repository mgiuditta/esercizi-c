/*
 * 01 — es03: somma dei primi N numeri con goto  (Base)
 *
 * Testo: completa somma_primi_goto(n), che restituisce 1 + 2 + ... + n
 * (0 se n <= 0), traducendo con goto ed etichette questo pseudocodice:
 *
 *     1  s = 0
 *     2  i = 1
 *     3  if i > n then goto 7
 *     4  s = s + i
 *     5  i = i + 1
 *     6  goto 3
 *     7  write s
 *
 * Esempio: n = 5  ->  "Somma da 1 a 5 = 15"
 *
 * Come testarlo: make test T=01 E=es03
 */
#include <stdio.h>

int somma_primi_goto(int n)
{
    int s = 0;
    int i = 1;

    /* TODO: traduci le righe 3-7 con un'etichetta "controllo:",
       un'etichetta "fine:" e due goto. */
    (void)n;
    (void)i;

    return s; /* TODO: per ora restituisce sempre 0 */
}

int main(void)
{
    int n = 0;

    if (scanf("%d", &n) != 1) {
        printf("Input non valido\n");
        return 1;
    }
    printf("Somma da 1 a %d = %d\n", n, somma_primi_goto(n));
    return 0;
}
