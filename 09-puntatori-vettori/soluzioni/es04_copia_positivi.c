/*
 * es04 — Copia (solo i positivi) con due puntatori  (Intermedio)  — SOLUZIONE
 *
 * Testo: implementa copia_positivi(dest, src, n): copia in dest, nello
 * stesso ordine, solo gli elementi > 0 di src. Usa due puntatori (uno che
 * legge, uno che scrive) e restituisci quanti elementi hai copiato come
 * DIFFERENZA tra puntatori.
 *
 * Come testarlo: make sol T=09 E=es04
 */
#include <stdio.h>

#define MAX 100

int copia_positivi(int *dest, const int *src, int n)
{
    const int *s;          /* puntatore di LETTURA: scorre tutto src  */
    int *d = dest;         /* puntatore di SCRITTURA: avanza solo quando scrivo */

    for (s = src; s < src + n; s++) {
        if (*s > 0) {      /* 0 non e' positivo: non lo copio */
            *d = *s;       /* scrivo nella cella puntata da d... */
            d++;           /* ...e solo ora sposto d sulla cella libera successiva */
        }
    }
    /* d e' avanzato una volta per ogni copia: d - dest = numero di copie */
    return (int)(d - dest);
}

static void stampa(const char *etichetta, const int *v, int n)
{
    const int *p;
    printf("%s", etichetta);
    for (p = v; p < v + n; p++)
        printf(" %d", *p);  /* spazio PRIMA del numero: niente spazio finale */
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
    stampa("originale:", src, n);   /* src non e' stato toccato (const) */
    return 0;
}
