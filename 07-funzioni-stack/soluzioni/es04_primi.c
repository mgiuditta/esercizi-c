/* =====================================================================
 * es04 — Numeri primi con una funzione "sì/no"  ·  Intermedio  ·  SOLUZIONE
 * Scrivi e_primo(n): restituisce 1 se n è primo, 0 altrimenti.
 * Il main (già scritto) la usa in un ciclo per stampare i primi fino a N.
 * Come testarlo: make sol T=07 E=es04
 * ===================================================================== */
#include <stdio.h>

int e_primo(int n);   /* in C (fino a C99 senza stdbool) "vero" = 1, "falso" = 0 */

int main(void) {
    int n, k, conta = 0;
    if (scanf("%d", &n) != 1) {
        printf("input non valido\n");
        return 1;
    }
    printf("primi fino a %d:", n);
    for (k = 2; k <= n; k++) {
        /* la chiamata sta dentro la condizione dell'if: il valore
         * restituito (0 o 1) decide se stampare */
        if (e_primo(k)) {
            printf(" %d", k);   /* spazio PRIMA del numero: niente spazio in fondo */
            conta++;
        }
    }
    printf("\ntotale: %d\n", conta);
    return 0;
}

int e_primo(int n) {
    int d;
    if (n < 2)
        return 0;            /* 0, 1 e i negativi non sono primi */
    /* Basta provare i divisori d con d*d <= n: se n = d*e con d <= e,
     * allora d*d <= n. Oltre la radice non serve guardare. */
    for (d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;        /* trovato un divisore: esco SUBITO dalla funzione */
    return 1;                /* nessun divisore trovato */
}
