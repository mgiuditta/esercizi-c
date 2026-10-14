/*
 * es04 — Fibonacci: quante chiamate costa la ricorsione multipla?  ·  Intermedio
 * Ispirato a: Appunti Unità 4, par. 2.11 (Ricorsione multipla) e 2.13 (Ricorsione ed efficienza).
 *
 * 1) F(n): versione ricorsiva degli appunti (F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)),
 *    che a OGNI chiamata incrementa la variabile globale "chiamate".
 * 2) F_iter(n): stessa cosa con un ciclo for (nessuna chiamata ricorsiva).
 * Il main legge vari n e stampa risultato, numero di chiamate e risultato iterativo.
 *
 * Come testarlo: make test T=13 E=es04
 */
#include <stdio.h>

long chiamate = 0;   /* globale: la vedono tutte le funzioni del file */

int F(int n)
{
    /* TODO: incrementa chiamate, poi i DUE casi base e il passo con due chiamate */
    (void)n;
    return 0;
}

int F_iter(int n)
{
    /* TODO: tieni solo gli ultimi due valori (prec e corr) e falli avanzare in un for */
    (void)n;
    return 0;
}

int main(void)
{
    int n, r;

    while (scanf("%d", &n) == 1) {
        if (n < 0 || n > 30) {
            printf("n fuori intervallo (0..30)\n");
            continue;
        }
        chiamate = 0;
        r = F(n);
        printf("F(%d) = %d | chiamate ricorsive: %ld | iterativo: %d\n",
               n, r, chiamate, F_iter(n));
    }
    return 0;
}
