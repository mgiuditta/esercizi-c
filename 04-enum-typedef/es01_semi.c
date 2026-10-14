/*
 * es01 — I semi delle carte con enum e switch  (Base)
 * Legge numeri interi fino a fine input. Per ognuno stampa:
 *   0 -> "PICCHE (nero)"   1 -> "CUORI (rosso)"
 *   2 -> "QUADRI (rosso)"  3 -> "FIORI (nero)"
 *   altro -> "Seme non valido: N"
 * Come testarlo: make test T=04 E=es01
 */
#include <stdio.h>

/* TODO: dichiara qui l'enum con tag "seme" e i valori PICCHE, CUORI, QUADRI, FIORI
         (in quest'ordine, senza valori espliciti). Poi cambia il tipo del
         parametro di stampa_seme da int a enum seme. */

void stampa_seme(int s) {
    /* TODO: switch su s, un case per ogni seme (usa i NOMI, non i numeri), piu' default. */
    (void)s;
}

int main(void) {
    int n;
    while (scanf("%d", &n) == 1) {
        stampa_seme(n);
    }
    return 0;
}
