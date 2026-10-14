/*
 * es01 — I semi delle carte con enum e switch  (Base)
 * Legge numeri interi (fino a fine input). Per ognuno, se e' un seme valido
 * (0..3) stampa nome e colore, altrimenti "Seme non valido: N".
 * Come testarlo: make test T=04 E=es01
 */
#include <stdio.h>

/* L'esempio del prof: senza valori espliciti PICCHE=0, CUORI=1, QUADRI=2, FIORI=3.
   "seme" e' il TAG: il nome dell'enum. Per usarlo serve sempre la parola enum. */
enum seme {PICCHE, CUORI, QUADRI, FIORI};

void stampa_seme(enum seme s) {
    /* switch funziona sugli enum perche' i loro valori sono interi. */
    switch (s) {
    case PICCHE:
        printf("PICCHE (nero)\n");
        break;
    case CUORI:
        printf("CUORI (rosso)\n");
        break;
    case QUADRI:
        printf("QUADRI (rosso)\n");
        break;
    case FIORI:
        printf("FIORI (nero)\n");
        break;
    default:
        /* Un enum e' un intero: puo' contenere QUALSIASI valore, non solo quelli
           elencati. Il C non controlla: il default e' la nostra difesa. */
        printf("Seme non valido: %d\n", (int)s);
    }
}

int main(void) {
    int n;
    /* scanf non sa leggere "un enum": leggo un int e poi lo converto. */
    while (scanf("%d", &n) == 1) {
        stampa_seme((enum seme)n);   /* cast esplicito: dichiaro che so cosa faccio */
    }
    return 0;
}
