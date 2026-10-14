/*
 * es07 — file 3 di 3: main.c
 * Per ogni parola letta, controlla se le parentesi ( ) [ ] { } sono bilanciate.
 * Gli altri caratteri si ignorano. Valori di ritorno di controlla():
 *   0 = bilanciata
 *   1 = chiusura sbagliata (o senza apertura): posizione (da 0) in *pos
 *   2 = aperture rimaste senza chiusura: quante, in *pos
 *   3 = troppo annidata (pila piena): posizione in *pos
 * Esempi:  ([]{}) -> bilanciata   (] -> errore in posizione 1   (( -> 2 parentesi non chiuse
 */
#include <stdio.h>
#include "pila.h"

static char apertura_di(char chiusa)
{
    if (chiusa == ')') return '(';
    if (chiusa == ']') return '[';
    return '{';
}

int controlla(const char s[], int *pos)
{
    /* TODO: svuota la pila; scorri s: le aperture vanno con pila_push (se fallisce -> 3),
       le chiusure con pila_pop e confronto con apertura_di (se fallisce -> 1);
       alla fine, se la pila non è vuota -> 2 */
    (void)s;
    (void)pos;
    (void)apertura_di;
    return 0;
}

int main(void)
{
    char s[201];
    int pos = 0;

    while (scanf("%200s", s) == 1) {
        switch (controlla(s, &pos)) {
        case 0: printf("%s -> bilanciata\n", s); break;
        case 1: printf("%s -> errore in posizione %d\n", s, pos); break;
        case 2: printf("%s -> %d parentesi non chiuse\n", s, pos); break;
        default: printf("%s -> troppo annidata (posizione %d)\n", s, pos); break;
        }
    }
    return 0;
}
