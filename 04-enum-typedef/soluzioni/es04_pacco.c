/*
 * es04 — TROVA E CORREGGI L'ERRORE: tracciamento di un pacco  (Intermedio)
 * Gli stati di un ordine sono un enum che parte da 1. Il programma:
 *   1) elenca tutti gli stati possibili;
 *   2) legge lo stato di partenza (1..4) e un numero di passi;
 *   3) fa avanzare lo stato passo per passo, fermandosi a CONSEGNATO.
 * Questa e' la versione CORRETTA.
 * Come testarlo: make test T=04 E=es04
 */
#include <stdio.h>

/* Valore esplicito solo sul primo: gli altri seguono (PAGATO=2, SPEDITO=3, CONSEGNATO=4). */
typedef enum {CREATO = 1, PAGATO, SPEDITO, CONSEGNATO} stato;

void stampa_stato(stato s) {
    switch (s) {
    case CREATO:     printf("creato");     break;
    case PAGATO:     printf("pagato");     break;   /* CORREZIONE 1: mancava il break,
                                                       "pagato" diventava "pagatospedito" */
    case SPEDITO:    printf("spedito");    break;
    case CONSEGNATO: printf("consegnato"); break;
    default:         printf("sconosciuto(%d)", (int)s);
    }
}

stato avanza(stato s) {
    /* CORREZIONE 2: il C non impedisce a un enum di uscire dall'elenco
       (CONSEGNATO + 1 = 5 e' un valore legale per il compilatore).
       Il controllo lo dobbiamo fare noi. */
    if (s == CONSEGNATO)
        return s;
    return s + 1;
}

int main(void) {
    printf("Stati possibili:");
    /* CORREZIONE 3: <= e non <, altrimenti CONSEGNATO non viene mai stampato
       (errore off-by-one). Gli enum si possono usare come indici di un ciclo. */
    for (stato s = CREATO; s <= CONSEGNATO; s++) {
        printf(" ");
        stampa_stato(s);
    }
    printf("\n");

    int partenza, passi;
    if (scanf("%d %d", &partenza, &passi) != 2 || partenza < CREATO || partenza > CONSEGNATO) {
        printf("Input non valido\n");
        return 1;
    }

    stato s = (stato)partenza;
    printf("partenza: ");
    stampa_stato(s);
    printf("\n");
    for (int i = 1; i <= passi; i++) {
        s = avanza(s);
        printf("passo %d: ", i);
        stampa_stato(s);
        printf("\n");
    }
    return 0;
}
