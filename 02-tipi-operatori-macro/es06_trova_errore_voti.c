/*
 * 02 — es06: trova e correggi l'errore — media di tre voti  (Intermedio)
 *
 * Testo: il programma legge tre voti (interi da 0 a 30) e dovrebbe stampare:
 *   - "Voto non valido" se almeno un voto e' fuori da 0..30;
 *   - altrimenti la media con 2 decimali e quanti voti sono sufficienti
 *     (sufficiente = almeno 18).
 * Esempio:  30 25 18  ->  Media = 24.33
 *                         Sufficienti: 3 su 3
 *
 * Il programma compila ma contiene 3 errori (uno nella macro, uno nella
 * funzione, uno nel conteggio). Con gcc non ci sono avvisi; clang (il cc di
 * macOS) ne da' uno su un errore: leggilo! Correggili senza riscriverlo.
 *
 * Come testarlo: make test T=02 E=es06
 */
#include <stdio.h>

#define NUM_VOTI 3
#define SOGLIA 18
#define MEDIA(somma, n) somma / n

int voto_valido(int v)
{
    return v >= 0 || v <= 30;
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
    sufficienti = (v1 >= SOGLIA) + (v2 >= SOGLIA) + (v3 > SOGLIA);

    printf("Media = %.2f\n", media);
    printf("Sufficienti: %d su %d\n", sufficienti, NUM_VOTI);
    return 0;
}
