/*
 * es02 — Studente con media  (Base)  — SOLUZIONE
 *
 * Testo: la struttura Studente raggruppa cognome, matricola e fino a 5 voti
 * (con il numero di voti effettivi nvoti). Implementa media(s), che
 * restituisce la media dei voti come double (0.0 se nvoti == 0).
 *
 * Come testarlo: make sol T=10 E=es02
 */
#include <stdio.h>

#define MAX_VOTI 5

typedef struct {
    char cognome[20];      /* vettore DENTRO la struttura */
    long matricola;
    int voti[MAX_VOTI];
    int nvoti;             /* quanti elementi di voti[] sono significativi */
} Studente;

double media(Studente s)
{
    int i;
    int somma = 0;

    if (s.nvoti == 0)      /* evito la divisione per zero */
        return 0.0;
    for (i = 0; i < s.nvoti; i++)
        somma += s.voti[i];          /* campo vettore: s.voti[i] = (s.voti)[i] */
    /* (double) PRIMA della divisione: altrimenti 82 / 3 farebbe 27 (divisione intera) */
    return (double)somma / s.nvoti;
}

int main(void)
{
    Studente s;
    int i;

    if (scanf("%19s %ld %d", s.cognome, &s.matricola, &s.nvoti) != 3)
        return 1;                    /* s.cognome e' un vettore: niente & */
    if (s.nvoti < 0 || s.nvoti > MAX_VOTI)
        return 1;
    for (i = 0; i < s.nvoti; i++)
        if (scanf("%d", &s.voti[i]) != 1)
            return 1;

    if (s.nvoti == 0)
        printf("%s (matricola %ld): nessun voto\n", s.cognome, s.matricola);
    else
        printf("%s (matricola %ld): media %.2f\n", s.cognome, s.matricola, media(s));
    return 0;
}
