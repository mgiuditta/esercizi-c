/*
 * es05 — Inverti un pezzo di vettore con due puntatori  (Intermedio)  — SOLUZIONE
 *
 * Testo: implementa scambia(x, y) e inverti(sx, dx). inverti riceve DUE
 * PUNTATORI: al primo e all'ultimo elemento (compreso) del pezzo da
 * invertire, e lo inverte facendo avvicinare i due puntatori.
 * Il main legge il vettore e due indici a, b e chiama inverti(&v[a], &v[b]).
 *
 * Come testarlo: make sol T=09 E=es05
 */
#include <stdio.h>

#define MAX 100

/* Riceve gli INDIRIZZI delle due celle: cosi' puo' modificare le celle
 * originali del chiamante (passaggio per indirizzo). */
void scambia(int *x, int *y)
{
    int t = *x;   /* salvo il valore puntato da x, se no lo perdo */
    *x = *y;
    *y = t;
}

void inverti(int *sx, int *dx)
{
    /* sx < dx: confronto tra puntatori nello STESSO vettore = "sx viene prima di dx" */
    while (sx < dx) {
        scambia(sx, dx);  /* sono gia' indirizzi: niente & */
        sx++;             /* il sinistro avanza di un elemento */
        dx--;             /* il destro arretra di un elemento */
    }
    /* Se il pezzo ha lunghezza dispari, sx e dx si fermano sullo stesso
     * elemento centrale (sx == dx), che resta dov'e'. */
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

    inverti(&v[a], &v[b]);   /* equivalente a inverti(v + a, v + b) */

    for (i = 0; i < n; i++)
        printf("%d%s", v[i], i < n - 1 ? " " : "\n");
    return 0;
}
