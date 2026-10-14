/*
 * es02 — Conta ogni vocale separatamente  (SOLUZIONE)
 *
 * Input:  una riga di testo.
 * Output: quante a, e, i, o, u (maiuscole o minuscole) contiene,
 *         il totale delle vocali e quante altre lettere (consonanti).
 *
 * Come testarlo: make sol T=06 E=es02
 */
#include <stdio.h>
#include <ctype.h>

#define DIM 200

/* cont[0] = quante 'a', cont[1] = 'e', cont[2] = 'i', cont[3] = 'o', cont[4] = 'u'.
 * Restituisce quante lettere NON vocali ha trovato. */
int conta_vocali(char s[], int cont[])
{
    char vocali[] = "aeiou";   /* una stringa usata come "tabella" */
    int i, k, c, altre = 0, vocale;

    for (k = 0; k < 5; k++)
        cont[k] = 0;           /* azzerare: il vettore arriva con spazzatura */

    for (i = 0; s[i] != '\0'; i++) {
        /* Il cast a unsigned char è necessario: le funzioni di ctype.h
         * vogliono un valore tra 0 e 255. Una lettera accentata in UTF-8
         * produce char negativi, e passare un negativo è comportamento
         * indefinito. */
        c = tolower((unsigned char)s[i]);   /* 'A' -> 'a', '3' resta '3' */
        if (!isalpha(c))
            continue;                       /* spazi, cifre, punteggiatura: salta */
        vocale = 0;
        for (k = 0; k < 5; k++)
            if (c == vocali[k]) {
                cont[k]++;
                vocale = 1;
            }
        if (!vocale)
            altre++;
    }
    return altre;
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
