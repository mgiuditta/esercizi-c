/*
 * es03 — Che giorno sara' tra n giorni? Aritmetica sugli enum  (Base)
 * Legge il giorno di partenza (0=lunedi' ... 6=domenica) e n (anche negativo).
 * Stampa ad es. "venerdi' + 3 giorni = lunedi'".
 * Se la partenza non e' fra 0 e 6 (o l'input non e' valido): "Input non valido".
 * Come testarlo: make test T=04 E=es03
 */
#include <stdio.h>

typedef enum {LUN, MAR, MER, GIO, VEN, SAB, DOM} giorno;

void stampa_giorno(giorno g) {
    /* TODO: switch che stampa (senza a capo) lunedi', martedi', mercoledi',
             giovedi', venerdi', sabato, domenica; "?" per valori fuori elenco. */
    (void)g;
}

giorno avanza(giorno g, int n) {
    /* TODO: restituisci il giorno che si ottiene spostandosi di n giorni.
             Attenzione ai valori negativi di n. */
    (void)n;
    return g;
}

int main(void) {
    int partenza, n;
    if (scanf("%d %d", &partenza, &n) != 2 || partenza < LUN || partenza > DOM) {
        printf("Input non valido\n");
        return 1;
    }
    giorno g = (giorno)partenza;
    stampa_giorno(g);
    printf(" + %d giorni = ", n);
    stampa_giorno(avanza(g, n));
    printf("\n");
    return 0;
}
