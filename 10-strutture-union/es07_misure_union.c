/*
 * es07 — Misure dei sensori con una union etichettata  (Tipo esame)
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
 * Input:  n, poi n righe.   Esempio: 2  porta I 42  luce S acceso
 * Output: porta: 42 (intero)
 *         luce: acceso (testo)
 *         totale numerico: 42.00
 *         byte di una Misura: 32
 *
 * Come testarlo: make test T=10 E=es07
 */
#include <stdio.h>

#define MAX 20

typedef enum { INTERO, REALE, TESTO } TipoMisura;

typedef struct {
    char sensore[12];
    TipoMisura tipo;
    union {
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
    /* TODO: switch sulla lettera t.
       'I': imposta m->tipo = INTERO e leggi un int in m->dato.conteggio
       'D': REALE, leggi un double (%lf) in m->dato.valore
       'S': TESTO, leggi una parola (%11s) in m->dato.stato
       altrimenti: restituisci 0.
       Restituisci 1 solo se anche la lettura del dato e' riuscita. */
    return 0;
}

void stampa_misura(const Misura *m)
{
    printf("%s: ", m->sensore);
    /* TODO: switch su m->tipo, stampa nei formati
       "%d (intero)\n"   "%.2f (reale)\n"   "%s (testo)\n" */
    printf("?\n");   /* provvisorio */
}

double somma_numeriche(const Misura v[], int n)
{
    /* TODO: somma v[i].dato.conteggio se INTERO, v[i].dato.valore se REALE */
    (void)v; (void)n;   /* cancella questa riga */
    return 0.0;
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
