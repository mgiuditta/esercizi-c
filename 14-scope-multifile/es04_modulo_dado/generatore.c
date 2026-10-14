/*
 * es04 — Modulo "dado" con stato nascosto (static globale e funzione static)  ·  Intermedio
 * File 2 di 3: generatore.c
 * Ispirato a: Trascrizione 4.4 (globale static e funzione static: linkage interno),
 * Appunti Unità 4 par. 4.8-4.10.
 *
 * Completa le tre funzioni pubbliche. Lo stato (seme, estrazioni) e la funzione
 * prossimo() sono static: da main.c NON si vedono.
 *
 * Come testarlo: make test T=14 E=es04
 */
#include "generatore.h"

static unsigned long long seme = 1;
static int estrazioni = 0;

/* Generatore congruenziale lineare (LCG): GIÀ SCRITTO, non modificarlo. */
static unsigned long long prossimo(void)
{
    seme = (seme * 1103515245ULL + 12345ULL) % 2147483648ULL;
    return seme;
}

void gen_seme(unsigned int s)
{
    /* TODO: imposta il seme a s e azzera le estrazioni */
    (void)s;
}

int gen_dado(void)
{
    unsigned long long r = prossimo();
    /* TODO: conta l'estrazione e restituisci (r / 65536) % 6 + 1, convertito in int */
    (void)r;
    return 1;
}

int gen_estrazioni(void)
{
    return estrazioni;
}
