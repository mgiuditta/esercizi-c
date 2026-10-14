/*
 * 02 — es05: Cosa stampa? (Intermedio) — SOLUZIONE (stesso codice: la spiegazione e' nel README)
 *
 * Testo: NON eseguire subito. Per ogni printf, espandi a mano la macro
 * (scrivi il testo che il preprocessore mette al suo posto), poi calcola.
 * Scrivi la previsione nel README (sezione es05), poi esegui il test.
 * Puoi vedere l'espansione vera con:  cc -E es05_cosa_stampa_macro.c | tail -20
 *
 * Come testarlo: make test T=02 E=es05
 * (il test passa gia': serve a confrontare la TUA previsione con la realta')
 */
#include <stdio.h>

#define LUNGHEZZA 20
#define DIFFERENZA 3-2
#define DIFFERENZA_OK (3-2)
#define MOLTIPLICA(a, b) a * b
#define MOLTIPLICA_OK(a, b) ((a) * (b))
#define META(x) x / 2
#define QUADRATO(x) (x) * (x)
#define QUADRATO_OK(x) ((x) * (x))

int main(void)
{
    int x = 4;
    int y = 3;

    printf("1) %d\n", LUNGHEZZA * 2);
    printf("2) %d\n", 10 * DIFFERENZA);
    printf("3) %d\n", 10 * DIFFERENZA_OK);
    printf("4) %d\n", MOLTIPLICA(x - 1, y));
    printf("5) %d\n", MOLTIPLICA_OK(x - 1, y));
    printf("6) %d\n", META(x + 6));
    printf("7) %d\n", 100 / QUADRATO(5));
    printf("8) %d\n", 100 / QUADRATO_OK(5));
    printf("9) %d\n", MOLTIPLICA(y, y) - DIFFERENZA);
    return 0;
}
