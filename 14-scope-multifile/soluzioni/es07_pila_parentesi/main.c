/*
 * main.c — controllo delle parentesi bilanciate usando il modulo pila  (SOLUZIONE di es07)
 */
#include <stdio.h>
#include "pila.h"

/* Restituisce la parentesi aperta che corrisponde a una chiusa (')' -> '('). */
static char apertura_di(char chiusa)
{
    if (chiusa == ')') return '(';
    if (chiusa == ']') return '[';
    return '{';
}

/* Esito: 0 = bilanciata, 1 = chiusura sbagliata in *pos, 2 = aperture non chiuse
 * (quante in *pos), 3 = troppo annidata (pila piena, posizione in *pos). */
int controlla(const char s[], int *pos)
{
    int i;
    char c, top;

    pila_svuota();                            /* la pila è condivisa: la azzero a ogni riga */
    for (i = 0; s[i] != '\0'; i++) {
        c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            if (!pila_push(c)) {              /* apertura: la "ricordo" in cima alla pila */
                *pos = i;
                return 3;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            /* chiusura: deve corrispondere all'ULTIMA apertura non ancora chiusa */
            if (!pila_pop(&top) || top != apertura_di(c)) {
                *pos = i;
                return 1;
            }
        }                                     /* gli altri caratteri si ignorano */
    }
    if (!pila_vuota()) {                      /* sono rimaste aperture senza chiusura */
        *pos = pila_dimensione();
        return 2;
    }
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
