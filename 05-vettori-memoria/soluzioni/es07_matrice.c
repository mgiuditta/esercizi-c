/*
 * es07 — Matrice: somme di righe e colonne, trasposta  (SOLUZIONE)
 *
 * Input:  r e c (righe e colonne, da 1 a MAX), poi r*c interi riga per riga.
 * Output: la somma di ogni riga, la somma di ogni colonna,
 *         la matrice trasposta (le righe diventano colonne).
 *
 * Come testarlo: make sol T=05 E=es07
 */
#include <stdio.h>

#define MAX 10

/* Perché "int m[][MAX]"? Una matrice in memoria è una riga dopo l'altra.
 * Per trovare m[i][j] il compilatore calcola  i * (lunghezza di una riga) + j,
 * quindi DEVE sapere quante colonne ha ogni riga (MAX). Il numero di righe
 * invece può restare vuoto. r e c dicono quante righe/colonne sono USATE. */

void somme_righe(int m[][MAX], int r, int c, int out[])
{
    int i, j;
    for (i = 0; i < r; i++) {
        out[i] = 0;                  /* azzerare PRIMA di sommare la riga i */
        for (j = 0; j < c; j++)
            out[i] += m[i][j];       /* i fisso, j scorre: percorro la riga */
    }
}

void somme_colonne(int m[][MAX], int r, int c, int out[])
{
    int i, j;
    for (j = 0; j < c; j++) {
        out[j] = 0;
        for (i = 0; i < r; i++)
            out[j] += m[i][j];       /* j fisso, i scorre: percorro la colonna */
    }
}

/* t ha c righe e r colonne: l'elemento in riga i, colonna j di m
 * finisce in riga j, colonna i di t. */
void trasposta(int m[][MAX], int r, int c, int t[][MAX])
{
    int i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[j][i] = m[i][j];
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

    /* r e c devono stare in 1..MAX: altrimenti i cicli userebbero
     * indici oltre MAX-1 e uscirebbero dalla matrice. */
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
    for (i = 0; i < c; i++) {            /* la trasposta ha c righe ... */
        for (j = 0; j < r; j++)          /* ... e r colonne */
            printf("%d%s", t[i][j], j < r - 1 ? " " : "\n");
    }
    return 0;
}
