/*
 * es01 — Fattoriale e potenza ricorsivi  ·  Base
 * Ispirato a: Trascrizione 4.2 (fattoriale e potenza), Appunti Unità 4, par. 2.6 e 2.8.
 *
 * Completa le due funzioni SENZA cicli (niente for/while): devono richiamare se stesse.
 *   fattoriale(n): 1 se n <= 1, altrimenti n * fattoriale(n-1)
 *   potenza(i, n): 1 se n == 0, altrimenti i * potenza(i, n-1)
 * Il main è già scritto: legge n, poi base ed esponente, e stampa i risultati.
 *
 * Come testarlo: make test T=13 E=es01
 */
#include <stdio.h>

int fattoriale(int n)
{
    /* TODO: caso base (n <= 1) e passo ricorsivo */
    (void)n;          /* evita il warning "parametro non usato": toglila quando scrivi il codice */
    return 0;
}

int potenza(int i, int n)
{
    /* TODO: caso base (n == 0) e passo ricorsivo */
    (void)i;
    (void)n;
    return 0;
}

int main(void)
{
    int n, base, esp;

    if (scanf("%d", &n) != 1)
        return 1;
    printf("%d! = %d\n", n, fattoriale(n));

    if (scanf("%d %d", &base, &esp) != 2)
        return 1;
    if (esp < 0) {
        printf("Esponente negativo non gestito\n");
        return 0;
    }
    printf("%d^%d = %d\n", base, esp, potenza(base, esp));
    return 0;
}
