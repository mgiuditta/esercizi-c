/* =====================================================================
 * es05 — MCD come funzione, e mcm che la riusa  ·  Intermedio  ·  SOLUZIONE
 * mcd(a, b) con l'algoritmo di Euclide (quello del prof, ma con while
 * al posto del goto); mcm(a, b) = a / mcd(a, b) * b.
 * Input: due interi >= 0, non entrambi 0.
 * Come testarlo: make sol T=07 E=es05
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
    int r;
    /* Euclide: mcd(a, b) = mcd(b, a % b). Ci si ferma quando il
     * secondo numero è 0: a quel punto il primo è il MCD.
     * Il controllo b != 0 viene PRIMA di a % b: così non divido mai per 0. */
    while (b != 0) {
        r = a % b;
        a = b;       /* modifico a e b: sono COPIE, le variabili del main */
        b = r;       /* restano intatte (passaggio per valore) */
    }
    return a;
}

int mcm(int a, int b) {
    if (a == 0 || b == 0)
        return 0;                 /* per convenzione mcm con 0 vale 0 */
    /* divido PRIMA di moltiplicare: il numero intermedio resta più
     * piccolo e si riduce il rischio di overflow */
    return a / mcd(a, b) * b;
}
