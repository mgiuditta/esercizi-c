/*
 * es06 — Confronta due stringhe a mano (la tua strcmp)  ·  Intermedio
 *
 * Input:  coppie di parole (due per riga), fino alla fine dell'input.
 * Output: per ogni coppia una riga come
 *     abc abd -> mia: -1, strcmp: -1, ==: 0
 * dove "mia" è il segno del risultato di mia_strcmp, "strcmp" il segno
 * della funzione vera (devono coincidere) e "==" il confronto tra gli
 * indirizzi dei due vettori.
 * Completa mia_strcmp (SENZA usare strcmp) e segno.
 *
 * Come testarlo: make test T=06 E=es06
 */
#include <stdio.h>
#include <string.h>

#define DIM 50

/* <0 se s1 viene prima di s2, 0 se sono uguali, >0 se viene dopo. */
int mia_strcmp(char s1[], char s2[])
{
    /* TODO: avanza finché i caratteri sono uguali e non sei alla fine,
     *       poi restituisci la differenza tra i due caratteri */
    (void)s1; (void)s2;
    return 0;
}

/* Restituisce -1 se x < 0, 1 se x > 0, 0 se x == 0. */
int segno(int x)
{
    /* TODO */
    (void)x;
    return 0;
}

int main(void)
{
    char a[DIM], b[DIM];

    while (scanf("%49s %49s", a, b) == 2) {
        printf("%s %s -> mia: %d, strcmp: %d, ==: %d\n",
               a, b,
               segno(mia_strcmp(a, b)),
               segno(strcmp(a, b)),
               &a[0] == &b[0]);
    }
    return 0;
}
