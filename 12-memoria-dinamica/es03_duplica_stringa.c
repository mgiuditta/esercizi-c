/*
 * Esercizio 03 — Duplicare una stringa nello heap (strdup fatta a mano)  (Base)
 *
 * Completa duplica(s): alloca ESATTAMENTE i byte necessari per una copia
 * di s (terminatore '\0' compreso), copia i caratteri e restituisce il
 * puntatore alla copia (NULL se malloc fallisce).
 * Il main mette la copia in maiuscolo: l'originale non deve cambiare.
 *
 * Input: una riga di testo (anche vuota).
 *
 * Come testarlo: make test T=12 E=es03
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *duplica(const char *s)
{
    /* TODO:
       1. calcola la lunghezza con strlen
       2. alloca con malloc i byte necessari (ricordati del '\0'!)
       3. se malloc da' NULL, ritorna NULL
       4. copia i caratteri (terminatore compreso) e ritorna la copia */
    (void)s;
    return NULL;
}

int main(void)
{
    char riga[200];
    char *c;
    size_t i, len;

    if (fgets(riga, sizeof riga, stdin) == NULL)
        riga[0] = '\0';                 /* input del tutto vuoto */
    riga[strcspn(riga, "\n")] = '\0';   /* toglie l'a capo letto da fgets */

    c = duplica(riga);
    if (c == NULL) {
        printf("errore di allocazione\n");
        return 1;
    }
    len = strlen(c);
    for (i = 0; i < len; i++)
        c[i] = (char) toupper((unsigned char) c[i]);

    printf("originale: [%s]\n", riga);
    printf("copia:     [%s]\n", c);
    printf("blocchi distinti: %s\n", c != riga ? "si" : "no");
    printf("byte allocati: %d\n", (int)(len + 1));

    free(c);
    return 0;
}
