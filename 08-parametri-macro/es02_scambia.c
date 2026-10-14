/* =====================================================================
 * es02 — scambia() che funziona davvero  ·  Base
 * In 07 (es06) hai visto che void scambia(int x, int y) non funziona:
 * riceve COPIE. Qui la funzione riceve gli INDIRIZZI delle variabili:
 *   void scambia(int *x, int *y);   chiamata:  scambia(&a, &b);
 * Completa scambia usando *x e *y.
 * Input: a b. Output:
 *   prima: a=5 b=3
 *   dopo: a=3 b=5
 * Come testarlo: make test T=08 E=es02
 * ===================================================================== */
#include <stdio.h>

void scambia(int *x, int *y);

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("input non valido\n");
        return 1;
    }
    printf("prima: a=%d b=%d\n", a, b);
    scambia(&a, &b);
    printf("dopo: a=%d b=%d\n", a, b);
    return 0;
}

void scambia(int *x, int *y) {
    /* TODO: usa una variabile di appoggio t.
     * *x è "la variabile che sta all'indirizzo x" (cioè a del main). */
    (void)x; (void)y;   /* cancella questa riga */
}
