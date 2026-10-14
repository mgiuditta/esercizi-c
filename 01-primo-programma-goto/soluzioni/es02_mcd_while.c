/*
 * 01 — es02: MCD senza goto, con while  (Base) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es02
 */
#include <stdio.h>

int mcd_while(int x, int y)
{
    int r;

    /* Il while controlla la condizione PRIMA di ogni giro.
       Se y e' gia' 0 non entro mai nel ciclo: niente x % 0, niente crash.
       Nella versione con goto il controllo (r == 0) veniva DOPO il %:
       per questo li' y = 0 era un problema. */
    while (y != 0) {
        r = x % y;   /* stesso passo della "riga 3" */
        x = y;       /* "riga 5" */
        y = r;       /* "riga 6" */
    }                /* la "riga 7" (goto 3) e' sparita: la fa il while */

    /* Attenzione: ho spostato tutto di un passo. Quando esco, y vale 0 e
       il vecchio y (l'ultimo divisore utile) e' stato copiato in x. */
    return x;
}

int main(void)
{
    int x = 0;
    int y = 0;

    if (scanf("%d %d", &x, &y) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    printf("MCD(%d, %d) = %d\n", x, y, mcd_while(x, y));
    return 0;
}
