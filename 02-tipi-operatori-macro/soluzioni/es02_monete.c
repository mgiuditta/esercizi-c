/*
 * 02 — es02: cambio in monete con / e %  (Base) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es02
 */
#include <stdio.h>

double in_euro(int centesimi)
{
    /* centesimi / 100 sarebbe una divisione INTERA: 1234 / 100 = 12.
       100.0 e' una costante double: centesimi viene promosso a double
       e la divisione diventa reale: 12.34. */
    return centesimi / 100.0;
}

int quante(int importo, int taglio)
{
    return importo / taglio;   /* divisione intera: tronca, ed e' quello che voglio */
}

int avanzo(int importo, int taglio)
{
    return importo % taglio;   /* resto: i centesimi che non bastano per un'altra moneta */
}

int passo(int resto, int taglio, const char *nome)
{
    printf("%s: %d\n", nome, quante(resto, taglio));
    return avanzo(resto, taglio);
}

int main(void)
{
    int c = 0;
    int resto = 0;

    /* || in cortocircuito: se scanf fallisce, c < 0 non viene nemmeno valutato */
    if (scanf("%d", &c) != 1 || c < 0) {
        printf("Importo non valido\n");
        return 0;
    }
    printf("%d centesimi = %.2f euro\n", c, in_euro(c));

    resto = c;
    resto = passo(resto, 200, "2 euro");
    resto = passo(resto, 100, "1 euro");
    resto = passo(resto, 50, "50 cent");
    resto = passo(resto, 20, "20 cent");
    resto = passo(resto, 10, "10 cent");
    resto = passo(resto, 5, "5 cent");
    resto = passo(resto, 2, "2 cent");
    resto = passo(resto, 1, "1 cent");
    printf("Resto non cambiato: %d\n", resto);   /* deve essere sempre 0 */
    return 0;
}
