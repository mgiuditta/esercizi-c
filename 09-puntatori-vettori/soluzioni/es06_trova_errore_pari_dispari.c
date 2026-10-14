/*
 * es06 — Trova e correggi l'errore: pari e dispari  (Intermedio)  — SOLUZIONE
 *
 * Testo: conta_pari_dispari(v, n, pari, dispari) deve scrivere in *pari e
 * *dispari quanti numeri pari e dispari ci sono nel vettore. Lo starter ha
 * TRE errori tipici sui puntatori. Questa e' la versione corretta: i
 * commenti CORRETTO spiegano cosa e' cambiato.
 *
 * Come testarlo: make sol T=09 E=es06
 */
#include <stdio.h>

#define MAX 100

void conta_pari_dispari(const int *v, int n, int *pari, int *dispari)
{
    const int *p;

    *pari = 0;      /* scrivo 0 nelle variabili del CHIAMANTE */
    *dispari = 0;

    /* CORRETTO (errore 2): p < v + n, non <=. v + n e' l'indirizzo "uno oltre
     * l'ultimo": ci si puo' arrivare per fermarsi, ma NON si legge *(v + n). */
    for (p = v; p < v + n; p++) {
        if (*p % 2 == 0)
            (*pari)++;      /* CORRETTO (errore 3): incremento l'intero PUNTATO.
                               "pari++" spostava il puntatore (copia locale)
                               e il contatore del main restava fermo. */
        else
            (*dispari)++;   /* le parentesi servono: ++ lega piu' forte di * */
    }
}

int main(void)
{
    int v[MAX] = {0};
    int n, i;
    int np, nd;   /* CORRETTO (errore 1): due interi VERI dove la funzione
                     puo' scrivere. Prima c'era int *np = NULL: un puntatore
                     che non punta a nessuna variabile. */

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    conta_pari_dispari(v, n, &np, &nd);   /* passo gli INDIRIZZI di np e nd */
    printf("pari: %d\n", np);
    printf("dispari: %d\n", nd);
    return 0;
}
