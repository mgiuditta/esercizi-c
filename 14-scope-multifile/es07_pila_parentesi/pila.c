/*
 * es07 — Modulo pila con stato privato + controllo delle parentesi  ·  Tipo esame
 * File 2 di 3: pila.c
 * Ispirato a: Trascrizione 4.4 ("se non è visibile non può essere modificata, quindi viene
 * protetta"), Appunti Unità 4 par. 4.9-4.10 (incapsulamento con static).
 *
 * pila_push è GIÀ SCRITTA come modello. Completa pila_pop.
 *
 * Come testarlo: make test T=14 E=es07
 */
#include "pila.h"

#define MAX_PILA 100

static char dati[MAX_PILA];
static int cima = 0;             /* numero di elementi; la cima è dati[cima-1] */

void pila_svuota(void)      { cima = 0; }
int  pila_vuota(void)       { return cima == 0; }
int  pila_dimensione(void)  { return cima; }

int pila_push(char c)
{
    if (cima == MAX_PILA)
        return 0;
    dati[cima] = c;
    cima++;
    return 1;
}

int pila_pop(char *c)
{
    /* TODO: se la pila è vuota restituisci 0; altrimenti togli l'elemento in cima,
       scrivilo in *c e restituisci 1 */
    (void)c;
    return 0;
}
