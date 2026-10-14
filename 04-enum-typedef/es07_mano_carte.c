/*
 * es07 — Punteggio di una mano di carte  (Tipo esame)
 * Legge carte fino a fine input, nel formato VALORE SEME (es. "1 C", "13 p"):
 *   valore 1..13, seme P/C/Q/F (picche, cuori, quadri, fiori), maiuscolo o minuscolo.
 * Punti: asso(1)=11, tre=10, re(13)=4, regina(12)=3, fante(11)=2, le altre 0.
 * Output (formato esatto nel README):
 *   Carta non valida: V S          (per ogni carta sbagliata, appena letta)
 *   PICCHE  carte=N punti=P        (una riga per seme, nell'ordine dell'enum, %-7s)
 *   ...
 *   Totale: T punti in N carte
 *   Seme migliore: NOME (P punti)  (a parita' vince il primo nell'ordine)
 * Se nessuna carta e' valida: solo "Nessuna carta valida".
 * Come testarlo: make test T=04 E=es07
 */
#include <stdio.h>

/* TODO: typedef enum "seme" con SEME_NON_VALIDO = -1, PICCHE, CUORI, QUADRI, FIORI */

/* TODO: seme seme_da_char(char c)     -> converte 'P','p','C',... nel seme (switch) */

/* TODO: const char *nome_seme(seme s) -> restituisce "PICCHE", "CUORI", ... */

/* TODO: int punti_carta(int valore)   -> punteggio della carta (switch) */

int main(void) {
    int v;
    char ch;

    while (scanf("%d %c", &v, &ch) == 2) {
        /* TODO: valida la carta, aggiorna i contatori del seme giusto */
    }

    /* TODO: tabella per seme con un for sull'enum, totale, seme migliore */
    printf("Nessuna carta valida\n");
    return 0;
}
