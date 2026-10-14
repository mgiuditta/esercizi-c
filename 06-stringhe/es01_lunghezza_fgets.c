/*
 * es01 — Lunghezza a mano e il '\n' di fgets  ·  Base
 *
 * Input:  una riga di testo (può contenere spazi).
 * Output (esempio con la riga "ciao mondo"):
 *     con a capo: 11
 *     senza a capo: 10
 *     strlen: 10
 *     [ciao mondo]
 * Completa mia_strlen (SENZA usare strlen) e togli_a_capo. Il main è già pronto.
 *
 * Come testarlo: make test T=06 E=es01
 */
#include <stdio.h>
#include <string.h>

#define DIM 100

/* Restituisce il numero di caratteri prima del terminatore '\0'. */
int mia_strlen(char s[])
{
    /* TODO: scorri finché non trovi '\0' */
    (void)s;
    return 0;
}

/* Se l'ultimo carattere di s è '\n', lo sostituisce con '\0'. */
void togli_a_capo(char s[])
{
    /* TODO: attenzione alla stringa vuota (lunghezza 0) */
    (void)s;
}

int main(void)
{
    char s[DIM];

    if (fgets(s, DIM, stdin) == NULL) {
        printf("nessuna riga\n");
        return 1;
    }
    printf("con a capo: %d\n", mia_strlen(s));
    togli_a_capo(s);
    printf("senza a capo: %d\n", mia_strlen(s));
    printf("strlen: %zu\n", strlen(s));
    printf("[%s]\n", s);
    return 0;
}
