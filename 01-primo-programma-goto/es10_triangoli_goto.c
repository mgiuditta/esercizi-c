/*
 * 01 — es10: triangoli numerici validati, versione con goto  (Tipo esame)
 *
 * Stesso testo e stesso output di es09, ma SENZA cicli strutturati:
 * niente while, do while, for. Solo if e goto.
 *   - ogni ciclo diventa una coppia di etichette (inizio / fine ciclo)
 *   - l'uscita anticipata (raggiunto max) diventa un salto all'etichetta finale
 *   - il do while della validazione resta post-condizionato:
 *     prima leggi, poi controlli e, se serve, torni indietro
 *
 * Esempio: righe = 4, max = 8  ->  1 / 1 2 / 1 2 3 / 1 2
 *
 * Come testarlo: make test T=01 E=es10
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void getInputFromUser(int *input) {

    bool do_retry = false;

    do {
        do_retry ? printf("Riprova per favore: \n"): printf("Inserisci numero righe: \n");
        int scanfResult = scanf("%d", input);

        if (scanfResult == EOF) {
            exit(1);
        }

        if (scanfResult != 1) {
            int c = 0;
            while ((c = getchar()) != '\n' && c != EOF) {}
            *input = 0;
        }

        do_retry=true;

    } while (*input <= 0);
}

int main(void)
{

    int lines = 0;
    int max = 0;

    getInputFromUser(&lines);
    getInputFromUser(&max);

    int printed = 0;
    int i = 1;

    while (i <= lines && printed < max) {
        int j = 1;
        while (j <= i && printed < max) {
            if (j > 1) printf(" ");
            printf("%d", j);
            printed++;
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}