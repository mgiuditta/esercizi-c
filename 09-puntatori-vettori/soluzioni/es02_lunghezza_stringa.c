/*
 * es02 — La mia strlen con i puntatori  (Base)  — SOLUZIONE
 *
 * Testo: implementa lunghezza(s), che restituisce quanti caratteri ha la
 * stringa s (terminatore '\0' escluso) SENZA usare strlen e senza indice:
 * fai scorrere un puntatore fino al '\0' e restituisci la DIFFERENZA tra
 * puntatori.
 *
 * Come testarlo: make sol T=09 E=es02
 */
#include <stdio.h>

int lunghezza(const char *s)
{
    const char *p = s;     /* p parte dal primo carattere */

    while (*p != '\0')     /* finche' il carattere puntato non e' il terminatore */
        p++;               /* avanzo di 1 char = 1 byte */

    /* p ora punta al '\0'. La differenza p - s NON e' in byte ma in
     * "numero di elementi" (qui char, quindi coincidono): e' proprio
     * quanti caratteri ho superato. */
    return (int)(p - s);
}

int main(void)
{
    char riga[101];
    int n;

    /* %100[^\n] legge fino a fine riga (spazi compresi), max 100 caratteri.
     * Se la riga e' vuota scanf non legge nulla e restituisce 0 (o EOF):
     * in quel caso la stringa la rendo vuota io. */
    if (scanf("%100[^\n]", riga) != 1)
        riga[0] = '\0';

    n = lunghezza(riga);
    printf("\"%s\": lunghezza %d\n", riga, n);
    if (n > 0)
        /* riga + n - 1 = indirizzo dell'ultimo carattere prima del '\0' */
        printf("ultimo carattere: '%c'\n", *(riga + n - 1));
    else
        printf("stringa vuota: nessun ultimo carattere\n");
    return 0;
}
