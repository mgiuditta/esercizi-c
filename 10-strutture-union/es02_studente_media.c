/*
 * es02 — Studente con media  (Base)
 *
 * Testo: la struttura Studente raggruppa cognome, matricola e fino a 5 voti
 * (con il numero di voti effettivi nvoti). Implementa media(s), che
 * restituisce la media dei voti come double (0.0 se nvoti == 0).
 *
 * Input:  cognome matricola nvoti, poi i voti.   Esempio: Rossi 12345 3  27 30 25
 * Output: Rossi (matricola 12345): media 27.33
 *
 * Come testarlo: make test T=10 E=es02
 */
#include <stdio.h>

#define MAX_VOTI 5

typedef struct {
    char cognome[20];
    long matricola;
    int voti[MAX_VOTI];
    int nvoti;
} Studente;

double media(Studente s)
{
    /* TODO: se s.nvoti e' 0 restituisci 0.0; altrimenti somma s.voti[i]
       per i da 0 a s.nvoti - 1 e dividi in double. */
    (void)s;   /* cancella questa riga */
    return 0.0;
}

int main(void)
{
    Studente s;
    int i;

    if (scanf("%19s %ld %d", s.cognome, &s.matricola, &s.nvoti) != 3)
        return 1;
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
