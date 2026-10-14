/*
 * 01 — es05: trova e correggi l'errore  (Intermedio)
 *
 * Testo: questo programma legge due interi a e b e dovrebbe stampare
 *   - la media (con due cifre dopo la virgola)
 *   - la distanza tra i due numeri, cioe' |a - b| (sempre >= 0).
 * Esempio:  7 2   ->   Media = 4.50   Distanza = 5
 *
 * Il programma COMPILA (con qualche avviso del compilatore: leggili!)
 * ma contiene 3 errori. Trovali e correggili SENZA riscriverlo da zero.
 *
 * Come testarlo: make test T=01 E=es05
 */
#include <stdio.h>

int main(void)
{
    int a = 0;
    int b = 0;
    int distanza = 0;
    double media = 0.0;

    if (scanf("%d", &a) != 1)
        return 1;
    if (scanf("%d", b) != 1)
        return 1;

    media = (a + b) / 2;

    distanza = a - b;
    if (distanza < 0);
        distanza = -distanza;

    printf("Media = %.2f\n", media);
    printf("Distanza = %d\n", distanza);
    return 0;
}
