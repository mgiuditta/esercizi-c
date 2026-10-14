/* =====================================================================
 * es05 — Cosa stampa? Macro contro funzioni  ·  Intermedio  ·  SOLUZIONE
 * Il codice è identico allo starter: l'esercizio è PREVEDERE l'output.
 * Per vedere il codice dopo l'espansione:  cc -E es05_macro_cosa_stampa.c
 * Come testarlo: make sol T=08 E=es05
 * ===================================================================== */
#include <stdio.h>

#define MOLTIPLICA(a, b) a * b                  /* come nella slide del prof: senza parentesi */
#define MUL(a, b) ((a) * (b))                   /* versione corretta */
#define QUADRATO(x) x * x                       /* senza parentesi */
#define QUAD_OK(x) ((x) * (x))                  /* con parentesi */
#define MAX(a, b) ((a) > (b) ? (a) : (b))       /* parentesi perfette, ma a compare 2 volte */

int massimo(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int a = 4, b = 3, c = 1;
    int i, j = 4, m;

    printf("1) %d\n", MOLTIPLICA(a - c, b));    /* a - c * b  = 4 - 3     = 1   */
    printf("2) %d\n", MUL(a - c, b));           /* ((a - c) * (b)) = 3 * 3 = 9  */
    printf("3) %d\n", QUADRATO(a + 1));         /* a + 1 * a + 1 = 4+4+1  = 9   */
    printf("4) %d\n", 100 / QUADRATO(2));       /* 100 / 2 * 2 = 50 * 2   = 100 */
    printf("5) %d\n", 100 / QUAD_OK(2));        /* 100 / ((2) * (2))      = 25  */

    i = 2;
    m = MAX(i++, j);       /* ((i++) > (j) ? (i++) : (j)): 2 > 4 falso -> j; i++ UNA volta */
    printf("6) m=%d i=%d\n", m, i);             /* m=4 i=3 */

    i = 7;
    m = MAX(i++, j);       /* 7 > 4 vero (i diventa 8) -> (i++) vale 8, poi i diventa 9 */
    printf("7) m=%d i=%d\n", m, i);             /* m=8 i=9: 8 non era nemmeno nei dati! */

    i = 7;
    m = massimo(i++, j);   /* funzione: i++ valutato UNA volta, passa 7, i diventa 8 */
    printf("8) m=%d i=%d\n", m, i);             /* m=7 i=8 */
    return 0;
}
