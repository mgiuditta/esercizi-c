/* =====================================================================
 * es04 — Minimo e massimo "restituiti" tramite puntatori  ·  Intermedio
 * return può restituire UN solo valore. Completa
 *   void min_max(const int v[], int n, int *pmin, int *pmax)
 * che scrive il minimo in *pmin e il massimo in *pmax.
 * Input: n (>= 1), poi n interi. Output:
 *   min = ...
 *   max = ...
 * Come testarlo: make test T=08 E=es04
 * ===================================================================== */
#include <stdio.h>

#define MAXN 100

void min_max(const int v[], int n, int *pmin, int *pmax);

int main(void) {
    int v[MAXN];
    int n, i, mi = 0, ma = 0;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
    min_max(v, n, &mi, &ma);
    printf("min = %d\n", mi);
    printf("max = %d\n", ma);
    return 0;
}

void min_max(const int v[], int n, int *pmin, int *pmax) {
    /* TODO: 1) da che valore partono *pmin e *pmax? (attenzione ai negativi)
     *       2) scorri il vettore e aggiorna *pmin e *pmax */
    (void)v; (void)n; (void)pmin; (void)pmax;   /* cancella questa riga */
}
