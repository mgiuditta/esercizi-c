/*
 * 01 — es02: MCD senza goto, con while  (Base)
 *
 * Testo: riscrivi l'algoritmo di es01 SENZA goto, usando un ciclo while.
 * E' il teorema di Bohm-Jacopini visto nel blocco 1: ogni programma con
 * i salti si puo' riscrivere con sequenza, selezione (if) e iterazione (while).
 * In piu': la tua versione deve funzionare anche quando y vale 0
 * (in matematica MCD(x, 0) = x). La versione con goto di es01 invece,
 * con y = 0, farebbe x % 0: divisione per zero, il programma va in crash.
 *
 * Come testarlo: make test T=01 E=es02
 */
#include <stdio.h>

int mcd_while(int x, int y)
{
    /* TODO: finche' y e' diverso da 0:
             calcola il resto r = x % y, poi x = y, poi y = r.
             Alla fine l'MCD e' in x. Nessun goto! */
    (void)x;
    (void)y;
    return 0; /* TODO: valore provvisorio */
}

int main(void)
{
    int x = 0;
    int y = 0;

    if (scanf("%d %d", &x, &y) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    printf("MCD(%d, %d) = %d\n", x, y, mcd_while(x, y));
    return 0;
}
