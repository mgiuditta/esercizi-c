/*
 * es04 — Copia (solo i positivi) con due puntatori  (Intermedio)
 *
 * Testo: implementa copia_positivi(dest, src, n): copia in dest, nello
 * stesso ordine, solo gli elementi > 0 di src. Usa due puntatori (uno che
 * legge, uno che scrive) e restituisci quanti elementi hai copiato come
 * DIFFERENZA tra puntatori.
 *
 * Input:  n, poi n interi.     Esempio: 7  3 -1 0 8 -5 2 9
 * Output: copiati: 4
 *         copia: 3 8 2 9
 *         originale: 3 -1 0 8 -5 2 9
 *
 * Come testarlo: make test T=09 E=es04
 */
#include <stdio.h>

#define MAX 100

int copia_positivi(int *dest, const int *src, int n)
{
    /* TODO:
       - const int *s scorre src da src a src + n (escluso);
       - int *d parte da dest e avanza SOLO quando scrivi un elemento;
       - alla fine restituisci (int)(d - dest). */
    (void)dest; (void)src; (void)n;   /* cancella questa riga */
    return 0;
}

static void stampa(const char *etichetta, const int *v, int n)
{
    const int *p;
    printf("%s", etichetta);
    for (p = v; p < v + n; p++)
        printf(" %d", *p);
    printf("\n");
}

int main(void)
{
    int src[MAX], dest[MAX];
    int n, i, k;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &src[i]) != 1)
            return 1;

    k = copia_positivi(dest, src, n);
    printf("copiati: %d\n", k);
    stampa("copia:", dest, k);
    stampa("originale:", src, n);
    return 0;
}
