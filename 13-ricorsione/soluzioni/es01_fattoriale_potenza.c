/*
 * es01 — Fattoriale e potenza ricorsivi  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.2 (fattoriale e potenza), Appunti Unità 4, par. 2.6 e 2.8.
 */
#include <stdio.h>

/* Fattoriale ricorsivo, esattamente come lo scrive il prof.
 * Caso base: n <= 1. Il prof usa "<= 1" (e non "== 0") perché:
 *   - 0! = 1 e 1! = 1, quindi entrambi si risolvono subito;
 *   - un numero negativo cade comunque nel caso base e la ricorsione
 *     termina invece di scendere a -1, -2, ... all'infinito. */
int fattoriale(int n)
{
    if (n <= 1)                      /* caso base: risposta diretta */
        return 1;
    return n * fattoriale(n - 1);    /* passo ricorsivo: problema più piccolo (n-1) */
}

/* Potenza i^n ricorsiva (Appunti par. 2.8): i^0 = 1, i^n = i * i^(n-1).
 * Ogni chiamata riduce n di 1, quindi prima o poi n arriva a 0 (caso base). */
int potenza(int i, int n)
{
    if (n == 0)                      /* caso base: qualunque numero alla 0 vale 1 */
        return 1;
    return i * potenza(i, n - 1);    /* la base i resta uguale, cala solo l'esponente */
}

int main(void)
{
    int n, base, esp;

    if (scanf("%d", &n) != 1)        /* scanf restituisce quanti valori ha letto */
        return 1;
    printf("%d! = %d\n", n, fattoriale(n));

    if (scanf("%d %d", &base, &esp) != 2)
        return 1;
    if (esp < 0) {                   /* con esponente negativo la ricorsione non arriverebbe mai a 0 */
        printf("Esponente negativo non gestito\n");
        return 0;
    }
    printf("%d^%d = %d\n", base, esp, potenza(base, esp));
    return 0;
}
