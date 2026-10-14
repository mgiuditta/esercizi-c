/*
 * Esercizio 07 — Tipo esame: matrice dinamica, eliminare una riga  (Tipo esame)
 *
 * La matrice e' un VETTORE DI PUNTATORI (int **): ogni casella punta a una
 * riga allocata a parte (Appunti Unita' 4, par. 1.10). Questo permette di
 * eliminare una riga senza copiare i numeri: si libera la riga e si spostano
 * solo i puntatori.
 *
 * Completa:
 *   - crea_matrice(r, c): alloca r puntatori e poi r righe da c interi
 *     (con calloc). Se una allocazione fallisce, libera quello che hai gia'
 *     allocato e restituisci NULL.
 *   - libera_matrice(m, r): libera ogni riga e poi il vettore di puntatori.
 *   - elimina_riga(m, r, k): libera la riga k, sposta di un posto verso l'alto
 *     i puntatori alle righe successive e restituisce il nuovo numero di
 *     righe. Se k non e' valido restituisce r senza toccare nulla.
 *
 * Input: r c, poi r*c interi, poi l'indice k della riga da eliminare.
 * Output: la matrice risultante con la somma di ogni riga.
 *
 * Come testarlo: make test T=12 E=es07
 */
#include <stdio.h>
#include <stdlib.h>

void libera_matrice(int **m, int r)
{
    int i;
    if (m == NULL)
        return;
    for (i = 0; i < r; i++)
        free(m[i]);   /* PRIMA le righe: dopo free(m) non potremmo piu' leggere m[i] */
    free(m);          /* POI il vettore di puntatori */
}

int **crea_matrice(int r, int c)
{
    int **m;
    int i;

    /* r caselle da sizeof(int *) byte (8), NON sizeof(int) (4) */
    m = (int **) calloc(r, sizeof(int *));
    if (m == NULL)
        return NULL;
    for (i = 0; i < r; i++) {
        m[i] = (int *) calloc(c, sizeof(int));
        if (m[i] == NULL) {
            libera_matrice(m, i);   /* libera solo le i righe gia' create */
            return NULL;
        }
    }
    return m;
}

int elimina_riga(int **m, int r, int k)
{
    int i;
    if (k < 0 || k >= r)
        return r;               /* indice non valido: nessuna modifica */
    free(m[k]);                 /* la riga k torna al sistema */
    for (i = k; i < r - 1; i++)
        m[i] = m[i + 1];        /* si spostano gli INDIRIZZI, non i numeri */
    m[r - 1] = NULL;            /* l'ultima casella ora e' un doppione: la "spegniamo" */
    return r - 1;
}

int main(void)
{
    int **m;
    int r, c, k, i, j, s, nuove;

    if (scanf("%d %d", &r, &c) != 2 || r <= 0 || c <= 0) {
        printf("dimensioni non valide\n");
        return 1;
    }
    m = crea_matrice(r, c);
    if (m == NULL) {
        printf("errore di allocazione\n");
        return 1;
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            if (scanf("%d", &m[i][j]) != 1) {
                libera_matrice(m, r);
                return 1;
            }
    if (scanf("%d", &k) != 1) {
        libera_matrice(m, r);
        return 1;
    }

    nuove = elimina_riga(m, r, k);
    if (nuove == r)
        printf("riga %d inesistente, matrice invariata\n", k);

    if (nuove == 0) {
        printf("matrice vuota\n");
    } else {
        for (i = 0; i < nuove; i++) {
            s = 0;
            printf("riga %d:", i);
            for (j = 0; j < c; j++) {
                printf(" %d", m[i][j]);
                s += m[i][j];
            }
            printf(" | somma %d\n", s);
        }
    }

    /* Si liberano le righe rimaste (nuove). Il vettore di puntatori era
       stato allocato per r caselle, ma free(m) libera l'intero blocco. */
    libera_matrice(m, nuove);
    return 0;
}
