/*
 * es08 — Parole e parola piu' lunga con char*  (Tipo esame)
 *
 * Testo: una riga contiene parole separate da uno o piu' spazi ' '.
 *  1) conta_parole(s) restituisce quante parole ci sono.
 *  2) parola_piu_lunga(s, &lung) restituisce un PUNTATORE al primo carattere
 *     della parola piu' lunga (a parita', la prima) e scrive in *lung la sua
 *     lunghezza. Se non ci sono parole restituisce NULL e *lung = 0.
 * Tutto scorrendo la stringa con puntatori a char, senza indici e senza
 * funzioni di <string.h>.
 *
 * Input:  una riga.   Esempio: ciao mare sole
 * Output: parole: 3
 *         piu' lunga: "ciao" (4 caratteri, posizione 0)
 *
 * Come testarlo: make test T=09 E=es08
 */
#include <stdio.h>

int conta_parole(const char *s)
{
    /* TODO: scorri con un const char *p: salta gli spazi, se trovi l'inizio
       di una parola conta +1 e salta fino al prossimo spazio o al '\0'. */
    (void)s;   /* cancella questa riga */
    return 0;
}

const char *parola_piu_lunga(const char *s, int *lung)
{
    /* TODO: come sopra, ma per ogni parola ricordati il puntatore "inizio";
       quando la parola finisce, la sua lunghezza e' p - inizio. */
    (void)s;   /* cancella questa riga */
    *lung = 0;
    return NULL;
}

int main(void)
{
    char riga[201];
    const char *p;
    int lung;

    if (scanf("%200[^\n]", riga) != 1)
        riga[0] = '\0';

    printf("parole: %d\n", conta_parole(riga));
    p = parola_piu_lunga(riga, &lung);
    if (p == NULL) {
        printf("nessuna parola\n");
    } else {
        /* %.*s stampa al massimo "lung" caratteri a partire da p */
        printf("piu' lunga: \"%.*s\" (%d caratteri, posizione %d)\n",
               lung, p, lung, (int)(p - riga));
    }
    return 0;
}
