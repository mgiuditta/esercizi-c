/*
 * es04 — Aggiorna un orario tramite puntatore  (Intermedio)  — SOLUZIONE
 *
 * Testo: Orario ha i campi ore (0-23) e minuti (0-59). Implementa
 * aggiungi_minuti(o, m): aggiunge m minuti (anche negativi) all'orario
 * PUNTATO da o, usando l'operatore ->, e lo riporta nell'intervallo
 * 00:00 - 23:59 (si "gira" oltre la mezzanotte, come un orologio).
 * Il main mostra anche che la versione "per valore" non modifica nulla.
 *
 * Come testarlo: make sol T=10 E=es04
 */
#include <stdio.h>

#define MINUTI_GIORNO (24 * 60)

typedef struct {
    int ore;
    int minuti;
} Orario;

/* Versione SBAGLIATA (gia' scritta, per confronto): o e' una COPIA. */
void aggiungi_per_valore(Orario o, int m)
{
    o.minuti += m;    /* modifica la copia, che sparisce al return */
}

void aggiungi_minuti(Orario *o, int m)
{
    /* o->ore e' un'abbreviazione di (*o).ore: "il campo ore della
     * struttura puntata da o". Le parentesi in (*o).ore servono perche'
     * il punto lega piu' forte dell'asterisco: *o.ore sarebbe *(o.ore). */
    int totale = o->ore * 60 + o->minuti + m;   /* tutto in minuti dalla mezzanotte */

    totale %= MINUTI_GIORNO;   /* in C il resto ha il segno del dividendo: */
    if (totale < 0)            /* -20 % 1440 = -20, quindi lo riporto in [0, 1440) */
        totale += MINUTI_GIORNO;

    o->ore = totale / 60;      /* scrivo nella struttura del CHIAMANTE */
    o->minuti = totale % 60;
}

int main(void)
{
    Orario t;
    int m;

    if (scanf("%d %d %d", &t.ore, &t.minuti, &m) != 3)
        return 1;

    aggiungi_per_valore(t, m);
    printf("per valore:    %02d:%02d\n", t.ore, t.minuti);   /* invariato */

    aggiungi_minuti(&t, m);    /* passo l'INDIRIZZO della struttura */
    printf("per indirizzo: %02d:%02d\n", t.ore, t.minuti);
    return 0;
}
