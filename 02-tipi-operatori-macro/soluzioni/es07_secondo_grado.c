/*
 * 02 — es07: equazione di secondo grado  (Tipo esame) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es07
 */
#include <stdio.h>
#include <math.h>    /* sqrt. Su Linux serve anche -lm al linker (il runner lo mette) */

int calcola_delta(int a, int b, int c)
{
    /* Tutto intero: con coefficienti piccoli non c'e' rischio di overflow.
       Precedenza: prima le moltiplicazioni, poi la sottrazione. */
    return b * b - 4 * a * c;
}

double soluzione_doppia(int a, int b)
{
    /* -b / (2 * a) tra int sarebbe divisione intera: con a=4, b=4
       darebbe -4 / 8 = 0 invece di -0.5.
       2.0 e' double: tutto il denominatore diventa double e la
       divisione e' reale. */
    return -b / (2.0 * a);
}

double soluzione(int a, int b, int delta, int segno)
{
    /* sqrt vuole un double: (double)delta rende esplicita la conversione
       (sarebbe avvenuta comunque, implicitamente). sqrt restituisce double,
       quindi -b + segno * ... e' gia' double. Il denominatore lo scrivo
       con 2.0 per coerenza con soluzione_doppia. */
    return (-b + segno * sqrt((double)delta)) / (2.0 * a);
}

int main(void)
{
    int a = 0, b = 0, c = 0;
    int delta = 0;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Input non valido\n");
        return 1;
    }
    if (a == 0) {                 /* niente x^2: dividerei per 2a = 0 */
        printf("Non e' di secondo grado\n");
        return 0;
    }

    delta = calcola_delta(a, b, c);
    if (delta < 0)
        printf("Delta = %d: nessuna soluzione reale\n", delta);
    else if (delta == 0)
        printf("Delta = 0: x = %.2f\n", soluzione_doppia(a, b));
    else
        printf("Delta = %d: x1 = %.2f, x2 = %.2f\n", delta,
               soluzione(a, b, delta, -1), soluzione(a, b, delta, 1));
    return 0;
}
