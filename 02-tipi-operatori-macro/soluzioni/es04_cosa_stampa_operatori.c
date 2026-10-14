/*
 * 02 — es04: Cosa stampa? (Intermedio) — SOLUZIONE (stesso codice: la spiegazione e' nel README)
 *
 * Testo: NON eseguire subito. Prevedi l'output riga per riga e scrivilo
 * nel README (sezione es04). Tieni una tabella con i valori delle variabili.
 * Poi esegui il test per controllare.
 *
 * Come testarlo: make test T=02 E=es04
 * (il test passa gia': serve a confrontare la TUA previsione con la realta')
 */
#include <stdio.h>

int main(void)
{
    int a = 7, b = 3, c = 0;
    int p = 7, q = 2;
    int i = 1, j = 1;
    double r = 0.0;

    c = a++ + --b;
    printf("1) a = %d, b = %d, c = %d\n", a, b, c);

    c = a + b * 3 % 4;
    printf("2) c = %d\n", c);

    c = (a + b) * 3 % 4;
    printf("3) c = %d\n", c);

    r = p / q;
    printf("4) r = %.2f\n", r);

    r = (double)(p / q);
    printf("5) r = %.2f\n", r);

    r = (double)p / q;
    printf("6) r = %.2f\n", r);

    printf("7) %d %d\n", -p / q, -p % q);

    c = (i > 0) || (j++ > 0);
    printf("8) c = %d, j = %d\n", c, j);

    c = (i < 0) && (j++ > 0);
    printf("9) c = %d, j = %d\n", c, j);

    c = (i < 0) || (j++ > 0);
    printf("10) c = %d, j = %d\n", c, j);

    c = 10;
    c -= 2 + 3;
    c *= 2 + 1;
    printf("11) c = %d\n", c);

    c = 3 + (7 > 2) * 10;
    printf("12) c = %d\n", c);
    return 0;
}
