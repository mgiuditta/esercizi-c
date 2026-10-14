/*
 * es07 — Analisi di una frase: parole, parola più lunga, maiuscolo  (SOLUZIONE)
 *
 * Input:  una riga di testo (parole separate da uno o più spazi).
 * Output:
 *     parole: N
 *     piu lunga: PAROLA (L)        oppure "piu lunga: nessuna (0)" se N = 0
 *     maiuscolo: [RIGA IN MAIUSCOLO]
 * A parità di lunghezza vince la PRIMA parola trovata.
 *
 * Come testarlo: make sol T=06 E=es07
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Conta le parole contando gli INIZI di parola:
 * un carattere non-spazio che segue uno spazio (o è il primo). */
int conta_parole(char s[])
{
    int i, dentro = 0, parole = 0;   /* dentro: 1 se siamo in mezzo a una parola */
    for (i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i]))
            dentro = 0;
        else if (!dentro) {           /* passaggio da "fuori" a "dentro" */
            dentro = 1;
            parole++;
        }
    }
    return parole;
}

/* Copia in out la parola più lunga di s (con il suo '\0') e ne
 * restituisce la lunghezza. Se non ci sono parole, out = "" e restituisce 0.
 * out deve avere almeno DIM celle. */
int parola_piu_lunga(char s[], char out[])
{
    int i = 0, inizio, len;
    int best_inizio = 0, best_len = 0, k;

    while (s[i] != '\0') {
        while (s[i] != '\0' && isspace((unsigned char)s[i]))
            i++;
        inizio = i;
        while (s[i] != '\0' && !isspace((unsigned char)s[i]))
            i++;
        len = i - inizio;
        if (len > best_len) {         /* > e non >=: a parità resta la prima */
            best_len = len;
            best_inizio = inizio;
        }
    }
    /* Copia a mano dei best_len caratteri... */
    for (k = 0; k < best_len; k++)
        out[k] = s[best_inizio + k];
    /* ...e il terminatore! Senza, printf("%s", out) continuerebbe
     * a stampare quello che trova dopo, fuori dalla parola. */
    out[best_len] = '\0';
    return best_len;
}

void maiuscolo(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        s[i] = (char)toupper((unsigned char)s[i]);   /* toupper lascia invariato ciò che non è lettera minuscola */
}

int main(void)
{
    char s[DIM], lunga[DIM];
    size_t n;
    int len;

    if (fgets(s, DIM, stdin) == NULL) {
        printf("nessuna riga\n");
        return 1;
    }
    n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';

    printf("parole: %d\n", conta_parole(s));
    len = parola_piu_lunga(s, lunga);
    if (len == 0)
        printf("piu lunga: nessuna (0)\n");
    else
        printf("piu lunga: %s (%d)\n", lunga, len);
    maiuscolo(s);                     /* dopo: maiuscolo modifica s sul posto */
    printf("maiuscolo: [%s]\n", s);
    return 0;
}
