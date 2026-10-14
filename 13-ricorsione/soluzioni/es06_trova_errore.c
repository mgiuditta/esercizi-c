/*
 * es06 — Trova e correggi l'errore: tre funzioni ricorsive  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.2 ("una ricorsione è ben definita se ogni passo
 * si avvicina al caso base"), Appunti Unità 4 par. 2.5, LEZ 20 cap. 5.
 */
#include <stdio.h>

/* Quante cifre ha n (n >= 0)?  Es. 1234 -> 4, 7 -> 1, 0 -> 1. */
int cifre(int n)
{
    if (n < 10)                 /* CORRETTO: un numero da 0 a 9 ha UNA cifra (prima c'era return 0) */
        return 1;
    return 1 + cifre(n / 10);   /* tolgo l'ultima cifra e la conto */
}

/* Somma 1 + 2 + ... + n (per n <= 0 la somma è vuota e vale 0). */
int somma_fino(int n)
{
    if (n <= 0)                 /* CORRETTO: prima era "n == 1", e con n = 0 la ricorsione */
        return 0;               /* scendeva a -1, -2, ... senza mai fermarsi (stack overflow) */
    return n + somma_fino(n - 1);
}

/* Conto alla rovescia: n n-1 ... 1 via! */
void rovescia(int n)
{
    if (n <= 0) {
        printf("via!\n");
        return;
    }
    printf("%d ", n);           /* CORRETTO: la stampa va PRIMA della chiamata (fase di winding), */
    rovescia(n - 1);            /* altrimenti i numeri escono al ritorno, cioè in ordine crescente */
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
