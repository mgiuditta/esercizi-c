/*
 * es05 — Vettore di studenti e strutture annidate  (Intermedio)  — SOLUZIONE
 *
 * Testo: Studente contiene un campo identita di tipo Persona (struttura
 * annidata, come nell'esempio del prof). Implementa:
 *  - migliore(classe, n): restituisce un PUNTATORE allo studente con la media
 *    piu' alta (a parita', il primo); n >= 1;
 *  - conta_sopra(classe, n, soglia): quanti studenti hanno media >= soglia.
 *
 * Come testarlo: make sol T=10 E=es05
 */
#include <stdio.h>

#define MAX 50

typedef struct {
    char nome[20];
    char cognome[20];
} Persona;

typedef struct {
    long matricola;
    Persona identita;   /* una struttura DENTRO un'altra struttura */
    double media;
} Studente;

/* classe[] in un parametro e' un puntatore al primo Studente (come per i
 * vettori di int): non viene copiata tutta la classe. */
const Studente *migliore(const Studente classe[], int n)
{
    const Studente *best = &classe[0];   /* candidato: il primo */
    int i;

    for (i = 1; i < n; i++)
        if (classe[i].media > best->media)  /* classe[i] e' una struct: punto;
                                               best e' un puntatore: freccia */
            best = &classe[i];
    return best;
}

int conta_sopra(const Studente classe[], int n, double soglia)
{
    int i, c = 0;
    for (i = 0; i < n; i++)
        if (classe[i].media >= soglia)
            c++;
    return c;
}

int main(void)
{
    Studente classe[MAX];
    const Studente *b;
    double soglia;
    int n, i;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
        return 1;
    for (i = 0; i < n; i++)
        if (scanf("%ld %19s %19s %lf", &classe[i].matricola,
                  classe[i].identita.nome, classe[i].identita.cognome,
                  &classe[i].media) != 4)
            return 1;
    if (scanf("%lf", &soglia) != 1)
        return 1;

    if (n == 0) {
        printf("classe vuota\n");
        return 0;
    }

    b = migliore(classe, n);
    /* b->identita.nome: freccia per entrare nella struct puntata,
       poi punto per entrare nella struct annidata */
    printf("migliore: %s %s (matricola %ld, media %.2f)\n",
           b->identita.nome, b->identita.cognome, b->matricola, b->media);
    printf("indice del migliore: %d\n", (int)(b - classe));
    printf("media >= %.2f: %d\n", soglia, conta_sopra(classe, n, soglia));
    return 0;
}
