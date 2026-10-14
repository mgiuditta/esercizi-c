/*
 * es02 — MCD ricorsivo (algoritmo di Euclide)  ·  Base
 * Ispirato a: Trascrizione 2.1 E-tivity (MCD con goto), riscritto con la ricorsione (Trascrizione 4.2).
 *
 * Nel blocco 2 il prof calcolava l'MCD con i salti:
 *   modulo:    r = x % y;
 *              if (r == 0) goto risultato;
 *              x = y; y = r;
 *              goto modulo;
 *   risultato: printf("l'MCD e' %d", y);
 * Riscrivilo come funzione RICORSIVA, senza goto e senza cicli.
 * Il main legge coppie "x y" fino alla fine dell'input e stampa MCD(x, y).
 *
 * Come testarlo: make test T=13 E=es02
 */
#include <stdio.h>

int mcd(int x, int y)
{
    /* TODO: caso base (quando y vale 0, il risultato è x) e passo ricorsivo */
    (void)x;
    (void)y;
    return 0;
}

int main(void)
{
    int x, y;

    while (scanf("%d %d", &x, &y) == 2) {
        if (x < 0 || y < 0) {
            printf("Servono numeri non negativi\n");
            continue;
        }
        printf("MCD(%d, %d) = %d\n", x, y, mcd(x, y));
    }
    return 0;
}
