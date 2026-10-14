/*
 * es08 — Torre di Hanoi con numero del disco e conteggio delle mosse  (SOLUZIONE)
 * Ispirato a: Appunti Unità 4, par. 2.12 (funzione hanoi(n, s, d, a) e muoviDisco).
 */
#include <stdio.h>

/* Stampa una mossa e aggiorna il contatore del chiamante.
 * mosse è un PUNTATORE: tutte le chiamate ricorsive scrivono sullo stesso contatore
 * (quello del main), invece che su copie private nei loro record di attivazione. */
void muoviDisco(int disco, int s, int d, int *mosse)
{
    (*mosse)++;
    printf("mossa %d: disco %d da %d a %d\n", *mosse, disco, s, d);
}

/* n dischi da s (sorgente) a d (destinazione) usando a (appoggio). Firma degli Appunti + contatore. */
void hanoi(int n, int s, int d, int a, int *mosse)
{
    if (n == 1)                         /* caso base: un disco si sposta direttamente */
        muoviDisco(1, s, d, mosse);     /* il disco più piccolo è il numero 1 */
    else {
        hanoi(n - 1, s, a, d, mosse);   /* 1. gli n-1 dischi sopra vanno sull'appoggio */
        muoviDisco(n, s, d, mosse);     /* 2. il disco n (il più grande) va a destinazione */
        hanoi(n - 1, a, d, s, mosse);   /* 3. gli n-1 dischi tornano sopra al disco n */
    }
}

/* Potenza ricorsiva di es01: serve per verificare la formula 2^n - 1. */
int potenza(int i, int n)
{
    if (n == 0)
        return 1;
    return i * potenza(i, n - 1);
}

int main(void)
{
    int n, mosse = 0;

    if (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        /* n = 0 farebbe saltare il caso base n == 1 (0, -1, -2, ...): lo blocchiamo qui */
        printf("Numero di dischi non valido (1..10)\n");
        return 0;
    }
    hanoi(n, 1, 3, 2, &mosse);          /* paletti numerati 1, 2, 3: da 1 a 3 usando 2 */
    printf("Totale mosse: %d (2^%d - 1 = %d)\n", mosse, n, potenza(2, n) - 1);
    return 0;
}
