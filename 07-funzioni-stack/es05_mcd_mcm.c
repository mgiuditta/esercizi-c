/* =====================================================================
 * es05 — MCD come funzione, e mcm che la riusa  ·  Intermedio
 * Completa:
 *   mcd(a, b): massimo comune divisore con l'algoritmo di Euclide
 *              (quello dell'E-tivity 2.1 del prof, ma con un ciclo while
 *              invece dei goto). Deve funzionare anche se b vale 0.
 *   mcm(a, b): minimo comune multiplo, calcolato CHIAMANDO mcd:
 *              mcm = a / mcd(a, b) * b  (e vale 0 se a o b è 0).
 * Input: due interi >= 0, non entrambi 0 (il main controlla).
 * Output:
 *   mcd(12, 18) = 6
 *   mcm(12, 18) = 36
 * Come testarlo: make test T=07 E=es05
 * ===================================================================== */
#include <stdio.h>

int mcd(int a, int b);
int mcm(int a, int b);

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b < 0 || (a == 0 && b == 0)) {
        printf("servono due interi >= 0, non entrambi 0\n");
        return 0;
    }
    printf("mcd(%d, %d) = %d\n", a, b, mcd(a, b));
    printf("mcm(%d, %d) = %d\n", a, b, mcm(a, b));
    return 0;
}

int mcd(int a, int b) {
    /* TODO: finché b != 0: r = a % b; a = b; b = r;  poi restituisci a */
    (void)a; (void)b;   /* cancella questa riga */
    return 0;
}

int mcm(int a, int b) {
    /* TODO: caso con uno zero, poi usa mcd */
    (void)a; (void)b;   /* cancella questa riga */
    return 0;
}
