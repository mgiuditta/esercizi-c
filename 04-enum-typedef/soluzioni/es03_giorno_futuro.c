/*
 * es03 — Che giorno sara' tra n giorni? Aritmetica sugli enum  (Base)
 * Legge il giorno di partenza (0=lunedi' ... 6=domenica) e un numero n di giorni
 * (anche negativo: n giorni fa). Stampa il giorno di arrivo.
 * Come testarlo: make test T=04 E=es03
 */
#include <stdio.h>

/* L'esempio del prof (Appunti 2.18.6): enum week {Mon, Tue, ..., Sun}.
   Qui con nomi italiani e typedef. Valori: LUN=0 ... DOM=6. */
typedef enum {LUN, MAR, MER, GIO, VEN, SAB, DOM} giorno;

void stampa_giorno(giorno g) {
    switch (g) {
    case LUN: printf("lunedi'");   break;
    case MAR: printf("martedi'");  break;
    case MER: printf("mercoledi'"); break;
    case GIO: printf("giovedi'");  break;
    case VEN: printf("venerdi'");  break;
    case SAB: printf("sabato");    break;
    case DOM: printf("domenica");  break;
    default:  printf("?");          /* un enum puo' contenere valori fuori elenco */
    }
}

giorno avanza(giorno g, int n) {
    /* Gli enum sono interi: posso sommarli. Il % 7 "riavvolge" la settimana
       come le lancette di un orologio.
       TRAPPOLA (la stessa del prof con il tipo "naturale"): un enum senza valori
       negativi, con gcc e clang, e' un unsigned int. Allora g + n con n negativo
       viene calcolato SENZA SEGNO: 1 + (-10) diventa 4294967287, non -9!
       Per questo converto prima g in int con un cast. */
    int r = ((int)g + n) % 7;
    /* In C il resto di un numero negativo e' negativo (-9 % 7 == -2):
       aggiungo 7 per riportarlo fra 0 e 6. */
    if (r < 0)
        r += 7;
    return (giorno)r;
}

int main(void) {
    int partenza, n;
    if (scanf("%d %d", &partenza, &n) != 2 || partenza < LUN || partenza > DOM) {
        printf("Input non valido\n");
        return 1;
    }
    giorno g = (giorno)partenza;
    stampa_giorno(g);
    printf(" + %d giorni = ", n);
    stampa_giorno(avanza(g, n));
    printf("\n");
    return 0;
}
