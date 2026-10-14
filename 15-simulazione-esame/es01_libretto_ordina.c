/*
 * es01 — Libretto universitario: record da stdin, realloc e ordinamento  (Tipo esame)
 *
 * Prima riga: il criterio di ordinamento ("voto", "nome" oppure "crediti").
 * Poi, fino alla fine dell'input, un esame per riga:  nome voto crediti
 * (esempio: "Analisi 28 9"). Gli esami con voto fuori da 18..30 oppure
 * con crediti <= 0 vengono scartati dal main (gia' scritto).
 *
 * Completa:
 *   - aggiungi_esame: aggiunge in fondo al vettore dinamico; se e' pieno
 *     RADDOPPIA la capacita' con realloc (in modo sicuro). Ritorna 1 se ha
 *     fatto la realloc, 0 se no, -1 se la realloc fallisce.
 *   - per_voto, per_nome, per_crediti: i tre criteri. Rispondono 1 se a
 *     deve stare PRIMA di b. voto: voto piu' alto prima; crediti: piu'
 *     crediti prima; a parita' (e per "nome"): ordine alfabetico.
 *   - ordina: ordinamento per selezione che usa il criterio ricevuto.
 *   - medie: media aritmetica dei voti, media ponderata sui crediti
 *     (somma voto*crediti / somma crediti) e totale crediti.
 *
 * Esempio:  input  voto / Analisi 28 9 / Programmazione 30 12 / Fisica 24 6 / Inglese 30 3
 *           output (vedi README)  ... media ponderata: 28.20
 *
 * Come testarlo: make test T=15 E=es01
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

int aggiungi_esame(Esame **pv, int *n, int *cap, Esame e)
{
    /* TODO:
       1. se *n == *cap: realloc di *pv a (*cap * 2) esami usando un puntatore
          TEMPORANEO; se e' NULL ritorna -1; altrimenti aggiorna *pv e *cap
       2. copia e in (*pv)[*n] e incrementa *n (attento alle parentesi!)
       3. ritorna 1 se hai fatto la realloc, altrimenti 0 */
    (void)pv; (void)n; (void)cap; (void)e;
    return 0;
}

int per_voto(const Esame *a, const Esame *b)
{
    /* TODO: voto piu' alto prima; a parita' di voto, strcmp sui nomi */
    (void)a; (void)b;
    return 0;
}

int per_nome(const Esame *a, const Esame *b)
{
    /* TODO */
    (void)a; (void)b;
    return 0;
}

int per_crediti(const Esame *a, const Esame *b)
{
    /* TODO: piu' crediti prima; a parita', ordine alfabetico */
    (void)a; (void)b;
    return 0;
}

void ordina(Esame v[], int n, int (*precede)(const Esame *, const Esame *))
{
    /* TODO: selection sort. Per ogni i, cerca tra i..n-1 l'elemento "scelto"
       tale che precede(&v[j], &v[scelto]) e scambialo con v[i]. */
    (void)v; (void)n; (void)precede;
}

void medie(const Esame v[], int n, double *aritmetica, double *ponderata, int *cfu)
{
    /* TODO: si assume n > 0. Occhio alla divisione tra interi. */
    (void)v; (void)n;
    *aritmetica = 0.0;
    *ponderata = 0.0;
    *cfu = 0;
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

    free(v);
    return 0;
}
