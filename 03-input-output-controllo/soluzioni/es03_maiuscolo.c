/*
 * es03 — Copia in MAIUSCOLO con getchar/putchar fino a EOF  (Base)
 * Legge l'input un carattere alla volta, lo ricopia in output trasformando
 * le lettere minuscole in maiuscole, e alla fine stampa quanti caratteri,
 * righe e cifre ha letto.
 * Come testarlo: make test T=03 E=es03
 */
#include <stdio.h>

int main(void) {
    int c;              /* int e NON char: getchar deve poter restituire anche EOF,
                           che non e' un carattere valido (di solito vale -1). */
    int caratteri = 0;  /* contatori: vanno inizializzati a 0, altrimenti */
    int righe = 0;      /* conterrebbero un valore casuale ("spazzatura"). */
    int cifre = 0;

    /* (c = getchar()) prima assegna, poi il valore dell'assegnamento viene
       confrontato con EOF. Le parentesi sono obbligatorie: senza, != ha
       precedenza su = e c riceverebbe 0 o 1. */
    while ((c = getchar()) != EOF) {
        caratteri++;
        if (c == '\n') {
            righe++;                    /* ogni a capo chiude una riga */
        } else if (c >= '0' && c <= '9') {
            cifre++;                    /* le cifre '0'..'9' sono consecutive nella tabella ASCII */
        } else if (c >= 'a' && c <= 'z') {
            /* Anche le lettere sono consecutive: 'a'->'A' e' uno spostamento fisso.
               c - 'a' = posizione della lettera (0 per 'a'), + 'A' = stessa posizione fra le maiuscole. */
            c = c - 'a' + 'A';
        }
        putchar(c);                     /* ricopia il carattere (eventualmente trasformato) */
    }

    printf("--\n");
    printf("caratteri=%d righe=%d cifre=%d\n", caratteri, righe, cifre);
    return 0;
}
