/*
 * 01 — es06: Cosa stampa?  (Intermedio) — SOLUZIONE (stesso codice: la spiegazione e' nel README)
 *
 * Testo: NON eseguire subito. Leggi il codice, simula a mano i salti
 * (tieni una tabella con i valori di i e s) e scrivi nel README, sezione
 * es06, l'output che prevedi, riga per riga. Solo dopo esegui:
 *
 * Come testarlo: make test T=01 E=es06
 * (il test passa gia': serve a confrontare la TUA previsione con la realta')
 */
#include <stdio.h>

int main(void)
{
    int i = 1;
    int s = 0;

inizio:
    if (i > 10)
        goto fine;
    if (i % 3 == 0)
        goto salta;
    s = s + i;
    printf("i = %d, s = %d\n", i, s);
salta:
    i = i + 2;
    goto inizio;
fine:
    printf("Fine: i = %d, s = %d, s / 3 = %d\n", i, s, s / 3);
    return 0;
}
