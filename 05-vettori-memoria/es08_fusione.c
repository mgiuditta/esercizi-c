/*
 * es08 — Fusione di due vettori ordinati (merge)  ·  Tipo esame
 *
 * Input:  n (0..N_MAX), n interi (vettore a);
 *         m (0..N_MAX), m interi (vettore b). Non sono necessariamente ordinati.
 * Output:
 *     a ordinato: ...
 *     b ordinato: ...
 *     fusione: ...      (tutti gli n+m elementi in ordine crescente)
 * La fusione va costruita SENZA riordinare tutto da capo: scorri a e b
 * insieme e prendi ogni volta il più piccolo dei due elementi "in testa".
 *
 * Come testarlo: make test T=05 E=es08
 */
#include <stdio.h>

#define N_MAX 50
#define F_MAX (2 * N_MAX)

/* Ordina v in modo crescente (puoi riusare il selection sort di es06). */
void ordina(int v[], int n)
{
    /* TODO */
    (void)v; (void)n;
}

/* Riempie f con gli elementi di a (n) e b (m), già ordinati, in ordine
 * crescente. Restituisce quante celle di f ha riempito. */
int fondi(int a[], int n, int b[], int m, int f[])
{
    /* TODO: tre indici i (su a), j (su b), k (su f) */
    (void)a; (void)n; (void)b; (void)m; (void)f;
    return 0;
}

void stampa(const char *etichetta, int v[], int n)
{
    int i;
    printf("%s:", etichetta);
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}

int leggi(int v[])
{
    int n, i;
    if (scanf("%d", &n) != 1 || n < 0 || n > N_MAX)
        return -1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return -1;
    return n;
}

int main(void)
{
    int a[N_MAX], b[N_MAX], f[F_MAX];
    int n, m, k;

    n = leggi(a);
    if (n < 0) {
        printf("input non valido\n");
        return 1;
    }
    m = leggi(b);
    if (m < 0) {
        printf("input non valido\n");
        return 1;
    }

    ordina(a, n);
    ordina(b, m);
    k = fondi(a, n, b, m, f);

    stampa("a ordinato", a, n);
    stampa("b ordinato", b, m);
    stampa("fusione", f, k);
    return 0;
}
