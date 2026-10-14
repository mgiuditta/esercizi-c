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
    /* TODO: apri il file in lettura (NULL -> ritorna -1); leggi con
             fscanf(fp, "%lf %lf %lf", ...) finche' ne legge 3 e n < max;
             chiudi il file e ritorna n */
    (void)nome; (void)v; (void)max;
    return 0;
}

int radici(const Equazione *e, double *x1, double *x2)
{
    /* TODO: a == 0 -> -1; discriminante < 0 -> 0;
             == 0 -> una radice in *x1, ritorna 1;
             > 0  -> due radici in *x1 e *x2, ritorna 2 */
    (void)e; (void)x1; (void)x2;
    return 0;
}

int scrivi_soluzioni(const char *nome_out, const Equazione v[], int n)
{
    /* TODO: apri nome_out in scrittura (NULL -> -1); per ogni equazione
             scrivi con fprintf la riga nel formato del README usando radici();
             chiudi il file e ritorna 0 */
    (void)nome_out; (void)v; (void)n;
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
