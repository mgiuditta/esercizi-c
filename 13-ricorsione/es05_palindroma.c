/*
 * es05 — Palindroma ricorsiva, senza distinguere maiuscole e minuscole  ·  Intermedio
 * Ispirato a: Trascrizione 4.2 (riduzione del problema verso il caso base), Appunti Unità 4 par. 2.5.
 *
 * Scrivi palindroma(s, i, j): restituisce 1 se la parte di stringa s[i..j] si legge
 * uguale nei due versi, 0 altrimenti. NIENTE cicli: confronta gli estremi e richiamati
 * sulla parte interna. "Anna" e "Radar" devono risultare palindrome (usa tolower di <ctype.h>).
 * Il main legge parole fino alla fine dell'input.
 *
 * Come testarlo: make test T=13 E=es05
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int palindroma(char s[], int i, int j)
{
    /* TODO: caso base (i >= j), confronto degli estremi con tolower, passo ricorsivo */
    (void)s;
    (void)i;
    (void)j;
    return 0;
}

int main(void)
{
    char parola[101];

    while (scanf("%100s", parola) == 1) {
        int n = (int)strlen(parola);
        if (palindroma(parola, 0, n - 1))
            printf("%s: palindroma\n", parola);
        else
            printf("%s: non palindroma\n", parola);
    }
    return 0;
}
