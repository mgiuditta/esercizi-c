/*
 * es03 — Una variabile condivisa tra due file con extern  ·  Base  (file 1 di 3)
 * Ispirato a: Trascrizione 3.2 (main.c + foo.c con extern int n), Appunti Unità 3 par. 2.4.
 *
 * Il programma è diviso in TRE file: punteggio.h (questo), punteggio.c, main.c.
 * Il runner li compila insieme, come:  cc main.c punteggio.c -o es03
 *
 * Come testarlo: make test T=14 E=es03
 */
#ifndef PUNTEGGIO_H          /* include guard: impedisce di includere due volte questo file */
#define PUNTEGGIO_H

/* TODO 1: DICHIARA qui (con extern) la variabile int punteggio_totale,
           che è DEFINITA in punteggio.c. Così main.c potrà usarla. */

void aggiungi_punti(int p);

#endif
