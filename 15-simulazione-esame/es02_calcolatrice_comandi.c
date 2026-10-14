/*
 * es02 — Calcolatrice a comandi: tabella di puntatori a funzione  (Tipo esame)
 *
 * Ogni riga di input e' un comando:
 *   <operazione> a b     operazioni: somma diff prod div mod pot mcd
 *   stat                 stampa quante operazioni sono riuscite e quante fallite
 *   fine                 termina (anche la fine dell'input termina)
 * Le operazioni stanno in una TABELLA (vettore di struct Comando): nome,
 * puntatore alla funzione che calcola, vincolo sul secondo operando (enum).
 *
 * Completa:
 *   - pot(a, b): potenza RICORSIVA con b >= 0 (caso base b == 0).
 *     Bonus: versione "veloce" che usa pot(a, b/2).
 *   - mcd(a, b): MCD di Euclide RICORSIVO, risultato sempre >= 0.
 *   - cerca(nome): indirizzo della riga della tabella con quel nome, o NULL.
 *   - esegui(c, a, b, &ris): con uno switch sul vincolo controlla b
 *     (B_NON_ZERO -> se b == 0 ritorna 1; B_NON_NEGATIVO -> se b < 0
 *     ritorna 2); se va bene calcola con c->calcola e ritorna 0.
 *   - statistiche(ev): conta riuscite e fallite con due variabili
 *     static LOCALI; con ev == STAMPA stampa
 *     "stat: X riuscite, Y fallite".
 *
 * Come testarlo: make test T=15 E=es02
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

int pot(int a, int b)
{
    /* TODO: ricorsiva. Caso base: b == 0 */
    (void)a; (void)b;
    return 0;
}

int mcd(int a, int b)
{
    /* TODO: ricorsiva. Caso base: b == 0 -> valore assoluto di a */
    (void)a; (void)b;
    return 0;
}

static const Comando tabella[] = {
    { "somma", somma, NESSUNO },
    { "diff",  diff,  NESSUNO },
    { "prod",  prod,  NESSUNO },
    { "div",   divi,  B_NON_ZERO },
    { "mod",   modu,  B_NON_ZERO },
    { "pot",   pot,   B_NON_NEGATIVO },
    { "mcd",   mcd,   NESSUNO }
};
#define N_COMANDI ((int)(sizeof tabella / sizeof tabella[0]))

const Comando *cerca(const char *nome)
{
    /* TODO: ricerca lineare con strcmp su tabella[i].nome (i < N_COMANDI);
       ritorna &tabella[i] oppure NULL */
    (void)nome; (void)tabella;
    return NULL;
}

int esegui(const Comando *c, int a, int b, int *ris)
{
    /* TODO: switch (c->vincolo) { ... }, poi *ris = c->calcola(a, b) */
    (void)c; (void)a; (void)b;
    *ris = 0;
    return 0;
}

void statistiche(Evento ev)
{
    /* TODO: due static int locali e uno switch su ev */
    (void)ev;
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
