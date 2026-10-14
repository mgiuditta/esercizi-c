/* =====================================================================
 * es01 — Massimo di due e di tre numeri  ·  Base  ·  SOLUZIONE
 * Scrivi max2(a, b) e max3(a, b, c). max3 deve USARE max2
 * (una funzione che ne chiama un'altra, come cubo che usa quadrato).
 * Come testarlo: make sol T=07 E=es01
 * ===================================================================== */
#include <stdio.h>

/* PROTOTIPI (dichiarazioni): dicono al compilatore "esistono queste
 * funzioni, ricevono questi tipi, restituiscono un int".
 * Servono perché main le usa PRIMA che il compilatore ne veda la
 * definizione, che sta più in basso nel file. */
int max2(int a, int b);
int max3(int a, int b, int c);

int main(void) {
    int a, b, c;
    /* scanf restituisce quanti valori ha letto: se non sono 3 l'input
     * è sbagliato e non ha senso continuare. */
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("input non valido\n");
        return 1;
    }
    /* a, b, c qui sono i PARAMETRI ATTUALI: i valori che passo. */
    printf("max2(%d, %d) = %d\n", a, b, max2(a, b));
    printf("max3(%d, %d, %d) = %d\n", a, b, c, max3(a, b, c));
    return 0;
}

/* DEFINIZIONE = intestazione (uguale al prototipo ma senza ';') + corpo.
 * a e b sono i PARAMETRI FORMALI: variabili locali di max2 che
 * ricevono una COPIA dei valori passati. */
int max2(int a, int b) {
    if (a > b)
        return a;   /* return: restituisce il valore E torna al chiamante */
    return b;       /* qui arrivo solo se a > b era falso */
}

/* max3 non ripete il confronto: riusa max2 due volte.
 * Il massimo di tre = il massimo tra (il massimo dei primi due) e il terzo. */
int max3(int a, int b, int c) {
    return max2(max2(a, b), c);
}
