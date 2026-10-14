/*
 * 02 — es06: trova e correggi l'errore — media di tre voti  (Intermedio) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es06
 */
#include <stdio.h>

#define NUM_VOTI 3
#define SOGLIA 18
/* ERRORE 1: era  somma / n  (senza parentesi e tra interi).
   MEDIA(v1 + v2 + v3, NUM_VOTI) diventava  v1 + v2 + v3 / 3 :
   per la precedenza si divideva solo v3! E la divisione era intera.
   Ora: parentesi attorno a ogni parametro e a tutta la macro,
   piu' un cast a double per avere la divisione reale. */
#define MEDIA(somma, n) ((double)(somma) / (n))

int voto_valido(int v)
{
    /* ERRORE 2: era  v >= 0 || v <= 30 , vero per QUALSIASI numero
       (ogni numero e' >= 0 oppure <= 30). Servono entrambe: && */
    return v >= 0 && v <= 30;
}

int main(void)
{
    int v1 = 0, v2 = 0, v3 = 0;
    int sufficienti = 0;
    double media = 0.0;

    if (scanf("%d %d %d", &v1, &v2, &v3) != 3) {
        printf("Input non valido\n");
        return 1;
    }
    if (!voto_valido(v1) || !voto_valido(v2) || !voto_valido(v3)) {
        printf("Voto non valido\n");
        return 0;
    }

    media = MEDIA(v1 + v2 + v3, NUM_VOTI);
    /* Un confronto in C vale 1 (vero) o 0 (falso): sommandoli conto i veri.
       ERRORE 3: per v3 c'era > invece di >= : un 18 non veniva contato. */
    sufficienti = (v1 >= SOGLIA) + (v2 >= SOGLIA) + (v3 >= SOGLIA);

    printf("Media = %.2f\n", media);
    printf("Sufficienti: %d su %d\n", sufficienti, NUM_VOTI);
    return 0;
}
