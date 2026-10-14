/*
 * Esercizio 08 — Tipo esame: parole nello heap e concatenazione in nuova memoria  (Tipo esame)
 *
 * Completa:
 *   - leggi_parole(n): crea un vettore DINAMICO di n puntatori a char
 *     (char **) e, per ogni parola letta con scanf("%30s", buf), alloca un
 *     blocco della misura ESATTA e ci copia la parola. Ritorna il vettore,
 *     oppure NULL se qualcosa fallisce (liberando tutto quello che aveva preso).
 *   - concatena(parole, n, sep): crea una NUOVA stringa con tutte le parole
 *     separate dal carattere sep, allocando esattamente i byte necessari.
 *     Con n == 0 restituisce una stringa vuota (comunque allocata).
 *   - libera_parole(parole, n): libera ogni parola e poi il vettore.
 *
 * Input: n (0..100), poi n parole (max 30 caratteri), poi il separatore
 *        (un carattere non-spazio).
 *
 * Come testarlo: make test T=12 E=es08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void libera_parole(char **parole, int n)
{
    /* TODO: se parole non e' NULL, libera ogni parola e poi il vettore */
    (void)parole; (void)n;
}

char **leggi_parole(int n)
{
    /* TODO:
       1. calloc di (almeno 1) puntatori a char: sizeof(char *)
       2. per ogni parola: scanf("%30s", buf) in un buffer char buf[31],
          malloc(strlen(buf) + 1), strcpy
       3. se qualcosa fallisce: libera tutto e ritorna NULL */
    (void)n;
    return NULL;
}

char *concatena(char **parole, int n, char sep)
{
    /* TODO:
       1. calcola i byte: somma delle lunghezze + (n - 1) separatori + 1
       2. malloc, controllo NULL
       3. copia le parole e i separatori, chiudi con '\0', ritorna la stringa */
    (void)parole; (void)n; (void)sep;
    return NULL;
}

int main(void)
{
    int n, i;
    char sep;
    char **parole;
    char *frase;

    if (scanf("%d", &n) != 1 || n < 0 || n > 100) {
        printf("numero non valido\n");
        return 1;
    }
    parole = leggi_parole(n);
    if (parole == NULL) {
        printf("errore in lettura o allocazione\n");
        return 1;
    }
    if (scanf(" %c", &sep) != 1) {   /* lo spazio prima di %c salta gli a capo */
        libera_parole(parole, n);
        return 1;
    }

    frase = concatena(parole, n, sep);
    if (frase == NULL) {
        libera_parole(parole, n);
        printf("errore di allocazione\n");
        return 1;
    }
    printf("parole:");
    for (i = 0; i < n; i++)
        printf(" [%s]", parole[i]);
    printf("\nrisultato: [%s]\n", frase);
    printf("byte allocati per il risultato: %d\n", (int)strlen(frase) + 1);

    free(frase);
    libera_parole(parole, n);
    return 0;
}
