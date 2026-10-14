/*
 * Esercizio 05 — Funzioni che creano vettori dinamici: con return e con int **  (Intermedio)
 *
 * Gli appunti (Unita' 4, par. 1.11 e 1.12) mostrano DUE modi per far
 * "uscire" da una funzione un vettore creato al suo interno:
 *   a) la funzione restituisce il puntatore con return;
 *   b) la funzione riceve l'INDIRIZZO di un puntatore (int **) e lo modifica.
 *
 * Completa:
 *   - crea_inverso(v, n): restituisce (modo a) un NUOVO vettore dinamico con
 *     gli elementi di v in ordine inverso; NULL se l'allocazione fallisce.
 *   - crea_fibonacci(&f, n): (modo b) alloca in *pV un vettore di n interi con
 *     i primi n numeri di Fibonacci (0 1 1 2 3 5 ...). Ritorna 0, o -1 se fallisce.
 *
 * Input: n (>= 1), poi n interi.
 *
 * Come testarlo: make test T=12 E=es05
 */
#include <stdio.h>
#include <stdlib.h>

int *crea_inverso(const int *v, int n)
{
    int *r;
    int i;

    r = (int *) calloc(n, sizeof(int));   /* n blocchi da sizeof(int) byte, azzerati */
    if (r == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        r[i] = v[n - 1 - i];
    return r;   /* OK: r punta allo heap, non a una variabile locale */
}

int crea_fibonacci(int **pV, int n)
{
    int i;

    /* *pV e' il puntatore del chiamante: scrivendoci dentro lo modifichiamo */
    *pV = (int *) calloc(n, sizeof(int));
    if (*pV == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        if (i < 2)
            (*pV)[i] = i;                         /* F(0) = 0, F(1) = 1 */
        else
            (*pV)[i] = (*pV)[i - 1] + (*pV)[i - 2];
        /* le parentesi (*pV)[i] servono: *pV[i] vorrebbe dire *(pV[i]) */
    }
    return 0;
}

int main(void)
{
    int n, i;
    int *v, *inv, *fib = NULL;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("nessun valore\n");
        return 0;
    }
    v = (int *) malloc(n * sizeof(int));
    if (v == NULL)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            free(v);
            return 1;
        }

    inv = crea_inverso(v, n);                    /* modo a: con return */
    if (inv == NULL || crea_fibonacci(&fib, n) != 0) {   /* modo b: passo &fib */
        printf("errore di allocazione\n");
        free(v);
        free(inv);   /* free(NULL) e' permesso e non fa nulla */
        return 1;
    }

    printf("inverso:");
    for (i = 0; i < n; i++)
        printf(" %d", inv[i]);
    printf("\nfibonacci(%d):", n);
    for (i = 0; i < n; i++)
        printf(" %d", fib[i]);
    printf("\n");

    free(v);     /* tre allocazioni -> tre free */
    free(inv);
    free(fib);
    return 0;
}
