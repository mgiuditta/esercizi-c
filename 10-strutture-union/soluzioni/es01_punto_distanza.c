/*
 * es01 — Punto 2D e distanza  (Base)  — SOLUZIONE
 *
 * Testo: con il tipo Punto (typedef struct con campi x e y) implementa
 * distanza(a, b), che restituisce la distanza tra due punti:
 *      sqrt( (bx - ax)^2 + (by - ay)^2 )
 * Il main legge le coordinate di due punti e stampa la distanza con 2 decimali.
 *
 * Come testarlo: make sol T=10 E=es01
 */
#include <stdio.h>
#include <math.h>   /* sqrt: radice quadrata (serve -lm, che il runner aggiunge) */

/* typedef struct {...} Punto; crea un NUOVO NOME DI TIPO: da qui in poi
 * scrivo "Punto p;" invece di "struct {...} p;". */
typedef struct {
    double x;   /* ascissa  */
    double y;   /* ordinata */
} Punto;

/* a e b arrivano PER VALORE: la funzione riceve una copia di ciascun punto.
 * Va benissimo: deve solo leggere i campi, non modificarli. */
double distanza(Punto a, Punto b)
{
    double dx = b.x - a.x;   /* operatore punto: "il campo x della struct b" */
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);   /* teorema di Pitagora */
}

int main(void)
{
    Punto p, q;

    /* &p.x: il punto lega piu' forte di &, quindi e' &(p.x), l'indirizzo del campo x */
    if (scanf("%lf %lf %lf %lf", &p.x, &p.y, &q.x, &q.y) != 4)
        return 1;

    printf("P = (%.2f, %.2f)\n", p.x, p.y);
    printf("Q = (%.2f, %.2f)\n", q.x, q.y);
    printf("distanza: %.2f\n", distanza(p, q));
    return 0;
}
