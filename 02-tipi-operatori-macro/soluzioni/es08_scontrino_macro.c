/*
 * 02 — es08: scontrino con sconto e IVA, macro e arrotondamenti  (Tipo esame) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es08
 */
#include <stdio.h>

#define IVA_PERC 22
#define MAX_IMPORTO 100000000
/* Parentesi attorno a x (potrebbe essere un'espressione come a * b / 100.0)
   e attorno a tutta la macro (potrebbe finire dentro un'espressione piu' grande).
   (int) tronca verso lo zero: 599.7 + 0.5 = 600.2 -> 600 ; 1187.34 + 0.5 -> 1187.
   Funziona per x >= 0, che e' il nostro caso. */
#define ARROTONDA(x) ((int)((x) + 0.5))

int percentuale(int cent, int perc)
{
    /* 100.0 rende la divisione reale: con / 100 tra interi 599.7 diventerebbe
       599 (troncato) e non potrei arrotondare a 600. */
    return ARROTONDA(cent * perc / 100.0);
}

int ordine_valido(int prezzo, int quantita, int sconto)
{
    /* && valuta da sinistra a destra e si FERMA al primo falso (cortocircuito).
       Grazie a questo, MAX_IMPORTO / quantita viene calcolato solo se
       quantita > 0: niente divisione per zero.
       Confronto prezzo <= MAX_IMPORTO / quantita invece di
       prezzo * quantita <= MAX_IMPORTO: il prodotto potrebbe gia' andare
       in overflow (comportamento indefinito per gli int con segno). */
    return quantita > 0
        && prezzo > 0
        && prezzo <= MAX_IMPORTO / quantita
        && sconto >= 0
        && sconto <= 100;
}

void stampa_euro(const char *etichetta, int cent)
{
    /* / 100 = euro interi, % 100 = centesimi; %02d stampa sempre 2 cifre (5 -> 05) */
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

    imponibile = prezzo * quantita;       /* sicuro: controllato da ordine_valido */
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
