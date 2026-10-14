/*
 * Esercizio 04 — Trova e correggi gli errori di memoria  (Intermedio)
 *
 * Il programma dovrebbe:
 *   1. leggere n e poi n interi in un vettore dinamico;
 *   2. stampare il massimo e la sua posizione;
 *   3. stampare i numeri al contrario usando un secondo vettore dinamico;
 *   4. liberare tutta la memoria.
 *
 * Ci sono QUATTRO errori di gestione della memoria. Tre li fa "esplodere"
 * AddressSanitizer quando lanci il test (CRASH), uno alla volta: correggi,
 * rilancia, leggi il messaggio successivo. Il quarto il test NON lo vede.
 * Il compilatore potrebbe darti qualche avviso: leggilo, e' un indizio.
 *
 * Come testarlo: make test T=12 E=es04
 */
#include <stdio.h>
#include <stdlib.h>

/* restituisce l'INDIRIZZO dell'elemento massimo del vettore */
int *trova_max(int *v, int n)
{
    int *m = v;
    int i;
    for (i = 1; i < n; i++)
        if (v[i] > *m)
            m = &v[i];
    return m;
}

int main(void)
{
    int n, i;
    int *v, *inverso, *pmax;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("nessun numero\n");
        return 0;
    }

    v = (int *) malloc(n);
    if (v == NULL)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    inverso = (int *) malloc(n * sizeof(int));
    if (inverso == NULL)
        return 1;
    for (i = 0; i < n; i++)
        inverso[i] = v[n - 1 - i];

    pmax = trova_max(v, n);
    free(v);
    printf("massimo: %d (posizione %d)\n", *pmax, (int)(pmax - v));

    printf("al contrario:");
    for (i = 0; i < n; i++)
        printf(" %d", inverso[i]);
    printf("\n");

    free(v);
    return 0;
}
