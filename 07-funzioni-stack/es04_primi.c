/* =====================================================================
 * es04 — Numeri primi con una funzione "sì/no"  ·  Intermedio
 * Completa e_primo(n): restituisce 1 se n è primo, 0 altrimenti
 * (0, 1 e i negativi NON sono primi). Il main (già scritto) la chiama
 * per ogni k da 2 a N e stampa i primi trovati e quanti sono.
 * Input: N. Output (esempio con 20):
 *   primi fino a 20: 2 3 5 7 11 13 17 19
 *   totale: 8
 * Come testarlo: make test T=07 E=es04
 * ===================================================================== */
#include <stdio.h>

int e_primo(int n);

int main(void) {
    int n, k, conta = 0;
    if (scanf("%d", &n) != 1) {
        printf("input non valido\n");
        return 1;
    }
    printf("primi fino a %d:", n);
    for (k = 2; k <= n; k++) {
        if (e_primo(k)) {
            printf(" %d", k);
            conta++;
        }
    }
    printf("\ntotale: %d\n", conta);
    return 0;
}

int e_primo(int n) {
    /* TODO: 1) se n < 2 restituisci 0
     *       2) prova i divisori d = 2, 3, ... : se n % d == 0 non è primo
     *       3) se nessun divisore funziona, restituisci 1 */
    (void)n;   /* cancella questa riga */
    return 0;
}
