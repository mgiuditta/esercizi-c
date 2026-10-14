/*
 * punteggio.c — implementazione del modulo "punteggio"  (SOLUZIONE di es03)
 * Ispirato a: Trascrizione 3.2 (main.c + foo.c con extern int n), Appunti Unità 3 par. 2.4.
 */
#include "punteggio.h"       /* includo il MIO header: il compilatore controlla che
                                dichiarazioni e definizioni coincidano */

/* DEFINIZIONE: qui la variabile viene allocata (una volta sola in tutto il programma). */
int punteggio_totale = 0;

/* Aggiunge p al totale; le penalità (p negativo) non portano mai il totale sotto 0. */
void aggiungi_punti(int p)
{
    punteggio_totale += p;           /* modifico la globale: la vedrà anche main.c */
    if (punteggio_totale < 0)
        punteggio_totale = 0;
}
