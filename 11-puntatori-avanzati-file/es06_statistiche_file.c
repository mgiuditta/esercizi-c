/*
 * Esercizio 06 — Leggere numeri da un file e scrivere le statistiche  (Intermedio)
 *
 * Completa:
 *   - statistiche(in, &min, &max, &media): legge con fscanf TUTTI gli interi
 *     dallo stream "in" (gia' aperto) e calcola minimo, massimo e media.
 *     Ritorna quanti numeri ha letto (0 se il file non ne contiene).
 *   - scrivi_report(nome, n, min, max, media): crea il file "nome" e ci
 *     scrive il report con fprintf (formato nel README). Ritorna 0 oppure -1.
 *
 * Il main apre il file dei numeri, chiama le funzioni e poi RILEGGE il
 * report dal disco stampandolo a video: se lo vedi, l'hai scritto davvero.
 *
 * Input: il nome del file con i numeri.
 *
 * Come testarlo: make test T=11 E=es06
 */
#include <stdio.h>

int statistiche(FILE *in, int *min, int *max, double *media)
{
    /* TODO: ciclo while (fscanf(in, "%d", &x) == 1) { ... }
             aggiornando *min, *max, la somma e il contatore.
             Alla fine, se hai letto almeno un numero, calcola *media. */
    (void)in; (void)min; (void)max; (void)media;
    return 0;
}

int scrivi_report(const char *nome, int n, int min, int max, double media)
{
    /* TODO: apri "nome" in scrittura, controlla NULL, scrivi le 4 righe
             con fprintf (la media con %.2f), chiudi e ritorna 0 */
    (void)nome; (void)n; (void)min; (void)max; (void)media;
    return 0;
}

int main(void)
{
    char nome[100];
    char riga[100];
    FILE *fp;
    int n, min = 0, max = 0;
    double media = 0.0;

    if (scanf("%99s", nome) != 1)
        return 1;

    fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Errore: impossibile aprire %s\n", nome);
        return 1;
    }
    n = statistiche(fp, &min, &max, &media);
    fclose(fp);

    if (n == 0) {
        printf("nessun numero in %s\n", nome);
        return 0;
    }
    if (scrivi_report("statistiche.txt", n, min, max, media) != 0) {
        printf("Errore: impossibile scrivere il report\n");
        return 1;
    }

    /* rilettura del report dal disco */
    fp = fopen("statistiche.txt", "r");
    if (fp == NULL) {
        printf("Errore: report non trovato\n");
        return 1;
    }
    while (fgets(riga, sizeof riga, fp) != NULL)
        printf("%s", riga);
    fclose(fp);
    return 0;
}
