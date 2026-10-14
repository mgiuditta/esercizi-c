/*
 * es03 — Cosa stampa?  ·  Base
 *
 * Non devi scrivere codice: leggi il programma e, SENZA eseguirlo,
 * scrivi la tua previsione delle righe A..I (sul README o nel commento in fondo).
 * Poi esegui il test: passa già, quindi l'output vero è in
 * tests/es03_cosa_stampa.out. Confrontalo con la tua previsione.
 * Ipotesi: codifica ASCII ('a' = 97, 'A' = 65).
 *
 * Come testarlo: make test T=06 E=es03
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[10] = "ciao";
    char t[] = "ciao";
    char u[] = {'o', 'k', '\0', 'n', 'o', '\0'};
    char w[20];

    printf("A: %zu %zu %zu\n", sizeof(s), sizeof(t), strlen(s));

    printf("B: %zu %zu\n", sizeof(u), strlen(u));

    printf("C: %s|%s\n", u, &u[3]);

    printf("D: %d %d\n", s[1], s[4]);

    printf("E: %c%c\n", s[0] - 32, t[3] + 1);

    strcpy(w, s);
    strcat(w, "-");
    strcat(w, t);
    printf("F: %s %zu\n", w, strlen(w));

    printf("G: %d %d\n", &s[0] == &t[0], strcmp(s, t) == 0);

    s[2] = '\0';
    printf("H: %s %zu %d\n", s, strlen(s), strcmp(s, "ci"));

    printf("I: %d %d\n", strcmp("abc", "abd") < 0, strcmp("casa", "cas") > 0);

    /* La tua previsione:
     * A:
     * B:
     * C:
     * D:
     * E:
     * F:
     * G:
     * H:
     * I:
     */
    return 0;
}
