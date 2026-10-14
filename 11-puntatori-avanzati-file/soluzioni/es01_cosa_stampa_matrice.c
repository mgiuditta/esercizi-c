/*
 * Esercizio 01 — Cosa stampa? Matrici e puntatori (E-tivity MatriciePuntatori rifatta)
 *
 * Questo file e' GIA' completo. L'esercizio e' nel README:
 * leggi il codice, scrivi nel README (o su un foglio) cosa pensi che stampi
 * ogni riga, POI esegui il test e confronta.
 *
 * Nota: il prof nella E-tivity stampa gli indirizzi con %p. Qui stampiamo le
 * DIFFERENZE tra indirizzi in byte, cosi' l'output e' sempre uguale su ogni
 * computer. Assumiamo sizeof(int) = 4 (vero su macOS arm64 e Linux x86-64).
 *
 * Come testarlo: make test T=11 E=es01
 */
#include <stdio.h>

int main(void)
{
    int ar[2][3] = {{11, 22, 33}, {44, 55, 66}}; /* matrice 2 righe x 3 colonne */
    int (*p)[3];                                 /* puntatore a una riga di 3 int */
    int i = 1, j = 1;

    /* 1) di quanti byte si sposta ar + i rispetto ad ar? (salta i righe) */
    printf("A: %d\n", (int)((char *)(ar + i) - (char *)ar));

    /* 2) ar + i e *(ar + i): stesso indirizzo? */
    printf("B: %d\n", (int)((char *)*(ar + i) - (char *)(ar + i)));

    /* 3) *(ar + i) + 1 rispetto a *(ar + i): ora si salta un int */
    printf("C: %d\n", (int)((char *)(*(ar + i) + 1) - (char *)*(ar + i)));

    /* 4) quanto e' grande la cosa puntata? una riga oppure un int */
    printf("D: %d %d\n", (int)sizeof(*(ar + i)), (int)sizeof(*(*(ar + i))));

    /* 5) l'elemento (i, j) scritto con la sola aritmetica dei puntatori */
    printf("E: %d %d\n", *(*(ar + i) + j), ar[i][j]);

    /* 6) lo stesso con il puntatore a riga p, come nella E-tivity */
    p = ar;
    printf("F: %d\n", *(*(p + i) + j));

    /* 7) p++ salta un'intera riga */
    p++;
    printf("G: %d %d\n", (*p)[0], p[0][2]);

    /* 8) torno indietro di una riga e dereferenzio due volte */
    p--;
    printf("H: %d\n", **p);

    return 0;
}
