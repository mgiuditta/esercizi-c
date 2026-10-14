/*
 * es08 — Spese da file: struct, vettore dinamico, categorie e report  (Tipo esame)
 *
 * Input (stdin): il nome di un file di testo. Ogni riga del file e' una spesa:
 *     GG/MM categoria importo          es.:  03/01 cibo 12.50
 * La lettura si ferma alla prima riga non valida.
 *
 * Completa:
 *   - conta_spese(fp): quante righe valide (fscanf restituisce 4) ci sono.
 *   - carica_spese(nome, &n): apre il file ("r"); se non si apre -> NULL e
 *     *n = -1. Conta le spese, poi rewind(fp), poi calloc della misura
 *     ESATTA e seconda lettura nel vettore. Con 0 spese -> NULL e *n = 0
 *     (niente calloc). Chiudi sempre il file. Ritorna il vettore.
 *   - indice_massima: indice della spesa piu' alta (la prima a parita').
 *   - raggruppa: riempie c[] con nome, numero di spese e totale di ogni
 *     categoria, nell'ordine di prima comparsa; ritorna quante categorie.
 *   - scrivi_report: crea il file ("w") e scrive una riga per categoria:
 *         cibo: 50.00 euro (33.7%), spese: 3
 *     (percentuale = 100 * totale categoria / totale generale, con %.1f;
 *     per stampare il carattere % si scrive %%). Ritorna 0, o -1 se fallisce.
 * Il main (gia' scritto) stampa i totali, scrive "report.txt", lo rilegge
 * con fgets e lo stampa.
 *
 * Come testarlo: make test T=15 E=es08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCAT 10
#define LUNCAT 20

typedef struct {
    int giorno, mese;
    char categoria[LUNCAT];
    double importo;
} Spesa;

typedef struct {
    char nome[LUNCAT];
    int quante;
    double totale;
} Categoria;

int conta_spese(FILE *fp)
{
    /* TODO: fscanf(fp, "%d/%d %19s %lf", ...) finche' restituisce 4 */
    (void)fp;
    return 0;
}

Spesa *carica_spese(const char *nome_file, int *n)
{
    /* TODO: fopen, conta_spese, rewind, calloc, seconda lettura, fclose */
    (void)nome_file;
    *n = -1;
    return NULL;
}

int indice_massima(const Spesa v[], int n)
{
    /* TODO: si assume n > 0 */
    (void)v; (void)n;
    return 0;
}

int raggruppa(const Spesa v[], int n, Categoria c[], int max)
{
    /* TODO: per ogni spesa cerca la categoria in c[0..nc-1] con strcmp;
       se non c'e' (e nc < max) aggiungila in fondo con strcpy */
    (void)v; (void)n; (void)c; (void)max;
    return 0;
}

int scrivi_report(const char *nome_file, const Categoria c[], int nc, double totale)
{
    /* TODO: fopen in "w", fprintf per ogni categoria, fclose */
    (void)nome_file; (void)c; (void)nc; (void)totale;
    return -1;
}

int main(void)
{
    char nome_file[64], riga[128];
    Spesa *v;
    Categoria cat[MAXCAT];
    int n, i, imax, nc;
    double totale = 0.0;
    FILE *fp;

    if (scanf("%63s", nome_file) != 1)
        return 1;
    v = carica_spese(nome_file, &n);
    if (n < 0) {
        printf("impossibile aprire %s\n", nome_file);
        return 1;
    }
    printf("spese lette: %d\n", n);
    if (n == 0) {
        printf("nessuna spesa\n");
        return 0;
    }

    for (i = 0; i < n; i++)
        totale += v[i].importo;
    printf("totale: %.2f euro, media: %.2f euro\n", totale, totale / n);
    imax = indice_massima(v, n);
    printf("spesa piu' alta: %.2f euro il %02d/%02d (%s)\n",
           v[imax].importo, v[imax].giorno, v[imax].mese, v[imax].categoria);

    nc = raggruppa(v, n, cat, MAXCAT);
    if (scrivi_report("report.txt", cat, nc, totale) != 0) {
        printf("impossibile scrivere report.txt\n");
        free(v);
        return 1;
    }

    printf("--- report.txt ---\n");
    fp = fopen("report.txt", "r");
    if (fp != NULL) {
        while (fgets(riga, sizeof riga, fp) != NULL)   /* fgets tiene il '\n': niente \n in printf */
            printf("%s", riga);
        fclose(fp);
    }

    free(v);
    return 0;
}
