/*
 * es04 — Inverti un tratto del vettore "sul posto"  (SOLUZIONE)
 *
 * Input:  n (da 1 a N_MAX), n interi, poi due indici a e b.
 * Output: il vettore dopo aver invertito SOLO gli elementi da v[a] a v[b]
 *         (estremi compresi), senza usare un secondo vettore.
 *         Se gli indici non sono validi stampa "intervallo non valido".
 *
 * Come testarlo: make sol T=05 E=es04
 */
#include <stdio.h>

#define N_MAX 100

/* Idea: due indici che si vengono incontro.
 * sx parte da a, dx parte da b. Scambiamo v[sx] e v[dx],
 * poi sx avanza e dx arretra. Ci fermiamo quando si incontrano:
 * se continuassimo, ri-scambieremmo coppie già scambiate e il tratto
 * tornerebbe com'era! */
void inverti_tratto(int v[], int a, int b)
{
    int sx = a, dx = b;
    int tmp;
    while (sx < dx) {
        /* Scambio con variabile d'appoggio: se scrivessimo solo
         * v[sx] = v[dx]; v[dx] = v[sx]; perderemmo il valore di v[sx]
         * (come travasare due bicchieri senza un terzo bicchiere). */
        tmp = v[sx];
        v[sx] = v[dx];
        v[dx] = tmp;
        sx++;
        dx--;
    }
}

int main(void)
{
    int v[N_MAX];
    int n, i, a, b;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("intervallo non valido\n");
        return 1;
    }

    /* Controllo FONDAMENTALE: il C non controlla gli indici per noi.
     * Se a fosse -1 o b fosse n, la funzione scriverebbe fuori dal
     * vettore (out of bounds). Indici validi: 0 <= a <= b <= n-1. */
    if (a < 0 || b >= n || a > b) {
        printf("intervallo non valido\n");
        return 1;
    }

    inverti_tratto(v, a, b);

    for (i = 0; i < n; i++)
        printf("%d%s", v[i], i < n - 1 ? " " : "\n");
    return 0;
}
