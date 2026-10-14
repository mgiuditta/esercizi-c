/* =====================================================================
 * es02 — Potenza con un ciclo  ·  Base
 * Completa potenza(base, esp): restituisce base elevato a esp
 * (esp >= 0) usando un ciclo for. Non usare pow() di math.h.
 * Il main (già scritto) rifiuta gli esponenti negativi.
 * Input: base esp. Output: potenza(base, esp) = risultato
 * Come testarlo: make test T=07 E=es02
 * ===================================================================== */
#include <stdio.h>

int potenza(int base, int esp);

int main(void) {
    int base, esp;
    if (scanf("%d %d", &base, &esp) != 2) {
        printf("input non valido\n");
        return 1;
    }
    if (esp < 0) {
        printf("esponente negativo: non gestito\n");
        return 0;
    }
    printf("potenza(%d, %d) = %d\n", base, esp, potenza(base, esp));
    return 0;
}

int potenza(int base, int esp) {
    /* TODO: moltiplica base per se stessa esp volte.
     * Domanda guida: da che valore deve partire il risultato? */
    (void)base; (void)esp;   /* cancella questa riga */
    return 0;
}
