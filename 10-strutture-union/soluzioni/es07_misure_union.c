/*
 * es07 — Misure dei sensori con una union etichettata  (Tipo esame)  — SOLUZIONE
 *
 * Testo: ogni Misura ha il nome del sensore, un'ETICHETTA (enum) che dice
 * che tipo di dato contiene, e una union con il dato vero:
 *    I -> conteggio (int)    D -> valore (double)    S -> stato (stringa)
 * Implementa:
 *  - leggi_misura(m): legge "sensore lettera dato", imposta etichetta e campo
 *    giusto della union; restituisce 1 se ok, 0 se la lettera e' sconosciuta
 *    o l'input e' finito/sbagliato;
 *  - stampa_misura(m): stampa usando SOLO il campo indicato dall'etichetta;
 *  - somma_numeriche(v, n): somma conteggi e valori (ignora gli stati).
 *
 * Come testarlo: make sol T=10 E=es07
 */
#include <stdio.h>

#define MAX 20

typedef enum { INTERO, REALE, TESTO } TipoMisura;

typedef struct {
    char sensore[12];
    TipoMisura tipo;          /* l'etichetta: dice QUALE campo della union e' valido */
    union {                   /* union anonima dentro la struct: si usa m.dato.xxx */
        int conteggio;
        double valore;
        char stato[12];
    } dato;
} Misura;

int leggi_misura(Misura *m)
{
    char t;

    if (scanf("%11s %c", m->sensore, &t) != 2)
        return 0;
    switch (t) {
    case 'I':
        m->tipo = INTERO;     /* chi SCRIVE il dato aggiorna anche l'etichetta */
        return scanf("%d", &m->dato.conteggio) == 1;
    case 'D':
        m->tipo = REALE;
        return scanf("%lf", &m->dato.valore) == 1;
    case 'S':
        m->tipo = TESTO;
        return scanf("%11s", m->dato.stato) == 1;
    default:
        return 0;             /* lettera sconosciuta */
    }
}

void stampa_misura(const Misura *m)
{
    printf("%s: ", m->sensore);
    switch (m->tipo) {        /* chi LEGGE controlla prima l'etichetta */
    case INTERO: printf("%d (intero)\n", m->dato.conteggio); break;
    case REALE:  printf("%.2f (reale)\n", m->dato.valore);   break;
    case TESTO:  printf("%s (testo)\n", m->dato.stato);      break;
    }
}

double somma_numeriche(const Misura v[], int n)
{
    double s = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        if (v[i].tipo == INTERO)
            s += v[i].dato.conteggio;   /* int convertito automaticamente in double */
        else if (v[i].tipo == REALE)
            s += v[i].dato.valore;
        /* TESTO: non e' un numero, lo salto */
    }
    return s;
}

int main(void)
{
    Misura v[MAX];
    int n, i, letti = 0;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++) {
        if (!leggi_misura(&v[letti])) {
            printf("misura %d non valida: mi fermo\n", i + 1);
            break;
        }
        letti++;
    }

    for (i = 0; i < letti; i++)
        stampa_misura(&v[i]);
    printf("totale numerico: %.2f\n", somma_numeriche(v, letti));
    printf("byte di una Misura: %zu\n", sizeof(Misura));
    return 0;
}
