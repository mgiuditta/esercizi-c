/* =====================================================================
 * es06 — Inverti un vettore "sul posto"  ·  Intermedio
 * Completa:
 *   scambia(int *x, int *y)   (come in es02)
 *   inverti(int v[], int n)   inverte l'ordine degli elementi di v
 *                             usando scambia su coppie di elementi:
 *                             scambia(&v[i], &v[...]);
 * Non usare un secondo vettore.
 * Input: n, poi n interi. Output (esempio con 1 2 3 4 5 6):
 *   invertito: 6 5 4 3 2 1
 * Come testarlo: make test T=08 E=es06
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
    /* TODO */
    (void)x; (void)y;   /* cancella questa riga */
}

void inverti(int v[], int n) {
    /* TODO: con quale elemento va scambiato v[i]? Fino a dove va il ciclo? */
    (void)v; (void)n;   /* cancella questa riga */
}
