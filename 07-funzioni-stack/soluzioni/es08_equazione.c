/* =====================================================================
 * es08 — Equazione di secondo grado scomposta in funzioni
 * Tipo esame  ·  SOLUZIONE
 * Scomposizione del prof (lezione 3.1): leggi coefficienti -> calcola
 * discriminante -> calcola radici. Qui SENZA puntatori: ogni funzione
 * restituisce UN valore con return, e le stampe stanno nel main.
 * Input: a b c (numeri reali). Output con %.2f.
 * Come testarlo: make sol T=07 E=es08
 * ===================================================================== */
#include <stdio.h>
#include <math.h>   /* sqrt: il runner compila già con -lm */

double discriminante(double a, double b, double c);
int numero_radici(double delta);
double radice(double a, double b, double delta, int segno);

int main(void) {
    double a, b, c, delta;
    int n;

    /* sottoproblema 1: leggere i coefficienti (%lf = double in scanf) */
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("input non valido\n");
        return 1;
    }
    /* con a = 0 la formula dividerebbe per 0: non è di secondo grado */
    if (a == 0) {
        printf("a = 0: non e' un'equazione di secondo grado\n");
        return 0;
    }

    /* sottoproblema 2: discriminante, calcolato UNA volta e salvato */
    delta = discriminante(a, b, c);
    printf("delta = %.2f\n", delta);

    /* sottoproblema 3: quante radici reali? */
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
    return b * b - 4 * a * c;     /* il valore esce con return */
}

int numero_radici(double delta) {
    /* Confronto esatto con 0: va bene qui perché con coefficienti
     * interi delta è calcolato senza errori di arrotondamento. */
    if (delta > 0)
        return 2;
    if (delta == 0)
        return 1;
    return 0;
}

/* segno = +1 per (-b + sqrt(delta)) / 2a, segno = -1 per (-b - sqrt(delta)) / 2a.
 * Un'unica funzione con un parametro in più evita di scrivere due
 * funzioni quasi identiche. Va chiamata solo con delta >= 0. */
double radice(double a, double b, double delta, int segno) {
    return (-b + segno * sqrt(delta)) / (2 * a);
}
