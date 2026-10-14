/*
 * es07 — Matrice: somme di righe e colonne, trasposta  ·  Tipo esame
 *
 * Input:  r e c (righe e colonne, da 1 a MAX), poi r*c interi riga per riga.
 * Output (esempio con la matrice 2x3  1 2 3 / 4 5 6):
 *     somme righe: 6 15
 *     somme colonne: 5 7 9
 *     trasposta:
 *     1 4
 *     2 5
 *     3 6
 * Completa le tre funzioni. Il main è già pronto.
 *
 * Come testarlo: make test T=05 E=es07
 */
#include <stdio.h>

#define MAX 10

/* out[i] = somma della riga i, per i = 0 .. r-1 */
void somme_righe(int m[][MAX], int r, int c, int out[])
{
    /* TODO */
    int i;
    (void)m; (void)c;
    for (i = 0; i < r; i++)
        out[i] = 0;   /* provvisorio: solo per avere valori stampabili */
}

/* out[j] = somma della colonna j, per j = 0 .. c-1 */
void somme_colonne(int m[][MAX], int r, int c, int out[])
{
    /* TODO */
    int j;
    (void)m; (void)r;
    for (j = 0; j < c; j++)
        out[j] = 0;   /* provvisorio */
}

/* t (c righe, r colonne) diventa la trasposta di m (r righe, c colonne) */
void trasposta(int m[][MAX], int r, int c, int t[][MAX])
{
    /* TODO */
    int i, j;
    (void)m;
    for (i = 0; i < c; i++)
        for (j = 0; j < r; j++)
            t[i][j] = 0;   /* provvisorio */
}

void stampa_vettore(const char *etichetta, int v[], int n)
{
    int i;
    printf("%s:", etichetta);
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}

int main(void)
{
    int m[MAX][MAX], t[MAX][MAX];
    int sr[MAX], sc[MAX];
    int r, c, i, j;

    if (scanf("%d %d", &r, &c) != 2 || r < 1 || r > MAX || c < 1 || c > MAX) {
        printf("dimensioni non valide\n");
        return 1;
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &m[i][j]);

    somme_righe(m, r, c, sr);
    somme_colonne(m, r, c, sc);
    trasposta(m, r, c, t);

    stampa_vettore("somme righe", sr, r);
    stampa_vettore("somme colonne", sc, c);
    printf("trasposta:\n");
    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++)
            printf("%d%s", t[i][j], j < r - 1 ? " " : "\n");
    }
    return 0;
}
