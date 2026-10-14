/*
 * generatore.c — implementazione con stato privato  (SOLUZIONE di es04)
 * Ispirato a: Trascrizione 4.4 (variabile globale static e funzione static: "linkage interno"),
 * Appunti Unità 4 par. 4.8-4.10.
 */
#include "generatore.h"

/* Variabili globali static: vivono per tutto il programma, ma il loro nome
 * è visibile SOLO in questo file. Nessun altro file può modificarle "per errore". */
static unsigned long long seme = 1;
static int estrazioni = 0;

/* Funzione static: è un "attrezzo interno" del modulo; da main.c non si può chiamare.
 * Formula di un generatore congruenziale lineare (LCG): numeri che SEMBRANO casuali,
 * ma sono sempre gli stessi a parità di seme. Per questo il test è ripetibile. */
static unsigned long long prossimo(void)
{
    seme = (seme * 1103515245ULL + 12345ULL) % 2147483648ULL;   /* 2147483648 = 2^31 */
    return seme;
}

void gen_seme(unsigned int s)
{
    seme = s;            /* l'unico modo "ufficiale" per cambiare il seme */
    estrazioni = 0;
}

int gen_dado(void)
{
    estrazioni++;
    /* divido per 65536 per usare i bit "alti", più vari di quelli bassi; % 6 dà 0..5 */
    return (int)((prossimo() / 65536ULL) % 6ULL) + 1;
}

int gen_estrazioni(void)
{
    return estrazioni;   /* lettura controllata dello stato privato */
}
