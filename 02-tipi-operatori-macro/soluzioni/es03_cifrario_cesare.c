/*
 * 02 — es03: cifrario di Cesare su un carattere  (Base) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es03
 */
#include <stdio.h>

char cifra(char c, int k)
{
    int pos;

    /* I codici di 'a'..'z' sono consecutivi nella tabella ASCII,
       quindi posso confrontare i caratteri come numeri. */
    if (c < 'a' || c > 'z')
        return c;                 /* non e' una minuscola: non la tocco */

    pos = c - 'a';                /* char promosso a int: 'd' - 'a' = 3 */
    pos = (pos + k) % 26;         /* % 26 fa "ripartire da capo" dopo la z */

    /* Dal C99 la divisione intera tronca verso lo zero, quindi
       -1 % 26 vale -1 (non 25 come in matematica). Lo correggo: */
    if (pos < 0)
        pos = pos + 26;

    /* 'a' + pos e' un int: il cast esplicito dice "so che ci sta in un char" */
    return (char)('a' + pos);
}

int main(void)
{
    char c = 0;
    int k = 0;

    if (scanf(" %c %d", &c, &k) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    /* stesso valore, due interpretazioni: %c lo mostra come carattere,
       %d come numero */
    printf("%c + %d -> %c\n", c, k, cifra(c, k));
    printf("codici ASCII: %d -> %d\n", c, cifra(c, k));
    return 0;
}
