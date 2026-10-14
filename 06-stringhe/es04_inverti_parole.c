/*
 * es04 — Inverti ogni parola, lasciando le parole al loro posto  ·  Intermedio
 *
 * Input:  una riga di testo.
 * Output: la stessa riga tra [ ] in cui OGNI parola è scritta al contrario,
 *         ma l'ordine delle parole e gli spazi restano uguali.
 *         Esempio: "ciao mondo crudele" -> [oaic odnom eledurc]
 * Una "parola" è una sequenza di caratteri che non sono spazi (usa isspace).
 *
 * Come testarlo: make test T=06 E=es04
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 200

/* Inverte i caratteri da s[a] a s[b] compresi, sul posto (se a >= b non fa nulla). */
void inverti_tratto(char s[], int a, int b)
{
    /* TODO */
    (void)s; (void)a; (void)b;
}

/* Inverte ogni parola di s chiamando inverti_tratto. */
void inverti_parole(char s[])
{
    /* TODO: trova inizio e fine di ogni parola */
    (void)s;
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
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';

    inverti_parole(s);
    printf("[%s]\n", s);
    return 0;
}
