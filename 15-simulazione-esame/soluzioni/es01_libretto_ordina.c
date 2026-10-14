/*
 * es01 — Libretto universitario: record da stdin, realloc e ordinamento  (Tipo esame) — SOLUZIONE
 *
 * Prima riga: il criterio di ordinamento ("voto", "nome" oppure "crediti").
 * Poi, fino alla fine dell'input, un esame per riga:  nome voto crediti
 * (esempio: "Analisi 28 9"). Un esame con voto fuori da 18..30 oppure con
 * crediti <= 0 viene scartato con un messaggio.
 *
 * Il vettore degli esami e' DINAMICO: parte con capacita' 1 e raddoppia con
 * realloc quando e' pieno. Poi il vettore viene ordinato con una funzione di
 * ordinamento che riceve il CRITERIO come puntatore a funzione.
 *
 * Come testarlo: make sol T=15 E=es01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 32

typedef struct {
    char nome[MAXNOME];
    int voto;
    int crediti;
} Esame;

/* Aggiunge e in fondo al vettore *pv (che contiene *n esami su *cap posti).
 * Ritorna 1 se ha dovuto fare una realloc, 0 se c'era gia' posto, -1 se la
 * realloc fallisce (il vecchio vettore resta valido). */
int aggiungi_esame(Esame **pv, int *n, int *cap, Esame e)
{
    int rialloc = 0;

    if (*n == *cap) {
        /* Puntatore TEMPORANEO: se realloc fallisce restituisce NULL ma il
         * vecchio blocco resta allocato. Scrivendo subito *pv = realloc(...)
         * perderemmo l'unico indirizzo del vecchio blocco (memory leak). */
        Esame *tmp = (Esame *) realloc(*pv, (size_t)(*cap * 2) * sizeof(Esame));
        if (tmp == NULL)
            return -1;
        *pv = tmp;          /* il blocco puo' essersi SPOSTATO: aggiorno il puntatore del main */
        *cap = *cap * 2;
        rialloc = 1;
    }
    (*pv)[*n] = e;          /* assegnamento tra struct: copia campo per campo (anche l'array nome) */
    (*n)++;                 /* le parentesi servono: *n++ incrementerebbe il PUNTATORE */
    return rialloc;
}

/* I tre criteri. Ognuno risponde alla domanda: "a deve stare PRIMA di b?" (1 = si', 0 = no). */
int per_voto(const Esame *a, const Esame *b)
{
    if (a->voto != b->voto)
        return a->voto > b->voto;            /* voto piu' alto prima */
    return strcmp(a->nome, b->nome) < 0;     /* a parita' di voto: ordine alfabetico */
}

int per_nome(const Esame *a, const Esame *b)
{
    return strcmp(a->nome, b->nome) < 0;     /* strcmp < 0: a viene prima nel dizionario */
}

int per_crediti(const Esame *a, const Esame *b)
{
    if (a->crediti != b->crediti)
        return a->crediti > b->crediti;
    return strcmp(a->nome, b->nome) < 0;
}

/* Ordinamento per selezione (selection sort, cartella 05): a ogni passo i cerca
 * l'elemento che deve stare PRIMA di tutti gli altri rimasti e lo porta in posizione i.
 * La funzione non sa quale criterio usa: glielo passa chi la chiama (cartella 14). */
void ordina(Esame v[], int n, int (*precede)(const Esame *, const Esame *))
{
    int i, j, scelto;
    Esame tmp;

    for (i = 0; i < n - 1; i++) {
        scelto = i;
        for (j = i + 1; j < n; j++)
            if (precede(&v[j], &v[scelto]))   /* chiamata tramite il puntatore a funzione */
                scelto = j;
        if (scelto != i) {                     /* scambio di due struct intere */
            tmp = v[i];
            v[i] = v[scelto];
            v[scelto] = tmp;
        }
    }
}

/* Tre risultati "restituiti" tramite puntatori (cartella 08). Si assume n > 0. */
void medie(const Esame v[], int n, double *aritmetica, double *ponderata, int *cfu)
{
    int i, somma_voti = 0, somma_pesata = 0;

    *cfu = 0;
    for (i = 0; i < n; i++) {
        somma_voti += v[i].voto;
        somma_pesata += v[i].voto * v[i].crediti;
        *cfu += v[i].crediti;
    }
    /* cast PRIMA della divisione: altrimenti int / int tronca (cartella 02) */
    *aritmetica = (double) somma_voti / n;
    *ponderata = (double) somma_pesata / *cfu;
}

int main(void)
{
    char criterio[16];
    int (*precede)(const Esame *, const Esame *);
    Esame e, *v;
    int n = 0, cap = 1, r, riallocazioni = 0, i, cfu;
    double aritmetica, ponderata;

    if (scanf("%15s", criterio) != 1) {
        printf("manca il criterio\n");
        return 1;
    }
    if (strcmp(criterio, "voto") == 0)
        precede = per_voto;
    else if (strcmp(criterio, "nome") == 0)
        precede = per_nome;
    else if (strcmp(criterio, "crediti") == 0)
        precede = per_crediti;
    else {
        printf("criterio sconosciuto: %s\n", criterio);
        return 1;
    }

    v = (Esame *) malloc((size_t) cap * sizeof(Esame));
    if (v == NULL)
        return 1;

    while (scanf("%31s %d %d", e.nome, &e.voto, &e.crediti) == 3) {
        if (e.voto < 18 || e.voto > 30 || e.crediti <= 0) {
            printf("scartato: %s %d %d\n", e.nome, e.voto, e.crediti);
            continue;
        }
        r = aggiungi_esame(&v, &n, &cap, e);
        if (r < 0) {
            printf("memoria esaurita\n");
            break;
        }
        riallocazioni += r;
    }

    printf("letti %d esami (capacita' %d, riallocazioni %d)\n", n, cap, riallocazioni);
    ordina(v, n, precede);
    printf("ordine: %s\n", criterio);
    for (i = 0; i < n; i++)
        printf("%d) %s %d (%d CFU)\n", i + 1, v[i].nome, v[i].voto, v[i].crediti);

    if (n == 0) {
        printf("nessun esame: medie non calcolabili\n");
    } else {
        medie(v, n, &aritmetica, &ponderata, &cfu);
        printf("media aritmetica: %.2f\n", aritmetica);
        printf("media ponderata: %.2f\n", ponderata);
        printf("CFU totali: %d\n", cfu);
    }

    free(v);    /* un solo blocco: un solo free */
    return 0;
}
