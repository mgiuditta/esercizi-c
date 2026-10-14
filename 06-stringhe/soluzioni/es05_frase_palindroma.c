/*
 * es05 — Frase palindroma  (SOLUZIONE)
 *
 * Input:  più righe di testo, fino alla fine dell'input.
 * Output: per ogni riga "SI: riga" se è palindroma, "NO: riga" se non lo è.
 *         Si considerano SOLO lettere e cifre, senza distinguere maiuscole
 *         e minuscole: "I topi non avevano nipoti" è palindroma.
 *
 * Come testarlo: make sol T=06 E=es05
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Restituisce 1 se s è palindroma (ignorando ciò che non è lettera o cifra), 0 altrimenti. */
int palindroma(char s[])
{
    int i = 0;
    int j = (int)strlen(s) - 1;   /* ultimo carattere; -1 se la stringa è vuota */

    while (i < j) {
        /* sposta i in avanti finché non trova una lettera/cifra */
        if (!isalnum((unsigned char)s[i])) {
            i++;
            continue;
        }
        /* sposta j indietro finché non trova una lettera/cifra */
        if (!isalnum((unsigned char)s[j])) {
            j--;
            continue;
        }
        /* ora entrambi puntano a caratteri "utili": confrontiamoli
         * senza distinguere maiuscole/minuscole */
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j]))
            return 0;            /* una coppia diversa basta per dire NO */
        i++;
        j--;
    }
    /* i e j si sono incontrati senza trovare differenze */
    return 1;
}

int main(void)
{
    char s[DIM];
    size_t n;

    /* fgets restituisce NULL alla fine dell'input: il ciclo legge tutte le righe */
    while (fgets(s, DIM, stdin) != NULL) {
        n = strlen(s);
        if (n > 0 && s[n - 1] == '\n')
            s[n - 1] = '\0';
        printf("%s: %s\n", palindroma(s) ? "SI" : "NO", s);
    }
    return 0;
}
