/*
 * 01 — es07: divisione intera per sottrazioni successive  (Tipo esame)
 *
 * Testo: il processore "sa" solo sommare e sottrarre: la divisione intera
 * si puo' fare togliendo b da a finche' si puo', e contando quante volte.
 * Pseudocodice (come quelli del blocco 1):
 *
 *     1  read a            (a >= 0)
 *     2  read b            (b > 0)
 *     3  q = 0
 *     4  if a < b then goto 8
 *     5  a = a - b
 *     6  q = q + 1
 *     7  goto 4
 *     8  write q           (quoziente)  e  a  (cio' che resta = resto)
 *
 * Devi scrivere DUE funzioni:
 *   - quoziente_goto(a, b): restituisce q, traducendo lo pseudocodice con goto;
 *   - resto_while(a, b):    restituisce il resto, stessa idea ma con while
 *                           (nessun goto).
 * Non usare gli operatori / e % dentro le due funzioni: li usa il main
 * per CONTROLLARE che i tuoi risultati siano giusti.
 *
 * Input: a b.  Se a < 0 oppure b <= 0 stampa "Input non valido".
 * Esempio:  17 5   ->   17 = 5 * 3 + 2
 *                       Controllo con / e %: OK
 *
 * Come testarlo: make test T=01 E=es07
 */
#include <stdio.h>

int quoziente_goto(int a, int b)
{
    int q = 0;
    /* TODO: traduci le righe 4-8 con un'etichetta e goto */
    (void)a;
    (void)b;
    return q; /* TODO: valore provvisorio */
}

int resto_while(int a, int b)
{
    /* TODO: finche' a >= b, togli b da a. Alla fine a e' il resto. */
    (void)b;
    return a; /* TODO: valore provvisorio */
}

int main(void)
{
    int a = 0;
    int b = 0;
    int q = 0;
    int r = 0;

    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b <= 0) {
        printf("Input non valido\n");
        return 0;
    }

    q = quoziente_goto(a, b);
    r = resto_while(a, b);
    printf("%d = %d * %d + %d\n", a, b, q, r);

    if (q == a / b && r == a % b)
        printf("Controllo con / e %%: OK\n");
    else
        printf("Controllo con / e %%: SBAGLIATO (atteso q = %d, r = %d)\n",
               a / b, a % b);
    return 0;
}
