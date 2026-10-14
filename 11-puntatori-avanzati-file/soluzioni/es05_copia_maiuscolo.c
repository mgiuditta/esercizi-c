/*
 * Esercizio 05 — Copiare un file trasformandolo in maiuscolo  (Intermedio)
 *
 * Completa:
 *   - copia_maiuscolo(sorgente, destinazione): apre la sorgente in lettura
 *     ("r") e la destinazione in scrittura ("w"); copia carattere per carattere
 *     con getc/putc trasformando le lettere in maiuscolo (toupper).
 *     Ritorna quanti caratteri ha copiato, oppure -1 se uno dei due file
 *     non si apre.
 *   - stampa_file(nome): riapre il file in lettura e lo stampa su stdout
 *     riga per riga con fgets. Ritorna 0, oppure -1 se non si apre.
 *
 * Input: nome del file sorgente e nome del file destinazione.
 *
 * Come testarlo: make test T=11 E=es05
 */
#include <stdio.h>
#include <ctype.h>

int copia_maiuscolo(const char *sorgente, const char *destinazione)
{
    FILE *in, *out;
    int c, quanti = 0;

    in = fopen(sorgente, "r");
    if (in == NULL)
        return -1;
    out = fopen(destinazione, "w");   /* "w": crea il file o lo svuota */
    if (out == NULL) {
        fclose(in);                   /* non lasciare aperto il primo file */
        return -1;
    }

    while ((c = getc(in)) != EOF) {
        putc(toupper(c), out);        /* toupper lascia invariato cio' che non e' una lettera */
        quanti++;
    }

    fclose(in);
    fclose(out);   /* IMPORTANTE: svuota il buffer di scrittura sul disco */
    return quanti;
}

int stampa_file(const char *nome)
{
    FILE *fp;
    char riga[256];

    fp = fopen(nome, "r");
    if (fp == NULL)
        return -1;
    /* fgets restituisce NULL quando non c'e' piu' niente da leggere */
    while (fgets(riga, sizeof riga, fp) != NULL)
        fputs(riga, stdout);   /* fputs NON aggiunge '\n': c'e' gia' in riga */
    fclose(fp);
    return 0;
}

int main(void)
{
    char src[100], dst[100];
    int n;

    if (scanf("%99s %99s", src, dst) != 2)
        return 1;

    n = copia_maiuscolo(src, dst);
    if (n < 0) {
        printf("Errore: impossibile copiare %s in %s\n", src, dst);
        return 1;
    }
    printf("copiati %d caratteri\n", n);
    printf("--- contenuto di %s ---\n", dst);
    if (stampa_file(dst) != 0)
        printf("Errore: impossibile rileggere %s\n", dst);
    printf("--- fine ---\n");
    return 0;
}
