/*
 * es03 — Cosa stampa?  (SOLUZIONE: stesso codice dello starter, con commenti)
 *
 * Ipotesi: codifica ASCII ('a' = 97, 'A' = 65, differenza 32).
 *
 * Come testarlo: make test T=06 E=es03
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[10] = "ciao";              /* 10 celle: c i a o \0 \0 \0 \0 \0 \0 */
    char t[] = "ciao";                /* dimensione scelta dal compilatore: 4 + 1 = 5 */
    char u[] = {'o', 'k', '\0', 'n', 'o', '\0'};   /* 6 celle, DUE terminatori */
    char w[20];

    /* A: sizeof = celle del vettore; strlen = caratteri prima di '\0' */
    printf("A: %zu %zu %zu\n", sizeof(s), sizeof(t), strlen(s));

    /* B: la stringa u finisce al PRIMO '\0' */
    printf("B: %zu %zu\n", sizeof(u), strlen(u));

    /* C: &u[3] è l'indirizzo della cella 3: da lì parte un'altra stringa */
    printf("C: %s|%s\n", u, &u[3]);

    /* D: un char stampato con %d mostra il suo codice ASCII */
    printf("D: %d %d\n", s[1], s[4]);

    /* E: aritmetica sui caratteri: 'c' - 32 = 'C', 'o' + 1 = 'p' */
    printf("E: %c%c\n", s[0] - 32, t[3] + 1);

    /* F: copia e concatenazione con string.h (w è abbastanza grande) */
    strcpy(w, s);
    strcat(w, "-");
    strcat(w, t);
    printf("F: %s %zu\n", w, strlen(w));

    /* G: confrontare indirizzi (sempre diversi per due vettori diversi)
     *    contro confrontare il contenuto con strcmp */
    printf("G: %d %d\n", &s[0] == &t[0], strcmp(s, t) == 0);

    /* H: un '\0' messo a mano "accorcia" la stringa */
    s[2] = '\0';
    printf("H: %s %zu %d\n", s, strlen(s), strcmp(s, "ci"));

    /* I: ordine lessicografico: si guarda il primo carattere diverso */
    printf("I: %d %d\n", strcmp("abc", "abd") < 0, strcmp("casa", "cas") > 0);

    return 0;
}
