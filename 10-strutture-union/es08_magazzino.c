/*
 * es08 — Gestione magazzino con vettore di struct e menu'  (Tipo esame)
 *
 * Testo: un Magazzino contiene fino a MAX_ART articoli (codice, nome,
 * quantita, prezzo unitario) e il numero n di articoli presenti.
 * Implementa:
 *  - cerca(m, codice): indice dell'articolo con quel codice, -1 se non c'e';
 *  - aggiungi(m, codice, nome, q, prezzo): se il codice esiste somma q alla
 *    quantita' e restituisce 1; se e' nuovo e c'e' posto lo aggiunge in fondo
 *    e restituisce 2; se il magazzino e' pieno restituisce 0;
 *  - preleva(m, codice, q): toglie q pezzi; restituisce 0 se ok, -1 se il
 *    codice non esiste, -2 se la quantita' disponibile non basta;
 *  - valore_totale(m): somma di quantita * prezzo su tutti gli articoli.
 * Il main (gia' scritto) gestisce il menu':
 *   1 codice nome q prezzo | 2 codice q | 3 (stampa) | 4 (valore) | 0 (esci)
 *
 * Come testarlo: make test T=10 E=es08
 */
#include <stdio.h>
#include <string.h>

#define MAX_ART 4    /* piccolo apposta: cosi' il test puo' riempire il magazzino */

typedef struct {
    int codice;
    char nome[20];
    int quantita;
    double prezzo;
} Articolo;

typedef struct {
    Articolo art[MAX_ART];
    int n;               /* quanti elementi di art[] sono usati: art[0..n-1] */
} Magazzino;

/* const Magazzino *: passo l'indirizzo (niente copia di tutto il vettore)
 * e prometto di non modificarlo. */
int cerca(const Magazzino *m, int codice)
{
    /* TODO: scorri m->art[0..m->n-1] e restituisci l'indice i se
       m->art[i].codice == codice; se non lo trovi, -1. */
    (void)m; (void)codice;   /* cancella questa riga */
    return -1;
}

int aggiungi(Magazzino *m, int codice, const char *nome, int q, double prezzo)
{
    /* TODO:
       - i = cerca(m, codice); se i >= 0 somma q a m->art[i].quantita e restituisci 1
       - se m->n == MAX_ART restituisci 0
       - altrimenti riempi m->art[m->n] (nome con strcpy!), incrementa m->n,
         restituisci 2 */
    (void)m; (void)codice; (void)nome; (void)q; (void)prezzo;   /* cancella */
    return 0;
}

int preleva(Magazzino *m, int codice, int q)
{
    /* TODO: -1 se il codice non esiste, -2 se la quantita' non basta
       (in quel caso NON modificare nulla), altrimenti togli q e restituisci 0 */
    (void)m; (void)codice; (void)q;   /* cancella questa riga */
    return -1;
}

double valore_totale(const Magazzino *m)
{
    /* TODO: somma quantita * prezzo di tutti gli articoli */
    (void)m;   /* cancella questa riga */
    return 0.0;
}

static void stampa(const Magazzino *m)
{
    int i;
    if (m->n == 0) {
        printf("magazzino vuoto\n");
        return;
    }
    for (i = 0; i < m->n; i++)
        printf("  %d %-10s q=%d prezzo=%.2f\n", m->art[i].codice,
               m->art[i].nome, m->art[i].quantita, m->art[i].prezzo);
}

int main(void)
{
    Magazzino mag = { .n = 0 };   /* inizializzatore "designato": n = 0, il resto a zero */
    int scelta, codice, q, r, i;
    char nome[20];
    double prezzo;

    printf("Comandi: 1=aggiungi 2=preleva 3=stampa 4=valore 0=esci\n");
    while (scanf("%d", &scelta) == 1 && scelta != 0) {
        switch (scelta) {
        case 1:
            if (scanf("%d %19s %d %lf", &codice, nome, &q, &prezzo) != 4)
                return 1;
            if (q <= 0 || prezzo < 0) {
                printf("dati non validi\n");
                break;
            }
            r = aggiungi(&mag, codice, nome, q, prezzo);
            if (r == 0)
                printf("magazzino pieno: %d non aggiunto\n", codice);
            else if (r == 1)
                printf("aggiornato %d: quantita %d\n", codice,
                       mag.art[cerca(&mag, codice)].quantita);
            else
                printf("aggiunto %d %s\n", codice, nome);
            break;
        case 2:
            if (scanf("%d %d", &codice, &q) != 2)
                return 1;
            if (q <= 0) {
                printf("dati non validi\n");
                break;
            }
            r = preleva(&mag, codice, q);
            if (r == -1) {
                printf("articolo %d inesistente\n", codice);
            } else if (r == -2) {
                i = cerca(&mag, codice);
                printf("quantita insufficiente per %d (disponibili %d)\n",
                       codice, mag.art[i].quantita);
            } else {
                i = cerca(&mag, codice);
                printf("prelevati %d di %d: restano %d\n", q, codice, mag.art[i].quantita);
            }
            break;
        case 3:
            stampa(&mag);
            break;
        case 4:
            printf("valore totale: %.2f\n", valore_totale(&mag));
            break;
        default:
            printf("scelta non valida\n");
        }
    }
    printf("ciao!\n");
    return 0;
}
