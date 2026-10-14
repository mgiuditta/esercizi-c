/*
 * es01 — Scontrino formattato con printf  (Base)
 * Legge: quantita' (int), prezzo unitario (double), categoria (char).
 * Devi stampare una piccola tabella allineata (vedi README per il formato esatto):
 *   Cat.      Qta   Prezzo   Totale
 *   A           3     2.50     7.50
 *   IVA 22% inclusa: 1.65
 * Come testarlo: make test T=03 E=es01
 */
#include <stdio.h>

int main(void) {
    int qta;
    double prezzo;
    char cat;

    if (scanf("%d %lf %c", &qta, &prezzo, &cat) != 3) {
        printf("Input non valido\n");
        return 1;
    }

    double totale = qta * prezzo;
    double iva = totale * 22 / 100;

    /* TODO: stampa l'intestazione "Cat." "Qta" "Prezzo" "Totale"
             con larghezze 8 (a sinistra), 5, 9, 9 (a destra). */

    /* TODO: stampa la riga con cat, qta, prezzo, totale
             (stesse larghezze, prezzi con 2 decimali). */

    /* TODO: stampa "IVA 22% inclusa: " seguito da iva con 2 decimali.
             Attenzione: come si stampa il carattere % ? */

    (void)cat; (void)qta; (void)totale; (void)iva; /* togli questa riga quando hai finito */
    return 0;
}
