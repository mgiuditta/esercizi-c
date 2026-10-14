/*
 * es05 — Inverti un pezzo di vettore con due puntatori  (Intermedio)
 *
 * Testo: implementa scambia(x, y) e inverti(sx, dx). inverti riceve DUE
 * PUNTATORI: al primo e all'ultimo elemento (compreso) del pezzo da
 * invertire, e lo inverte facendo avvicinare i due puntatori.
 * Il main (gia' scritto) legge il vettore e due indici a, b e chiama
 * inverti(&v[a], &v[b]).
 *
 * Input:  n, n interi, poi a b.   Esempio: 6  1 2 3 4 5 6  1 4
 * Output: 1 5 4 3 2 6
 *
 * Come testarlo: make test T=09 E=es05
 */
#include <stdio.h>

#define MAX 100

void scambia(int *x, int *y)
{
    /* TODO: scambia gli interi PUNTATI da x e y (serve una variabile d'appoggio) */
    (void)x; (void)y;   /* cancella questa riga */
}

void inverti(int *sx, int *dx)
{
    /* TODO: finche' sx sta prima di dx: scambia, sx avanza, dx arretra */
    (void)sx; (void)dx;   /* cancella questa riga */
}

int main(void)
{
    int v[MAX];
    int n, i, a, b;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;
    if (scanf("%d %d", &a, &b) != 2)
        return 1;

    if (a < 0 || b >= n || a > b) {
        printf("intervallo non valido\n");
        return 0;
    }

    inverti(&v[a], &v[b]);

    for (i = 0; i < n; i++)
        printf("%d%s", v[i], i < n - 1 ? " " : "\n");
    return 0;
}
