/*
 * es01 — Scontrino formattato con printf  (Base)
 * Legge: quantita' (int), prezzo unitario (double), categoria (char).
 * Stampa una piccola tabella allineata con larghezza di campo e %.2f.
 * Come testarlo: make test T=03 E=es01
 */
#include <stdio.h>

int main(void) {
    int qta;          /* quantita' acquistata: numero intero */
    double prezzo;    /* prezzo unitario: numero con la virgola, quindi double */
    char cat;         /* categoria dell'articolo: un singolo carattere */

    /* %d -> int, %lf -> double (in scanf la l e' obbligatoria per i double!),
       " %c" -> lo spazio prima di %c salta spazi e a capo rimasti nel buffer. */
    if (scanf("%d %lf %c", &qta, &prezzo, &cat) != 3) {
        printf("Input non valido\n");
        return 1;
    }

    double totale = qta * prezzo;   /* int * double -> il risultato e' double */
    double iva = totale * 22 / 100; /* 22 * totale / 100: tutto in double */

    /* Intestazione: %-8s = stringa allineata a SINISTRA in 8 colonne,
       %5s / %9s = stringhe allineate a DESTRA in 5 e 9 colonne. */
    printf("%-8s%5s%9s%9s\n", "Cat.", "Qta", "Prezzo", "Totale");
    /* Riga dati: stesse larghezze, cosi' le colonne si allineano.
       %9.2f = numero reale in 9 colonne con esattamente 2 decimali. */
    printf("%-8c%5d%9.2f%9.2f\n", cat, qta, prezzo, totale);
    /* %% stampa il simbolo % (da solo, % introdurrebbe un segnaposto). */
    printf("IVA 22%% inclusa: %.2f\n", iva);
    return 0;
}
