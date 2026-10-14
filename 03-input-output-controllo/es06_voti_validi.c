/*
 * es06 — Validazione dell'input con do-while  (Intermedio)
 * Completa leggi_voto(): chiede un voto finche' non ne arriva uno valido
 * (intero fra 18 e 30). Messaggi (esatti):
 *   "Input non numerico, riprova"               (scanf restituisce 0: scarta la riga)
 *   "Voto V fuori intervallo (18-30), riprova"  (numero fuori 18..30)
 * Se l'input finisce (scanf restituisce EOF) restituisce -1.
 * Il main e' gia' scritto.
 * Come testarlo: make test T=03 E=es06
 */
#include <stdio.h>

int leggi_voto(void) {
    /* TODO: do { ... } while (...);  con scanf, controllo del valore di ritorno,
             svuotamento del buffer con getchar() quando l'input non e' numerico. */
    return -1;
}

int main(void) {
    int somma = 0;
    for (int i = 0; i < 3; i++) {
        int v = leggi_voto();
        if (v == -1) {
            printf("Input terminato prima di 3 voti\n");
            return 1;
        }
        somma += v;
    }
    printf("Media: %.2f\n", (double)somma / 3);
    return 0;
}
