/*
 * main.c — lancia il dado n volte e stampa l'istogramma  (SOLUZIONE di es04)
 */
#include <stdio.h>
#include "generatore.h"

/* static anche qui: stampa_istogramma serve solo a main.c.
 * Potrebbe esistere una funzione con lo stesso nome, static, in un altro file: nessun conflitto. */
static void stampa_istogramma(const int cont[])
{
    int faccia, k;

    for (faccia = 1; faccia <= 6; faccia++) {
        printf("%d: ", faccia);
        for (k = 0; k < cont[faccia]; k++)
            printf("*");
        printf(" (%d)\n", cont[faccia]);
    }
}

int main(void)
{
    unsigned int s;
    int n, i, lancio;
    int cont[7] = {0};               /* cont[1]..cont[6]; cont[0] non usato */

    if (scanf("%u %d", &s, &n) != 2 || n < 0) {
        printf("Input non valido\n");
        return 0;
    }
    gen_seme(s);
    printf("lanci:");
    for (i = 0; i < n; i++) {
        lancio = gen_dado();
        cont[lancio]++;
        printf(" %d", lancio);
    }
    printf("\n");
    stampa_istogramma(cont);
    printf("estrazioni: %d\n", gen_estrazioni());
    /* seme = 0;   <- NON compilerebbe: "seme" non è visibile fuori da generatore.c */
    return 0;
}
