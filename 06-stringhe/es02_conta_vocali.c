/*
 * es02 — Conta ogni vocale separatamente  ·  Base
 *
 * Input:  una riga di testo.
 * Output: quante a, e, i, o, u (maiuscole o minuscole) contiene,
 *         il totale delle vocali e quante altre lettere (consonanti).
 *         Spazi, cifre e punteggiatura non si contano.
 * Esempio: "Programmare In C e Bello" -> a: 2, e: 3, i: 1, o: 2, u: 0,
 *          vocali: 8, altre lettere: 12
 * Completa conta_vocali usando tolower e isalpha di <ctype.h>.
 *
 * Come testarlo: make test T=06 E=es02
 */
#include <stdio.h>
#include <ctype.h>

#define DIM 200

/* Riempie cont[0..4] con il numero di a, e, i, o, u.
 * Restituisce quante lettere NON vocali ci sono. */
int conta_vocali(char s[], int cont[])
{
    int k;
    (void)s;
    for (k = 0; k < 5; k++)
        cont[k] = 0;
    /* TODO: scorri s fino al '\0'; per ogni carattere:
     *       - convertilo in minuscolo con tolower((unsigned char)s[i])
     *       - se non è una lettera (isalpha) saltalo
     *       - se è una vocale incrementa il contatore giusto, altrimenti conta una "altra" */
    return 0;
}

int main(void)
{
    char s[DIM];
    char nomi[] = "aeiou";
    int cont[5];
    int k, altre, totale = 0;

    if (fgets(s, DIM, stdin) == NULL) {
        printf("nessuna riga\n");
        return 1;
    }
    altre = conta_vocali(s, cont);
    for (k = 0; k < 5; k++) {
        printf("%c: %d\n", nomi[k], cont[k]);
        totale += cont[k];
    }
    printf("vocali: %d\n", totale);
    printf("altre lettere: %d\n", altre);
    return 0;
}
