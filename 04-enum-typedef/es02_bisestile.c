/*
 * es02 — typedef anno e boolean: anni bisestili  (Base)
 * Legge anni fino a fine input e per ognuno stampa "A: bisestile" o "A: non bisestile".
 * Bisestile = divisibile per 4 ma non per 100, oppure divisibile per 400.
 * Come testarlo: make test T=04 E=es02
 */
#include <stdio.h>

/* TODO: con typedef crea il tipo "anno" (basato su int)
         e il tipo "boolean" (un enum con FALSE e TRUE).
         Poi sostituisci int con i nuovi tipi qui sotto, dove ha senso. */

int e_bisestile(int a) {
    /* TODO: restituisci TRUE o FALSE secondo la regola. */
    (void)a;
    return 0;
}

int main(void) {
    int a;
    while (scanf("%d", &a) == 1) {
        if (e_bisestile(a))
            printf("%d: bisestile\n", a);
        else
            printf("%d: non bisestile\n", a);
    }
    return 0;
}
