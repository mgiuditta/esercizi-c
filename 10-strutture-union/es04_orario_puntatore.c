/*
 * es04 — Aggiorna un orario tramite puntatore  (Intermedio)
 *
 * Testo: Orario ha i campi ore (0-23) e minuti (0-59). Implementa
 * aggiungi_minuti(o, m): aggiunge m minuti (anche negativi) all'orario
 * PUNTATO da o, usando l'operatore ->, e lo riporta nell'intervallo
 * 00:00 - 23:59 (si "gira" oltre la mezzanotte, come un orologio).
 * Il main mostra anche che la versione "per valore" (gia' scritta) non
 * modifica nulla.
 *
 * Input:  ore minuti m         Esempio: 23 50 20
 * Output: per valore:    23:50
 *         per indirizzo: 00:10
 *
 * Come testarlo: make test T=10 E=es04
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
    o.minuti += m;
}

void aggiungi_minuti(Orario *o, int m)
{
    /* TODO:
       1) converti tutto in minuti dalla mezzanotte: o->ore * 60 + o->minuti + m
       2) riportalo tra 0 e MINUTI_GIORNO - 1 (attenzione ai negativi!)
       3) riscrivi o->ore e o->minuti */
    (void)o; (void)m;   /* cancella questa riga */
}

int main(void)
{
    Orario t;
    int m;

    if (scanf("%d %d %d", &t.ore, &t.minuti, &m) != 3)
        return 1;

    aggiungi_per_valore(t, m);
    printf("per valore:    %02d:%02d\n", t.ore, t.minuti);

    aggiungi_minuti(&t, m);
    printf("per indirizzo: %02d:%02d\n", t.ore, t.minuti);
    return 0;
}
