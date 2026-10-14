/*
 * es06 — Contare le parole con un booleano simulato  (Intermedio)
 * Legge tutto l'input con getchar fino a EOF e stampa:
 *   parole=N vocali=V piu_lunga=L
 * Una parola e' una sequenza di caratteri diversi da spazio, tab e a capo.
 * Vocali: a e i o u, minuscole e maiuscole. piu_lunga = lunghezza della parola piu' lunga.
 * Come testarlo: make test T=04 E=es06
 */
#include <stdio.h>

/* TODO: definisci con typedef il tipo boolean (enum con FALSE e TRUE). */

int e_separatore(int c) {
    /* TODO: vero se c e' spazio, tab o a capo. Cambia il tipo restituito in boolean. */
    (void)c;
    return 0;
}

int e_vocale(int c) {
    /* TODO: usa uno switch con i case raggruppati. Cambia il tipo restituito in boolean. */
    (void)c;
    return 0;
}

int main(void) {
    int parole = 0, vocali = 0;
    int piu_lunga = 0;

    /* TODO: leggi con getchar fino a EOF; usa una variabile boolean "dentro"
             per sapere se sei dentro una parola. */

    printf("parole=%d vocali=%d piu_lunga=%d\n", parole, vocali, piu_lunga);
    return 0;
}
