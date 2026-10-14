/* =====================================================================
 * es08 — Equazione di secondo grado come nell'E-tivity 3.6  ·  Tipo esame
 * Riprendi la struttura del prof:
 *   coefficienti(float *c1, float *c2, float *c3)
 *       legge i tre coefficienti con scanf e li scrive nelle variabili
 *       del main; restituisce 1 se ha letto 3 numeri, 0 altrimenti.
 *   discriminante(c1, c2, c3)  -> restituisce b*b - 4*a*c (double)
 *   radici(a, b, d, &x1, &x2)  -> restituisce quante radici reali ci sono
 *       (2, 1 o 0) e scrive le radici in *x1 e *x2 (con 1 radice: entrambe
 *       uguali a -b/2a).
 * Il main è già scritto: stampa con %.2f. Esempio con "1 -5 6":
 *   delta = 1.00
 *   radici reali: 2
 *   x1 = 3.00
 *   x2 = 2.00
 * Sfida: dopo, riscrivi tutto da zero senza guardare (è da esame).
 * Come testarlo: make test T=08 E=es08
 * ===================================================================== */
#include <stdio.h>
#include <math.h>

int coefficienti(float *c1, float *c2, float *c3);
double discriminante(float c1, float c2, float c3);
int radici(float a, float b, double d, double *x1, double *x2);

int main(void) {
    float a, b, c;
    double d, x1 = 0, x2 = 0;
    int n;

    if (!coefficienti(&a, &b, &c)) {
        printf("input non valido\n");
        return 1;
    }
    if (a == 0) {
        printf("a = 0: non e' un'equazione di secondo grado\n");
        return 0;
    }
    d = discriminante(a, b, c);
    printf("delta = %.2f\n", d);

    n = radici(a, b, d, &x1, &x2);
    if (n == 0) {
        printf("nessuna radice reale\n");
    } else if (n == 1) {
        printf("radici reali: 1 (coincidenti)\n");
        printf("x1 = x2 = %.2f\n", x1);
    } else {
        printf("radici reali: 2\n");
        printf("x1 = %.2f\n", x1);
        printf("x2 = %.2f\n", x2);
    }
    return 0;
}

int coefficienti(float *c1, float *c2, float *c3) {
    /* TODO: una scanf con tre %f. Serve la & davanti a c1? Perché? */
    (void)c1; (void)c2; (void)c3;   /* cancella questa riga */
    return 0;
}

double discriminante(float c1, float c2, float c3) {
    /* TODO */
    (void)c1; (void)c2; (void)c3;   /* cancella questa riga */
    return 0;
}

int radici(float a, float b, double d, double *x1, double *x2) {
    /* TODO: tre casi, d > 0, d == 0, d < 0. Usa sqrt(d). */
    (void)a; (void)b; (void)d; (void)x1; (void)x2;   /* cancella questa riga */
    return 0;
}
