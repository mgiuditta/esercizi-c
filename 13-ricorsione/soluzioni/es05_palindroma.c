/*
 * es05 — Palindroma ricorsiva, senza distinguere maiuscole e minuscole  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.2 (riduzione del problema verso il caso base),
 * Appunti Unità 4 par. 2.5; variante dell'esercizio "parola palindroma" di LEZ 20.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Controlla se s[i..j] è palindroma.
 * Idea: confronto il primo e l'ultimo carattere, poi "accorcio" la parola da entrambi i lati. */
int palindroma(char s[], int i, int j)
{
    if (i >= j)                         /* caso base: 0 o 1 caratteri rimasti -> è palindroma */
        return 1;
    if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j]))
        return 0;                       /* secondo caso base: estremi diversi -> NON palindroma */
    return palindroma(s, i + 1, j - 1); /* passo: la parola si accorcia di 2, quindi i e j si avvicinano */
}
/* Nota sul cast (unsigned char): tolower vuole un valore positivo (o EOF);
 * un char con valore negativo (lettere accentate) darebbe comportamento indefinito. */

int main(void)
{
    char parola[101];

    /* %100s legge una parola (si ferma agli spazi) di al massimo 100 caratteri */
    while (scanf("%100s", parola) == 1) {
        int n = (int)strlen(parola);
        if (palindroma(parola, 0, n - 1))
            printf("%s: palindroma\n", parola);
        else
            printf("%s: non palindroma\n", parola);
    }
    return 0;
}
