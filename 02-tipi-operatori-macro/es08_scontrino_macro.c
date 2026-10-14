/*
 * 02 — es08: scontrino con sconto e IVA, macro e arrotondamenti  (Tipo esame)
 *
 * Testo: legge prezzo unitario in CENTESIMI, quantita' e sconto in percentuale
 * (tutti interi) e stampa lo scontrino. Si lavora in centesimi interi per non
 * avere gli errori di approssimazione dei numeri reali (0.1 + 0.2 != 0.3!).
 *
 *   imponibile = prezzo * quantita
 *   sconto     = percentuale "sconto" dell'imponibile, arrotondata al centesimo
 *   netto      = imponibile - sconto
 *   iva        = 22% del netto, arrotondata al centesimo
 *   totale     = netto + iva
 *
 * Completa:
 *   - la macro ARROTONDA(x): da double a int, al centesimo piu' vicino
 *     (x >= 0). Idea: aggiungi 0.5 e tronca. Metti le parentesi giuste!
 *   - percentuale(cent, perc): perc% di cent, arrotondato (usa ARROTONDA)
 *   - ordine_valido(prezzo, quantita, sconto): 1 se prezzo > 0, quantita > 0,
 *     sconto tra 0 e 100 e l'imponibile non supera MAX_IMPORTO; 0 altrimenti.
 *     ATTENZIONE: per controllare il limite senza rischiare overflow
 *     confronta prezzo con MAX_IMPORTO / quantita (e la divisione per zero?).
 *
 * Esempio:  1999 3 10  ->  Totale: 65.84 euro
 *
 * Come testarlo: make test T=02 E=es08
 */
#include <stdio.h>

#define IVA_PERC 22
#define MAX_IMPORTO 100000000          /* 1 milione di euro, in centesimi */
#define ARROTONDA(x) 0                 /* TODO: scrivi la macro giusta */

int percentuale(int cent, int perc)
{
    /* TODO */
    (void)cent;
    (void)perc;
    return ARROTONDA(0.0);
}

int ordine_valido(int prezzo, int quantita, int sconto)
{
    /* TODO */
    (void)prezzo;
    (void)quantita;
    (void)sconto;
    return 1;
}

/* Stampa un importo in centesimi come euro: 6584 -> "65.84". Gia' completa. */
void stampa_euro(const char *etichetta, int cent)
{
    printf("%s: %d.%02d euro\n", etichetta, cent / 100, cent % 100);
}

int main(void)
{
    int prezzo = 0, quantita = 0, sconto = 0;
    int imponibile, sconto_cent, netto, iva, totale;

    if (scanf("%d %d %d", &prezzo, &quantita, &sconto) != 3
        || !ordine_valido(prezzo, quantita, sconto)) {
        printf("Ordine non valido\n");
        return 0;
    }

    imponibile = prezzo * quantita;
    sconto_cent = percentuale(imponibile, sconto);
    netto = imponibile - sconto_cent;
    iva = percentuale(netto, IVA_PERC);
    totale = netto + iva;

    stampa_euro("Imponibile", imponibile);
    printf("Sconto %d%%: -%d.%02d euro\n", sconto, sconto_cent / 100, sconto_cent % 100);
    stampa_euro("Netto", netto);
    printf("IVA %d%%: %d.%02d euro\n", IVA_PERC, iva / 100, iva % 100);
    stampa_euro("Totale", totale);
    return 0;
}
