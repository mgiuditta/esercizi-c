/*
 * es03 — Ricerca lineare e conteggio delle occorrenze  (SOLUZIONE)
 *
 * Input:  n (da 1 a N_MAX), poi n interi, poi il valore x da cercare.
 * Output: la posizione (indice) della PRIMA volta in cui compare x
 *         (-1 se non c'è) e quante volte compare in tutto.
 *
 * Come testarlo: make sol T=05 E=es03
 */
#include <stdio.h>

#define N_MAX 100

/* Ricerca lineare: guardiamo le celle una dopo l'altra, da sinistra.
 * Appena troviamo x restituiamo SUBITO l'indice: così otteniamo la
 * prima occorrenza e non perdiamo tempo a guardare il resto. */
int cerca(int v[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (v[i] == x)
            return i;      /* trovato: esce dalla funzione */
    /* Se arriviamo qui il ciclo è finito senza trovare nulla.
     * -1 è un indice impossibile (gli indici partono da 0):
     * per questo è un buon segnale di "non trovato". */
    return -1;
}

/* Conteggio: qui invece NON possiamo fermarci al primo,
 * dobbiamo guardare tutte le n celle. */
int conta(int v[], int n, int x)
{
    int i;
    int c = 0;
    for (i = 0; i < n; i++)
        if (v[i] == x)
            c++;
    return c;
}

int main(void)
{
    int v[N_MAX];
    int n, i, x;

    if (scanf("%d", &n) != 1 || n < 1 || n > N_MAX) {
        printf("n non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &x);

    printf("posizione: %d\n", cerca(v, n, x));
    printf("occorrenze: %d\n", conta(v, n, x));
    return 0;
}
