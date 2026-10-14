/*
 * es05 — COSA STAMPA?  Valori degli enum, interi con e senza segno, typedef  (Intermedio)
 * NON modificare questo file. Scrivi la tua previsione nel README, riga per riga,
 * poi esegui il test e confronta con tests/es05_cosa_stampa.out.
 * Ipotesi: gcc o clang su Linux x86-64 / macOS arm64 (int di 4 byte).
 * Come testarlo: make test T=04 E=es05
 */
#include <stdio.h>

enum colore {ROSSO, VERDE = 5, BLU, GIALLO = 2, NERO};

/* L'esempio del prof (trascrizione 2.4 e Appunti 2.18.4) */
typedef enum {MENOUNO = -1, ZERO, UNO, DUE} intero;
typedef enum {ZERO_N, UNO_N, DUE_N} naturale;

enum year {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

typedef int anno;
typedef anno anno_bisestile;      /* typedef "in catena", come nella lezione */

int main(void) {
    /* Riga A: valori impliciti ed espliciti */
    printf("A: %d %d %d %d %d\n", ROSSO, VERDE, BLU, GIALLO, NERO);

    /* Riga B: aritmetica con le costanti enum */
    printf("B: %d\n", BLU - VERDE + NERO * 2);

    /* Riga C: la stessa sottrazione su un enum con e senza valori negativi */
    intero a = MENOUNO;
    naturale b = ZERO_N;
    printf("C: %d %d\n", a - 1 > 1000, b - 1 > 1000);

    /* Riga D: la stessa sottrazione, ma sulla COSTANTE invece che sulla variabile */
    printf("D: %d\n", ZERO_N - 1 > 1000);

    /* Riga E: un enum puo' uscire dall'elenco? */
    enum colore c = NERO;
    c = c + 10;
    printf("E: %d\n", (int)c);

    /* Riga F: ciclo sui mesi */
    printf("F:");
    for (int i = Jan; i <= Dec; i += 3)
        printf(" %d", i);
    printf("\n");

    /* Riga G: typedef in catena e sizeof */
    anno_bisestile x = 2024;
    printf("G: %d %zu %zu\n", x + 4, sizeof(anno_bisestile), sizeof(enum colore));

    return 0;
}
