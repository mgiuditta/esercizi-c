/* =====================================================================
 * es08 — Equazione di secondo grado come nell'E-tivity 3.6
 * Tipo esame  ·  SOLUZIONE
 * Struttura del prof: coefficienti(float *, float *, float *) legge i
 * coefficienti DENTRO la funzione e li scrive nelle variabili del main;
 * discriminante(...) restituisce un double; radici(...) calcola le
 * radici. Miglioria suggerita dal prof stesso: le stampe stanno nel
 * main e radici "restituisce" x1 e x2 tramite puntatori.
 * Come testarlo: make sol T=08 E=es08
 * ===================================================================== */
#include <stdio.h>
#include <math.h>

int coefficienti(float *c1, float *c2, float *c3);
double discriminante(float c1, float c2, float c3);
int radici(float a, float b, double d, double *x1, double *x2);

int main(void) {
    float a, b, c;          /* come il prof: tre float e un double */
    double d, x1, x2;
    int n;

    /* &a, &b, &c: passo gli indirizzi, così la funzione può riempirli */
    if (!coefficienti(&a, &b, &c)) {
        printf("input non valido\n");
        return 1;
    }
    if (a == 0) {           /* come nell'E-tivity: con a = 0 non si va avanti */
        printf("a = 0: non e' un'equazione di secondo grado\n");
        return 0;
    }
    d = discriminante(a, b, c);   /* qui basta il passaggio per valore */
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

/* Restituisce 1 se ha letto tre numeri, 0 altrimenti (il prof la scrive
 * void: il valore di ritorno è un'aggiunta per controllare scanf). */
int coefficienti(float *c1, float *c2, float *c3) {
    /* c1 è GIÀ un indirizzo (float *): in scanf NON serve la &.
     * scanf scrive direttamente nella a del main. */
    return scanf("%f %f %f", c1, c2, c3) == 3;
}

double discriminante(float c1, float c2, float c3) {
    /* converto in double prima di moltiplicare, così il calcolo avviene
     * con la precisione maggiore del double e non del float */
    return (double)c2 * c2 - 4.0 * c1 * c3;
}

/* Restituisce il numero di radici reali (0, 1 o 2) e scrive le radici
 * in *x1 e *x2. Se non ci sono radici reali, *x1 e *x2 non vengono toccati. */
int radici(float a, float b, double d, double *x1, double *x2) {
    if (d > 0) {
        *x1 = (-b + sqrt(d)) / (2.0 * a);
        *x2 = (-b - sqrt(d)) / (2.0 * a);
        return 2;
    }
    if (d == 0) {
        *x1 = *x2 = -b / (2.0 * a);
        return 1;
    }
    return 0;
}
