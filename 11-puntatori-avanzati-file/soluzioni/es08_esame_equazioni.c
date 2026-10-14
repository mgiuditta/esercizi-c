/*
 * Esercizio 08 — Tipo esame: equazioni di secondo grado da file a file  (Tipo esame)
 *
 * E' il programma della E-tivity "Parametri e Puntatori" (radici
 * dell'equazione di secondo grado), portato su file e con una struct.
 *
 * Il file di ingresso contiene una equazione per riga: tre numeri a b c
 * (coefficienti di a*x^2 + b*x + c = 0).
 *
 * Completa:
 *   - leggi_equazioni: legge dal file al massimo max equazioni nel vettore v.
 *     Ritorna quante ne ha lette, oppure -1 se il file non si apre.
 *   - radici: calcola le radici reali e le restituisce in *x1 e *x2.
 *     Ritorna -1 se a == 0 (non e' di secondo grado), 0 se non ci sono
 *     radici reali, 1 se sono coincidenti (solo *x1), 2 se sono distinte.
 *   - scrivi_soluzioni: crea il file nome_out con una riga per equazione
 *     (formato nel README). Ritorna 0, oppure -1 se non riesce a crearlo.
 *
 * Input: il nome del file con le equazioni.
 * Il main scrive le soluzioni in "soluzioni.txt" e poi lo rilegge a video.
 *
 * Come testarlo: make test T=11 E=es08
 */
#include <stdio.h>
#include <math.h>

#define MAXEQ 50

typedef struct {
    double a, b, c;   /* coefficienti di a*x^2 + b*x + c = 0 */
} Equazione;

/* Il discriminante, come nella E-tivity: b^2 - 4ac.
   Riceve un puntatore a struct (const = "non la modifico"): si evita di copiarla. */
double discriminante(const Equazione *e)
{
    return e->b * e->b - 4 * e->a * e->c;   /* e->b equivale a (*e).b */
}

int leggi_equazioni(const char *nome, Equazione v[], int max)
{
    FILE *fp = fopen(nome, "r");
    int n = 0;

    if (fp == NULL)
        return -1;
    /* fscanf restituisce quanti valori ha assegnato: ne vogliamo 3.
       Il controllo n < max evita di scrivere oltre la fine del vettore. */
    while (n < max && fscanf(fp, "%lf %lf %lf", &v[n].a, &v[n].b, &v[n].c) == 3)
        n++;
    fclose(fp);
    return n;
}

int radici(const Equazione *e, double *x1, double *x2)
{
    double d;

    if (e->a == 0)          /* come nella E-tivity: se a e' 0 non si va avanti */
        return -1;
    d = discriminante(e);
    if (d < 0)
        return 0;           /* nessuna radice reale: *x1 e *x2 restano intatti */
    if (d == 0) {
        *x1 = -e->b / (2 * e->a);
        return 1;
    }
    /* due radici distinte: le "restituiamo" scrivendo nelle variabili del chiamante */
    *x1 = (-e->b + sqrt(d)) / (2 * e->a);
    *x2 = (-e->b - sqrt(d)) / (2 * e->a);
    return 2;
}

int scrivi_soluzioni(const char *nome_out, const Equazione v[], int n)
{
    FILE *out = fopen(nome_out, "w");
    int i, k;
    double x1 = 0, x2 = 0;

    if (out == NULL)
        return -1;
    for (i = 0; i < n; i++) {
        fprintf(out, "%d) a=%.2f b=%.2f c=%.2f: ", i + 1, v[i].a, v[i].b, v[i].c);
        k = radici(&v[i], &x1, &x2);   /* & perche' radici vuole indirizzi */
        if (k == -1)
            fprintf(out, "non e' di secondo grado\n");
        else if (k == 0)
            fprintf(out, "nessuna radice reale\n");
        else if (k == 1)
            fprintf(out, "radici coincidenti x=%.2f\n", x1);
        else
            fprintf(out, "x1=%.2f x2=%.2f\n", x1, x2);
    }
    fclose(out);
    return 0;
}

int main(void)
{
    Equazione eq[MAXEQ];
    char nome[100], riga[200];
    FILE *fp;
    int n, i, reali = 0;
    double x1, x2;

    if (scanf("%99s", nome) != 1)
        return 1;

    n = leggi_equazioni(nome, eq, MAXEQ);
    if (n < 0) {
        printf("Errore: impossibile aprire %s\n", nome);
        return 1;
    }
    if (scrivi_soluzioni("soluzioni.txt", eq, n) != 0) {
        printf("Errore: impossibile creare soluzioni.txt\n");
        return 1;
    }

    fp = fopen("soluzioni.txt", "r");
    if (fp == NULL) {
        printf("Errore: impossibile rileggere soluzioni.txt\n");
        return 1;
    }
    while (fgets(riga, sizeof riga, fp) != NULL)
        printf("%s", riga);
    fclose(fp);

    for (i = 0; i < n; i++)
        if (radici(&eq[i], &x1, &x2) > 0)
            reali++;
    printf("equazioni: %d, con radici reali: %d\n", n, reali);
    return 0;
}
