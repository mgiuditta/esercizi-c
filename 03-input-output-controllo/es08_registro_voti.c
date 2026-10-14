/*
 * es08 — Registro voti con sentinella e istogramma  (Tipo esame)
 * Legge voti interi fino alla sentinella 0 (o fine input / input non numerico).
 * Ignora i voti fuori da 18..30 stampando "Ignorato: V".
 * Alla fine stampa (formato esatto nel README):
 *   Voti validi: N
 *   Media: M.MM
 *   Minimo: A  Massimo: B
 *   18-23 | *** (3)
 *   24-27 |  (0)
 *   28-30 | ** (2)
 * Se non c'e' nessun voto valido stampa solo "Nessun voto valido".
 * Come testarlo: make test T=03 E=es08
 */
#include <stdio.h>

/* Stampa una riga dell'istogramma: "etichetta | " + quanti asterischi + " (quanti)". */
void stampa_barra(const char *etichetta, int quanti) {
    /* TODO: usa printf per l'etichetta, un for con putchar('*'), poi " (quanti)\n". */
    (void)etichetta; (void)quanti;
}

int main(void) {
    int n = 0, somma = 0;
    int min = 0, max = 0;
    int f1 = 0, f2 = 0, f3 = 0;

    /* TODO: ciclo di lettura con sentinella 0; aggiorna n, somma, min, max, fasce. */

    if (n == 0) {
        printf("Nessun voto valido\n");
        return 0;
    }

    printf("Voti validi: %d\n", n);
    printf("Media: %.2f\n", (double)somma / n);
    printf("Minimo: %d  Massimo: %d\n", min, max);
    stampa_barra("18-23", f1);
    stampa_barra("24-27", f2);
    stampa_barra("28-30", f3);
    return 0;
}
