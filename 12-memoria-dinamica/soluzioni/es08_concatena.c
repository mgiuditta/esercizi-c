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
    int i;
    if (parole == NULL)
        return;
    for (i = 0; i < n; i++)
        free(parole[i]);    /* free(NULL) e' innocua: va bene anche su righe mai allocate */
    free(parole);
}

char **leggi_parole(int n)
{
    char buf[31];           /* buffer d'appoggio sullo stack: 30 caratteri + '\0' */
    char **parole;
    int i;
    /* calloc(0, ...) puo' restituire NULL anche se va tutto bene:
       chiediamo almeno 1 casella, cosi' NULL vuol dire solo "errore" */
    int caselle = (n > 0) ? n : 1;

    parole = (char **) calloc(caselle, sizeof(char *));   /* caselle a NULL grazie a calloc */
    if (parole == NULL)
        return NULL;
    for (i = 0; i < n; i++) {
        if (scanf("%30s", buf) != 1) {
            libera_parole(parole, n);
            return NULL;
        }
        parole[i] = (char *) malloc(strlen(buf) + 1);   /* +1 per il '\0' */
        if (parole[i] == NULL) {
            libera_parole(parole, n);
            return NULL;
        }
        strcpy(parole[i], buf);   /* sicura: il blocco e' grande esattamente quanto serve */
    }
    return parole;
}

char *concatena(char **parole, int n, char sep)
{
    size_t tot = 0;
    char *ris, *dove;
    int i;

    for (i = 0; i < n; i++)
        tot += strlen(parole[i]);
    if (n > 1)
        tot += n - 1;       /* un separatore TRA due parole: n - 1 separatori */

    ris = (char *) malloc(tot + 1);   /* +1 per il terminatore */
    if (ris == NULL)
        return NULL;

    dove = ris;             /* secondo puntatore che avanza; ris resta sull'inizio per la free */
    for (i = 0; i < n; i++) {
        size_t len = strlen(parole[i]);
        memcpy(dove, parole[i], len);
        dove += len;
        if (i < n - 1)
            *dove++ = sep;  /* scrive sep e avanza di un char */
    }
    *dove = '\0';
    return ris;
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
