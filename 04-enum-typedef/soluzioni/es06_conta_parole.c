/*
 * es06 — Contare le parole con un booleano simulato  (Intermedio)
 * Legge tutto l'input con getchar fino a EOF e stampa:
 *   parole=N vocali=V piu_lunga=L
 * Una parola e' una sequenza di caratteri diversi da spazio, tab e a capo.
 * Come testarlo: make test T=04 E=es06
 */
#include <stdio.h>

/* Booleano simulato del prof: FALSE=0, TRUE=1. */
typedef enum {FALSE, TRUE} boolean;

boolean e_separatore(int c) {
    /* L'espressione logica vale gia' 0 o 1: coincide con FALSE/TRUE. */
    return c == ' ' || c == '\t' || c == '\n';
}

boolean e_vocale(int c) {
    switch (c) {
    case 'a': case 'e': case 'i': case 'o': case 'u':   /* raggruppamento di case */
    case 'A': case 'E': case 'I': case 'O': case 'U':
        return TRUE;
    default:
        return FALSE;
    }
}

int main(void) {
    int c;
    int parole = 0, vocali = 0;
    int lung = 0, piu_lunga = 0;
    /* Il "flag" che ricorda se siamo dentro una parola. Con il tipo boolean
       il codice dice chiaramente che puo' valere solo vero o falso. */
    boolean dentro = FALSE;

    while ((c = getchar()) != EOF) {
        if (e_separatore(c)) {
            dentro = FALSE;              /* una parola (se c'era) e' finita */
            lung = 0;
        } else {
            if (!dentro) {               /* passaggio separatore -> carattere: */
                dentro = TRUE;           /* inizia una NUOVA parola */
                parole++;
            }
            lung++;
            if (lung > piu_lunga)
                piu_lunga = lung;
            if (e_vocale(c))
                vocali++;
        }
    }
    printf("parole=%d vocali=%d piu_lunga=%d\n", parole, vocali, piu_lunga);
    return 0;
}
