/*
 * 01 — es03: somma dei primi N numeri con goto  (Base) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es03
 */
#include <stdio.h>

int somma_primi_goto(int n)
{
    int s = 0;   /* riga 1: la somma parte da 0 (elemento neutro della +)  */
    int i = 1;   /* riga 2: il primo numero da sommare                     */

controllo:              /* "riga 3": qui si torna a ogni giro              */
    if (i > n)          /* se ho superato n ho finito.                     */
        goto fine;      /* Con n = 0 salto subito: la somma resta 0.       */
    s = s + i;          /* riga 4: aggiungo il numero corrente             */
    i = i + 1;          /* riga 5: passo al numero successivo              */
    goto controllo;     /* riga 6: torno al controllo                      */

fine:                   /* "riga 7"                                        */
    return s;           /* invariante: qui s = 1 + 2 + ... + (i - 1)       */
}

int main(void)
{
    int n = 0;

    if (scanf("%d", &n) != 1) {
        printf("Input non valido\n");
        return 1;
    }
    printf("Somma da 1 a %d = %d\n", n, somma_primi_goto(n));
    return 0;
}
