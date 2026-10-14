/*
 * es01 — Somma, media, massimo e minimo di un vettore  (SOLUZIONE)
 *
 * Input:  n (da 1 a N_MAX), poi n numeri interi.
 * Output: somma, media (2 decimali), massimo e minimo.
 *
 * Come testarlo: make sol T=05 E=es01
 */
#include <stdio.h>

/* Dimensione massima del vettore. È una costante: il C (nella versione
 * che usa il prof) vuole che la dimensione di un vettore sia nota
 * prima di eseguire il programma. Usiamo #define così, se un giorno
 * serve un vettore più grande, cambiamo un solo numero. */
#define N_MAX 100

/* Somma di tutti gli elementi: stesso schema del prof
 * (somma = somma + v[i]), ma con un for perché sappiamo
 * in anticipo quante volte ripetere (n volte). */
int somma(int v[], int n)
{
    int i;
    int s = 0;               /* parte da 0: elemento neutro della somma */
    for (i = 0; i < n; i++)  /* i < n e NON i <= n: l'ultimo indice è n-1 */
        s = s + v[i];
    return s;
}

/* Massimo: partiamo dal PRIMO elemento, non da 0.
 * Perché? Se tutti i numeri sono negativi (es. -8) e partissimo da 0,
 * il "massimo" risulterebbe 0, che nel vettore non c'è. */
int massimo(int v[], int n)
{
    int i;
    int max = v[0];
    for (i = 1; i < n; i++)  /* da 1: v[0] l'abbiamo già "visto" */
        if (v[i] > max)
            max = v[i];
    return max;
}

/* Minimo: stesso ragionamento del massimo, con < al posto di >. */
int minimo(int v[], int n)
{
    int i;
    int min = v[0];
    for (i = 1; i < n; i++)
        if (v[i] < min)
            min = v[i];
    return min;
}

int main(void)
{
    int v[N_MAX];
    int n, i;

    /* scanf restituisce quanti valori è riuscita a leggere: se non è 1,
     * l'input non era un numero. Controlliamo anche che n stia nei limiti
     * del vettore: se n fosse 200 scriveremmo fuori da v (out of bounds). */
    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);   /* &v[i]: scanf vuole l'indirizzo della cella */

    printf("somma: %d\n", somma(v, n));
    /* (double) PRIMA della divisione: altrimenti 12 / 5 farebbe 2
     * (divisione tra interi) e perderemmo i decimali. */
    printf("media: %.2f\n", (double)somma(v, n) / n);
    printf("massimo: %d\n", massimo(v, n));
    printf("minimo: %d\n", minimo(v, n));
    return 0;
}
