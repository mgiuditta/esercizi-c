/*
 * 02 — es03: cifrario di Cesare su un carattere  (Base)
 *
 * Testo: un char e' un numero (il suo codice ASCII: 'a' = 97, 'b' = 98, ...).
 * Il cifrario di Cesare sposta ogni lettera di k posizioni nell'alfabeto,
 * ricominciando da capo dopo la 'z': con k = 3, 'a' -> 'd', 'z' -> 'c'.
 * Completa cifra(c, k):
 *   - se c e' una lettera minuscola ('a'..'z') restituisci la lettera spostata;
 *     k puo' essere anche negativo (decifrare) o maggiore di 26;
 *   - altrimenti restituisci c invariato.
 *
 * Input: un carattere e un intero.  Esempio:  z 1  ->  z + 1 -> a
 *
 * Come testarlo: make test T=02 E=es03
 */
#include <stdio.h>

char cifra(char c, int k)
{
    /* TODO: 1) posizione = c - 'a'   (0 per 'a', 25 per 'z')
             2) nuova posizione con + k e % 26
             3) attenzione: in C il % di un numero negativo e' negativo!
             4) ritorna 'a' + nuova posizione */
    (void)k;
    return c;
}

int main(void)
{
    char c = 0;
    int k = 0;

    /* lo spazio prima di %c salta eventuali spazi e a capo */
    if (scanf(" %c %d", &c, &k) != 2) {
        printf("Input non valido\n");
        return 1;
    }
    printf("%c + %d -> %c\n", c, k, cifra(c, k));
    printf("codici ASCII: %d -> %d\n", c, cifra(c, k));
    return 0;
}
