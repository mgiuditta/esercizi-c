/*
 * Esercizio 04 — Trova e correggi gli errori di memoria  (Intermedio)
 * SOLUZIONE: gli errori corretti sono segnalati con "ERRORE n".
 *
 * Come testarlo: make sol T=12 E=es04
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

    /* ERRORE 1: era malloc(n). malloc vuole un numero di BYTE, non di
       elementi: per n interi servono n * sizeof(int) byte. Con malloc(n)
       la scanf scriveva oltre la fine del blocco (heap-buffer-overflow). */
    v = (int *) malloc(n * sizeof(int));
    if (v == NULL)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            free(v);
            return 1;
        }

    inverso = (int *) malloc(n * sizeof(int));
    if (inverso == NULL) {
        free(v);
        return 1;
    }
    for (i = 0; i < n; i++)
        inverso[i] = v[n - 1 - i];

    /* ERRORE 2: la free(v) veniva PRIMA di usare *pmax. pmax punta dentro
       il blocco di v: dopo la free e' un "dangling pointer" (puntatore
       pendente) e leggerlo e' un heap-use-after-free. Si usa, poi si libera. */
    pmax = trova_max(v, n);
    printf("massimo: %d (posizione %d)\n", *pmax, (int)(pmax - v));

    printf("al contrario:");
    for (i = 0; i < n; i++)
        printf(" %d", inverso[i]);
    printf("\n");

    /* ERRORE 3: c'erano DUE free(v): la seconda e' un double free.
       ERRORE 4 (il test non lo vede): inverso non veniva mai liberato
       -> memory leak. Ogni malloc ha la sua free, una sola volta. */
    free(v);
    free(inverso);
    v = NULL;        /* da qui in poi nessuno puo' usarli per sbaglio */
    inverso = NULL;
    pmax = NULL;
    return 0;
}
