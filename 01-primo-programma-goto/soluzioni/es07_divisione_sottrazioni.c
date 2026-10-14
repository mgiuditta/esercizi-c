/*
 * 01 — es07: divisione intera per sottrazioni successive  (Tipo esame) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es07
 */
#include <stdio.h>

int quoziente_goto(int a, int b)
{
    int q = 0;          /* riga 3: nessuna sottrazione fatta finora */

controllo:              /* "riga 4" */
    if (a < b)          /* non ci sta piu' un b intero dentro a: stop */
        goto fine;
    a = a - b;          /* riga 5: tolgo un b. Modifico la COPIA locale   */
                        /* di a: la variabile a del main non cambia.      */
    q = q + 1;          /* riga 6: conto la sottrazione appena fatta      */
    goto controllo;     /* riga 7 */

fine:                   /* "riga 8" */
    return q;
}

int resto_while(int a, int b)
{
    /* Stessa idea, versione strutturata (Bohm-Jacopini):
       il blocco "4-7" diventa un while con la condizione ROVESCIATA.
       Nel goto la condizione era "se a < b ESCI";
       nel while e' "finche' a >= b RESTA DENTRO". */
    while (a >= b) {
        a = a - b;
    }
    return a;           /* quello che non si e' potuto togliere e' il resto */
}

int main(void)
{
    int a = 0;
    int b = 0;
    int q = 0;
    int r = 0;

    /* || valuta da sinistra e si ferma al primo vero (cortocircuito):
       se scanf fallisce non guardo nemmeno a e b. */
    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b <= 0) {
        printf("Input non valido\n");
        return 0;
    }

    q = quoziente_goto(a, b);
    r = resto_while(a, b);
    printf("%d = %d * %d + %d\n", a, b, q, r);

    /* %% dentro printf stampa un singolo carattere % */
    if (q == a / b && r == a % b)
        printf("Controllo con / e %%: OK\n");
    else
        printf("Controllo con / e %%: SBAGLIATO (atteso q = %d, r = %d)\n",
               a / b, a % b);
    return 0;
}
