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
    int x, n = 0;
    long somma = 0;

    /* Si controlla il valore di ritorno di fscanf, NON feof:
       fscanf restituisce 1 finche' riesce a leggere un intero,
       EOF (o 0) quando il file e' finito (o c'e' un dato non numerico). */
    while (fscanf(in, "%d", &x) == 1) {
        if (n == 0 || x < *min)   /* il primo numero e' sia min sia max */
            *min = x;
        if (n == 0 || x > *max)
            *max = x;
        somma += x;
        n++;
    }
    if (n > 0)
        *media = (double)somma / n;   /* cast: altrimenti divisione intera */
    return n;
}

int scrivi_report(const char *nome, int n, int min, int max, double media)
{
    FILE *out = fopen(nome, "w");
    if (out == NULL)
        return -1;
    fprintf(out, "numeri letti: %d\n", n);   /* come printf, ma sul file */
    fprintf(out, "minimo: %d\n", min);
    fprintf(out, "massimo: %d\n", max);
    fprintf(out, "media: %.2f\n", media);
    fclose(out);
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
