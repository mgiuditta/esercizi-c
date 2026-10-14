/*
 * es01 — Punto 2D e distanza  (Base)
 *
 * Testo: con il tipo Punto (typedef struct con campi x e y) implementa
 * distanza(a, b), che restituisce la distanza tra due punti:
 *      sqrt( (bx - ax)^2 + (by - ay)^2 )
 * Il main (gia' scritto) legge le coordinate di due punti e stampa la
 * distanza con 2 decimali.
 *
 * Input:  ax ay bx by          Esempio: 0 0 3 4
 * Output: P = (0.00, 0.00)
 *         Q = (3.00, 4.00)
 *         distanza: 5.00
 *
 * Come testarlo: make test T=10 E=es01
 */
#include <stdio.h>
#include <math.h>   /* sqrt */

typedef struct {
    double x;
    double y;
} Punto;

double distanza(Punto a, Punto b)
{
    /* TODO: calcola le differenze tra i campi (b.x - a.x, b.y - a.y)
       e restituisci la radice quadrata della somma dei loro quadrati. */
    (void)a; (void)b;   /* cancella questa riga */
    return 0.0;
}

int main(void)
{
    Punto p, q;

    if (scanf("%lf %lf %lf %lf", &p.x, &p.y, &q.x, &q.y) != 4)
        return 1;

    printf("P = (%.2f, %.2f)\n", p.x, p.y);
    printf("Q = (%.2f, %.2f)\n", q.x, q.y);
    printf("distanza: %.2f\n", distanza(p, q));
    return 0;
}
