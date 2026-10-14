/*
 * es04 — Espandere stringhe compresse con la ricorsione  (Tipo esame) — SOLUZIONE
 *
 * Una stringa compressa usa la notazione  k[...]  = "ripeti k volte il contenuto".
 * Le parentesi possono essere annidate:
 *     2[ab]3[x]c   ->  ababxxxc
 *     2[a3[b]]     ->  abbbabbb
 * Grammatica (cioe' le regole di com'e' fatta una stringa valida):
 *     sequenza := { lettera | numero '[' sequenza ']' }
 * Ogni parola letta da stdin viene espansa in un buffer di al massimo
 * MAXOUT caratteri. Errori: "errore di formato", "troppo lunga".
 *
 * Come testarlo: make sol T=15 E=es04
 */
#include <stdio.h>
#include <ctype.h>

#define MAXIN 64
#define MAXOUT 64

#define ERR_FORMATO (-1)
#define ERR_LUNGA   (-2)

/* Espande una SEQUENZA a partire dal carattere puntato da *p e la scrive in
 * out a partire dalla posizione pos. Si ferma (senza consumarli) su '\0' o ']'.
 * Ritorna la nuova posizione libera in out, oppure ERR_FORMATO / ERR_LUNGA.
 *
 * Perche' const char **p (puntatore a puntatore)? Perche' la funzione deve
 * far AVANZARE il cursore del chiamante: dopo che la chiamata ricorsiva ha
 * letto "3[b]", il chiamante deve ripartire dal carattere dopo la ']'.
 * Con un normale const char *p avanzerebbe solo la copia locale (cartella 12, Appunti 1.12). */
int espandi(const char **p, char out[], int pos, int max)
{
    int k, inizio, lun, r, i;

    while (**p != '\0' && **p != ']') {
        if (isdigit((unsigned char) **p)) {
            k = 0;
            while (isdigit((unsigned char) **p)) {   /* numero di piu' cifre: "12" = 1*10 + 2 */
                k = k * 10 + (**p - '0');
                (*p)++;                              /* (*p)++ sposta il cursore; *p++ sposterebbe p */
                if (k > 1000)
                    return ERR_LUNGA;                /* evita overflow di k su numeri enormi */
            }
            if (**p != '[')
                return ERR_FORMATO;                  /* "3a": dopo il numero serve '[' */
            (*p)++;                                  /* salto '[' */

            inizio = pos;
            pos = espandi(p, out, pos, max);         /* CHIAMATA RICORSIVA sul contenuto */
            if (pos < 0)
                return pos;                          /* l'errore "risale" tutte le chiamate */
            if (**p != ']')
                return ERR_FORMATO;                  /* "2[ab": la stringa e' finita prima della ']' */
            (*p)++;                                  /* salto ']' */

            lun = pos - inizio;                      /* il contenuto e' gia' scritto UNA volta */
            if (k == 0) {
                pos = inizio;                        /* 0 ripetizioni: lo cancello */
            } else {
                for (r = 1; r < k; r++) {            /* ne aggiungo altre k-1 copie */
                    if (pos + lun > max)
                        return ERR_LUNGA;
                    for (i = 0; i < lun; i++)
                        out[pos + i] = out[inizio + i];
                    pos += lun;
                }
            }
        } else if (isalpha((unsigned char) **p)) {
            if (pos >= max)
                return ERR_LUNGA;                    /* controllo PRIMA di scrivere */
            out[pos] = **p;
            pos++;
            (*p)++;
        } else {
            return ERR_FORMATO;                      /* carattere non previsto, es. '[' senza numero */
        }
    }
    return pos;
}

/* Funzione "di comodo" che prepara il cursore e controlla la fine. */
int decodifica(const char *s, char out[], int max)
{
    const char *cursore = s;
    int lun = espandi(&cursore, out, 0, max);

    if (lun < 0)
        return lun;
    if (*cursore != '\0')
        return ERR_FORMATO;      /* ci siamo fermati su una ']' senza '[': es. "ab]" */
    out[lun] = '\0';             /* out ha MAXOUT+1 posti: c'e' sempre spazio per '\0' */
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
