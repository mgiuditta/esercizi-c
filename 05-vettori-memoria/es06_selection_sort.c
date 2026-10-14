/*
 * es06 — Ordinamento per selezione (selection sort), passo per passo  ·  Intermedio
 *
 * Input:  n (da 1 a N_MAX), poi n interi.
 * Output: dopo ogni passata stampa "passata K:" seguito dal vettore,
 *         alla fine "ordinato:" seguito dal vettore in ordine crescente.
 * Passata p (p = 0, 1, ..., n-2): cerca la POSIZIONE del minimo tra v[p]..v[n-1]
 * e scambialo con v[p]. A parità di valore prendi il primo che trovi (usa <, non <=).
 *
 * Come testarlo: make test T=05 E=es06
 */
#include <stdio.h>

#define N_MAX 100

void stampa(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}

void ordina(int v[], int n)
{
    /* TODO: ciclo esterno sulle passate p = 0 .. n-2
     *         ciclo interno: trova pos_min tra p+1 .. n-1
     *         scambia v[p] e v[pos_min]
     *         printf("passata %d:", p + 1); stampa(v, n);            */
    (void)v; (void)n;
}

int main(void)
{
    int v[N_MAX];
    int n, i;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    ordina(v, n);
    printf("ordinato:");
    stampa(v, n);
    return 0;
}
