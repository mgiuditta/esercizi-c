/*
 * 02 — es02: cambio in monete con / e %  (Base)
 *
 * Testo: dato un importo in centesimi (intero), stampa il valore in euro
 * con due decimali e quante monete servono di ogni taglio, usando sempre
 * la moneta piu' grande possibile (2 euro, 1 euro, 50, 20, 10, 5, 2, 1 cent).
 * Completa:
 *   - in_euro(centesimi): l'importo in euro come double (1234 -> 12.34);
 *   - quante(importo, taglio): quante monete di quel taglio ci stanno;
 *   - avanzo(importo, taglio): quanti centesimi restano dopo averle date.
 * Con un importo negativo stampa "Importo non valido".
 *
 * Esempio: 388 -> 3.88 euro, una moneta per ogni taglio.
 *
 * Come testarlo: make test T=02 E=es02
 */
#include <stdio.h>

double in_euro(int centesimi)
{
    /* TODO: attenzione al tipo della divisione! */
    (void)centesimi;
    return 0.0;
}

int quante(int importo, int taglio)
{
    /* TODO */
    (void)importo;
    (void)taglio;
    return 0;
}

int avanzo(int importo, int taglio)
{
    /* TODO */
    (void)taglio;
    return importo;
}

/* Stampa una riga e restituisce i centesimi che restano da cambiare.
   "nome" e' il testo da stampare (es. "2 euro"). Gia' completa. */
int passo(int resto, int taglio, const char *nome)
{
    printf("%s: %d\n", nome, quante(resto, taglio));
    return avanzo(resto, taglio);
}

int main(void)
{
    int c = 0;
    int resto = 0;

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
    printf("Resto non cambiato: %d\n", resto);
    return 0;
}
