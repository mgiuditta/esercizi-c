/*
 * es04 — Espandere stringhe compresse con la ricorsione  (Tipo esame)
 *
 * Una stringa compressa usa la notazione  k[...]  = "ripeti k volte il contenuto".
 * Le parentesi possono essere annidate:
 *     2[ab]3[x]c   ->  ababxxxc
 *     2[a3[b]]     ->  abbbabbb
 * Regola (grammatica):  sequenza := { lettera | numero '[' sequenza ']' }
 * Il main legge una parola alla volta e la espande in un buffer di al
 * massimo MAXOUT caratteri.
 *
 * Completa espandi(p, out, pos, max):
 *   - *p e' il cursore sulla stringa compressa: la funzione lo fa AVANZARE
 *     (per questo riceve const char **p);
 *   - scrive i caratteri espansi in out a partire da pos;
 *   - si ferma, SENZA consumarli, su '\0' o ']';
 *   - ritorna la nuova posizione libera in out, oppure ERR_FORMATO
 *     (es. "3a", "2[ab", "x-y") o ERR_LUNGA (si supererebbe max).
 * Idea: lettera -> la copi; numero k -> leggi il numero, salta '[',
 * chiama RICORSIVAMENTE espandi per il contenuto, controlla e salta ']',
 * poi ricopia il pezzo appena scritto altre k-1 volte (k == 0: cancellalo).
 * decodifica() e main() sono gia' scritti.
 *
 * Come testarlo: make test T=15 E=es04
 */
#include <stdio.h>
#include <ctype.h>

#define MAXIN 64
#define MAXOUT 64

#define ERR_FORMATO (-1)
#define ERR_LUNGA   (-2)

int espandi(const char **p, char out[], int pos, int max)
{
    /* TODO: while (**p != '\0' && **p != ']') { ... }
       Ricorda: (*p)++ sposta il cursore del chiamante; isdigit e isalpha
       vogliono un (unsigned char). Controlla SEMPRE pos < max prima di scrivere. */
    (void)p; (void)out; (void)max;
    return pos;
}

int decodifica(const char *s, char out[], int max)
{
    const char *cursore = s;
    int lun = espandi(&cursore, out, 0, max);

    if (lun < 0)
        return lun;
    if (*cursore != '\0')
        return ERR_FORMATO;      /* ci siamo fermati su una ']' senza '[' (o espandi non e' avanzata) */
    out[lun] = '\0';
    return lun;
}

int main(void)
{
    char s[MAXIN + 1];
    char out[MAXOUT + 1];
    int lun;

    while (scanf("%64s", s) == 1) {
        lun = decodifica(s, out, MAXOUT);
        if (lun == ERR_FORMATO)
            printf("%s -> errore di formato\n", s);
        else if (lun == ERR_LUNGA)
            printf("%s -> troppo lunga\n", s);
        else
            printf("%s -> \"%s\" (lunghezza %d)\n", s, out, lun);
    }
    return 0;
}
