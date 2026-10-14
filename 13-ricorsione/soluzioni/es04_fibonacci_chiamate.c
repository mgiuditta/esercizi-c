/*
 * es04 — Fibonacci: quante chiamate costa la ricorsione multipla?  (SOLUZIONE)
 * Ispirato a: Appunti Unità 4, par. 2.11 (Ricorsione multipla) e 2.13 (Ricorsione ed efficienza).
 */
#include <stdio.h>

/* Variabile globale: visibile da tutte le funzioni del file.
 * La usiamo per contare le chiamate senza doverla passare come parametro. */
long chiamate = 0;

/* Versione ricorsiva degli Appunti (par. 2.11), con in più il contatore. */
int F(int n)
{
    chiamate++;                     /* ogni volta che entro qui è una chiamata in più */
    if (n == 0)                     /* primo caso base */
        return 0;
    if (n == 1)                     /* secondo caso base: servono DUE casi base perché */
        return 1;                   /* il passo usa sia n-1 sia n-2 */
    return F(n - 1) + F(n - 2);     /* ricorsione multipla: DUE chiamate per ogni chiamata */
}

/* Versione iterativa: tiene solo gli ultimi due valori e li fa "scorrere". */
int F_iter(int n)
{
    int prec = 0, corr = 1, i, prossimo;   /* prec = F(0), corr = F(1) */

    if (n == 0)
        return 0;
    for (i = 2; i <= n; i++) {
        prossimo = prec + corr;     /* F(i) = F(i-1) + F(i-2) */
        prec = corr;                /* faccio avanzare la "finestra" di due valori */
        corr = prossimo;
    }
    return corr;
}

int main(void)
{
    int n, r;

    while (scanf("%d", &n) == 1) {
        if (n < 0 || n > 30) {      /* oltre 30 la versione ricorsiva diventa lentissima */
            printf("n fuori intervallo (0..30)\n");
            continue;
        }
        chiamate = 0;               /* azzero il contatore prima di ogni misura */
        r = F(n);
        printf("F(%d) = %d | chiamate ricorsive: %ld | iterativo: %d\n",
               n, r, chiamate, F_iter(n));
    }
    return 0;
}
