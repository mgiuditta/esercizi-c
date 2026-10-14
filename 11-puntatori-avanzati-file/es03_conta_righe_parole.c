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
    /* TODO:
       1. apri il file con fopen in modalita' lettura
       2. se fopen restituisce NULL, ritorna -1
       3. azzera *righe, *parole, *maxlen
       4. leggi con getc fino a EOF contando righe, parole e lunghezza
       5. ricordati dell'ultima riga senza '\n' e chiudi il file */
    (void)nome;
    *righe = 0;
    *parole = 0;
    *maxlen = 0;
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
