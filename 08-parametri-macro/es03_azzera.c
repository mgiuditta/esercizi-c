/* =====================================================================
 * es03 — Azzera i primi k elementi di un vettore  ·  Base
 * Completa azzera(v, k): mette a 0 gli elementi v[0] ... v[k-1].
 * Osserva: la funzione è void, eppure il main vede il vettore cambiato.
 * Perché con un int non succedeva e con un vettore sì? (vedi README)
 * Input: n, poi n interi, poi k (0 <= k <= n). Output (esempio):
 *   prima: 1 2 3 4 5
 *   dopo: 0 0 3 4 5
 * Come testarlo: make test T=08 E=es03
 * ===================================================================== */
#include <stdio.h>

#define MAXN 100

void azzera(int v[], int k);
void stampa(const char *etichetta, const int v[], int n);

int main(void) {
    int v[MAXN];
    int n, k, i;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
    if (scanf("%d", &k) != 1 || k < 0 || k > n) {
        printf("k non valido\n");
        return 0;
    }
    stampa("prima", v, n);
    azzera(v, k);
    stampa("dopo", v, n);
    return 0;
}

void azzera(int v[], int k) {
    /* TODO: un ciclo da 0 a k-1 che scrive 0 in v[i] */
    (void)v; (void)k;   /* cancella questa riga */
}

void stampa(const char *etichetta, const int v[], int n) {
    int i;
    printf("%s:", etichetta);
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}
