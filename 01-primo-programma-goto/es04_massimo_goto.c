/*
 * 01 — es04: massimo di numeri letti fino a 0, con goto  (Intermedio)
 *
 * Testo: leggi interi uno alla volta finche' arriva 0 (lo 0 NON fa parte
 * dei dati: e' il "tappo" che dice "ho finito"). Alla fine stampa quanti
 * numeri hai letto e il massimo. Se il primo numero e' gia' 0 stampa
 * "Nessun numero inserito". Se l'input finisce senza lo 0, fermati comunque.
 * Usa SOLO if e goto (niente while/for): e' l'esercizio di traduzione
 * dei salti come nell'E-tivity.
 *
 * Esempio:  3 9 -2 7 0   ->   "Numeri letti: 4, massimo = 9"
 * Attenzione ai numeri tutti negativi: -5 -2 -9 0 -> massimo = -2.
 *
 * Come testarlo: make test T=01 E=es04
 */
#include <stdio.h>

int main(void)
{
    int x = 0;        /* numero appena letto                  */
    int massimo = 0;  /* il piu' grande visto finora          */
    int contati = 0;  /* quanti numeri (diversi da 0) ho letto */

    /* TODO: 1) leggi il primo numero: se la lettura fallisce o vale 0,
                salta all'etichetta "fine".
             2) altrimenti il primo numero e' il massimo provvisorio.
             3) etichetta "leggi": leggi il prossimo, se e' 0 (o la lettura
                fallisce) salta a "fine"; altrimenti contalo, aggiorna il
                massimo e torna a "leggi".
             4) etichetta "fine": qui sotto c'e' gia' la stampa. */
    (void)x;

    if (contati == 0) {
        printf("Nessun numero inserito\n");
    } else {
        printf("Numeri letti: %d, massimo = %d\n", contati, massimo);
    }
    return 0;
}
