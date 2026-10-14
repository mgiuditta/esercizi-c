/*
 * es07 — Analisi di una frase: parole, parola più lunga, maiuscolo  ·  Tipo esame
 *
 * Input:  una riga di testo (parole separate da uno o più spazi).
 * Output (esempio con "oggi studio   la programmazione in C"):
 *     parole: 6
 *     piu lunga: programmazione (14)
 *     maiuscolo: [OGGI STUDIO   LA PROGRAMMAZIONE IN C]
 * Se non ci sono parole: "piu lunga: nessuna (0)".
 * A parità di lunghezza vince la PRIMA parola trovata.
 * Completa le tre funzioni. Il main è già pronto.
 *
 * Come testarlo: make test T=06 E=es07
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Restituisce il numero di parole di s. */
int conta_parole(char s[])
{
    /* TODO */
    (void)s;
    return 0;
}

/* Copia in out la parola più lunga di s (terminata da '\0')
 * e restituisce la sua lunghezza (0 se non ci sono parole). */
int parola_piu_lunga(char s[], char out[])
{
    /* TODO */
    (void)s;
    out[0] = '\0';   /* provvisorio: out è una stringa vuota */
    return 0;
}

/* Trasforma s in maiuscolo, sul posto (usa toupper). */
void maiuscolo(char s[])
{
    /* TODO */
    (void)s;
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
    maiuscolo(s);
    printf("maiuscolo: [%s]\n", s);
    return 0;
}
