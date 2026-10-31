/*
 * 01 — es09: triangoli numerici validati, versione strutturata — SOLUZIONE
 */
#include <stdio.h>

int main(void)
{
    int righe = 0;
    int max = 0;
    int stampati = 0; /* variabile di appoggio: quanti numeri ho stampato finora */
    int i = 1;
    int j;

    /* Ciclo post-condizionato: leggo almeno una volta, poi controllo.
       Se scanf non legge un intero (input finito) esco: senza questo
       controllo il ciclo girerebbe per sempre. */
    do {
        if (scanf("%d", &righe) != 1) {
            printf("Input non valido\n");
            return 1;
        }
    } while (righe <= 0);

    do {
        if (scanf("%d", &max) != 1) {
            printf("Input non valido\n");
            return 1;
        }
    } while (max <= 0);

    /* Uscita anticipata nella condizione: stampati < max. */
    while (i <= righe && stampati < max) {
        j = 1;
        while (j <= i && stampati < max) {
            if (j > 1) {
                printf(" ");
            }
            printf("%d", j);
            stampati = stampati + 1;
            j = j + 1;
        }
        printf("\n"); /* la riga ha almeno un numero: stampati < max all'ingresso */
        i = i + 1;
    }

    return 0;
}
