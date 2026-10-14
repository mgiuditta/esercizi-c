/*
 * es05 — Frase palindroma  ·  Intermedio
 *
 * Input:  più righe di testo, fino alla fine dell'input.
 * Output: per ogni riga "SI: riga" se è palindroma, "NO: riga" se non lo è.
 *         Si considerano SOLO lettere e cifre (isalnum), senza distinguere
 *         maiuscole e minuscole (tolower).
 *         Esempi: "I topi non avevano nipoti" -> SI;  "Ciao" -> NO.
 *         Una riga senza lettere né cifre (anche vuota) è palindroma.
 *
 * Come testarlo: make test T=06 E=es05
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Restituisce 1 se s è palindroma, 0 altrimenti. */
int palindroma(char s[])
{
    /* TODO: due indici, uno dall'inizio e uno dalla fine, che saltano
     *       i caratteri che non sono lettere/cifre */
    (void)s;
    return 0;
}

int main(void)
{
    char s[DIM];
    size_t n;

    while (fgets(s, DIM, stdin) != NULL) {
        n = strlen(s);
        if (n > 0 && s[n - 1] == '\n')
            s[n - 1] = '\0';
        printf("%s: %s\n", palindroma(s) ? "SI" : "NO", s);
    }
    return 0;
}
