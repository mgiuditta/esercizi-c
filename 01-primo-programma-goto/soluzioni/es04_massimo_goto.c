/*
 * 01 — es04: massimo di numeri letti fino a 0, con goto  (Intermedio) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es04
 */
#include <stdio.h>

int main(void)
{
    int x = 0;
    int massimo = 0;
    int contati = 0;

    /* Primo numero: trattato a parte, perche' diventa il massimo provvisorio.
       Se partissi da massimo = 0, con tutti numeri negativi stamperei 0,
       che non e' nemmeno tra i dati! */
    if (scanf("%d", &x) != 1)   /* input finito o non numerico */
        goto fine;
    if (x == 0)                 /* il tappo arriva subito: nessun dato */
        goto fine;
    massimo = x;
    contati = 1;

leggi:                          /* qui si torna per ogni nuovo numero */
    if (scanf("%d", &x) != 1)   /* input finito senza lo 0: mi fermo */
        goto fine;
    if (x == 0)                 /* il tappo: ho finito */
        goto fine;
    contati = contati + 1;
    if (x > massimo)            /* ho trovato un nuovo "campione" */
        massimo = x;
    goto leggi;

fine:
    if (contati == 0) {
        printf("Nessun numero inserito\n");
    } else {
        printf("Numeri letti: %d, massimo = %d\n", contati, massimo);
    }
    return 0;
}
