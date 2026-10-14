/*
 * pila.c — pila con stato PRIVATO  (SOLUZIONE di es07)
 * Ispirato a: Trascrizione 4.4 ("se non è visibile non può essere modificata, quindi viene
 * protetta"), Appunti Unità 4 par. 4.9-4.10 (incapsulamento con static).
 */
#include "pila.h"

#define MAX_PILA 100

/* Stato del modulo: static = visibile solo in questo file.
 * main.c non può scrivere "cima = 50": è costretto a passare dalle funzioni,
 * che controllano sempre i limiti. */
static char dati[MAX_PILA];
static int cima = 0;             /* numero di elementi; la cima è dati[cima-1] */

void pila_svuota(void)      { cima = 0; }
int  pila_vuota(void)       { return cima == 0; }
int  pila_dimensione(void)  { return cima; }

int pila_push(char c)
{
    if (cima == MAX_PILA)        /* pila piena: rifiuto invece di scrivere fuori dal vettore */
        return 0;
    dati[cima] = c;
    cima++;
    return 1;
}

int pila_pop(char *c)
{
    if (cima == 0)               /* pila vuota: niente da togliere */
        return 0;
    cima--;
    *c = dati[cima];             /* restituisco il valore tramite puntatore: il return
                                    è già usato per dire "riuscito / non riuscito" */
    return 1;
}
