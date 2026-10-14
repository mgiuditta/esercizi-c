/*
 * es06 — Trova e correggi l'errore: tre funzioni ricorsive  ·  Intermedio
 * Ispirato a: Trascrizione 4.2 ("una ricorsione è ben definita se ogni passo si avvicina
 * al caso base"), Appunti Unità 4 par. 2.5, LEZ 20 cap. 5.
 *
 * Il programma compila, ma ci sono TRE errori (uno per funzione).
 * Con input 5 l'output è sbagliato; con input 0 il programma CROLLA
 * (AddressSanitizer scrive "stack-overflow"). Trova e correggi tutti e tre.
 * Output corretto con input 5:
 *   cifre(5) = 1
 *   somma 1..5 = 15
 *   rovescia: 5 4 3 2 1 via!
 *
 * Come testarlo: make test T=13 E=es06
 */
#include <stdio.h>

/* Quante cifre ha n (n >= 0)?  Es. 1234 -> 4, 7 -> 1, 0 -> 1. */
int cifre(int n)
{
    if (n < 10)
        return 0;
    return 1 + cifre(n / 10);
}

/* Somma 1 + 2 + ... + n (per n <= 0 la somma è vuota e vale 0). */
int somma_fino(int n)
{
    if (n == 1)
        return 1;
    return n + somma_fino(n - 1);
}

/* Conto alla rovescia: n n-1 ... 1 via! */
void rovescia(int n)
{
    if (n <= 0) {
        printf("via!\n");
        return;
    }
    rovescia(n - 1);
    printf("%d ", n);
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Serve un intero >= 0\n");
        return 0;
    }
    printf("cifre(%d) = %d\n", n, cifre(n));
    printf("somma 1..%d = %d\n", n, somma_fino(n));
    printf("rovescia: ");
    rovescia(n);
    return 0;
}
