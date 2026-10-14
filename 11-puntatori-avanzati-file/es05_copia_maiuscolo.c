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
    /* TODO:
       1. apri sorgente in "r" e destinazione in "w", controllando NULL
          (se la seconda fopen fallisce, chiudi la prima!)
       2. ciclo: while ((c = getc(in)) != EOF) { putc(toupper(c), out); ... }
       3. chiudi ENTRAMBI i file e ritorna quanti caratteri hai copiato */
    (void)sorgente; (void)destinazione;
    return 0;
}

int stampa_file(const char *nome)
{
    /* TODO: apri il file in lettura (controlla NULL), stampalo con
             fgets + fputs(riga, stdout), chiudilo e ritorna 0 */
    (void)nome;
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
