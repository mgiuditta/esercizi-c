/*
 * Esercizio 03 — Contare righe e parole di un file  (Base)
 *
 * Completa analizza_file: apre il file "nome" in lettura, lo legge un
 * carattere alla volta con getc e restituisce, tramite i parametri di
 * output (come scompone della lezione 3.6):
 *   *righe   -> numero di righe
 *   *parole  -> numero di parole (sequenze di caratteri non-spazio)
 *   *maxlen  -> lunghezza della riga piu' lunga ('\n' escluso)
 * Ritorna 0 se tutto va bene, -1 se il file non si puo' aprire.
 *
 * Input (da tastiera): il nome del file. I file di prova sono in tests/fixtures/.
 *
 * Come testarlo: make test T=11 E=es03
 */
#include <stdio.h>
#include <ctype.h>

int analizza_file(const char *nome, int *righe, int *parole, int *maxlen)
{
    FILE *fp;
    int c;            /* int, NON char: deve poter contenere anche EOF */
    int dentro = 0;   /* 1 se siamo in mezzo a una parola */
    int lung = 0;     /* lunghezza della riga corrente */

    fp = fopen(nome, "r");
    if (fp == NULL)   /* file inesistente o non leggibile: fopen da' NULL */
        return -1;

    *righe = 0;
    *parole = 0;
    *maxlen = 0;

    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            (*righe)++;              /* le parentesi servono: vedi README */
            if (lung > *maxlen)
                *maxlen = lung;
            lung = 0;
        } else {
            lung++;
        }

        if (isspace(c)) {
            dentro = 0;              /* uno spazio chiude la parola */
        } else if (!dentro) {
            dentro = 1;              /* primo carattere di una nuova parola */
            (*parole)++;
        }
    }

    /* ultima riga senza '\n' finale: va contata lo stesso */
    if (lung > 0) {
        (*righe)++;
        if (lung > *maxlen)
            *maxlen = lung;
    }

    fclose(fp);   /* ogni fopen riuscita va chiusa */
    return 0;
}

int main(void)
{
    char nome[100];
    int r, p, m;

    if (scanf("%99s", nome) != 1)
        return 1;

    if (analizza_file(nome, &r, &p, &m) != 0) {
        printf("Errore: impossibile aprire %s\n", nome);
        return 1;
    }
    printf("righe: %d\n", r);
    printf("parole: %d\n", p);
    printf("riga piu' lunga: %d caratteri\n", m);
    return 0;
}
