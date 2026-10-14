/*
 * es02 — MCD ricorsivo (algoritmo di Euclide)  (SOLUZIONE)
 * Ispirato a: Trascrizione 2.1 E-tivity (MCD con goto), riscritto con la ricorsione
 * della Trascrizione 4.2.
 */
#include <stdio.h>

/* Nel blocco 2 il prof calcolava l'MCD così (con i salti):
 *   modulo: r = x % y;
 *           if (r == 0) goto risultato;
 *           x = y; y = r; goto modulo;
 *   risultato: printf("l'MCD e' %d", y);
 * Il "goto modulo" ripete il calcolo con la coppia (y, r).
 * Con la ricorsione il "torna su e ripeti" diventa "richiamati con (y, x % y)". */
int mcd(int x, int y)
{
    if (y == 0)                 /* caso base: MCD(x, 0) = x (ogni numero divide 0) */
        return x;
    return mcd(y, x % y);       /* passo: il resto x % y è sempre < y, quindi y cala: si arriva a 0 */
}

int main(void)
{
    int x, y;

    /* leggo coppie finché ce ne sono: scanf restituisce 2 se ha letto entrambi i numeri */
    while (scanf("%d %d", &x, &y) == 2) {
        if (x < 0 || y < 0) {   /* il prof assume numeri naturali: rifiuto i negativi */
            printf("Servono numeri non negativi\n");
            continue;
        }
        printf("MCD(%d, %d) = %d\n", x, y, mcd(x, y));
    }
    return 0;
}
