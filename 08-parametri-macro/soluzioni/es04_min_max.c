/* =====================================================================
 * es04 — Minimo e massimo "restituiti" tramite puntatori
 * Intermedio  ·  SOLUZIONE
 * return restituisce UN valore. Per restituirne due si passano gli
 * indirizzi di due variabili del chiamante (parametri di uscita).
 * Come testarlo: make sol T=08 E=es04
 * ===================================================================== */
#include <stdio.h>

#define MAXN 100

void min_max(const int v[], int n, int *pmin, int *pmax);

int main(void) {
    int v[MAXN];
    int n, i, mi, ma;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
    min_max(v, n, &mi, &ma);    /* mi e ma vengono riempiti dalla funzione */
    printf("min = %d\n", mi);
    printf("max = %d\n", ma);
    return 0;
}

void min_max(const int v[], int n, int *pmin, int *pmax) {
    int i;
    /* Parto dal PRIMO elemento, non da 0: se tutti i valori fossero
     * negativi, un massimo iniziale 0 sarebbe sbagliato. */
    *pmin = v[0];
    *pmax = v[0];
    for (i = 1; i < n; i++) {
        if (v[i] < *pmin)
            *pmin = v[i];       /* scrivo direttamente nella mi del main */
        if (v[i] > *pmax)
            *pmax = v[i];
    }
}
