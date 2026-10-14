/*
 * es05 — Vettore di studenti e strutture annidate  (Intermedio)
 *
 * Testo: Studente contiene un campo identita di tipo Persona (struttura
 * annidata, come nell'esempio del prof). Implementa:
 *  - migliore(classe, n): restituisce un PUNTATORE allo studente con la media
 *    piu' alta (a parita', il primo); n >= 1;
 *  - conta_sopra(classe, n, soglia): quanti studenti hanno media >= soglia.
 *
 * Input:  n, poi n righe "matricola nome cognome media", poi la soglia.
 *         Esempio: 2  1001 Luca Rossi 26.5  1002 Anna Verdi 29.5  27
 * Output: migliore: Anna Verdi (matricola 1002, media 29.50)
 *         indice del migliore: 1
 *         media >= 27.00: 1
 *
 * Come testarlo: make test T=10 E=es05
 */
#include <stdio.h>

#define MAX 50

typedef struct {
    char nome[20];
    char cognome[20];
} Persona;

typedef struct {
    long matricola;
    Persona identita;
    double media;
} Studente;

const Studente *migliore(const Studente classe[], int n)
{
    /* TODO: parti da &classe[0]; per ogni i da 1 a n-1, se classe[i].media
       e' STRETTAMENTE maggiore della media del migliore attuale, aggiorna. */
    (void)n;   /* cancella questa riga */
    return &classe[0];   /* provvisorio */
}

int conta_sopra(const Studente classe[], int n, double soglia)
{
    /* TODO */
    (void)classe; (void)n; (void)soglia;   /* cancella questa riga */
    return 0;
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
    printf("migliore: %s %s (matricola %ld, media %.2f)\n",
           b->identita.nome, b->identita.cognome, b->matricola, b->media);
    printf("indice del migliore: %d\n", (int)(b - classe));
    printf("media >= %.2f: %d\n", soglia, conta_sopra(classe, n, soglia));
    return 0;
}
