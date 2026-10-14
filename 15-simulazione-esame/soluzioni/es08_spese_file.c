/*
 * es08 — Spese da file: struct, vettore dinamico, categorie e report  (Tipo esame) — SOLUZIONE
 *
 * Input (stdin): il nome di un file di testo. Ogni riga del file e' una spesa:
 *     GG/MM categoria importo          es.:  03/01 cibo 12.50
 * Il programma:
 *   1. conta le righe valide (prima lettura), torna all'inizio con rewind,
 *      alloca con calloc un vettore della misura ESATTA e lo riempie
 *      (seconda lettura);
 *   2. stampa totale, media e spesa piu' alta;
 *   3. raggruppa per categoria (nell'ordine di prima comparsa);
 *   4. scrive il riepilogo per categoria nel file "report.txt";
 *   5. rilegge report.txt e lo stampa a video.
 * La lettura si ferma alla prima riga non valida.
 *
 * Come testarlo: make sol T=15 E=es08
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

/* Prima lettura: conta quante spese valide ci sono (fscanf restituisce il
 * numero di campi assegnati: 4 = riga completa). */
int conta_spese(FILE *fp)
{
    Spesa s;
    int n = 0;
    while (fscanf(fp, "%d/%d %19s %lf", &s.giorno, &s.mese, s.categoria, &s.importo) == 4)
        n++;
    return n;
}

/* Restituisce un vettore nello heap con le spese del file e mette in *n
 * quante sono. Se il file non si apre: NULL e *n = -1.
 * Se non ci sono spese: NULL e *n = 0 (niente calloc di 0 elementi). */
Spesa *carica_spese(const char *nome_file, int *n)
{
    FILE *fp;
    Spesa *v;
    int i;

    fp = fopen(nome_file, "r");
    if (fp == NULL) {
        *n = -1;
        return NULL;
    }
    *n = conta_spese(fp);
    if (*n == 0) {
        fclose(fp);
        return NULL;
    }
    v = (Spesa *) calloc((size_t) *n, sizeof(Spesa));   /* calloc: n elementi, gia' azzerati */
    if (v == NULL) {
        fclose(fp);
        *n = -1;
        return NULL;
    }
    rewind(fp);              /* la prima lettura ci ha portati in fondo: torno all'inizio */
    for (i = 0; i < *n; i++)
        if (fscanf(fp, "%d/%d %19s %lf", &v[i].giorno, &v[i].mese,
                   v[i].categoria, &v[i].importo) != 4)
            break;           /* non dovrebbe succedere: il file e' lo stesso di prima */
    fclose(fp);
    return v;                /* lo heap sopravvive alla funzione: lo liberera' il main */
}

/* Indice della spesa piu' alta (la prima, a parita'). Si assume n > 0. */
int indice_massima(const Spesa v[], int n)
{
    int i, imax = 0;
    for (i = 1; i < n; i++)
        if (v[i].importo > v[imax].importo)
            imax = i;
    return imax;
}

/* Raggruppa le spese per categoria. Ritorna quante categorie diverse ha
 * trovato (al massimo max; le categorie oltre la max-esima sono ignorate). */
int raggruppa(const Spesa v[], int n, Categoria c[], int max)
{
    int i, k, nc = 0;

    for (i = 0; i < n; i++) {
        for (k = 0; k < nc; k++)                      /* ricerca lineare per nome */
            if (strcmp(c[k].nome, v[i].categoria) == 0)
                break;
        if (k == nc) {                                /* non trovata: nuova categoria */
            if (nc == max)
                continue;
            strcpy(c[nc].nome, v[i].categoria);
            c[nc].quante = 0;
            c[nc].totale = 0.0;
            nc++;
        }
        c[k].quante++;
        c[k].totale += v[i].importo;
    }
    return nc;
}

/* Scrive una riga per categoria. Ritorna 0 se ok, -1 se non riesce a creare il file. */
int scrivi_report(const char *nome_file, const Categoria c[], int nc, double totale)
{
    FILE *out;
    int k;

    out = fopen(nome_file, "w");          /* "w": crea il file (o lo svuota se esiste) */
    if (out == NULL)
        return -1;
    for (k = 0; k < nc; k++)
        fprintf(out, "%s: %.2f euro (%.1f%%), spese: %d\n",   /* %% stampa il carattere % */
                c[k].nome, c[k].totale, 100.0 * c[k].totale / totale, c[k].quante);
    fclose(out);                          /* chiude e svuota il buffer su disco */
    return 0;
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
