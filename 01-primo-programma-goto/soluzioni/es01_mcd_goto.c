/*
 * 01 — es01: MCD con goto  (Base) — SOLUZIONE
 * Traduzione "pari pari" dello pseudocodice dell'E-tivity 2.1.
 * Come testarlo: make sol T=01 E=es01
 */
#include <stdio.h>

int mcd_goto(int x, int y)
{
    int r; /* resto della divisione x / y (riga 3 dello pseudocodice) */

modulo:              /* etichetta = "riga 3": qui torniamo a ogni giro      */
    r = x % y;       /* riga 3: r = x mod y. % e' il resto della divisione  */
    if (r == 0)      /* riga 4: DUE uguali, perche' e' un confronto,        */
        goto risultato; /* non un assegnamento. Se il resto e' 0 ho finito */
    x = y;           /* riga 5: il vecchio divisore diventa il dividendo    */
    y = r;           /* riga 6: il resto diventa il nuovo divisore          */
    goto modulo;     /* riga 7: salto indietro a ricalcolare il resto       */

risultato:           /* etichetta = "riga 8"                                */
    return y;        /* l'ultimo divisore che ha dato resto 0 e' l'MCD.     */
                     /* Uso return invece di printf: la stampa la fa main.  */
}

int main(void)
{
    int x = 0;
    int y = 0;

    /* scanf restituisce quanti valori e' riuscita a leggere: se non sono 2,
       l'input e' sbagliato e non ha senso continuare. */
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    printf("MCD(%d, %d) = %d\n", x, y, mcd_goto(x, y));
    return 0;
}
