/* =====================================================================
 * es06 — Trova e correggi l'errore: la funzione che "non fa niente"
 * Intermedio
 * Il programma dovrebbe leggere a e b, metterli in ordine crescente
 * (a il minore, b il maggiore) e stampare il doppio del minore.
 * Esempio con input "5 3":
 *   prima: a=5 b=3
 *   dopo: a=3 b=5
 *   doppio del minimo: 6
 * Compila senza avvisi e gira, ma l'output è sbagliato: è un errore di
 * LOGICA, il compilatore non può accorgersene.
 * Correggilo SENZA usare puntatori (& e * li vedrai in 08 e 09).
 * Come testarlo: make test T=07 E=es06
 * ===================================================================== */
#include <stdio.h>

void scambia(int x, int y);
void raddoppia(int x);

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("input non valido\n");
        return 1;
    }
    printf("prima: a=%d b=%d\n", a, b);

    if (a > b)
        scambia(a, b);          /* dovrebbe scambiare a e b... */
    printf("dopo: a=%d b=%d\n", a, b);

    raddoppia(a);               /* dovrebbe raddoppiare a... */
    printf("doppio del minimo: %d\n", a);
    return 0;
}

void scambia(int x, int y) {
    int t = x;
    x = y;
    y = t;
}

void raddoppia(int x) {
    x = x * 2;
}
