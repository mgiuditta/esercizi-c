/*
 * es04 — file 3 di 3: main.c  (questo file è GIÀ COMPLETO)
 * Legge seme e numero di lanci, lancia il dado e stampa un istogramma.
 * Esempio con input "42 12":
 *   lanci: 2 6 6 4 3 2 4 5 2 2 3 1
 *   1: * (1)
 *   2: **** (4)
 *   ...
 *   estrazioni: 12
 */
#include <stdio.h>
#include "generatore.h"

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
    int cont[7] = {0};

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
    return 0;
}
