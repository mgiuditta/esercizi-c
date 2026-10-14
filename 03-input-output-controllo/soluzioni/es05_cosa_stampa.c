/*
 * es05 — COSA STAMPA?  Cicli, break, continue  (Intermedio)
 * NON modificare questo file. Leggi il codice, scrivi nel README (o su un foglio)
 * l'output che ti aspetti, parte per parte. Poi esegui il test: se passa,
 * il codice stampa esattamente quello che c'e' in tests/es05_cosa_stampa.out,
 * che puoi confrontare con la tua previsione.
 * Come testarlo: make test T=03 E=es05
 */
#include <stdio.h>

int main(void) {
    int i, j, x;

    /* Parte A: while e do-while con la stessa condizione, falsa fin dall'inizio */
    x = 10;
    while (x < 5) {
        printf("A-while %d\n", x);
        x++;
    }
    do {
        printf("A-do %d\n", x);
        x++;
    } while (x < 5);

    /* Parte B: continue e break nello stesso for */
    for (i = 0; i < 10; i++) {
        if (i % 3 == 0)
            continue;
        if (i > 7)
            break;
        printf("%d ", i);
    }
    printf("| B: i=%d\n", i);

    /* Parte C: cicli annidati, il break esce solo dal ciclo interno */
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) {
            if (j > i)
                break;
            printf("%d", j);
        }
        printf("\n");
    }

    /* Parte D: post-incremento dentro la condizione */
    x = 0;
    while (x++ < 3)
        printf("x=%d ", x);
    printf("| D: x=%d\n", x);

    /* Parte E: due variabili nel for con l'operatore virgola */
    for (i = 0, j = 5; i < j; i++, j--)
        printf("(%d,%d) ", i, j);
    printf("| E: i=%d j=%d\n", i, j);

    /* Parte F: printf con larghezza di campo */
    for (i = 1; i <= 100; i *= 10)
        printf("[%4d][%-4d]\n", i, i);

    return 0;
}
