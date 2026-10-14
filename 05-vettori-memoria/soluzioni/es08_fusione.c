/*
 * es08 — Fusione di due vettori ordinati (merge)  (SOLUZIONE)
 *
 * Input:  n (0..N_MAX), n interi (vettore a);
 *         m (0..N_MAX), m interi (vettore b). Non sono necessariamente ordinati.
 * Output: a ordinato, b ordinato, e il vettore fusione (n+m elementi
 *         in ordine crescente) costruito SENZA riordinare tutto da capo.
 *
 * Come testarlo: make sol T=05 E=es08
 */
#include <stdio.h>

#define N_MAX 50
#define F_MAX (2 * N_MAX)   /* la fusione può contenere tutti gli elementi di a e di b */

/* Selection sort (lo stesso di es06, senza le stampe intermedie). */
void ordina(int v[], int n)
{
    int p, i, pos_min, tmp;
    for (p = 0; p < n - 1; p++) {
        pos_min = p;
        for (i = p + 1; i < n; i++)
            if (v[i] < v[pos_min])
                pos_min = i;
        tmp = v[p];
        v[p] = v[pos_min];
        v[pos_min] = tmp;
    }
}

/* Fusione: tre indici. i scorre a, j scorre b, k scrive in f.
 * Ad ogni passo confrontiamo a[i] e b[j] e copiamo in f il più piccolo:
 * siccome a e b sono già ordinati, il più piccolo tra i due "in testa"
 * è il più piccolo di tutti quelli rimasti. È come unire due mazzi di
 * carte già in ordine prendendo sempre la carta più bassa in cima. */
int fondi(int a[], int n, int b[], int m, int f[])
{
    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {          /* finché ENTRAMBI hanno elementi */
        if (a[i] <= b[j])             /* <= : a parità prendiamo da a */
            f[k++] = a[i++];
        else
            f[k++] = b[j++];
    }
    /* Uno dei due è finito: copiamo quello che resta dell'altro.
     * Copia elemento per elemento: in C non si può scrivere f = a
     * (un vettore non si assegna in blocco). Solo uno dei due cicli
     * farà davvero qualcosa. */
    while (i < n)
        f[k++] = a[i++];
    while (j < m)
        f[k++] = b[j++];
    return k;                         /* k = n + m: quante celle di f sono usate */
}

void stampa(const char *etichetta, int v[], int n)
{
    int i;
    printf("%s:", etichetta);
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}

/* Legge un vettore: prima la quantità, poi gli elementi.
 * Restituisce la quantità, oppure -1 se l'input non va bene. */
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
