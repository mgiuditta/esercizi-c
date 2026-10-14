/*
 * es02 — typedef anno e boolean: anni bisestili  (Base)
 * Legge anni fino a fine input e per ognuno stampa "A: bisestile" o "A: non bisestile".
 * Come testarlo: make test T=04 E=es02
 */
#include <stdio.h>

/* typedef tipo_esistente nuovo_nome;  ->  "anno" e' un altro nome per int.
   Il compilatore lo tratta esattamente come int: serve a chi LEGGE il codice. */
typedef int anno;

/* Il booleano simulato del prof (Appunti 2.18.3): un enum con FALSE=0, TRUE=1,
   a cui typedef da' un nome di tipo, cosi' non serve scrivere "enum" ogni volta. */
typedef enum {FALSE, TRUE} boolean;

/* Regola del calendario gregoriano: bisestile se divisibile per 4,
   tranne i secoli (divisibili per 100), che lo sono solo se divisibili per 400. */
boolean e_bisestile(anno a) {
    if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)
        return TRUE;
    return FALSE;
}

int main(void) {
    anno a;   /* si legge e si stampa con %d: sotto sotto e' un int */
    while (scanf("%d", &a) == 1) {
        boolean b = e_bisestile(a);
        /* b vale 0 o 1, quindi si puo' usare direttamente come condizione. */
        if (b)
            printf("%d: bisestile\n", a);
        else
            printf("%d: non bisestile\n", a);
    }
    return 0;
}
