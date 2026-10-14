/*
 * es03 — Cosa stampa? Stampe prima e dopo la chiamata ricorsiva
 * Ispirato a: Trascrizione 4.2 (funzione leggi: winding e unwinding), LEZ 20 par. 5.6.
 *
 * Questo file È GIÀ COMPLETO. L'esercizio è nel README:
 * prevedi l'output SENZA eseguire, scrivilo nel README, poi lancia
 *   make test T=13 E=es03
 * e confronta.
 */
#include <stdio.h>

/* Parte A: una stampa PRIMA e una DOPO la chiamata ricorsiva. */
void scendi(int n)
{
    printf("giu %d\n", n);       /* eseguita mentre si scende (winding) */
    if (n > 0)
        scendi(n - 1);
    printf("su %d\n", n);        /* eseguita mentre si risale (unwinding) */
}

/* Parte B: stampa SOLO dopo la chiamata. */
void conta(int n)
{
    if (n == 0)
        return;
    conta(n - 1);
    printf("%d ", n);
}

/* Parte C: stampa dopo la chiamata, con n che si dimezza. */
void misterio(int n)
{
    if (n > 1)
        misterio(n / 2);
    printf("%d", n % 2);
}

int main(void)
{
    printf("--- A ---\n");
    scendi(2);

    printf("--- B ---\n");
    conta(3);
    printf("\n");

    printf("--- C ---\n");
    misterio(6);
    printf("\n");
    misterio(13);
    printf("\n");
    return 0;
}
