/*
 * es08 — Registro voti con sentinella e istogramma  (Tipo esame)
 * Legge voti interi fino alla sentinella 0 (o fine input / input non numerico).
 * Ignora i voti fuori da 18..30 (stampa "Ignorato: V").
 * Alla fine stampa numero voti validi, media, minimo, massimo e un istogramma
 * per fasce (18-23, 24-27, 28-30) fatto di asterischi.
 * Come testarlo: make test T=03 E=es08
 */
#include <stdio.h>

/* Stampa una riga dell'istogramma: etichetta, barra, e tanti '*' quanti 'quanti'. */
void stampa_barra(const char *etichetta, int quanti) {
    printf("%s | ", etichetta);
    for (int i = 0; i < quanti; i++)    /* ciclo interno: un asterisco per voto */
        putchar('*');
    printf(" (%d)\n", quanti);
}

int main(void) {
    int v;
    int n = 0, somma = 0;
    int min = 0, max = 0;               /* verranno sovrascritti dal primo voto valido */
    int f1 = 0, f2 = 0, f3 = 0;         /* contatori delle tre fasce */

    /* Lettura con sentinella: il while controlla PRIMA di elaborare, cosi' lo 0
       non viene mai trattato come un voto. La condizione e' composta:
       scanf deve aver letto 1 valore E quel valore non deve essere la sentinella. */
    while (scanf("%d", &v) == 1 && v != 0) {
        if (v < 18 || v > 30) {
            printf("Ignorato: %d\n", v);
            continue;                   /* salta il resto del corpo, passa al voto dopo */
        }
        n++;
        somma += v;
        if (n == 1 || v < min) min = v; /* il primo voto valido inizializza min e max */
        if (n == 1 || v > max) max = v;

        if (v <= 23)      f1++;         /* catena else if: le fasce si escludono a vicenda */
        else if (v <= 27) f2++;
        else              f3++;
    }

    if (n == 0) {
        printf("Nessun voto valido\n");  /* evita la divisione per zero nella media */
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
