/*
 * es04 — Inverti ogni parola, lasciando le parole al loro posto  (SOLUZIONE)
 *
 * Input:  una riga di testo.
 * Output: la stessa riga tra [ ] in cui OGNI parola è scritta al contrario,
 *         ma l'ordine delle parole e gli spazi restano uguali.
 *         Esempio: "ciao mondo crudele" -> "oaic odnom eledurc"
 *
 * Come testarlo: make sol T=06 E=es04
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Inverte i caratteri da s[a] a s[b] compresi, sul posto.
 * È lo stesso algoritmo di es04 della cartella 05 (vettori di int):
 * una stringa È un vettore, solo di char. */
void inverti_tratto(char s[], int a, int b)
{
    char tmp;
    while (a < b) {
        tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;
        a++;
        b--;
    }
}

/* Trova ogni parola (sequenza massimale di caratteri non-spazio)
 * e la inverte con inverti_tratto. */
void inverti_parole(char s[])
{
    int i = 0, inizio;
    while (s[i] != '\0') {
        /* salta gli spazi */
        while (s[i] != '\0' && isspace((unsigned char)s[i]))
            i++;
        inizio = i;                     /* qui comincia una parola (o la stringa è finita) */
        while (s[i] != '\0' && !isspace((unsigned char)s[i]))
            i++;
        /* ora i è il primo carattere DOPO la parola: l'ultimo della parola è i-1.
         * Se la parola è vuota (fine stringa), inizio = i e inizio > i-1:
         * inverti_tratto non fa nulla. */
        inverti_tratto(s, inizio, i - 1);
    }
}

int main(void)
{
    char s[DIM];
    size_t n;

    if (fgets(s, DIM, stdin) == NULL) {
        printf("nessuna riga\n");
        return 1;
    }
    n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')      /* togliamo l'a capo di fgets */
        s[n - 1] = '\0';

    inverti_parole(s);
    printf("[%s]\n", s);
    return 0;
}
