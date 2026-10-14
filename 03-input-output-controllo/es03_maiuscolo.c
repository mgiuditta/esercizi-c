/*
 * es03 — Copia in MAIUSCOLO con getchar/putchar fino a EOF  (Base)
 * Ricopia l'input in output trasformando le minuscole in maiuscole.
 * Alla fine stampa:
 *   --
 *   caratteri=N righe=R cifre=C
 * (un "carattere" e' qualunque cosa letta, compresi spazi e '\n';
 *  una "riga" e' un '\n'; una "cifra" e' un carattere fra '0' e '9').
 * Vietato usare toupper: fai il conto con i codici dei caratteri.
 * Come testarlo: make test T=03 E=es03
 */
#include <stdio.h>

int main(void) {
    int c = 0;
    int caratteri = 0;
    int righe = 0;
    int cifre = 0;

    /* TODO: ciclo while che legge con getchar() finche' non arriva EOF.
             Dentro: aggiorna i contatori, converti le minuscole, e ristampa con putchar. */
    (void)c;

    printf("--\n");
    printf("caratteri=%d righe=%d cifre=%d\n", caratteri, righe, cifre);
    return 0;
}
