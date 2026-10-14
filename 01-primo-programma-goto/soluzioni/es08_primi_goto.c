/*
 * 01 — es08: numeri primi fino a N  (Tipo esame) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es08
 */
#include <stdio.h>

int e_primo(int n)
{
    int d;

    if (n < 2)              /* riga 1: 0, 1 e i negativi non sono primi */
        goto no;
    d = 2;                  /* riga 2: primo divisore da provare        */

prova:                      /* "riga 3" */
    /* Basta provare i divisori fino alla radice di n: se n = d * e con
       d > radice(n), allora e < radice(n) e lo avrei gia' trovato.
       Scrivo d * d > n per evitare la radice (e i numeri reali). */
    if (d * d > n)
        goto si;
    if (n % d == 0)         /* riga 4: resto 0 = d divide n */
        goto no;
    d = d + 1;              /* riga 5 */
    goto prova;             /* riga 6 */

si:                         /* "riga 7" */
    return 1;               /* in C "vero" e' un numero diverso da 0: uso 1 */
no:                         /* "riga 8" */
    return 0;               /* "falso" e' 0 */
}

int conta_primi(int n)
{
    int conta = 0;
    int k = 2;              /* il piu' piccolo primo possibile */

    while (k <= n) {        /* se n < 2 non entro mai: conta resta 0 */
        if (e_primo(k))     /* e_primo da' 1 o 0: lo uso come condizione */
            conta = conta + 1;
        k = k + 1;
    }
    return conta;
}

int main(void)
{
    int n = 0;
    int k = 2;

    if (scanf("%d", &n) != 1) {
        printf("Input non valido\n");
        return 1;
    }

    printf("Primi fino a %d:", n);
    while (k <= n) {
        if (e_primo(k))
            printf(" %d", k);
        k = k + 1;
    }
    printf("\n");
    printf("Totale: %d\n", conta_primi(n));
    return 0;
}
