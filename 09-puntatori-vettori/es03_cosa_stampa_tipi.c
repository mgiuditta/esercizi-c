/*
 * es03 — Cosa stampa? Il tipo puntato comanda  (Base)
 *
 * Questo esercizio e' un "Cosa stampa?": il codice e' gia' completo.
 * Leggi il README, scrivi la tua previsione riga per riga, POI esegui.
 * Ispirato all'E-tivity 3.4 (pc, pc2, pi, pi2, v[], i).
 *
 * Per avere un output identico su ogni computer non stampiamo MAI
 * indirizzi (cambiano a ogni esecuzione): stampiamo DIFFERENZE in byte
 * e risultati di sizeof. Assunzione (vera su macOS arm64 e Linux x86-64):
 * sizeof(int) = 4, sizeof(char *) = sizeof(char **) = 8.
 *
 * Come testarlo: make test T=09 E=es03
 */
#include <stdio.h>

int main(void)
{
    char *pc, *pc2;                      /* due puntatori a char  */
    int *pi, *pi2;                       /* due puntatori a int   */
    char v[4] = {'a', 'b', 'c', 'd'};    /* 4 char = 4 byte       */
    int i = 0x01010101;                  /* ogni byte di i vale 1: cosi' il
                                            risultato non dipende dall'ordine
                                            in cui il processore salva i byte */

    pc = &v[1];                                   /* come nell'E-tivity: corretto */
    printf("A) *pc = %c\n", *pc);
    printf("B) pc - v = %d\n", (int)(pc - v));
    printf("C) sizeof *pc = %zu, sizeof pc = %zu\n", sizeof *pc, sizeof pc);

    pi = &i;                                      /* corretto: int* su un int */
    printf("D) *pi = %d, sizeof *pi = %zu\n", *pi, sizeof *pi);
    printf("E) byte tra pi e pi + 1 = %d\n", (int)((char *)(pi + 1) - (char *)pi));

    /* Il prof scrive pi2 = &v[1]: un int* su un char. NON lo eseguiamo
     * (leggere *pi2 sarebbe comportamento indefinito): vedi README. */
    pi2 = NULL;
    printf("F) pi2 == NULL vale %d\n", pi2 == NULL);

    pc2 = (char *)&i + 1;                         /* E-tivity: il cast viene PRIMA del + */
    printf("G) byte tra &i e pc2 = %d\n", (int)(pc2 - (char *)&i));
    printf("H) *pc2 = %d\n", *pc2);
    printf("I) byte tra &i e (char *)(&i + 1) = %d\n",
           (int)((char *)(&i + 1) - (char *)&i));

    /* &pc2 e' l'indirizzo DEL PUNTATORE pc2: tipo char ** */
    printf("L) byte tra &pc2 e &pc2 + 1 = %d\n",
           (int)((char *)(&pc2 + 1) - (char *)&pc2));

    *pc = 'X';                                    /* scrivo attraverso pc: cambia v[1] */
    printf("M) v = %c%c%c%c\n", v[0], v[1], v[2], v[3]);
    printf("N) *(v + 2) == v[2] vale %d\n", *(v + 2) == v[2]);
    printf("O) &v[3] - &v[0] = %d\n", (int)(&v[3] - &v[0]));
    return 0;
}
