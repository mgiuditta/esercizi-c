/*
 * es08 — Parole e parola piu' lunga con char*  (Tipo esame)  — SOLUZIONE
 *
 * Testo: una riga contiene parole separate da uno o piu' spazi ' '.
 *  1) conta_parole(s) restituisce quante parole ci sono.
 *  2) parola_piu_lunga(s, &lung) restituisce un PUNTATORE al primo carattere
 *     della parola piu' lunga (a parita', la prima) e scrive in lung la sua
 *     lunghezza. Se non ci sono parole restituisce NULL e lung = 0.
 * Tutto scorrendo la stringa con puntatori a char, senza indici e senza
 * funzioni di <string.h>.
 *
 * Come testarlo: make sol T=09 E=es08
 */
#include <stdio.h>

int conta_parole(const char *s)
{
    const char *p = s;
    int conta = 0;

    while (*p != '\0') {
        while (*p == ' ')            /* salto gli spazi (anche multipli) */
            p++;
        if (*p == '\0')              /* la riga finiva con spazi: niente parola */
            break;
        conta++;                     /* sono sull'inizio di una parola */
        while (*p != ' ' && *p != '\0')
            p++;                     /* salto fino alla fine della parola */
    }
    return conta;
}

const char *parola_piu_lunga(const char *s, int *lung)
{
    const char *p = s;
    const char *migliore = NULL;     /* NULL = "nessuna parola trovata finora" */
    *lung = 0;

    while (*p != '\0') {
        const char *inizio;
        while (*p == ' ')
            p++;
        if (*p == '\0')
            break;
        inizio = p;                  /* mi ricordo dove comincia la parola */
        while (*p != ' ' && *p != '\0')
            p++;                     /* ora p punta subito DOPO la parola */
        if (p - inizio > *lung) {    /* differenza tra puntatori = lunghezza */
            *lung = (int)(p - inizio);
            migliore = inizio;
        }
    }
    return migliore;  /* punta DENTRO la stringa del chiamante: valido dopo il return */
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
    if (p == NULL) {                 /* sempre controllare NULL prima di usare *p */
        printf("nessuna parola\n");
    } else {
        /* %.*s stampa al massimo "lung" caratteri a partire da p:
         * non serve un '\0' dopo la parola. p - riga = posizione nella riga. */
        printf("piu' lunga: \"%.*s\" (%d caratteri, posizione %d)\n",
               lung, p, lung, (int)(p - riga));
    }
    return 0;
}
