/*
 * es01 — Somma di un pezzo di vettore con un puntatore  (Base)  — SOLUZIONE
 *
 * Testo: implementa somma(p, n), che somma gli n interi che partono
 * dall'indirizzo p, scorrendoli con un PUNTATORE (niente indice i, niente p[i]).
 * Il main la usa tre volte: sul vettore intero, sulla prima meta' e sulla
 * seconda meta' (come nell'esempio del prof con p = v + n/2).
 *
 * Come testarlo: make sol T=09 E=es01
 */
#include <stdio.h>

#define MAX 100

/* p: indirizzo del PRIMO elemento da sommare; n: quanti elementi.
 * "const int *" significa: attraverso p posso LEGGERE gli interi, non
 * modificarli. E' una promessa al chiamante: "non ti tocco il vettore". */
int somma(const int *p, int n)
{
    const int *q;          /* cursore che scorre il vettore */
    const int *fine = p + n; /* indirizzo "uno oltre l'ultimo": p + n avanza
                                di n * sizeof(int) byte. Non lo leggo mai,
                                serve solo come traguardo del ciclo. */
    int s = 0;             /* accumulatore: parte da 0, l'elemento neutro della somma */

    for (q = p; q < fine; q++)  /* q++ avanza di UN int (4 byte), non di 1 byte */
        s += *q;                /* *q = "l'elemento puntato da q" */

    return s;              /* se n == 0 il ciclo non parte e restituisco 0 */
}

int main(void)
{
    int v[MAX];
    int n, i;
    int *p;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1)
            return 1;

    /* v da solo vale &v[0]: il nome del vettore e' l'indirizzo del primo elemento */
    printf("totale: %d\n", somma(v, n));
    printf("prima meta': %d\n", somma(v, n / 2));

    p = v + n / 2;   /* p punta a meta' vettore: la funzione "crede" che il
                        vettore cominci li' (e' il trucco del sottovettore) */
    printf("seconda meta': %d\n", somma(p, n - n / 2));
    return 0;
}
