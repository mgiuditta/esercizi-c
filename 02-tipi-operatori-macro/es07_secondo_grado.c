/*
 * 02 — es07: equazione di secondo grado  (Tipo esame)
 *
 * Testo: legge tre coefficienti INTERI a, b, c dell'equazione
 * a*x^2 + b*x + c = 0 e stampa le soluzioni reali con 2 decimali.
 *   - se a == 0:          "Non e' di secondo grado"
 *   - delta = b^2 - 4ac
 *   - delta < 0:          "Delta = D: nessuna soluzione reale"
 *   - delta == 0:         "Delta = 0: x = X"            con X = -b / (2a)
 *   - delta > 0:          "Delta = D: x1 = X1, x2 = X2" con
 *                          X1 = (-b - radice(delta)) / (2a)
 *                          X2 = (-b + radice(delta)) / (2a)
 * Completa le tre funzioni. sqrt(d) (da <math.h>) calcola la radice quadrata
 * di un double. Occhio: i coefficienti sono int, le soluzioni double!
 *
 * Esempio:  4 4 1  ->  Delta = 0: x = -0.50
 *
 * Come testarlo: make test T=02 E=es07
 */
#include <stdio.h>
#include <math.h>

int calcola_delta(int a, int b, int c)
{
    /* TODO */
    (void)a;
    (void)b;
    (void)c;
    return 0;
}

double soluzione_doppia(int a, int b)
{
    /* TODO: -b / (2a), ma come divisione REALE */
    (void)a;
    (void)b;
    return 0.0;
}

double soluzione(int a, int b, int delta, int segno)
{
    /* TODO: (-b + segno * radice(delta)) / (2a)
             segno vale -1 per x1 e +1 per x2 */
    (void)a;
    (void)b;
    (void)delta;
    (void)segno;
    return 0.0;
}

int main(void)
{
    int a = 0, b = 0, c = 0;
    int delta = 0;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Input non valido\n");
        return 1;
    }
    if (a == 0) {
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
