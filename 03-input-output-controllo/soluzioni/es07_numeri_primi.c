/*
 * es07 — Tabella dei numeri primi fino a n  (Tipo esame)
 * Legge n e stampa tutti i primi <= n, 8 per riga, ciascuno in 5 colonne (%5d).
 * Poi stampa quanti sono. Casi speciali: input non numerico, nessun primo.
 * Come testarlo: make test T=03 E=es07
 */
#include <stdio.h>

/* Restituisce 1 se k e' primo, 0 altrimenti. */
int e_primo(int k) {
    if (k < 2)
        return 0;                   /* 0, 1 e i negativi non sono primi per definizione */
    /* Basta provare i divisori d con d*d <= k: se k = a*b con a <= b,
       allora a*a <= k. Oltre la radice non serve cercare. */
    for (int d = 2; d * d <= k; d++) {
        if (k % d == 0)
            return 0;               /* trovato un divisore: esco subito (come un break) */
    }
    return 1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Input non valido\n");
        return 1;
    }

    int trovati = 0;
    for (int k = 2; k <= n; k++) {          /* ciclo esterno: i candidati */
        if (e_primo(k)) {                   /* "ciclo interno" nascosto nella funzione */
            printf("%5d", k);
            trovati++;
            if (trovati % 8 == 0)           /* ogni 8 numeri vado a capo */
                printf("\n");
        }
    }
    /* Se l'ultima riga non e' completa, manca l'a capo finale. */
    if (trovati % 8 != 0)
        printf("\n");

    if (trovati == 0)
        printf("Nessun primo <= %d\n", n);
    else
        printf("Trovati %d numeri primi\n", trovati);
    return 0;
}
