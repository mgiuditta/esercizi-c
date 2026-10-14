/*
 * es06 — Trova e correggi l'errore: pari e dispari  (Intermedio)
 *
 * Testo: conta_pari_dispari(v, n, pari, dispari) deve scrivere in *pari e
 * *dispari quanti numeri pari e dispari ci sono nel vettore.
 * Questo codice compila, ma contiene TRE errori tipici sui puntatori.
 * Eseguendo "make test T=09 E=es06" vedrai prima un CRASH, poi (corretto il
 * primo errore) risultati sbagliati. Trovali e correggili tutti e tre.
 * NON riscrivere tutto da capo: cambia il minimo indispensabile.
 *
 * Input:  n, poi n interi.     Esempio: 6  4 7 -3 0 -8 11
 * Output: pari: 3
 *         dispari: 3
 *
 * Come testarlo: make test T=09 E=es06
 */
#include <stdio.h>

#define MAX 100

void conta_pari_dispari(const int *v, int n, int *pari, int *dispari)
{
    const int *p;

    *pari = 0;
    *dispari = 0;

    for (p = v; p <= v + n; p++) {
        if (*p % 2 == 0)
            pari++;
        else
            (*dispari)++;
    }
}

int main(void)
{
    int v[MAX] = {0};
    int n, i;
    int *np = NULL;
    int nd;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    conta_pari_dispari(v, n, np, &nd);
    printf("pari: %d\n", *np);
    printf("dispari: %d\n", nd);
    return 0;
}
