/* =====================================================================
 * es06 — Inverti un vettore "sul posto"  ·  Intermedio  ·  SOLUZIONE
 * Combina due idee: il vettore passato a funzione (modificabile) e
 * scambia(int *, int *) applicata a due elementi: scambia(&v[i], &v[j]).
 * Come testarlo: make sol T=08 E=es06
 * ===================================================================== */
#include <stdio.h>

#define MAXN 100

void scambia(int *x, int *y);
void inverti(int v[], int n);

int main(void) {
    int v[MAXN];
    int n, i;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
    inverti(v, n);
    printf("invertito:");
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
    return 0;
}

void scambia(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void inverti(int v[], int n) {
    int i;
    /* Scambio il primo con l'ultimo, il secondo con il penultimo...
     * Mi fermo a METÀ (i < n / 2): se andassi fino a n, ogni coppia
     * verrebbe scambiata due volte e il vettore tornerebbe com'era.
     * Con n dispari l'elemento centrale resta al suo posto. */
    for (i = 0; i < n / 2; i++)
        scambia(&v[i], &v[n - 1 - i]);   /* &v[i] = indirizzo dell'elemento i */
}
