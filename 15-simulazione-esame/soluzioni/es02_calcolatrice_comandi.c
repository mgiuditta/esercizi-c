/*
 * es02 — Calcolatrice a comandi: tabella di puntatori a funzione  (Tipo esame) — SOLUZIONE
 *
 * Ogni riga di input e' un comando:
 *   <operazione> a b     operazioni: somma diff prod div mod pot mcd
 *   stat                 stampa quante operazioni sono riuscite e quante fallite
 *   fine                 termina (anche la fine dell'input termina)
 * Le operazioni stanno in una TABELLA: un vettore di struct, ognuna con il
 * nome, il puntatore alla funzione che calcola e il vincolo sul secondo
 * operando (un enum). pot e mcd sono ricorsive. I conteggi stanno in
 * variabili static locali di statistiche().
 *
 * Come testarlo: make sol T=15 E=es02
 */
#include <stdio.h>
#include <string.h>

typedef enum { NESSUNO, B_NON_ZERO, B_NON_NEGATIVO } Vincolo;

typedef struct {
    const char *nome;
    int (*calcola)(int, int);     /* puntatore a funzione: (int, int) -> int */
    Vincolo vincolo;
} Comando;

typedef enum { REGISTRA_OK, REGISTRA_ERRORE, STAMPA } Evento;

int somma(int a, int b) { return a + b; }
int diff(int a, int b)  { return a - b; }
int prod(int a, int b)  { return a * b; }
int divi(int a, int b)  { return a / b; }   /* "div" e' gia' il nome di una funzione di stdlib.h */
int modu(int a, int b)  { return a % b; }

/* Potenza ricorsiva "veloce" (cartella 13): a^b = (a^(b/2))^2, con un fattore a in piu' se b e' dispari.
 * Caso base: b == 0. Ogni chiamata dimezza b, quindi le chiamate sono poche (circa log2 b). */
int pot(int a, int b)
{
    int meta;
    if (b == 0)
        return 1;
    meta = pot(a, b / 2);
    if (b % 2 == 0)
        return meta * meta;
    return a * meta * meta;
}

/* MCD di Euclide ricorsivo (come il primo esempio del corso, ma senza goto).
 * Caso base: b == 0, l'MCD e' |a|. Caso ricorsivo: mcd(a, b) = mcd(b, a % b). */
int mcd(int a, int b)
{
    if (b == 0)
        return a < 0 ? -a : a;
    return mcd(b, a % b);
}

/* La tabella: aggiungere un'operazione = aggiungere una riga, senza toccare la logica. */
static const Comando tabella[] = {
    { "somma", somma, NESSUNO },
    { "diff",  diff,  NESSUNO },
    { "prod",  prod,  NESSUNO },
    { "div",   divi,  B_NON_ZERO },
    { "mod",   modu,  B_NON_ZERO },
    { "pot",   pot,   B_NON_NEGATIVO },
    { "mcd",   mcd,   NESSUNO }
};
#define N_COMANDI ((int)(sizeof tabella / sizeof tabella[0]))   /* 7, calcolato dal compilatore */

/* Ricerca lineare nella tabella: restituisce l'INDIRIZZO della riga trovata, NULL se non c'e'. */
const Comando *cerca(const char *nome)
{
    int i;
    for (i = 0; i < N_COMANDI; i++)
        if (strcmp(tabella[i].nome, nome) == 0)
            return &tabella[i];
    return NULL;
}

/* Controlla il vincolo e, se e' rispettato, calcola e mette il risultato in *ris.
 * Ritorna 0 se tutto bene, 1 = divisione per zero, 2 = esponente negativo. */
int esegui(const Comando *c, int a, int b, int *ris)
{
    switch (c->vincolo) {
    case B_NON_ZERO:
        if (b == 0)
            return 1;
        break;
    case B_NON_NEGATIVO:
        if (b < 0)
            return 2;
        break;
    case NESSUNO:
        break;
    }
    *ris = c->calcola(a, b);      /* chiamata tramite puntatore: non so QUALE funzione sia */
    return 0;
}

/* Due contatori che devono sopravvivere tra una chiamata e l'altra, ma che nessun
 * altro deve poter toccare: static LOCALI (cartella 14). */
void statistiche(Evento ev)
{
    static int riuscite = 0;      /* inizializzate una volta sola */
    static int fallite = 0;

    switch (ev) {
    case REGISTRA_OK:
        riuscite++;
        break;
    case REGISTRA_ERRORE:
        fallite++;
        break;
    case STAMPA:
        printf("stat: %d riuscite, %d fallite\n", riuscite, fallite);
        break;
    }
}

int main(void)
{
    char nome[16];
    const Comando *c;
    int a, b, ris, esito;

    while (scanf("%15s", nome) == 1) {
        if (strcmp(nome, "fine") == 0)
            break;
        if (strcmp(nome, "stat") == 0) {
            statistiche(STAMPA);
            continue;
        }
        if (scanf("%d %d", &a, &b) != 2) {
            printf("%s: mancano gli operandi\n", nome);
            break;
        }
        c = cerca(nome);
        if (c == NULL) {
            printf("%s: comando sconosciuto\n", nome);
            statistiche(REGISTRA_ERRORE);
            continue;
        }
        esito = esegui(c, a, b, &ris);
        if (esito == 0) {
            printf("%s %d %d = %d\n", nome, a, b, ris);
            statistiche(REGISTRA_OK);
        } else {
            printf("%s %d %d -> errore: %s\n", nome, a, b,
                   esito == 1 ? "divisione per zero" : "esponente negativo");
            statistiche(REGISTRA_ERRORE);
        }
    }
    printf("finale ");
    statistiche(STAMPA);
    return 0;
}
