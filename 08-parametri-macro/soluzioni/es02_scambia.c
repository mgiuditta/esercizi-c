/* =====================================================================
 * es02 — scambia() che funziona davvero  ·  Base  ·  SOLUZIONE
 * Passaggio per indirizzo: la funzione riceve gli INDIRIZZI di a e b
 * (int *x, int *y) e con *x / *y scrive nelle variabili del main.
 * Come testarlo: make sol T=08 E=es02
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
    /* &a = "l'indirizzo di a": passo DOVE si trova a, non quanto vale.
     * La copia che arriva alla funzione è una copia dell'indirizzo,
     * ma un indirizzo copiato indica sempre la stessa variabile. */
    scambia(&a, &b);
    printf("dopo: a=%d b=%d\n", a, b);
    return 0;
}

void scambia(int *x, int *y) {
    int t = *x;   /* *x = "la variabile che si trova all'indirizzo x", cioè a */
    *x = *y;      /* scrivo dentro a il valore di b */
    *y = t;       /* scrivo dentro b il vecchio valore di a */
}
