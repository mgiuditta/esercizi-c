/* =====================================================================
 * es01 — Cosa stampa? Una variabile n, cinque scope  ·  Base  ·  SOLUZIONE
 * Il codice è identico allo starter: l'esercizio è PREVEDERE l'output.
 * La spiegazione passo passo è nel README.
 * Come testarlo: make sol T=08 E=es01
 * ===================================================================== */
#include <stdio.h>

int n = 10;                       /* GLOBALE: scope = tutto il file */

void stampa_n(void);
void azzera(void);
void incrementa(int n);

int main(void) {
    printf("A: n=%d\n", n);       /* main non ha una sua n: usa la globale -> 10 */
    azzera();                     /* lavora su una SUA n locale */
    stampa_n();                   /* la globale non è cambiata -> 10 */
    incrementa(n);                /* passo una COPIA di 10 */
    printf("B: n=%d\n", n);       /* ancora 10 */
    {
        int n = 3;                /* scope di BLOCCO: fa ombra alla globale fino alla } */
        printf("C: n=%d\n", n);   /* -> 3 */
        stampa_n();               /* stampa_n NON vede questa n: vede quella del
                                     punto in cui è SCRITTA (la globale) -> 10 */
        n++;                      /* modifica la n del blocco, che poi sparisce */
    }
    for (int n = 0; n < 2; n++)   /* la n del for vive solo dentro il for */
        printf("D: n=%d\n", n);   /* -> 0 e poi 1 */
    n = n * 2;                    /* qui n è di nuovo la globale: 10 * 2 = 20 */
    stampa_n();                   /* -> 20 */
    return 0;
}

void stampa_n(void) {
    printf("stampa_n: n=%d\n", n);    /* nessuna n locale: è sempre la globale */
}

void azzera(void) {
    int n = 0;                        /* locale: nasce a 0 a ogni chiamata */
    n++;
    printf("azzera: n=%d\n", n);      /* -> 1 */
}

void incrementa(int n) {              /* il PARAMETRO n fa ombra alla globale */
    n = n + 5;
    printf("incrementa: n=%d\n", n);  /* -> 15, ma solo nella copia */
}
