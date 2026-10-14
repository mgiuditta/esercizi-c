/*
 * es02 — Leggere una data con scanf e controllarne il valore di ritorno  (Base)
 * Legge una data gg/mm/aaaa e la ristampa come gg-mm-aaaa (con gli zeri: 06-10-2026).
 * Gestisci 4 casi (vedi README): EOF, lettura parziale, fuori intervallo, ok.
 * Come testarlo: make test T=03 E=es02
 */
#include <stdio.h>

int main(void) {
    int giorno = 0, mese = 0, anno = 0;
    int letti = 0;

    /* TODO: leggi la data con UNA sola scanf, formato "%2d/%2d/%4d",
             e salva in 'letti' il valore restituito da scanf. */

    /* TODO: usa if / else if / else per stampare UNO di questi messaggi:
             "Errore: nessun input (EOF)"
             "Errore: letti N campi su 3"
             "Errore: data fuori intervallo"     (mese 1..12, giorno 1..31)
             "Data: gg-mm-aaaa"                  (usa %02d e %04d)            */

    (void)giorno; (void)mese; (void)anno; (void)letti; /* togli questa riga */
    return 0;
}
