/*
 * 01 — es08: numeri primi fino a N  (Tipo esame)
 *
 * Testo: un numero n e' PRIMO se e' >= 2 e non ha divisori tranne 1 e se
 * stesso (2, 3, 5, 7, 11, ...). Scrivi:
 *
 *   - e_primo(n): restituisce 1 se n e' primo, 0 altrimenti.
 *     Usa goto ed etichette, traducendo questo pseudocodice:
 *         1  if n < 2 then goto 8
 *         2  d = 2
 *         3  if d * d > n then goto 7
 *         4  if n mod d = 0 then goto 8
 *         5  d = d + 1
 *         6  goto 3
 *         7  return 1          (nessun divisore trovato: primo)
 *         8  return 0          (non primo)
 *
 *   - conta_primi(n): restituisce QUANTI primi ci sono tra 2 e n.
 *     Usa un while (niente goto) e chiama e_primo.
 *
 * Il main (gia' scritto) legge N, stampa la lista dei primi e il totale.
 * Esempio:  30  ->  Primi fino a 30: 2 3 5 7 11 13 17 19 23 29
 *                   Totale: 10
 *
 * Come testarlo: make test T=01 E=es08
 */
#include <stdio.h>

int e_primo(int n)
{
    int d = 2;
    /* TODO: traduci lo pseudocodice con le etichette "prova:", "si:", "no:" */
    (void)n;
    (void)d;
    return 0; /* TODO: valore provvisorio */
}

int conta_primi(int n)
{
    int conta = 0;
    /* TODO: con un while prova tutti i numeri da 2 a n
             e conta quelli per cui e_primo restituisce 1 */
    (void)n;
    return conta; /* TODO: valore provvisorio */
}

int main(void)
{
    int n = 0;
    int k = 2;

    if (scanf("%d", &n) != 1) {
        printf("Input non valido\n");
        return 1;
    }

    printf("Primi fino a %d:", n);
    while (k <= n) {
        if (e_primo(k))
            printf(" %d", k);
        k = k + 1;
    }
    printf("\n");
    printf("Totale: %d\n", conta_primi(n));
    return 0;
}
