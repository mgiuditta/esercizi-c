/*
 * es02 — La mia strlen con i puntatori  (Base)
 *
 * Testo: implementa lunghezza(s), che restituisce quanti caratteri ha la
 * stringa s (terminatore '\0' escluso) SENZA usare strlen e senza indice:
 * fai scorrere un puntatore fino al '\0' e restituisci la DIFFERENZA tra
 * puntatori.
 *
 * Input:  una riga di testo.   Esempio: ciao mondo
 * Output: "ciao mondo": lunghezza 10
 *         ultimo carattere: 'o'
 *
 * Come testarlo: make test T=09 E=es02
 */
#include <stdio.h>

int lunghezza(const char *s)
{
    /* TODO: const char *p = s; fai avanzare p finche' *p non e' '\0',
       poi restituisci (int)(p - s). */
    (void)s;   /* cancella questa riga quando scrivi la soluzione */
    return 0;
}

int main(void)
{
    char riga[101];
    int n;

    /* legge un'intera riga (spazi compresi); se e' vuota, la stringa resta vuota */
    if (scanf("%100[^\n]", riga) != 1)
        riga[0] = '\0';

    n = lunghezza(riga);
    printf("\"%s\": lunghezza %d\n", riga, n);
    if (n > 0)
        printf("ultimo carattere: '%c'\n", *(riga + n - 1));
    else
        printf("stringa vuota: nessun ultimo carattere\n");
    return 0;
}
