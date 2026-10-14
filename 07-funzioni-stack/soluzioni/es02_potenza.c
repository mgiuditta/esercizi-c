/* =====================================================================
 * es02 — Potenza con un ciclo  ·  Base  ·  SOLUZIONE
 * Scrivi potenza(base, esp) che calcola base elevato esp (esp >= 0)
 * con un ciclo for, senza usare pow().
 * Come testarlo: make sol T=07 E=es02
 * ===================================================================== */
#include <stdio.h>

int potenza(int base, int esp);   /* prototipo */

int main(void) {
    int base, esp;
    if (scanf("%d %d", &base, &esp) != 2) {
        printf("input non valido\n");
        return 1;
    }
    /* Il controllo sull'input lo fa il chiamante: così potenza resta
     * semplice e fa una cosa sola. */
    if (esp < 0) {
        printf("esponente negativo: non gestito\n");
        return 0;
    }
    printf("potenza(%d, %d) = %d\n", base, esp, potenza(base, esp));
    return 0;
}

int potenza(int base, int esp) {
    /* risultato parte da 1, l'elemento neutro della moltiplicazione:
     * se partisse da 0 ogni prodotto darebbe 0. Con esp = 0 il ciclo
     * non gira mai e restituisco 1 (per convenzione x^0 = 1, anche 0^0). */
    int risultato = 1;
    int i;
    for (i = 0; i < esp; i++)
        risultato = risultato * base;   /* moltiplico esp volte */
    return risultato;
}
