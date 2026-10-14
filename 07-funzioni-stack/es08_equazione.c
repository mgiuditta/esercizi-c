/* =====================================================================
 * es08 — Equazione di secondo grado scomposta in funzioni  ·  Tipo esame
 * È l'esempio del prof (lezione 3.1): leggi i coefficienti, calcola il
 * discriminante, calcola le radici. Qui SENZA puntatori: ogni funzione
 * restituisce UN solo valore con return e le stampe stanno nel main.
 * Completa le tre funzioni:
 *   discriminante(a, b, c)        -> b*b - 4*a*c
 *   numero_radici(delta)          -> 2 se delta > 0, 1 se delta == 0, 0 se < 0
 *   radice(a, b, delta, segno)    -> (-b + segno*sqrt(delta)) / (2*a)
 *                                    con segno = +1 oppure -1
 * Input: a b c. Output (esempio con 1 -5 6):
 *   delta = 1.00
 *   radici reali: 2
 *   x1 = 3.00
 *   x2 = 2.00
 * Sfida: dopo, prova a riscrivere da zero anche il main senza guardarlo.
 * Come testarlo: make test T=07 E=es08
 * ===================================================================== */
#include <stdio.h>
#include <math.h>   /* sqrt (il runner compila già con -lm) */

double discriminante(double a, double b, double c);
int numero_radici(double delta);
double radice(double a, double b, double delta, int segno);

int main(void) {
    double a, b, c, delta;
    int n;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("input non valido\n");
        return 1;
    }
    if (a == 0) {
        printf("a = 0: non e' un'equazione di secondo grado\n");
        return 0;
    }

    delta = discriminante(a, b, c);
    printf("delta = %.2f\n", delta);

    n = numero_radici(delta);
    if (n == 0) {
        printf("nessuna radice reale\n");
    } else if (n == 1) {
        printf("radici reali: 1 (coincidenti)\n");
        printf("x1 = x2 = %.2f\n", radice(a, b, delta, 1));
    } else {
        printf("radici reali: 2\n");
        printf("x1 = %.2f\n", radice(a, b, delta, +1));
        printf("x2 = %.2f\n", radice(a, b, delta, -1));
    }
    return 0;
}

double discriminante(double a, double b, double c) {
    /* TODO */
    (void)a; (void)b; (void)c;   /* cancella questa riga */
    return 0;
}

int numero_radici(double delta) {
    /* TODO */
    (void)delta;   /* cancella questa riga */
    return 0;
}

double radice(double a, double b, double delta, int segno) {
    /* TODO: usa sqrt(delta) */
    (void)a; (void)b; (void)delta; (void)segno;   /* cancella questa riga */
    return 0;
}
