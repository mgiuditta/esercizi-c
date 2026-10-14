/*
 * es07 — Tabella dei numeri primi fino a n  (Tipo esame)
 * Legge n e stampa tutti i primi <= n, 8 per riga, ciascuno con %5d.
 * Poi stampa "Trovati K numeri primi" oppure "Nessun primo <= n".
 * Se l'input non e' un numero stampa "Input non valido".
 * Come testarlo: make test T=03 E=es07
 */
#include <stdio.h>

/* Restituisce 1 se k e' primo, 0 altrimenti. */
int e_primo(int k) {
    /* TODO: k < 2 non e' primo; poi prova i divisori con un for. */
    (void)k;
    return 0;
}

int main(void) {
    int n = 0;
    /* TODO: leggi n controllando il valore di ritorno di scanf. */

    int trovati = 0;
    /* TODO: per ogni k da 2 a n, se e' primo stampalo con %5d,
             e vai a capo ogni 8 numeri stampati. Ricordati l'a capo finale
             se l'ultima riga e' incompleta. */

    if (trovati == 0)
        printf("Nessun primo <= %d\n", n);
    else
        printf("Trovati %d numeri primi\n", trovati);
    return 0;
}
